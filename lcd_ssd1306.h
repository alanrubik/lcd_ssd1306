/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_SSD1306_H
#define	LCD_SSD1306_H

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"

#define SSD1306_ADDRESS                     0x3C
#define SSD1306_NUM_INITIAL_CMDS            18

/* FUNDAMENTAL COMMAND TABLE */
#define SSD1306_SET_CONTRAST                0x81 /* Set contrast initialization */
#define SSD1306_INIT_CONTRAST_VALUE         0xAA /* Contrast initial value */
#define SSD1306_IGNORE_ENTIRE_DISPLAY_ON    0xA4 /* 0xA4 Resume to RAM content display (RESET) Output follows RAM content. 0xA5 Entire display ON, Output ignores RAM content */
#define SSD1306_SET_NORMAL_DISPLAY          0xA6 /* 0 in RAM: OFF in display panel - 1 in RAM: ON in display panel (RESET) */
#define SSD1306_SET_INVERSE_DISPLAY         0xA7 /* 0 in RAM: ON in display panel - 1 in RAM: OFF in display panel */
#define SSD1306_SET_DISPLAY_ON              0xAF /* Display OFF (sleep mode) (RESET) */
#define SSD1306_SET_DISPLAY_OFF             0xAE /* Display ON in normal mode */

/* SCROLLING COMMAND TABLE*/
#define SSD1306_RIGHT_SCROLL                0x26 /* Right Horizontal Scroll 1 column */
#define SSD1306_LEFT_SCROLL                 0x27 /* Left Horizontal Scroll 1 column */
#define SSD1306_VERTICAL_RIGHT_SCROLL       0x29 /* Vertical and right scroll (Horizontal scroll by 1 column) */
#define SSD1306_VERTICAL_LEFT_SCROLL        0x2A /* Vertical and left scroll (Horizontal scroll by 1 column) */
#define SSD1306_DUMMY_BYTE                  0x00 /* Dummy Byte */
#define SSD1306_START_PAGE                  0x00 /* Initialize start page on page zero */
#define SSD1306_SCROLL_STEP                 0x02 /* 010b ? 128 frames between each scroll */
#define SSD1306_END_PAGE                    0x07 /* Initialize end page on page seven */
#define SSD1306_DUMMY_BYTE_FINAL            0xFF /* Final Dummy Byte */
#define SSD1306_VERTICAL_SCROLL_OFFSET      0x01 /* 01h refer to offset = 1 row, No continuous vertical scrolling is available */
#define SSD1306_DEACTIVATE_SCROLL           0x2E /* Deactivate scroll */
#define SSD1306_ACTIVATE_SCROLL             0x2F /* Activate scroll */
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3 /* Set scroll range */

/* ADDRESSING SETTING COMMAND TABLE*/
#define SSD1306_SET_L_COLUMN_START_ADDRESS  0x00 /* Set the LOWER nibble of the column start address register for Page Addressing Mode using X[3:0] as data bits. The initial display line register is reset to 0000b after RESET. This command is only for page addressing mode */
#define SSD1306_SET_H_COLUMN_START_ADDRESS  0x10 /* Set the HIGHER nibble of the column start address register for Page Addressing Mode using X[3:0] as data bits. The initial display line register is reset to 0000b after RESET. This command is only for page addressing mode */
#define SSD1306_SET_MEMORY_ADDRESSING       0x20 /* Set memory addressing mode*/
#define SSD1306_ADDRESSING_HORIZONTAL       0x00 /* Addressing mode: 00b Horizontal, 01b Vertical, 10b Page (reset), 11b invalid */
#define SSD1306_SET_COLUMN_ADDRESS          0x21 /* Setup column start and end address . This command is only for horizontal or vertical addressing mode */
#define SSD1306_COLUMN_START_ADDRESS        0x00 /* Column START address, range : 0-127d, (RESET=0d). This command is only for horizontal or vertical addressing mode */
#define SSD1306_COLUMN_END_ADDRESS          0x7F /* Column END address, range : 0-127d, (RESET=127d). This command is only for horizontal or vertical addressing mode */
#define SSD1306_SET_PAGE_ADDRESS            0x22 /* Setup page start and end address. This command is only for horizontal or vertical addressing mode */
#define SSD1306_PAGE_START                  0x00 /* Page start Address, range : 0-7d, (RESET = 0d). This command is only for horizontal or vertical addressing mode */
#define SSD1306_PAGE_END                    0x07 /* Page end Address, range : 0-7d, (RESET = 7d). This command is only for horizontal or vertical addressing mode */
#define SSD1306_SET_PAGE_START_ADDRESS      0xB0 /* Setup page start and end address B0~B7 (PAGE0~PAGE7) This command is only for page addressing mode */

/* HARDWARE CONFIGURATION (PANEL RESOLUTION & LAYOUT RELATED) COMMAND TABLE */
#define SSD1306_SET_DISPLAY_START_LINE      0x40 /* Set display RAM display start line register from 0-63. 0x40 during RESET */
#define SSD1306_SEGREMAP                    0xA0 /* 0xA0 column address 0 is mapped to SEG0 (RESET). 0xA1 column address 127 is mapped to SEG0 */
#define SSD1306_SETMULTIPLEX                0xA8 /* See DataSheet RESET= 111111b */
#define SSD1306_SETMULTIPLEX_VALUE          0x3F /* See DataSheet RESET= 111111b */
#define SSD1306_COM_OUTPUT_SCAN_DIRECTION   0xC0 /* normal mode (RESET) Scan from COM0 to COM[N ?1]. remapped mode. Scan from COM[N-1] to COM0 Where N is the Multiplex ratio */
#define SSD1306_SET_DISPLAY_OFFSET          0xD3 /* Mapping of the display star line to one of COM0~COM63 */
#define SSD1306_SET_DISPLAY_OFFSET_VALUE    0x00 /* Value (RESET)COM0~COM63 */
#define SSD1306_COM_PINS_HARDWARE_CONFIG    0xDA /* Set the pins of the Hardware */
#define SSD1306_SEQ_COM_PIN_CONFIGURATION   0x12 /* Select sequential/alternative(Reset) COM pin configuration, (Reset)Disable/Enable COM left right Remap */


/* Timing & Driving Scheme Setting Command Table*/
#define SSD1306_SET_DISPLAY_CLOCK           0xD5 /* Set the clock of the display */
#define SSD1306_DISPLAY_CLK_DIVIDE_RATIO    0x80 /* Divide ratio of the Display clock in first nible A[3:0]+1,(reset 0000=1). Oscilator Frequency A[7:4] min 0000b~1111b max */
#define SSD1306_SET_PRE_CHARGED_PERIOD      0xD9 /* Set the pre-charged period */
#define SSD1306_PRE_CHARGED_PHASE           0x22 /* A[3:0] = Phase 1 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h). A[7:4] = Phase 2 period of up to 15 DCLK clocks 0 is invalid entry (RESET=2h )  */          
#define SSD1306_SET_VCOMH_DESELECT          0xDB /* Set the Vcomh */
#define SSD1306_SET_VCOMH_DESELECT_LEVEL    0x20 /* Vcomh Level */
#define SSD1306_NOP                         0xE3 /* Command for no operation */

/* CHARGE PUMP COMMAND TABLE */
#define SSD1306_CHARGE_PUMP_SETTING         0x8D /* Set the Charge pump */
#define SSD1306_CHARGE_PUMP_VALUE           0x10 /* A[2]= 0b, Disable charge pump(RESET). A[2] = 1b, Enable charge pump during display on. The Charge Pump must be enabled by the following command: 8Dh : Charge Pump Setting - 14h : Enable Charge Pump - AFh: Display ON */

/* Function prototypes */
void lcd_Initialize(void);
void lcd_Draw_Pixel(uint8_t x, uint8_t y);

#endif	/* LCD_SSD1306_H */

