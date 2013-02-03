 /*
 * Copyright (C) 2012  Jonah Murphy
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version 2
 *	of the License, or (at your option) any later version.
 *	
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/*****************************************************************************************//**
*
*     @file MCP4922_DAC_driver.h
*    @brief Driver for MCP4922 for NXP P89V51RD2 -8051
* @compiler Keil C51
*  @version 0.1
*   @author Jonah Murphy
*     @date 26-05-10
*
**********************************************************************************************/

#ifndef MCP4922_DAC_DRIVER_H
#define MCP4922_DAC_DRIVER_H

#include "t89c51rd2.h"
#include "SPI.h"

/**Chip Select pin definition*/
sbit CS = P2^1;

/**Defines*/
#define MCP4992_BUF
#define MCP4992_UNBUF
#define MCP4992_GAIN_X1
#define MCP4992_GAIN_X2


/**
    @brief     This function initializes SPI for the DAC
*/
void MCP4922_init();

/**
    @brief  This function is used to write a 16bit data word  to DAC B -12 data bit plus 4 configuration bits
    @param  dac_data A 12bit word
    @param  ip_buf_unbuf_select Input Buffered/unbuffered  select bit. Buffered = 1; Unbuffered = 0
    @param  gain_select Output Gain Selection bit. 1 = 1x (VOUT = VREF * D/4096).  0 =2x (VOUT = 2 * VREF * D/4096)
*/
void MCP4922_DAC_B_TX_word(unsigned short int dac_data, bit ip_buf_unbuf_select, bit gain_select);

/**
    @brief  This function is used to write a 16bit data word  to DAC A -12 data bit plus 4 configuration bits
    @param  dac_data A 12bit word
    @param  ip_buf_unbuf_select Input Buffered/unbuffered  select bit. Buffered = 1; Unbuffered = 0
    @param  gain_select Output Gain Selection bit. 1 = 1x (VOUT = VREF * D/4096).  0 =2x (VOUT = 2 * VREF * D/4096)
*/
void MCP4922_DAC_A_TX_word(unsigned short int dac_data, bit ip_buf_unbuf_select, bit gain_select);


/**
    @brief  This function shutsdown DAC channel A -saves power
*/
void MCP4922_SHDN_DAC_A();

/**
    @brief  This function shutsdown DAC channel B -saves power
*/
void MCP4922_SHDN_DAC_B();

#endif