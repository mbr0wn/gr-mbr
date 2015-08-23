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

#ifndef INCLUDED_MBR_UDP_TAGGED_SINK_IMPL_H
#define INCLUDED_MBR_UDP_TAGGED_SINK_IMPL_H

#include <mbr/udp_tagged_sink.h>
#include <boost/asio.hpp>

namespace gr {
  namespace mbr {

    class udp_tagged_sink_impl : public udp_tagged_sink
    {
     private:
      const int d_itemsize;
      const int d_mtu;
      bool      d_connected;             // are we connected?

      gr::thread::mutex  d_mutex;     // protects d_socket and d_connected

      boost::asio::ip::udp::socket *d_socket;          // handle to socket
      boost::asio::ip::udp::endpoint d_endpoint;
      boost::asio::io_service d_io_service;

     public:
      udp_tagged_sink_impl(
              const int itemsize,
              const std::string &host,
              const int port,
              const int mtu,
              const std::string &tsb_key
      );
      ~udp_tagged_sink_impl();

      int work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items
      );

      void connect(const std::string &host, int port);
      void disconnect();
    };

  } // namespace mbr
} // namespace gr

#endif /* INCLUDED_MBR_UDP_TAGGED_SINK_IMPL_H */

