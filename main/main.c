#include <stdio.h>
#include <time.h>

#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_sntp.h"
#include "nvs_flash.h"

#include "lv_demos.h"

#include "esp_lvgl_port.h"

#include "lvgl_port.h"
#include "rotary.h"
#include "button.h"
#include "weather.h"

#include "gui_guider.h"
#include "custom.h"

#include "ap_wifi.h"
#include "board_def.h"

#define TAG "main_app"

lv_ui guider_ui;

static uint8_t screen_index = 0;

static void my_sntp_sync_time_cb(struct timeval *tv)
{
    struct tm t;
    date_value_t my_date_value;

    ESP_LOGI(TAG, "SNTP have got the timestamp!");
    
    localtime_r(&(tv->tv_sec), &t);

    my_date_value.year = t.tm_year + 1900;
    my_date_value.month = t.tm_mon + 1;
    my_date_value.day = t.tm_mday;
    my_date_value.week = t.tm_wday;
    my_date_value.hour = t.tm_hour;
    my_date_value.minute = t.tm_min;
    my_date_value.second = t.tm_sec;

    set_home_time(&guider_ui, &my_date_value);
}

static void my_sntp_init(void)
{
    //0. check if sntp have been started
    if(esp_sntp_enabled()) {
        ESP_LOGW(TAG, "SNTP have been started!");
        return;
    }
    ESP_LOGI(TAG, "SNTP start init!");

    //1. set sntp working mode: poll mode
    esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);

    //2. set sntp server: 0-aliyun 1-apple 2-NTP
    esp_sntp_setservername(0, "ntp.aliyun.com");
    esp_sntp_setservername(1, "time.asia.apple.com");
    esp_sntp_setservername(2, "pool.ntp.org");

    //3. register callback
    esp_sntp_set_time_sync_notification_cb(my_sntp_sync_time_cb);

    //4. start sntp
    esp_sntp_init();
}

static void wifi_state_callback(WIFI_STATE state)
{
    if(state == WIFI_STATE_CONNECTED) {
        ESP_LOGI(TAG, "wifi connected!");
        if(lv_obj_has_flag(guider_ui.screen_main_img_wifi, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(guider_ui.screen_main_img_wifi, LV_OBJ_FLAG_HIDDEN);  //show the wifi state image
        }
        my_sntp_init();
    } else if(state == WIFI_STATE_DISCONNECTED) {
        ESP_LOGI(TAG, "wifi disconnected!");
    } else {
        ;
    }
}

#define SCROLL_PIXELS	(100)
extern lv_obj_t * cont;

static void rotary_rotate_trigger_cb(int8_t rotary_value)
{
    
    ESP_LOGI(TAG, "rotary_value: %d", rotary_value);

    if(screen_index == 2) {
        if(rotary_value == 1) {
            lvgl_port_lock(0);
            lv_obj_scroll_by(cont, 0, SCROLL_PIXELS, LV_ANIM_ON);
            lvgl_port_unlock();
        } else if(rotary_value == -1) {
            lvgl_port_lock(0);
            lv_obj_scroll_by(cont, 0, -SCROLL_PIXELS, LV_ANIM_ON);
            lvgl_port_unlock();
        } else {
            ;
        }
    }
}

void lv_example_scroll_6(void);

static void sw2_button_short_press_trigger_cb(int gpio)
{
    ESP_LOGI(TAG, "sw2 button short press: %d.", gpio);

    switch(screen_index) {
        case 0:
            lvgl_port_lock(0);
            lv_obj_send_event(guider_ui.screen_main, LV_EVENT_CLICKED, NULL);
            lvgl_port_unlock();
            break;
        case 1:
            lvgl_port_lock(0);
            lv_obj_send_event(guider_ui.screen_aclock, LV_EVENT_CLICKED, NULL);
            lv_example_scroll_6();
            lvgl_port_unlock();
            break;
        case 2:
            lvgl_port_lock(0);
            lv_obj_send_event(guider_ui.screen_list, LV_EVENT_CLICKED, NULL);
            lvgl_port_unlock();
            break;
        default:
            break;
    }

    screen_index ++;
    screen_index = screen_index%3;
}

static void sw2_button_long_press_trigger_cb(int gpio)
{
    ESP_LOGI(TAG, "sw2 button long press: %d.", gpio);
}

static void rotary_button_short_press_trigger_cb(int gpio)
{
    ESP_LOGI(TAG, "rotary button short press: %d.", gpio);
}

static void rotary_button_long_press_trigger_cb(int gpio)
{
    ESP_LOGI(TAG, "rotary button long press: %d.", gpio);
    ap_wifi_apcfg(true);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());

    rotary_cfg_t rotary_cfg = {
        .rotary_gpio_cfg.trigger_gpio_num = ROTARY_ES_A_GPIO,
        .rotary_gpio_cfg.another_gpio_num = ROTARY_ES_B_GPIO,
        .rotary_cb                        = rotary_rotate_trigger_cb,
        .button_cfg                       = {
            .active_level    = 0,
            .getlevel_cb     = gpio_get_level,
            .gpio_num        = ROTARY_BUTTON_GPIO,
            .long_cb         = rotary_button_long_press_trigger_cb,
            .long_press_time = 3000,
            .short_cb        = rotary_button_short_press_trigger_cb,
        }
    };
    rotary_init(&rotary_cfg);
    rotary_start_task();

    button_config_t button_cfg = {
        .active_level    = 0,
        .getlevel_cb     = gpio_get_level,
        .gpio_num        = SW2_BUTTON_GPIO,
        .long_cb         = sw2_button_long_press_trigger_cb,
        .long_press_time = 3000,
        .short_cb        = sw2_button_short_press_trigger_cb,
    };
    button_event_set(&button_cfg);

    lvgl_init();

    lvgl_port_lock(0);
    // lv_demo_widgets();
    setup_ui(&guider_ui);
    custom_init(&guider_ui);
    lvgl_port_unlock();

    ap_wifi_init(wifi_state_callback);

    setenv("TZ", "CST-8", 1);   //set timezone environment variable
    tzset();                    //enable timezone environment variable

    weather_start();
}