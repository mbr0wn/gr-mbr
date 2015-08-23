/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "udp_tagged_sink_impl.h"

namespace gr {
  namespace mbr {

    udp_tagged_sink::sptr
    udp_tagged_sink::make(int itemsize, const std::string &host, const int port, const int mtu, const std::string &tsb_key)
    {
      return gnuradio::get_initial_sptr
        (new udp_tagged_sink_impl(itemsize, host, port, mtu, tsb_key));
    }

    /*
     * The private constructor
     */
    udp_tagged_sink_impl::udp_tagged_sink_impl(
            const int itemsize,
            const std::string &host,
            const int port,
            const int mtu,
            const std::string &tsb_key
    ) : gr::tagged_stream_block("udp_tagged_sink",
              gr::io_signature::make(1, 1, itemsize),
              gr::io_signature::make(0, 0, 0), tsb_key),
        d_itemsize(itemsize),
        d_mtu(mtu),
        d_connected(false)
    {
      connect(host, port);
    }

    udp_tagged_sink_impl::~udp_tagged_sink_impl()
    {
      if (d_connected) {
        disconnect();
      }
    }

    void
    udp_tagged_sink_impl::connect(const std::string &host, int port)
    {
      if(d_connected)
        disconnect();

      std::string s_port = (boost::format("%d")%port).str();
      if(host.size() > 0) {
        boost::asio::ip::udp::resolver resolver(d_io_service);
        boost::asio::ip::udp::resolver::query query(host, s_port,
                                                    boost::asio::ip::resolver_query_base::passive);
        d_endpoint = *resolver.resolve(query);

        d_socket = new boost::asio::ip::udp::socket(d_io_service);
        d_socket->open(d_endpoint.protocol());

        boost::asio::socket_base::reuse_address roption(true);
        d_socket->set_option(roption);

        d_connected = true;
      }
    }

    void
    udp_tagged_sink_impl::disconnect()
    {
      if(!d_connected)
        return;

      gr::thread::scoped_lock guard(d_mutex);  // protect d_socket from work()

      d_socket->close();
      delete d_socket;

      d_connected = false;
    }

    int
    udp_tagged_sink_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      const ssize_t bytes_to_send = ninput_items[0] * d_itemsize;

      gr::thread::scoped_lock guard(d_mutex);  // protect d_socket
      if (!d_connected || bytes_to_send > d_mtu) {
        GR_LOG_INFO(d_debug_logger, boost::format("Dropped packet of length %d") % bytes_to_send);
        return ninput_items[0];
      }

      try {
        const ssize_t r = d_socket->send_to(
            boost::asio::buffer((void*)(in), ssize_t(bytes_to_send)),
            d_endpoint
        );
        if (r != bytes_to_send) {
            GR_LOG_WARN(d_logger, boost::format("bytes_to_send: %d  actually sent: %d") % bytes_to_send % r);
        }
      }
      catch (const std::exception& e) {
        GR_LOG_ERROR(d_logger, boost::format("send error: %s") % e.what());
        return WORK_DONE;
      }

      return ninput_items[0];
    }

  } /* namespace mbr */
} /* namespace gr */

