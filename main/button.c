#include "button.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <stdio.h>
#include <string.h>

static const char* TAG = "button";

typedef enum
{
    BUTTON_RELEASE,             //button not pressed
    BUTTON_PRESS,               //button pressed, wait time for debounce, trigger short press callback，enter button hold
    BUTTON_HOLD,                //button hold, if hold time more than long press time, trigger long press callback, enter button long press hold
    BUTTON_LONG_PRESS_HOLD,     //button long press hold, waiting release(active level disappear), back to button release
}BUTTON_STATE;

typedef struct Button
{
    button_config_t btn_cfg;    //button configuration
    BUTTON_STATE    state;      //current status
    int press_cnt;              //press count
    struct Button* next;        //next button parameters
}button_dev_t;

//button list
static button_dev_t *s_button_head = NULL;

//debounce time
#define FILITER_TIMER   (20)

//timer flag
static bool g_is_timer_running = false;

//timer period
#define TIMER_BUTTON_PERIOD_US      (5000)
#define TIMER_BUTTON_PERIOD_MS      (5)

//timer handler
static esp_timer_handle_t g_button_timer_handle;

static void button_handle(void *param);

/** Config the button event
 * @param cfg   button configuration struct
 * @return ESP_OK or ESP_FAIL 
*/
esp_err_t button_event_set(button_config_t *cfg)
{
    button_dev_t* btn = (button_dev_t*)malloc(sizeof(button_dev_t));
    if(!btn)
        return ESP_FAIL;
    memset(btn,0,sizeof(button_dev_t));
    if(!s_button_head)
    {
        s_button_head = btn;
    }
    else
    {
        button_dev_t* btn_p = s_button_head;
        while(btn_p->next != NULL)
            btn_p = btn_p->next;
        btn_p->next = btn;
    }
    memcpy(&btn->btn_cfg,cfg,sizeof(button_config_t));

    if (g_is_timer_running == false) {
        static int timer_interval = TIMER_BUTTON_PERIOD_MS;
        esp_timer_create_args_t button_timer;
        button_timer.arg = (void*)timer_interval;
        button_timer.callback = button_handle;
        button_timer.dispatch_method = ESP_TIMER_TASK;
        button_timer.name = "button_handle";
        esp_timer_create(&button_timer, &g_button_timer_handle);
        esp_timer_start_periodic(g_button_timer_handle, TIMER_BUTTON_PERIOD_US);
        g_is_timer_running = true;
    }

    return ESP_OK;
}

/** timer callback
 * @param param   timer period
 * @return ESP_OK or ESP_FAIL 
*/
static void button_handle(void *param)
{
    int increase_cnt = (int)param;  //period
    button_dev_t* btn_target = s_button_head;

    //traverse list
    for(;btn_target;btn_target = btn_target->next)
    {
        int gpio_num = btn_target->btn_cfg.gpio_num;
        if(!btn_target->btn_cfg.getlevel_cb)
            continue;

        switch(btn_target->state)
        {
            case BUTTON_RELEASE:             //button not pressed
                if(btn_target->btn_cfg.getlevel_cb(gpio_num) == btn_target->btn_cfg.active_level)
                {
                    btn_target->press_cnt += increase_cnt;
                    btn_target->state = BUTTON_PRESS;   //enter button press status
                }
                break;
            case BUTTON_PRESS:               //button pressed, wait time for debounce, trigger short press callback，enter button hold
                if(btn_target->btn_cfg.getlevel_cb(gpio_num) == btn_target->btn_cfg.active_level)
                {
                    btn_target->press_cnt += increase_cnt;
                    if(btn_target->press_cnt >= FILITER_TIMER)      //debounce，then call the short press callback
                    {
                        // not trigger short press at this stage
                        // if(btn_target->btn_cfg.short_cb)
                        //     btn_target->btn_cfg.short_cb(gpio_num);
                        btn_target->state = BUTTON_HOLD;            //enter button hold status
                    }
                }
                else
                {
                    btn_target->state = BUTTON_RELEASE;
                    btn_target->press_cnt = 0;
                }
                break;
            case BUTTON_HOLD:                //button hold, if hold time more than long press time, trigger long press callback, enter button long press hold
                if(btn_target->btn_cfg.getlevel_cb(gpio_num) == btn_target->btn_cfg.active_level)
                {
                    btn_target->press_cnt += increase_cnt;
                    if(btn_target->press_cnt >= btn_target->btn_cfg.long_press_time)  //press time more than long press time, trigger long press callback
                    {
                        if(btn_target->btn_cfg.long_cb)
                            btn_target->btn_cfg.long_cb(gpio_num);
                        btn_target->state = BUTTON_LONG_PRESS_HOLD;     //enter button long press hold
                    }
                }
                else
                {
                    //trigger short press at this stage
                    if(btn_target->btn_cfg.short_cb)
                            btn_target->btn_cfg.short_cb(gpio_num);

                    btn_target->state = BUTTON_RELEASE;
                    btn_target->press_cnt = 0;
                }
                break;
            case BUTTON_LONG_PRESS_HOLD:     //waiting release(active level disappear), back to button release
                if(btn_target->btn_cfg.getlevel_cb(gpio_num) != btn_target->btn_cfg.active_level)    //active level disappear, back to button release
                {
                    btn_target->state = BUTTON_RELEASE;
                    btn_target->press_cnt = 0;
                }
                break;
            default:break;
        }
    }
}
