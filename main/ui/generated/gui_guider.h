/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_digital_clock_main;
	lv_obj_t *screen_main_label_date;
	lv_obj_t *screen_main_label_week;
	lv_obj_t *screen_main_label_location;
	lv_obj_t *screen_main_label_today;
	lv_obj_t *screen_main_label_tomorrow;
	lv_obj_t *screen_main_label_after_tomorrow;
	lv_obj_t *screen_main_label_temp_today;
	lv_obj_t *screen_main_label_temp_tomorrow;
	lv_obj_t *screen_main_label_temp_after_tomorrow;
	lv_obj_t *screen_main_img_wifi;
	lv_obj_t *screen_main_img_line;
	lv_obj_t *screen_main_img_weather_taday;
	lv_obj_t *screen_main_img_weather_tomorrow;
	lv_obj_t *screen_main_img_weather_after_tomorrow;
	lv_obj_t *screen_aclock;
	bool screen_aclock_del;
	lv_obj_t *screen_aclock_img_second;
	lv_obj_t *screen_aclock_img_hour;
	lv_obj_t *screen_aclock_img_minute;
	lv_obj_t *screen_aclock_label_location;
	lv_obj_t *screen_aclock_label_date;
	lv_obj_t *screen_aclock_label_week;
	lv_obj_t *screen_aclock_img_weather;
	lv_obj_t *screen_aclock_label_temp_today;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_main(lv_ui *ui);
void setup_scr_screen_aclock(lv_ui *ui);
LV_IMAGE_DECLARE(_wifi_RGB565A8_32x32);
LV_IMAGE_DECLARE(_line_RGB565A8_429x21);
LV_IMAGE_DECLARE(_99_RGB565A8_64x64);

LV_IMAGE_DECLARE(_clock_bg_img_RGB565A8_480x320);
LV_IMAGE_DECLARE(_img_clockwise_sec_RGB565A8_20x135);
LV_IMAGE_DECLARE(_img_clockwise_hour_RGB565A8_15x100);
LV_IMAGE_DECLARE(_img_clockwise_min_RGB565A8_15x120);
LV_IMAGE_DECLARE(_99_RGB565A8_48x48);

LV_FONT_DECLARE(lv_font_ZiTiQuanWeiJunHeiW22_80)
LV_FONT_DECLARE(lv_font_ZiTiQuanWeiJunHeiW22_20)


#ifdef __cplusplus
}
#endif
#endif
