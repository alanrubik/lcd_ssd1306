/*
 * File:   lcd_ssd1306.c
 * Author: tonyx
 *
 * Created on 8 de abril de 2022, 08:59 PM
 */


#include "lcd_ssd1306.h"

uint8_t buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];

void lcd_Initialize(void) {
    uint8_t data[SSD1306_NUM_INITIAL_CMDS];
    I2C1_MESSAGE_STATUS status = -1;
    
    data[0] = SSD1306_CTRLBYTE_COMMAND;                 /* Will give Commands */
    data[1] = SSD1306_SET_DISPLAY_OFF;                  /* Set Disp off */
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
    
    I2C1_MasterWrite(data,SSD1306_NUM_INITIAL_CMDS,SSD1306_ADDRESS,&status);
    check_lcd_I2C_status(&status);
}

void lcd_Draw_Pixel(uint8_t x, uint8_t y, uint8_t pixel_color)
{
    if((x > DISPLAY_WIDTH-1) || (x < 0) || (y > DISPLAY_HEIGHT-1) || (y < 0))
        return;
    buffer[x][y] = pixel_color;
}

uint8_t lcd_Read_Pixel(uint8_t x, uint8_t y)
{
    if((x > DISPLAY_WIDTH-1) || (x < 0) || (y > DISPLAY_HEIGHT-1) || (y < 0))
        return 0;
    return buffer[x][y];
}

void clear_Display(void)
{
    memset(buffer, 0, sizeof buffer);   
}

void lcd_Draw_Vertical_Line(uint8_t x, uint8_t y, uint8_t lenght, uint8_t pixel_color)
{
    int i;
    if((x > DISPLAY_WIDTH-1) || (x < 0) || (y > DISPLAY_HEIGHT-1) || (y < 0) || (lenght < 0))
        return ;
    for(i=y; i<=lenght && i<DISPLAY_HEIGHT; i++)
    {
        buffer[x][i] = pixel_color;
    }
}

void lcd_Draw_Horizontal_Line(uint8_t x, uint8_t y, uint8_t lenght, uint8_t pixel_color)
{
    int i;
    if((x > DISPLAY_WIDTH-1) || (x < 0) || (y > DISPLAY_HEIGHT-1) || (y < 0) || (lenght < 0))
        return;
    for(i=x; i<=lenght && i<DISPLAY_WIDTH; i++)
    {
        buffer[i][y] = pixel_color;
    }
}

void show_Display(void)
{
    uint8_t i,j,ram_byte=0, page, ctrl_data=SSD1306_CTRLBYTE_DATA;  
    uint8_t data[7];
    I2C1_MESSAGE_STATUS status = -1;
    
    data[0] = SSD1306_CTRLBYTE_COMMAND;     /* Ready to set the start and end column address */    
    data[1] = SSD1306_SET_COLUMN_ADDRESS;     /* Ready to set the start and end column address */
    data[2] = SSD1306_COLUMN_START_ADDRESS;   /* Start address on column 0 */
    data[3] = SSD1306_COLUMN_END_ADDRESS;     /* End address on column 127 */
    data[4] = SSD1306_SET_PAGE_ADDRESS;       /* Ready to set the start and end page address */
    data[5] = SSD1306_PAGE_START;             /* Start address on page 0 */
    data[6] = SSD1306_PAGE_END;               /* End address on page 7 */    
    
    I2C1_MasterWrite(data,7,SSD1306_ADDRESS,&status);
    check_lcd_I2C_status(&status);

    I2C1_MasterWrite(&ctrl_data,1,SSD1306_ADDRESS,&status);
    check_lcd_I2C_status(&status);  
    
    for(page=0; page<8; page++)
    {
        for(i=0; i<DISPLAY_WIDTH; i++)
        {
            ram_byte = 0;
            for(j=0; j<8; j++)
            {
                if(buffer[i][j] == 1)
                    ram_byte = ram_byte | (1 << j);
                else
                    ram_byte = ram_byte & ~(1 << j);
            }
            I2C1_MasterWrite(&ram_byte,1,SSD1306_ADDRESS,&status);
            check_lcd_I2C_status(&status);
        }
    } 
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