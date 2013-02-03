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
*
**********************************************************************************************/
#include "MCP4922_DAC_driver.h"


#ifdef DEBUG
    int test=0;
#endif

static void MCP4922_DAC_WR_word(unsigned char* ubyte, unsigned char* lbyte)
{
    /**send the word*/
    SPI_master_byte(*ubyte);
    SPI_master_byte(*lbyte);

    CS = 1;
}

void MCP4922_init()
{
    SPI_init(SPI_MASTER, SPI_DORD_MSB_FIRST, SPI_ACTIVE_HIGH , SPI_L_EDG_TRIG, SPI_CLK_DIV_4);
}


void MCP4922_DAC_B_TX_word(unsigned short int dac_data, bit ip_buf_unbuf_select, bit gain_select)
{

    unsigned char low_byte=0, high_byte=0;
    CS = 0;                                                  /**Select the chip*/

    high_byte |= ((0x01 << 7) | (0x01 << 4));                /**Set bit to select DAC B and Set SHDN bit high for DAC A active operation*/
    if(ip_buf_unbuf_select) high_byte |= (0x01 << 6);
    if(gain_select)         high_byte |= (0x01 << 5);

    high_byte |= ((dac_data >> 8) & 0x0F);
    low_byte |= dac_data;

    /**send the word*/
    SPI_master_byte(high_byte);
    SPI_master_byte(low_byte);

    CS = 1;
}

void MCP4922_DAC_A_TX_word(unsigned short int dac_data, bit ip_buf_unbuf_select, bit gain_select)
{
    unsigned char low_byte=0, high_byte=0;
    CS = 0;                                                  /**Select the chip*/

    high_byte |= (0x01 << 4);                                /**DAC A and Set SHDN bit high for DAC A active operation*/
    if(ip_buf_unbuf_select) high_byte |= (0x01 << 6);
    if(gain_select)         high_byte |= (0x01 << 5);

    high_byte |= ((dac_data >> 8) & 0x0F);
    low_byte |= dac_data;

    #ifdef DEBUG
        test = 0;
        test |= ((high_byte <<    8) | low_byte);
    #endif

    /**send the word*/
    SPI_master_byte(high_byte);
    SPI_master_byte(low_byte);

    CS = 1;
}

void MCP4922_SHDN_DAC_A()
{
    MCP4922_DAC_WR_word(((0x01 << 7) | (0x01 << 4)), 0);
}

void MCP4922_SHDN_DAC_B()
{
    MCP4922_DAC_WR_word((0x01 << 4), 0);
}