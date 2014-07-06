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
#include "freq_counter1_impl.h"

namespace gr {
  namespace test1 {
  
    #define CYCLE 10     // produce one output calculation after this number of input cycle

    freq_counter1::sptr
    freq_counter1::make(float samp_rate, float threshold, float estimated_freq)
    {
      return gnuradio::get_initial_sptr
        (new freq_counter1_impl(samp_rate, threshold, estimated_freq));
    }


    // constructor
    freq_counter1_impl::freq_counter1_impl(float samp_rate, float threshold, float estimated_freq)
      : gr::block("freq_counter1",
              gr::io_signature::make( 1, 1, sizeof(float)),
              gr::io_signature::make( 1, 1, sizeof(float)) ),
          d_samp_rate( samp_rate ),
          d_estimated_freq( estimated_freq ),
          d_threshold( threshold ),
          d_previous_sign( true ),          
          d_nitem(0),
          d_cycle(0)
    { 
        if ( threshold <= 0.0 )
            throw std::runtime_error("threshold must be non-negative!");
    }


    // new_cycle
    bool
    freq_counter1_impl::new_cycle( float signal )
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


    // destructor
    freq_counter1_impl::~freq_counter1_impl()
    { }


    // forecast
    void
    freq_counter1_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] =  d_samp_rate / d_estimated_freq * noutput_items;
    }


    // general_work
    int
    freq_counter1_impl::general_work( int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in  =  (const float *) input_items[0];
        float      *out  =  (float *)      output_items[0];

        int output_counter = 0;

        for (int i=0; i < ninput_items[0]; i++)
        {
            if ( new_cycle(in[i]) )  
            {
                d_cycle++;                                
                if ( d_cycle >= CYCLE )
                {
                    out[ output_counter ]  = d_cycle * d_samp_rate / ( d_nitem + 1);
                    output_counter++;
                    d_cycle = 0;
                    d_nitem = 0;
                    continue;
                }                
            } 
            d_nitem++;
        }
        
        consume( 0, ninput_items[0] );
        return output_counter;
    }

  } /* namespace test1 */
} /* namespace gr */

