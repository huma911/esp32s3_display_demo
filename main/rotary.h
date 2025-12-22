#ifndef _ROTARY_ENCODER_SWITCH_H_
#define _ROTARY_ENCODER_SWITCH_H_

#include "driver/gpio.h"

#include "button.h"

typedef enum {
    ROTARY_DIRECTION_CCW     = -1,
    ROTARY_DIRECTION_INVALID = 0,
    ROTARY_DIRECTION_CW      = 1,
} rotary_direction_t;

// Event type define
typedef enum {
    ROTARY_A_TRIGGER,
} rotary_event_type_t;

// Event data struct
typedef struct {
    rotary_event_type_t type;       // event type
    gpio_num_t trigger_gpio_value;  // trigger GPIO value
    gpio_num_t another_gpio_value;  // another GPIO value
    uint32_t timestamp;             // timestamp
} rotary_event_t;

// Ratory gpio define
typedef struct {
    gpio_num_t trigger_gpio_num;    // trigger GPIO num
    gpio_num_t another_gpio_num;    // another GPIO num
} rotary_gpio_num_t;

typedef struct {
    union
    {
        struct
        {
            uint8_t current_another_gpio        : 1,
                    current_trigger_gpio        : 1,
                    last_another_gpio           : 1,
                    last_trigger_gpio           : 1,
                    reserved                    : 4;
        };
        uint8_t     rotary_gpio_status;
    };
} rotary_gpio_state_t;

typedef void (*rotary_trigger_cb_t)(int8_t rotary_value);

typedef struct {
    rotary_gpio_num_t rotary_gpio_cfg;
    rotary_trigger_cb_t rotary_cb;

    button_config_t button_cfg;
} rotary_cfg_t;

typedef struct {
    void* rotary_event_queue;
    
    rotary_gpio_num_t gpio_num;
    rotary_event_t gpio_trigger_event;
    rotary_gpio_state_t gpio_state;
    uint32_t last_timestamp;
    rotary_direction_t  last_direction;

    rotary_trigger_cb_t rotary_cb;

    button_config_t button_config;
} rotary_data_t;

void rotary_init(rotary_cfg_t* rotary_cfg);
void rotary_start_task(void);

// extern rotary_data_t rotary_data;

#endif