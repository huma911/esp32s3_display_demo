/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "custom.h"

#include "esp_log.h"
#include "lvgl.h"

#include "esp_lvgl_port.h"

/*********************
 *      DEFINES
 *********************/

 #define TAG "lvgl_custom"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

lv_ui*        custom_ui           = NULL;

lv_timer_t*   digital_clock_timer = NULL;

extern int screen_main_digital_clock_main_hour_value;
extern int screen_main_digital_clock_main_min_value;
extern int screen_main_digital_clock_main_sec_value;

const Week_Entry week_entries[] = {
	{WEEK_SUNDAY,        "Sunday"		},
	{WEEK_MONDAY,        "Monday"		},
	{WEEK_TUESDAY,       "Tuesday"		},
	{WEEK_WEDNESDAY,     "Wednesday"	},
	{WEEK_THURSDAY,      "Thursday"		},
	{WEEK_FRIDAY,        "Friday"		},
	{WEEK_SATURDAY,      "Saturday"		},
};

static void date_config(lv_ui* ui)
{
    time_t current_time = time(NULL);

    struct tm t;

    //1.convert the local time
    localtime_r(&current_time, &t);

    //2.set date
    char date_text[64];
    snprintf(date_text, sizeof(date_text), "%d/%d/%d", t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);

    //3.set week
    char week_text[64];
    memset(week_text, 0, sizeof(week_text));
    snprintf(week_text, sizeof(week_text), "%s", week_entries[t.tm_wday].value);

    //4.set tomorrow and after tomorrow week
    char week_tomorrow_text[64];
    memset(week_tomorrow_text, 0, sizeof(week_tomorrow_text));
    snprintf(week_tomorrow_text, sizeof(week_tomorrow_text), "%s", week_entries[(t.tm_wday + 1) % WEEK_DAY_NUM].value);

    char week_after_text[64];
    memset(week_after_text, 0, sizeof(week_after_text));
    snprintf(week_after_text, sizeof(week_after_text), "%s", week_entries[(t.tm_wday + 2) % WEEK_DAY_NUM].value);

    //5.set lvgl label
    lvgl_port_lock(0);
    lv_label_set_text(ui->screen_main_label_date, date_text);
    lv_label_set_text(ui->screen_main_label_week, week_text);
    lv_label_set_text(ui->screen_main_label_tomorrow, week_tomorrow_text);
    lv_label_set_text(ui->screen_main_label_after_tomorrow, week_after_text);
    lvgl_port_unlock();
}

void set_home_time(lv_ui* ui, date_value_t* date_value)
{
    //1.set clock
    screen_main_digital_clock_main_hour_value = (int)(date_value->hour);
    screen_main_digital_clock_main_min_value  = (int)(date_value->minute);
    screen_main_digital_clock_main_sec_value  = (int)(date_value->second);

    //2.set date
    char date_text[64];
    memset(date_text, 0, sizeof(date_text));
    snprintf(date_text, sizeof(date_text), "%d/%d/%d", date_value->day, date_value->month, date_value->year);

    //3.set week
    char week_text[64];
    memset(week_text, 0, sizeof(week_text));
    snprintf(week_text, sizeof(week_text), "%s", week_entries[date_value->week].value);

    //4.set tomorrow and after tomorrow week
    char week_tomorrow_text[64];
    memset(week_tomorrow_text, 0, sizeof(week_tomorrow_text));
    snprintf(week_tomorrow_text, sizeof(week_tomorrow_text), "%s", week_entries[(date_value->week + 1) % WEEK_DAY_NUM].value);

    char week_after_text[64];
    memset(week_after_text, 0, sizeof(week_after_text));
    snprintf(week_after_text, sizeof(week_after_text), "%s", week_entries[(date_value->week + 2) % WEEK_DAY_NUM].value);

    //5.set lvgl label
    lvgl_port_lock(0);
    lv_label_set_text(ui->screen_main_label_date, date_text);
    lv_label_set_text(ui->screen_main_label_week, week_text);
    lv_label_set_text(ui->screen_main_label_tomorrow, week_tomorrow_text);
    lv_label_set_text(ui->screen_main_label_after_tomorrow, week_after_text);

    lv_label_set_text(ui->screen_aclock_label_date, date_text);
    lv_label_set_text(ui->screen_aclock_label_week, week_text);
    lvgl_port_unlock();
}

static void aclock_update(lv_ui* ui, int *hour, int *min, int *sec)
{
    int32_t sec_angle  = (*sec) * 60;
    int32_t min_angle  = ((*sec) % 60) * 1 + (*min) * 60;
    int32_t hour_angle = ((*min) % 60) * 5 + (*hour) * 300;

    lv_image_set_rotation(ui->screen_aclock_img_second, sec_angle);
    lv_image_set_rotation(ui->screen_aclock_img_minute, min_angle);
    lv_image_set_rotation(ui->screen_aclock_img_hour, hour_angle);
}

static void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60) {
        *sec = 0;
        (*min)++;
    }

    if(*min == 60) {
        *min = 0;
        if(*hour < 23) {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %24;
        }
    }
}

static void screen_main_digital_clock_main_replace_timer(lv_timer_t *timer)
{
    clock_count(&screen_main_digital_clock_main_hour_value, &screen_main_digital_clock_main_min_value, &screen_main_digital_clock_main_sec_value);
    aclock_update(custom_ui, &screen_main_digital_clock_main_hour_value, &screen_main_digital_clock_main_min_value, &screen_main_digital_clock_main_sec_value);

    if(screen_main_digital_clock_main_hour_value == 0 && screen_main_digital_clock_main_min_value == 0 && screen_main_digital_clock_main_sec_value == 0)
    {
        ESP_LOGI(TAG, "update a new day!");
        date_config(custom_ui);
    }

    if (lv_obj_is_valid(guider_ui.screen_main_digital_clock_main))
    {
        lv_label_set_text_fmt(guider_ui.screen_main_digital_clock_main, "%d:%02d:%02d", screen_main_digital_clock_main_hour_value, screen_main_digital_clock_main_min_value, screen_main_digital_clock_main_sec_value);
    }
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    custom_ui = ui;

    setup_bottom_layer();
    init_scr_del_flag(ui);
    init_keyboard(ui);
    setup_scr_screen_main(ui);
    lv_screen_load(ui->screen_main);

    setup_scr_screen_aclock(ui);

    lvgl_port_lock(0);
    lv_obj_add_flag(ui->screen_main_img_wifi, LV_OBJ_FLAG_HIDDEN);  //hide the wifi state image

    if(digital_clock_timer != NULL) {
        lv_timer_pause(digital_clock_timer);
        lv_timer_set_cb(digital_clock_timer, screen_main_digital_clock_main_replace_timer);
        lv_timer_resume(digital_clock_timer);
    } else {
        ESP_LOGE(TAG, "digital clock timer have not been replaced!");
    }

    lvgl_port_unlock();
}

void set_location_parameter(lv_ui* ui, const char* location_name)
{
    if(ui == NULL || location_name == NULL) {
        return;
    }

    lvgl_port_lock(0);
    lv_label_set_text(ui->screen_main_label_location, location_name);
    lv_label_set_text(ui->screen_aclock_label_location, location_name);
    lvgl_port_unlock();

}

void set_weather_parameter(lv_ui* ui, Day_Type index, const char* image_path, int low_temperature, int high_temperature)
{
    char temperature_text[32];

    if(ui == NULL || image_path == NULL) {
        return;
    }

    lvgl_port_lock(0);
    switch(index) {
        case DAY_TODAY:
            snprintf(temperature_text, sizeof(temperature_text), "%d-%d℃", low_temperature, high_temperature);
            lv_label_set_text(ui->screen_main_label_temp_today, temperature_text);
            lv_image_set_src(ui->screen_main_img_weather_taday, image_path);

            lv_label_set_text(ui->screen_aclock_label_temp_today, temperature_text);
            lv_image_set_src(ui->screen_aclock_img_weather, image_path);
            break;
        case DAY_TOMORROW:
            snprintf(temperature_text, sizeof(temperature_text), "%d-%d℃", low_temperature, high_temperature);
            lv_label_set_text(ui->screen_main_label_temp_tomorrow, temperature_text);
            lv_image_set_src(ui->screen_main_img_weather_tomorrow, image_path);
            break;
        case DAY_AFTER_TOMORROW:
            snprintf(temperature_text, sizeof(temperature_text), "%d-%d℃", low_temperature, high_temperature);
            lv_label_set_text(ui->screen_main_label_temp_after_tomorrow, temperature_text);
            lv_image_set_src(ui->screen_main_img_weather_after_tomorrow, image_path);
            break;
        default:
            break;
    }
    
    lvgl_port_unlock();
}

void screen_bar_timer(lv_timer_t *timer)
{
    static uint8_t color_index = 0;
    static bool bar_full = true;

    if (lv_obj_is_valid(guider_ui.screen_bar))
    {
        if(color_index == 0) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_white_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_red_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 1) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_red_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_yellow_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 2) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_yellow_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_blue_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 3) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_blue_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_green_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 4) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_green_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_orange_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 5) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_orange_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_black_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else if(color_index == 6) {
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_black_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 0, LV_ANIM_OFF);
            lv_obj_set_style_bg_image_src(guider_ui.screen_bar_bar_logo, &_white_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
            lv_bar_set_value(guider_ui.screen_bar_bar_logo, 100, LV_ANIM_ON);
        } else {
            ;
        }

        // lv_bar_set_value(guider_ui.screen_bar_bar_logo, bar_full? 0 : 100, LV_ANIM_ON);
        // bar_full = !bar_full;

        color_index ++;
        color_index = color_index % 7;
    }
}