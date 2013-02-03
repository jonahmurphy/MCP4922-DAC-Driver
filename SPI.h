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
*     @file SPI_drv.h
*    @brief SPI driver for NXP P89V51RD2 -8051
* @compiler Keil C51
*  @version 0.1
*   @author Jonah Murphy
*     @date 26-05-10
*     @todo Testing of slave mode operations;
*            Implement busy flag/s and busy flag testing;
*            Add routine/s to implement SPI interrupt
*
**********************************************************************************************/

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

/** Pin Definitions */
sbit SS = P1^4;                  /** Slave Select  (When the P89V51RD2 is operating in slave mode)*/

#define SPI_MASTER 1
#define SPI_SLAVE 0
#define SPI_DORD_MSB_FIRST 0
#define SPI_DORD_LSB_FIRST 1
#define SPI_ACTIVE_LOW 1
#define SPI_ACTIVE_HIGH 0
#define SPI_L_EDG_TRIG 0
#define SPI_T_EDG_TRIG 1
#define SPI_CLK_DIV_4 0
#define SPI_CLK_DIV_16 1
#define SPI_CLK_DIV_64 2
#define SPI_CLK_DIV_128 3

/**
    @brief     This function used to initialize the SPI block
    @param  mode Master/slave select. 1 = master mode, 0 = slave mode.
    @param    data_order Data transmission order. 0 = MSB first; 1 = LSB first in data transmission.
    @param  clk_polarity Clock polarity. 1 = SCK is high when idle(activeLOW),0=SCK is low when idle (active HIGH).
    @param  clk_phase Clock Phase control bit. 1 = shift triggered on the trailing edge of the clock; 0 = shift triggered on the leading edge of the clock.
    @param  clk_divider Clock rate divder.  [0: SCK = fosc/4] [1: SCK = fosc/16]  [2: SCK = fosc/64] [3: SCK = fosc/128]
*/
void SPI_init(bit mode, bit data_order, bit clk_polarity, bit clk_phase, unsigned char clk_divider);

/**
    @brief This Function is used to transmit and revcieve a byte in Master mode
    @param SPI_TX_out Data to be transmitted
    @retval 0 Indicates a collision has occured
    @retval SPI_RX_data recived data if using full duplex SPI
*/
unsigned char SPI_master_byte( unsigned char SPI_TX_byte);

/**
    @brief This Function is used to recive and transmit a byte in Slave mode
    @param SPI_TX_byte to be transmitted
    @retval 0 Indicates a collision has occured
    @retval SPI_RX_data recived data if using full duplex SPI
*/
unsigned char SPI_slave_byte(unsigned char SPI_TX_byte);

#endif