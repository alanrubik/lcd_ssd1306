/*
 * File:   lcd_ssd1306.c
 * Author: tonyx
 *
 * Created on 8 de abril de 2022, 08:59 PM
 */


#include "lcd_ssd1306.h"

uint8_t buffer[DISPLAY_HEIGHT][DISPLAY_WIDTH]; 

void lcd_Initialize(void) 
{
    uint8_t data[SSD1306_NUM_INITIAL_CMDS];
    I2C1_MESSAGE_STATUS status = -1;
    bool completed = false;
    
    data[0] = 0x00;
    data[1] = SSD1306_SET_DISPLAY_OFF;
    data[2] = SSD1306_SET_DISPLAY_CLOCK;                /* Set Osc Frequency */
    data[3] = SSD1306_DISPLAY_CLK_DIVIDE_RATIO;         /* Divide ratio = 1. Oscilator freq = 8 */
    data[4] = SSD1306_SETMULTIPLEX;                     /* Set MUX ratio */
    data[5] = SSD1306_SETMULTIPLEX_VALUE;               /* MUX ratio value */
    data[6] = SSD1306_SET_DISPLAY_OFFSET;               /* Set Display Offset */
    data[7] = SSD1306_SET_DISPLAY_OFFSET_VALUE;         /* Set Display Offset value */
    data[8] = SSD1306_SET_DISPLAY_START_LINE | 0x0;     /* Set Display Start Line */
    data[9] = SSD1306_CHARGE_PUMP_SETTING;              /* Enable charge pump regulator */
    data[10] = SSD1306_CHARGE_PUMP_VALUE;               /* Set the pump value */
    data[11] = SSD1306_SET_MEMORY_ADDRESSING;           /* Set Memory Addressing */
    data[12] = SSD1306_ADDRESSING_HORIZONTAL;           /* Set Memory Addressing Horizontal */
    data[13] = SSD1306_SEGREMAP;                        /* Set Segment re-map */
    data[14] = SSD1306_COM_OUTPUT_SCAN_DIRECTION;       /* Set COM Output Scan Direction */
    data[15] = SSD1306_COM_PINS_HARDWARE_CONFIG;        /* Set COM Pins hardware configuration */
    data[16] = SSD1306_SEQ_COM_PIN_CONFIGURATION;       /* Sequential COM pin configuration */
    data[17] = SSD1306_SET_CONTRAST;                    /* Set Contrast Control */
    data[18] = SSD1306_INIT_CONTRAST_VALUE;             /* Set initial Contrast value */
    data[19] = SSD1306_SET_PRE_CHARGED_PERIOD;          /* Set pre-charged period */
    data[20] = SSD1306_PRE_CHARGED_PHASE;               /* Set pre-charged period */
    data[21] = SSD1306_SET_VCOMH_DESELECT;              /* Set Vcomh Level */
    data[22] = SSD1306_SET_VCOMH_DESELECT_LEVEL;        /* Set Vcomh Level */
    data[23] = SSD1306_IGNORE_ENTIRE_DISPLAY_ON;        /* Disable Entire Display On */
    data[24] = SSD1306_SET_NORMAL_DISPLAY;              /* Set Normal Display */
    data[25] = SSD1306_DEACTIVATE_SCROLL;               /* Deactivate scroll */
    data[26] = SSD1306_SET_DISPLAY_ON;                  /* Display on */
    
    send_i2c_lcd_cmd(data,SSD1306_NUM_INITIAL_CMDS);
}

void showDisplay( void)
{ 
    uint8_t commandList[] = 
    {
        SSD1306_SET_PAGE_ADDRESS,
        SSD1306_PAGE_START,
        SSD1306_PAGE_END,
        SSD1306_SET_COLUMN_ADDRESS,
        SSD1306_COLUMN_START_ADDRESS,
        SSD1306_COLUMN_END_ADDRESS
    };
    send_i2c_lcd_cmd(commandList, sizeof(commandList));
}

void send_i2c_lcd_cmd(  uint8_t *pdata,
                        uint8_t length)
{
    I2C1_MESSAGE_STATUS status = -1;
    I2C1_MasterWrite(pdata, length, SSD1306_ADDRESS, &status);
    check_lcd_I2C_status(&status);
}

void lcd_Draw_Pixel(uint8_t x, uint8_t y){
    
    uint8_t data[7];
    uint8_t current_column, pixel_byte;
    I2C1_MESSAGE_STATUS status;
    
    /* coordinates validation */
    if(x < 0 || x > 127)
    {
        return;
    }
    if(y < 0 || y > 63)
    {
        return;
    }
    
    data[0] = 0x00;
    
    /* Set Column Address */
    data[1] = SSD1306_SET_COLUMN_ADDRESS;
    data[2] = x;
    data[3] = x;
    
    /* Set Page Address */
    data[4] = SSD1306_SET_PAGE_ADDRESS;
    data[5] = y/8;
    data[6] = y/8;
    
    send_i2c_lcd_cmd(data,7); /* Send Commands to LCD */
    
    send_i2c_lcd_cmd(&current_column,1); /* Read of the current byte */
    
    /* pixel writing */
    pixel_byte = 1 << (y%8); /* formula to obtain the posicion of the bit to be turned ON */
    pixel_byte |= current_column; /* Added pixel to the current byte */
    
    send_i2c_lcd_cmd(&pixel_byte,1);
}

void check_lcd_I2C_status(I2C1_MESSAGE_STATUS *status)
{
    bool completed = false;
    
    while(!completed)
    {
        switch(*status)
        {
            case I2C1_MESSAGE_FAIL:
                completed = true;
                break;

            case I2C1_MESSAGE_PENDING:
                break;

            case I2C1_MESSAGE_COMPLETE:
                completed = true;
                break;

            case I2C1_STUCK_START:
                completed = true;
                break;

            case I2C1_MESSAGE_ADDRESS_NO_ACK:
                completed = true;
                break;

            case I2C1_DATA_NO_ACK:
                completed = true;
                break;

            case I2C1_LOST_STATE:
                completed = true;
                break;    
        }
    }
}
