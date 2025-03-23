#include "ssd1306.h"

#define BAUDRATE 115200

void init_uart()
{
    uart_init(uart0, 115200);
    gpio_set_function(0, UART_FUNCSEL_NUM(uart0, 0));
    gpio_set_function(1, UART_FUNCSEL_NUM(uart0, 1));
}

void init_i2c()
{
#ifndef i2c_default || PICO_DEFAULT_I2C_SDA_PIN || PICO_DEFAULT_I2C_SCL_PIN
    uart_puts(uart0, "Driver requires a board with i2c support\n");
    return;
#endif

    i2c_init(i2c_default, I2C_CLK * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

int main()
{
    stdio_init_all();

    init_uart();
    init_i2c();
    uart_puts(uart0, "I2C/UART initialisation finished\n\r");
    uart_puts(uart0, "OLED initialisation commands\n\r");

    init_ssd1306();

    render_area area;
    area.start_col = 0;
    area.end_col = SSD1306_WIDTH - 1;
    area.start_page = 0;
    area.end_page = SSD1306_HEIGHT - 1;

    set_area_buf_size(&area);

    uint8_t buf[MAX_BUFLEN];
    memset(buf, 0, MAX_BUFLEN);

    //test code
    buf[0] = 0xFF;

    render(area, buf, MAX_BUFLEN);

    return 0;
}