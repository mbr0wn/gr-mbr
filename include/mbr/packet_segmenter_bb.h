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


#ifndef INCLUDED_MBR_PACKET_SEGMENTER_BB_H
#define INCLUDED_MBR_PACKET_SEGMENTER_BB_H

#include <mbr/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace mbr {

    /*!
     * \brief <+description of block+>
     * \ingroup mbr
     *
     */
    class MBR_API packet_segmenter_bb : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<packet_segmenter_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of mbr::packet_segmenter_bb.
       *
       * To avoid accidental use of raw pointers, mbr::packet_segmenter_bb's
       * constructor is in a private implementation
       * class. mbr::packet_segmenter_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make(int packet_size, int n_segments);
    };

  } // namespace mbr
} // namespace gr

#endif /* INCLUDED_MBR_PACKET_SEGMENTER_BB_H */

