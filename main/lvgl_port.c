#include "esp_log.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_lvgl_port.h"
#include "esp_lcd_st7796.h"

// #include "rotary.h"

#define TAG "lvgl_port"

#define LCD_GPIO_BL     (GPIO_NUM_13)
#define LCD_BL_ON_LEVEL (1)

#define LCD_WIDTH   (480)
#define LCD_HEIGHT  (320)

#define LCD_DRAW_BUFF_HEIGHT    (80)

#define SPI_CLK_FREQUENCY   (80 * 1000 * 1000)

// Using SPI2 in the demo
#define LCD_HOST  SPI2_HOST

static esp_lcd_panel_io_handle_t lcd_io_handle = NULL;
static esp_lcd_panel_handle_t lcd_panel_handle = NULL;

static lv_display_t *lvgl_disp = NULL;

// static lv_indev_t *rotary_indev = NULL;

static void lvgl_display_hardware_init(void)
{
    ESP_LOGI(TAG, "Turn off LCD backlight");
    gpio_config_t bk_gpio_config = {
        .mode         = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << LCD_GPIO_BL
    };
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .sclk_io_num     = GPIO_NUM_10,
        .mosi_io_num     = GPIO_NUM_18,
        .miso_io_num     = GPIO_NUM_NC,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1,
        .max_transfer_sz = LCD_WIDTH * LCD_HEIGHT * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num       = GPIO_NUM_11,
        .cs_gpio_num       = GPIO_NUM_12,
        .pclk_hz           = SPI_CLK_FREQUENCY,
        .lcd_cmd_bits      = 8,
        .lcd_param_bits    = 8,
        .spi_mode          = 0,
        .trans_queue_depth = 10,
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &lcd_io_handle));

    ESP_LOGI(TAG, "Install ST7796 panel driver");
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = GPIO_NUM_8,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7796(lcd_io_handle, &panel_config, &lcd_panel_handle));

    esp_lcd_panel_reset(lcd_panel_handle);
    esp_lcd_panel_init(lcd_panel_handle);
    esp_lcd_panel_invert_color(lcd_panel_handle, true);
    esp_lcd_panel_swap_xy(lcd_panel_handle, true);
    esp_lcd_panel_mirror(lcd_panel_handle, false, false);
    esp_lcd_panel_disp_on_off(lcd_panel_handle, true);

    /* LCD backlight on */
    ESP_ERROR_CHECK(gpio_set_level(LCD_GPIO_BL, LCD_BL_ON_LEVEL));
}

// static void lv_indev_rotary_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
// {
//     // data->enc_diff = rotary_data.last_direction;
// }

static void lvgl_display_portation_init(void)
{
    /* Initialize LVGL */
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = 4,         /* LVGL task priority */
        .task_stack = 8192,         /* LVGL task stack size */
        .task_affinity = 1,         /* LVGL task pinned to core (-1 is no affinity) */
        .task_max_sleep_ms = 500,   /* Maximum sleep in LVGL task */
        .timer_period_ms = 5        /* LVGL timer tick period in ms */
    };
    
    // ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "LVGL port initialization failed");
    esp_err_t ert = lvgl_port_init(&lvgl_cfg);
    if(ert != ESP_OK) {
        ESP_LOGE(TAG, "LVGL port initialization failed");
        return;
    }

    /* Add LCD screen */
    ESP_LOGI(TAG, "Add LCD screen");
    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle     = lcd_io_handle,
        .panel_handle  = lcd_panel_handle,
        .buffer_size   = LCD_WIDTH * LCD_DRAW_BUFF_HEIGHT,
        .double_buffer = false,
        .hres          = LCD_WIDTH,
        .vres          = LCD_HEIGHT,
        .monochrome    = false,
        .color_format  = LV_COLOR_FORMAT_RGB565,
        .rotation      = {
            .swap_xy  = true,
            .mirror_x = false,
            .mirror_y = false,
        },
        .flags = {
            .buff_dma   = true,
            .swap_bytes = true,
        }
    };
    lvgl_disp = lvgl_port_add_disp(&disp_cfg);

    //add device 
    // lvgl_port_lock(0);
    // rotary_indev = lv_indev_create();
    // lv_indev_set_type(rotary_indev, LV_INDEV_TYPE_ENCODER);
    // lv_indev_set_read_cb(rotary_indev, lv_indev_rotary_read_cb);
    // lvgl_port_unlock();
}

void lvgl_init(void)
{
    lvgl_display_hardware_init();
    lvgl_display_portation_init();
}