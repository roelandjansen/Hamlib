/* -*-C++-*-
*******************************************************************************
*
* File:         microtune_eval_board.h
* Description:  
*
*******************************************************************************
*/

/*
 * Copyright 2001 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _MICROTUNE_EVAL_BOARD_H_
#define _MICROTUNE_EVAL_BOARD_H_

#include "microtune_4937.h"
#include "serial.h"

class i2cio;
class i2c;

/*!
 * \brief concrete class for controlling microtune 4937 eval board attached to parallel port
 */
class microtune_eval_board : public microtune_4937 {
public:
  microtune_eval_board (port_t *port);
  ~microtune_eval_board ();

  //! is the eval board present?
  bool board_present_p ();

  /*!
   * \brief set RF and IF AGC control voltages ([0, 5] volts)
   */
  void set_RF_AGC_voltage (float volts);
  void set_IF_AGC_voltage (float volts);

  /*!
   * \brief set RF and IF AGC levels together (scale [0, 1000])
   *
   * This provides a simple linear interface for adjusting both
   * the RF and IF gain in consort.  This is the easy to use interface.
   * 0 corresponds to minimum gain. 1000 corresponds to maximum gain.
   */
  void set_AGC (float value_0_1000);


private:
  //! \returns true iff successful
  virtual bool i2c_write (int addr, const unsigned char *buf, int nbytes);

  //! \returns number of bytes read or -1 if error
  virtual int i2c_read (int addr, unsigned char *buf, int max_bytes);

  void write_dac (int which, int value);
  void write_both_dacs (int val0, int val1);
  
  port_t	*m_ppio;
  i2cio	*m_i2cio;
  i2c	*m_i2c;
};


#endif /* _MICROTUNE_EVAL_BOARD_H_ */