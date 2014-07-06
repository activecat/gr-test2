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

#ifndef INCLUDED_TEST1_FREQ_COUNTER2_IMPL_H
#define INCLUDED_TEST1_FREQ_COUNTER2_IMPL_H

#include <test1/freq_counter2.h>

namespace gr {
  namespace test1 {

    class freq_counter2_impl : public freq_counter2
    {
     private:
        float d_samp_rate;
        float d_threshold;
        bool  d_previous_sign;
        
        float d_frequency;   // calculated frequency
        int   d_nitem;       // the number of items
        int   d_cycle;       // count the number of cycles
        
        bool  new_cycle( float );   

     public:
      freq_counter2_impl(float samp_rate, float threshold);
      ~freq_counter2_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace test1
} // namespace gr

#endif /* INCLUDED_TEST1_FREQ_COUNTER2_IMPL_H */

