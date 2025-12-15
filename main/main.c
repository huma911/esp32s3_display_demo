#include <stdio.h>

#include "lv_demos.h"

#include "esp_lvgl_port.h"

#include "lvgl_port.h"

void app_main(void)
{
    lvgl_init();

    lvgl_port_lock(0);
    lv_demo_widgets();
    lvgl_port_unlock();
}