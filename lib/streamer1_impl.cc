/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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
#include "streamer1_impl.h"

namespace gr {
  namespace test1 {

    streamer1::sptr
    streamer1::make()
    {
      return gnuradio::get_initial_sptr
        (new streamer1_impl());
    }


    // constructor
    streamer1_impl::streamer1_impl()
      : gr::block("streamer1",
              gr::io_signature::make( 2, 2, sizeof(float)),
              gr::io_signature::make( 2, 2, sizeof(float)))
    { }


    // destructor
    streamer1_impl::~streamer1_impl()
    { }


    // forecast
    void
    streamer1_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
        ninput_items_required[1] = 0; 
    }


    // general_work
    int
    streamer1_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float  *in0  =  (const float *)  input_items[0];
        const float  *in1  =  (const float *)  input_items[1];
        float       *out0  =  (float *)       output_items[0];
        float       *out1  =  (float *)       output_items[1];
        
        if ( ninput_items[0] < noutput_items )
          throw std::runtime_error("streamer1::general_work():  ninput_items[0] < noutput_items");

        int n1 = std::min( ninput_items[1], noutput_items );    // to ensure port 1 won't consume more than noutput_items
        
        for (int i=0; i < noutput_items; i++)
          out0[i] = in0[i];
        
        for (int i=0; i < n1; i++)
          out1[i] = in1[i];
          
        for (int i=n1; i < noutput_items; i++)
          out1[i] = 0.0;
        
        consume( 0, noutput_items );
        consume( 1, n1 );

        return noutput_items;
    }

  } /* namespace test1 */
} /* namespace gr */

