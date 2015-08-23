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


#ifndef INCLUDED_MBR_UDP_TAGGED_SINK_H
#define INCLUDED_MBR_UDP_TAGGED_SINK_H

#include <mbr/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace mbr {

    /*!
     * \brief <+description of block+>
     * \ingroup mbr
     *
     */
    class MBR_API udp_tagged_sink : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<udp_tagged_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of mbr::udp_tagged_sink.
       *
       * To avoid accidental use of raw pointers, mbr::udp_tagged_sink's
       * constructor is in a private implementation
       * class. mbr::udp_tagged_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(
              const int itemsize,
              const std::string &host,
              const int port,
              const int mtu,
              const std::string &tsb_key
      );
    };

  } // namespace mbr
} // namespace gr

#endif /* INCLUDED_MBR_UDP_TAGGED_SINK_H */

