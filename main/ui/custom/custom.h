/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    uint8_t week;
} date_value_t;

typedef enum {
    DAY_TODAY = 0,
    DAY_TOMORROW,
    DAY_AFTER_TOMORROW,
    DAY_DAY_NUM,
} Day_Type;
typedef enum {
    WEEK_SUNDAY = 0,
    WEEK_MONDAY,
    WEEK_TUESDAY,
    WEEK_WEDNESDAY,
    WEEK_THURSDAY,
    WEEK_FRIDAY,
    WEEK_SATURDAY,
    WEEK_DAY_NUM,
} Week_Type;

typedef struct {
    Week_Type       week;
    const char      *value;
} Week_Entry;

void custom_init(lv_ui *ui);

void set_home_time(lv_ui* ui, date_value_t* date_value);

void set_location_parameter(lv_ui* ui, const char* location_name);
void set_weather_parameter(lv_ui* ui, Day_Type index, const char* image_path, int low_temperature, int high_temperature);

extern lv_timer_t* digital_clock_timer;

extern lv_ui* custom_ui;

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
