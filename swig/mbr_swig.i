/* -*- c++ -*- */

#define MBR_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "mbr_swig_doc.i"

%{
#include "mbr/packet_segmenter_bb.h"
#include "mbr/udp_tagged_sink.h"
%}

%include "mbr/packet_segmenter_bb.h"
GR_SWIG_BLOCK_MAGIC2(mbr, packet_segmenter_bb);
%include "mbr/udp_tagged_sink.h"
GR_SWIG_BLOCK_MAGIC2(mbr, udp_tagged_sink);
