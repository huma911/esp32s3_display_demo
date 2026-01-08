#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "esp_err.h"

#include "driver/gpio.h"

//button callback
typedef void(*button_press_cb_t)(gpio_num_t gpio);

//get level
typedef int(*button_getleve_cb_t)(gpio_num_t gpio);

//button configuration struct
typedef struct
{
    int gpio_num;                       // GPIO NUM
    int active_level;                   // Active Level
    int long_press_time;                // Long press time
    button_getleve_cb_t getlevel_cb;    // get level callback
    button_press_cb_t short_cb;         // short press callback
    button_press_cb_t long_cb;          // long press call back
}my_button_config_t;

/** Config the button event
 * @param cfg   button configuration struct
 * @return ESP_OK or ESP_FAIL 
*/
esp_err_t button_event_set(my_button_config_t *cfg);


#endif
