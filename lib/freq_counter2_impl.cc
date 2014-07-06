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
#include "freq_counter2_impl.h"

namespace gr {
  namespace test1 {

    #define CYCLE 10
    
    freq_counter2::sptr
    freq_counter2::make(float samp_rate, float threshold)
    {
      return gnuradio::get_initial_sptr
        (new freq_counter2_impl(samp_rate, threshold));
    }


    // constructor
    freq_counter2_impl::freq_counter2_impl(float samp_rate, float threshold)
      : gr::sync_block("freq_counter2",
              gr::io_signature::make( 1, 1, sizeof(float)),
              gr::io_signature::make( 1, 1, sizeof(float))),
          d_samp_rate( samp_rate ),
          d_threshold( threshold ),
          d_previous_sign( true ),
          
          d_frequency(0.0),
          d_nitem(0),
          d_cycle(0)              
    { 
        if ( threshold <= 0.0 )
            throw std::runtime_error("threshold must be non-negative!");
    }

    
    // destructor
    freq_counter2_impl::~freq_counter2_impl()
    { }


    // new_cycle
    bool
    freq_counter2_impl::new_cycle( float signal )
    {
        if ( std::abs(signal) < d_threshold )
            return false;
        
        bool current_sign = ( signal > 0.0 );
        if ( current_sign && ! d_previous_sign )
        {
            d_previous_sign = true;
            return true;
        }        
        d_previous_sign = current_sign;
        return false;
    }


    // work
    int
    freq_counter2_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in  =  (const float *) input_items[0];
        float      *out  =  (float *)      output_items[0];

        for (int i=0; i < noutput_items; i++)
        {
            if ( new_cycle(in[i]) )  {

                d_cycle++;
                                
                if ( d_cycle >= CYCLE )
                {
                    d_frequency = CYCLE * d_samp_rate / ( d_nitem + 1);
                    d_cycle = 0;
                    d_nitem = 0;
                    out[i] = d_frequency;
                    continue;
                }                
            } 

            d_nitem++;
            
            out[i] = d_frequency;
        }
        
        return noutput_items;
    }

  } /* namespace test1 */
} /* namespace gr */

