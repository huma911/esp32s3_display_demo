/*
* Copyright 2026 NXP
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



void setup_scr_screen_bar(lv_ui *ui)
{
    //Write codes screen_bar
    ui->screen_bar = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_bar, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_bar_bar_logo
    ui->screen_bar_bar_logo = lv_bar_create(ui->screen_bar);
    lv_obj_set_pos(ui->screen_bar_bar_logo, 125, 135);
    lv_obj_set_size(ui->screen_bar_bar_logo, 240, 47);
    lv_obj_set_style_anim_duration(ui->screen_bar_bar_logo, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_bar_logo, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_bar_logo, 0, 100);
    lv_bar_set_value(ui->screen_bar_bar_logo, 100, LV_ANIM_ON);

    //Write style for screen_bar_bar_logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_bar_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_bar_logo, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_bar_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->screen_bar_bar_logo, &_black_RGB565A8_240x47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->screen_bar_bar_logo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->screen_bar_bar_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_bar_bar_logo, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_bar_logo, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_bar_logo, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(ui->screen_bar_bar_logo, &_white_RGB565A8_240x47, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui->screen_bar_bar_logo, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui->screen_bar_bar_logo, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //The custom code of screen_bar.
    static bool screen_bar_timer_enabled = false;
    if (!screen_bar_timer_enabled) {
        lv_timer_create(screen_bar_timer, 1000, NULL);
        screen_bar_timer_enabled = true;
    }

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_bar);

    //Init events for screen.
    events_init_screen_bar(ui);
}
