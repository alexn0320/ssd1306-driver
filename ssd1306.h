#ifndef SSD1306_H
#define SSD1306_H

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

/*
    Defines necessary OLED/I2C information, commands and functions
*/

#define I2C_ADDR 0x3C
#define I2C_CLK 400

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_PAGE_NUM (SSD1306_HEIGHT / 8)
#define MAX_BUFLEN SSD1306_WIDTH * SSD1306_PAGE_NUM

//commands
#define SSD1306_MEM_ADDRESS_MODE    0x20
#define SSD_1306_COL_START_ADDR     0x21
#define SSD_1306_PAGE_START_ADDR    0x22
#define SSD_1306_DISP_START_LINE    0x40
#define SSD_1306_CONTRAST_CONTROL   0x81
#define SSD_1306_SEG_REMAP          0xA0
#define SSD_1306_DISP_CONTENT_ON    0xA4
#define SSD_1306_DISP_ENTIRE_ON     0xA5
#define SSD_1306_DISP_NORMAL        0xA6
#define SSD_1306_DISP_INVERTED      0xA7
#define SSD_1306_MUX_RATIO          0xA8
#define SSD_1306_DISP_OFF           0xAE
#define SSD_1306_DISP_ON            0xAF
#define SSD_1306_COM_OUT_SCAN_DIR   0xC0
#define SSD_1306_DISP_OFFSET        0xD3
#define SSD_1306_DISP_CLK_DIV_RATIO 0xD5
#define SSD_1306_PRECHARGE_PERIOD   0xD9
#define SSD_1306_COM_PING_CONFIG    0xDA
#define SSD_1306_VCOM_DESEL         0xDB
#define SSD_1306_COM_PING_CONFIG    0xDA
#define SSD_1306_HORIZ_SCROLL       0x26
#define SSD_1306_SET_SCROLL         0x2E
#define SSD1306_CHARGE_PUMP         0x8D

#define BUFLEN 1024

//defines the boundaries of the render area for the OLED
typedef struct
{
    uint8_t start_col;
    uint8_t end_col;
    uint8_t start_page;
    uint8_t end_page;
    uint32_t buf_size;
} render_area;

//initialises the buf_size variable of the render_area
void set_area_buf_size(render_area *area);
//sends a command using I2C
uint8_t send_command(uint8_t cmd);
//sends the initialisation commands for the OLED
void init_ssd1306();
//sends the area and the buffer to the OLED
uint8_t render(render_area area, uint8_t *buf, uint32_t len);
//sets a pixel specified using the coordonates x, y
void set_pixel(render_area area, uint8_t buf[MAX_BUFLEN], uint8_t x, uint8_t y, uint8_t val);

#endif