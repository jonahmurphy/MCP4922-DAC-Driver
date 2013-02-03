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
*     @file SPI.c
*    @brief SPI driver for NXP P89V51RD2 -8051
* @compiler Keil C51
*  @version 0.1
*   @author Jonah Murphy
*     @date 26-05-10
*     @note This driver should be easily adaptable for other 8051 MCU's
*     @todo Testing of slave mode operations;
*            Implement busy flag/s and busy flag testing;
*            Add routine/s to implement SPI interrupt
*
**********************************************************************************************/

#include "t89c51rd2.h"
#include "SPI_driver.h"

void SPI_init(bit mode, bit data_order, bit clk_polarity, bit clk_phase, unsigned char clk_divider)
{
    SPCTL |= SP_MSK_SPE;             /**Enable SPI */

    /**Set mode Master/Slave*/
    if(mode)
        SPCTL |= SP_MSK_MSTR;
    else
        SPCTL &= ~SP_MSK_MSTR;

    /**Set clock polarity*/
    if(data_order)
        SPCTL |= SP_MSK_DORD;
    else
        SPCTL &= ~SP_MSK_DORD;

    /**Set clock phase*/
    if(clk_phase)
        SPCTL |= SP_MSK_CPHA;
    else
        SPCTL &= ~SP_MSK_CPHA;

    /**Set data order*/
    if(clk_polarity)
        SPCTL |= SP_MSK_CPOL;
    else
        SPCTL &= ~SP_MSK_CPOL;

    /**Set SPI clock rate*/
	SPCTL &= 0xFC;
    switch(clk_divider)
    {
		case 0:                                        /** SCK = fosc/4   */
            break;
        case 1:                                        /** SCK = fosc/16  */
            SPCTL |= 0x01;
            break;
        case 2:                                        /** SCK = fosc/64  */
            SPCTL |= 0x10;
            break;
        case 3:                                        /** SCK = fosc/128 */
            SPCTL |= 0x11;
            break;
        default:                                       /** SCK = fosc/128 */
            SPCTL |= 0x11;
            break;
    }
}

unsigned char SPI_master_byte( unsigned char SPI_TX_byte)
{
    unsigned char SPI_RX_data;

    SPDAT = SPI_TX_byte;
    while(!(SPCFG & SP_MSK_SPIF)) ;          /**Wait for TX to complete*/
	
    SPCFG &= ~SP_MSK_SPIF;                   /**Clear the SPIF flag*/

    SPI_RX_data = SPDAT;                     /**Get recived byte if using full duplex SPI*/

    if(SPCFG & SP_MSK_SPWCOL)                /**Check the write collison flag*/
    {
        SPCTL |= ~SP_MSK_SPWCOL;
        return 0;                            /**return 0 to indicate collision occured*/
    }
    return SPI_RX_data;
}

unsigned char SPI_slave_byte(unsigned char SPI_TX_byte)
{
    unsigned SPI_RX_data = SPDAT;
	
    while(!(SPCFG & SP_MSK_SPIF)) ;         /**Wait for RX to complete*/
	
    SPCFG &= ~SP_MSK_SPIF;                  /**Clear the SPIF flag*/
    SPDAT = SPI_TX_byte;

    if(SPCFG & SP_MSK_SPWCOL)               /**Check the write collison flag*/
    {
        SPCTL |= ~SP_MSK_SPWCOL;
        return 0;                           /**return 0 to indicate collision occured*/
    }
    return SPI_RX_data;
}

/*end of file*/