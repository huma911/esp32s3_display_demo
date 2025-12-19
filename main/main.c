#include <stdio.h>

#include "esp_log.h"
#include "driver/gpio.h"

#include "lv_demos.h"

#include "esp_lvgl_port.h"

#include "lvgl_port.h"
#include "rotary.h"

#include "gui_guider.h"
#include "custom.h"

#include "board_def.h"

#define TAG "main_app"

lv_ui guider_ui;

static void rotary_trigger_cb(int8_t rotary_value)
{
    ESP_LOGI(TAG, "rotary_value: %d", rotary_value);
}

void app_main(void)
{
    lvgl_init();

    rotary_init(ROTARY_ES_A_GPIO, ROTARY_ES_B_GPIO, rotary_trigger_cb);
    rotary_start_task();

    lvgl_port_lock(0);
    // lv_demo_widgets();
    setup_ui(&guider_ui);
    custom_init(&guider_ui);
    lvgl_port_unlock();
}