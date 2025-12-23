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

    //The custom code of screen_aclock.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_aclock);

    //Init events for screen.
    events_init_screen_aclock(ui);
}
