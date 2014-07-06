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


#ifndef INCLUDED_TEST1_PULSE1_H
#define INCLUDED_TEST1_PULSE1_H

#include <test1/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace test1 {

    /*!
     * \brief <+description of block+>
     * \ingroup test1
     *
     */
    class TEST1_API pulse1 : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<pulse1> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of test1::pulse1.
       *
       * To avoid accidental use of raw pointers, test1::pulse1's
       * constructor is in a private implementation
       * class. test1::pulse1::make is the public interface for
       * creating new instances.
       */
      static sptr make(float samp_rate);
    };

  } // namespace test1
} // namespace gr

#endif /* INCLUDED_TEST1_PULSE1_H */

