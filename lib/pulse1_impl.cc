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
#include "pulse1_impl.h"

namespace gr {
  namespace test1 {

    pulse1::sptr
    pulse1::make(float samp_rate)
    {
      return gnuradio::get_initial_sptr
        (new pulse1_impl(samp_rate));
    }

    /*
     * The private constructor
     */
    pulse1_impl::pulse1_impl(float samp_rate)
      : gr::sync_block("pulse1",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make( 1, 1, sizeof(float))),
          d_multiple( int(samp_rate/1000) )
    { 
        if ( int(samp_rate) % 1000 != 0 )
            throw std::runtime_error("Sample Rate of the \"Pulse1\" block must be multiple of 1000kHz.");
        set_output_multiple( int(samp_rate/200) );
    }

    /*
     * Our virtual destructor.
     */
    pulse1_impl::~pulse1_impl()
    { }

    int
    pulse1_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        float *out = (float *) output_items[0];
        //std::cout << "noutput_items=" << noutput_items << std::endl;
        
        int i = 0;
        while ( i < noutput_items )
        {
            for (int j=0; j < d_multiple * 4; j++)
            {
                out[i] = 0.0;
                i++;
            }
            
            for (int j=0; j < d_multiple; j++)
            {
                out[i] = 1.0;
                i++;            
            }
        }
        
        return noutput_items;
    }

  } /* namespace test1 */
} /* namespace gr */

