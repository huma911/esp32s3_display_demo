/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int screen_main_digital_clock_main_min_value = 59;
int screen_main_digital_clock_main_hour_value = 23;
int screen_main_digital_clock_main_sec_value = 0;
void setup_scr_screen_main(lv_ui *ui)
{
    //Write codes screen_main
    ui->screen_main = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_main, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_digital_clock_main
    static bool screen_main_digital_clock_main_timer_enabled = false;
    ui->screen_main_digital_clock_main = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_digital_clock_main, 33, 35);
    lv_obj_set_size(ui->screen_main_digital_clock_main, 329, 90);
    lv_label_set_text(ui->screen_main_digital_clock_main, "23:59:00");
    if (!screen_main_digital_clock_main_timer_enabled) {
        digital_clock_timer = lv_timer_create(screen_main_digital_clock_main_timer, 1000, NULL);
        screen_main_digital_clock_main_timer_enabled = true;
    }

    //Write style for screen_main_digital_clock_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_digital_clock_main, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_digital_clock_main, &lv_font_ZiTiQuanWeiJunHeiW22_80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_digital_clock_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_digital_clock_main, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_digital_clock_main, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_digital_clock_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_date
    ui->screen_main_label_date = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_date, 360, 55);
    lv_obj_set_size(ui->screen_main_label_date, 118, 25);
    lv_label_set_text(ui->screen_main_label_date, "00/00/0000");
    lv_label_set_long_mode(ui->screen_main_label_date, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_date, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_date, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_week
    ui->screen_main_label_week = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_week, 350, 90);
    lv_obj_set_size(ui->screen_main_label_week, 118, 22);
    lv_label_set_text(ui->screen_main_label_week, "Weekday");
    lv_label_set_long_mode(ui->screen_main_label_week, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_week, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_week, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_week, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_location
    ui->screen_main_label_location = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_location, 360, 5);
    lv_obj_set_size(ui->screen_main_label_location, 115, 22);
    lv_label_set_text(ui->screen_main_label_location, "Unknown");
    lv_label_set_long_mode(ui->screen_main_label_location, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_location, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_location, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_location, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_location, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_today
    ui->screen_main_label_today = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_today, 33, 186);
    lv_obj_set_size(ui->screen_main_label_today, 112, 24);
    lv_label_set_text(ui->screen_main_label_today, "Today");
    lv_label_set_long_mode(ui->screen_main_label_today, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_today, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_today, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_today, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_tomorrow
    ui->screen_main_label_tomorrow = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_tomorrow, 180, 186);
    lv_obj_set_size(ui->screen_main_label_tomorrow, 112, 24);
    lv_label_set_text(ui->screen_main_label_tomorrow, "Friday");
    lv_label_set_long_mode(ui->screen_main_label_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_after_tomorrow
    ui->screen_main_label_after_tomorrow = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_after_tomorrow, 333, 186);
    lv_obj_set_size(ui->screen_main_label_after_tomorrow, 112, 24);
    lv_label_set_text(ui->screen_main_label_after_tomorrow, "Saturday");
    lv_label_set_long_mode(ui->screen_main_label_after_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_after_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_after_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_after_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_after_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_after_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_temp_today
    ui->screen_main_label_temp_today = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_temp_today, 33, 283);
    lv_obj_set_size(ui->screen_main_label_temp_today, 112, 24);
    lv_label_set_text(ui->screen_main_label_temp_today, "10-15℃");
    lv_label_set_long_mode(ui->screen_main_label_temp_today, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_temp_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_temp_today, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_temp_today, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_temp_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_temp_today, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_temp_tomorrow
    ui->screen_main_label_temp_tomorrow = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_temp_tomorrow, 180, 283);
    lv_obj_set_size(ui->screen_main_label_temp_tomorrow, 112, 24);
    lv_label_set_text(ui->screen_main_label_temp_tomorrow, "8-14℃");
    lv_label_set_long_mode(ui->screen_main_label_temp_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_temp_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_temp_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_temp_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_temp_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_temp_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_temp_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_temp_after_tomorrow
    ui->screen_main_label_temp_after_tomorrow = lv_label_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_label_temp_after_tomorrow, 333, 283);
    lv_obj_set_size(ui->screen_main_label_temp_after_tomorrow, 112, 24);
    lv_label_set_text(ui->screen_main_label_temp_after_tomorrow, "5-10℃");
    lv_label_set_long_mode(ui->screen_main_label_temp_after_tomorrow, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_temp_after_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_temp_after_tomorrow, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_temp_after_tomorrow, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_temp_after_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_temp_after_tomorrow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_temp_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_wifi
    ui->screen_main_img_wifi = lv_image_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_img_wifi, 5, 5);
    lv_obj_set_size(ui->screen_main_img_wifi, 32, 32);
    lv_obj_add_flag(ui->screen_main_img_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_wifi, &_wifi_RGB565A8_32x32);
    lv_image_set_pivot(ui->screen_main_img_wifi, 50,50);
    lv_image_set_rotation(ui->screen_main_img_wifi, 0);

    //Write style for screen_main_img_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_line
    ui->screen_main_img_line = lv_image_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_img_line, 22, 137);
    lv_obj_set_size(ui->screen_main_img_line, 429, 21);
    lv_obj_add_flag(ui->screen_main_img_line, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_line, &_line_RGB565A8_429x21);
    lv_image_set_pivot(ui->screen_main_img_line, 50,50);
    lv_image_set_rotation(ui->screen_main_img_line, 0);

    //Write style for screen_main_img_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_line, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_weather_taday
    ui->screen_main_img_weather_taday = lv_image_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_img_weather_taday, 60, 210);
    lv_obj_set_size(ui->screen_main_img_weather_taday, 64, 58);
    lv_obj_add_flag(ui->screen_main_img_weather_taday, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_weather_taday, &_sun_RGB565A8_64x58);
    lv_image_set_pivot(ui->screen_main_img_weather_taday, 50,50);
    lv_image_set_rotation(ui->screen_main_img_weather_taday, 0);

    //Write style for screen_main_img_weather_taday, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_weather_taday, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_weather_taday, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_weather_tomorrow
    ui->screen_main_img_weather_tomorrow = lv_image_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_img_weather_tomorrow, 202, 210);
    lv_obj_set_size(ui->screen_main_img_weather_tomorrow, 64, 58);
    lv_obj_add_flag(ui->screen_main_img_weather_tomorrow, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_weather_tomorrow, &_cloudy_RGB565A8_64x58);
    lv_image_set_pivot(ui->screen_main_img_weather_tomorrow, 50,50);
    lv_image_set_rotation(ui->screen_main_img_weather_tomorrow, 0);

    //Write style for screen_main_img_weather_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_weather_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_weather_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_weather_after_tomorrow
    ui->screen_main_img_weather_after_tomorrow = lv_image_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_img_weather_after_tomorrow, 356, 210);
    lv_obj_set_size(ui->screen_main_img_weather_after_tomorrow, 64, 58);
    lv_obj_add_flag(ui->screen_main_img_weather_after_tomorrow, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_weather_after_tomorrow, &_rain_RGB565A8_64x58);
    lv_image_set_pivot(ui->screen_main_img_weather_after_tomorrow, 50,50);
    lv_image_set_rotation(ui->screen_main_img_weather_after_tomorrow, 0);

    //Write style for screen_main_img_weather_after_tomorrow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_weather_after_tomorrow, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_weather_after_tomorrow, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_main);

    //Init events for screen.
    events_init_screen_main(ui);
}
