/*
 * File:   lcd_ssd1306.c
 * Author: tonyx
 *
 * Created on 8 de abril de 2022, 08:59 PM
 */


#include "lcd_ssd1306.h"

int lcd_Initialize(void) {
    uint8_t data[13];
    I2C1_MESSAGE_STATUS status;
    
    data[0] = SSD1306_SETMULTIPLEX;                     /* Set MUX ratio */
    data[1] = SSD1306_SETMULTIPLEX_VALUE                /* MUX ratio value */
    data[2] = SSD1306_SET_DISPLAY_OFFSET;               /* Set Display Offset */
    data[2] = SSD1306_SET_DISPLAY_OFFSET_VALUE;         /* Set Display Offset value */
    data[3] = SSD1306_SET_DISPLAY_START_LINE;           /* Set Display Start Line */
    data[4] = SSD1306_SEGREMAP;                         /* Set Segment re-map */
    data[5] = SSD1306_COM_OUTPUT_SCAN_DIRECTION;        /* Set COM Output Scan Direction */
    data[6] = SSD1306_COM_PINS_HARDWARE_CONFIG;         /* Set COM Pins hardware configuration */
    data[7] = SSD1306_SEQ_COM_PIN_CONFIGURATION;        /* Sequential COM pin configuration */
    data[8] = SSD1306_SET_CONTRAST;                     /* Set Contrast Control */
    data[8] = SSD1306_INIT_CONTRAST_VALUE;              /* Set initial Contrast value */                               
    data[9] = SSD1306_ENTIRE_DISPLAY_ON;                /* Disable Entire Display On */
    data[10] = SSD1306_SET_NORMAL_DISPLAY;              /* Set Normal Display */
    data[11] = SSD1306_SET_DISPLAY_CLOCK;               /* Set Osc Frequency */
    data[12] = SSD1306_DISPLAY_CLK_DIVIDE_RATIO;        /* Divide ratio = 1. Oscilator freq = 8 */
    data[13] = SSD1306_CHARGE_PUMP_SETTING;             /* Enable charge pump regulator */
    data[14] = SSD1306_CHARGE_PUMP_VALUE;               /* Display On */
    
    I2C1_MasterWrite(data,12,SSD1306_ADDRESS,&status);

    return 0;
}
