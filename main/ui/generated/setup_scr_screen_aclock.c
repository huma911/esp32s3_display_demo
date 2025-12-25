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



void setup_scr_screen_aclock(lv_ui *ui)
{
    //Write codes screen_aclock
    ui->screen_aclock = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_aclock, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen_aclock, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_aclock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_aclock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_aclock, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_aclock, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->screen_aclock, &_clock_bg_img_RGB565A8_480x320, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->screen_aclock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->screen_aclock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_img_second
    ui->screen_aclock_img_second = lv_image_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_img_second, 230, 41);
    lv_obj_set_size(ui->screen_aclock_img_second, 20, 135);
    lv_obj_add_flag(ui->screen_aclock_img_second, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_aclock_img_second, &_img_clockwise_sec_RGB565A8_20x135);
    lv_image_set_pivot(ui->screen_aclock_img_second, 10,115);
    lv_image_set_rotation(ui->screen_aclock_img_second, 0);

    //Write style for screen_aclock_img_second, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_aclock_img_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_aclock_img_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_img_hour
    ui->screen_aclock_img_hour = lv_image_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_img_hour, 233, 57);
    lv_obj_set_size(ui->screen_aclock_img_hour, 15, 100);
    lv_obj_add_flag(ui->screen_aclock_img_hour, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_aclock_img_hour, &_img_clockwise_hour_RGB565A8_15x100);
    lv_image_set_pivot(ui->screen_aclock_img_hour, 8,100);
    lv_image_set_rotation(ui->screen_aclock_img_hour, 0);

    //Write style for screen_aclock_img_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_aclock_img_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_aclock_img_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_img_minute
    ui->screen_aclock_img_minute = lv_image_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_img_minute, 233, 37);
    lv_obj_set_size(ui->screen_aclock_img_minute, 15, 120);
    lv_obj_add_flag(ui->screen_aclock_img_minute, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_aclock_img_minute, &_img_clockwise_min_RGB565A8_15x120);
    lv_image_set_pivot(ui->screen_aclock_img_minute, 8,120);
    lv_image_set_rotation(ui->screen_aclock_img_minute, 0);

    //Write style for screen_aclock_img_minute, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_aclock_img_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_aclock_img_minute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_label_location
    ui->screen_aclock_label_location = lv_label_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_label_location, 300, 110);
    lv_obj_set_size(ui->screen_aclock_label_location, 115, 22);
    lv_label_set_text(ui->screen_aclock_label_location, "Unknown");
    lv_label_set_long_mode(ui->screen_aclock_label_location, LV_LABEL_LONG_WRAP);

    //Write style for screen_aclock_label_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_aclock_label_location, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_aclock_label_location, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_aclock_label_location, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_aclock_label_location, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_aclock_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_label_date
    ui->screen_aclock_label_date = lv_label_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_label_date, 65, 110);
    lv_obj_set_size(ui->screen_aclock_label_date, 118, 25);
    lv_label_set_text(ui->screen_aclock_label_date, "00/00/0000");
    lv_label_set_long_mode(ui->screen_aclock_label_date, LV_LABEL_LONG_WRAP);

    //Write style for screen_aclock_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_aclock_label_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_aclock_label_date, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_aclock_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_aclock_label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_aclock_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_label_week
    ui->screen_aclock_label_week = lv_label_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_label_week, 65, 145);
    lv_obj_set_size(ui->screen_aclock_label_week, 118, 22);
    lv_label_set_text(ui->screen_aclock_label_week, "Weekday");
    lv_label_set_long_mode(ui->screen_aclock_label_week, LV_LABEL_LONG_WRAP);

    //Write style for screen_aclock_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_aclock_label_week, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_aclock_label_week, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_aclock_label_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_aclock_label_week, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_aclock_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_img_weather
    ui->screen_aclock_img_weather = lv_image_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_img_weather, 360, 130);
    lv_obj_set_size(ui->screen_aclock_img_weather, 48, 48);
    lv_obj_add_flag(ui->screen_aclock_img_weather, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_aclock_img_weather, &_99_RGB565A8_48x48);
    lv_image_set_pivot(ui->screen_aclock_img_weather, 50,50);
    lv_image_set_rotation(ui->screen_aclock_img_weather, 0);

    //Write style for screen_aclock_img_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_aclock_img_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_aclock_img_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_aclock_label_temp_today
    ui->screen_aclock_label_temp_today = lv_label_create(ui->screen_aclock);
    lv_obj_set_pos(ui->screen_aclock_label_temp_today, 315, 175);
    lv_obj_set_size(ui->screen_aclock_label_temp_today, 112, 24);
    lv_label_set_text(ui->screen_aclock_label_temp_today, "0-100℃");
    lv_label_set_long_mode(ui->screen_aclock_label_temp_today, LV_LABEL_LONG_WRAP);

    //Write style for screen_aclock_label_temp_today, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_aclock_label_temp_today, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_aclock_label_temp_today, &lv_font_ZiTiQuanWeiJunHeiW22_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_aclock_label_temp_today, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_aclock_label_temp_today, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_aclock_label_temp_today, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_aclock.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_aclock);

    //Init events for screen.
    events_init_screen_aclock(ui);
}
