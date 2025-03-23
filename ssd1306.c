#include "ssd1306.h"

void set_area_buf_size(render_area *area)
{
    area->buf_size = (area->end_col - area->start_col + 1) * (area->end_page - area->start_page + 1);
}

uint8_t send_command(uint8_t cmd)
{
    //appends 0x80 at the start for the OLED to interpret the next byte as a command
    uint8_t send_cmd[2] = {0x80, cmd};
    
    //PICO_ERROR_GENERIC is thrown if the I2C communication fails
    if(i2c_write_blocking(i2c0, I2C_ADDR, send_cmd, 2, false) == PICO_ERROR_GENERIC)
        return 0;

    return 1;
}

void init_ssd1306()
{
    //initialisation commands necessary at the start
    uint8_t init_cmds[] = { SSD_1306_DISP_OFF, 
                            SSD1306_MEM_ADDRESS_MODE, 
                            0x00,
                            SSD_1306_DISP_START_LINE, 
                            SSD_1306_SEG_REMAP | 0x01, 
                            SSD_1306_MUX_RATIO, 
                            SSD1306_HEIGHT - 1, 
                            SSD_1306_COM_OUT_SCAN_DIR | 0x08, 
                            SSD_1306_DISP_OFFSET, 
                            0x00, 
                            SSD_1306_COM_PING_CONFIG, 

#if ((SSD1306_WIDTH == 128) & (SSD1306_HEIGHT == 32))
                            0x02,
#elif((SSD1306_WIDTH == 128) & (SSD1306_HEIGHT == 64))
                            0x12,
#endif
                            SSD_1306_DISP_CLK_DIV_RATIO, 
                            0x80,
                            SSD_1306_PRECHARGE_PERIOD, 
                            0xF1, 
                            SSD_1306_VCOM_DESEL, 
                            0x30, 
                            SSD_1306_CONTRAST_CONTROL, 
                            0xFF, 
                            SSD_1306_DISP_CONTENT_ON, 
                            SSD_1306_DISP_NORMAL, 
                            SSD1306_CHARGE_PUMP, 
                            0x14, 
                            0x2E, 
                            SSD_1306_DISP_ON };

    for(uint8_t i = 0; i < 26; i++)
    {
        char cmd_aux[3];
        sprintf(cmd_aux, "%02x", init_cmds[i]);

        //debug
        if(send_command(init_cmds[i]) == 1)
        {
            uart_puts(uart0, "Sent command: ");
            uart_puts(uart0, cmd_aux);
            uart_puts(uart0, "\n\r");
        }
        else
        {
            uart_puts(uart0, "Failed to send command\n\r");
        }
    }
}

uint8_t render(render_area area, uint8_t *buf, uint32_t len)
{
    uart_puts(uart0, "Render commands\n\r");

    //sends the render area
    uint8_t render_cmds[] = {   SSD_1306_COL_START_ADDR,
                                area.start_col,
                                area.end_col,
                                SSD_1306_PAGE_START_ADDR,
                                area.start_page,
                                area.end_page };

    for(uint8_t i = 0; i < 6; i++)
    {
        char cmd_aux[3];
        sprintf(cmd_aux, "%02x", render_cmds[i]);

        //debug
        if(send_command(render_cmds[i]) == 1)
        {
            uart_puts(uart0, "Sent command: ");
            uart_puts(uart0, cmd_aux);
            uart_puts(uart0, "\n\r");
        }
        else
        {
            uart_puts(uart0, "Failed to send command\n\r");
        }
    }

    //appends 0x40 at the start for the OLED to interpret the next bytes as the buffer 
    uint8_t send_buf[len + 1];
    send_buf[0] = 0x40;
    memcpy(send_buf + 1, buf, len);

    //PICO_ERROR_GENERIC is thrown if the I2C communication fails
    if(i2c_write_blocking(i2c0, I2C_ADDR, send_buf, len + 1, false) == PICO_ERROR_GENERIC)
        return 0;

    return 1;
}

void set_pixel(render_area area, uint8_t buf[MAX_BUFLEN], uint8_t x, uint8_t y, uint8_t val)
{
    //OLED uses pages made of 8 bits each. The division returns the coresponding page of the position
    uint8_t page = y / 8;
    //the bit position in the page
    uint8_t padding = y % 8;
    uint16_t pos = page * (area.end_col - area.start_col + 1) + x;

    //sets the specified value in the page
    uint8_t byte_val = 0;

    if(val)
        buf[pos] |= (1 << padding);
    else
        buf[pos] &= (0 << padding);
}   