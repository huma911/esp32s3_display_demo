#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "rotary.h"

#define TAG "rotary_encoder_switch"

/****************************************************
 * Rotary Encoder Switch
 * CW
 * A phase: ___|‾‾‾‾|____|‾‾‾‾|____
 * B phase: ______|‾‾‾‾|____|‾‾‾‾|____
 * 
 * CCW
 * A phase: ______|‾‾‾‾|____|‾‾‾‾|____
 * B phase: ___|‾‾‾‾|____|‾‾‾‾|____|‾‾‾‾
****************************************************/

static const int8_t transition_table[16] = {    // value: +1 = CW, -1 = CCW, 0 = invalid
    // last status  << 2 | current_status
    // 0: 00→00, 1: 00→01, 2: 00→10, 3: 00→11
    0,  0,  1, -1,
    // 4: 01→00, 5: 01→01, 6: 01→10, 7: 01→11
    0,  0,  1, -1,
    // 8: 10→00, 9: 10→01, A: 10→10, B: 10→11
    -1, 1,  0,  0,
    // C: 11→00, D: 11→01, E: 11→10, F: 11→11
    -1, 1,  0,  0,
};

static rotary_data_t rotary_data;

static void rotary_gpio_trigger_isr_handler(void *arg)
{
    BaseType_t high_task_awoken                       = pdFALSE;

    rotary_data.gpio_trigger_event.timestamp          = xTaskGetTickCountFromISR();
    rotary_data.gpio_trigger_event.trigger_gpio_value = gpio_get_level(((rotary_gpio_num_t*)(arg))->trigger_gpio_num);
    rotary_data.gpio_trigger_event.another_gpio_value = gpio_get_level(((rotary_gpio_num_t*)(arg))->another_gpio_num);
    
    xQueueSendFromISR((QueueHandle_t)(rotary_data.rotary_event_queue), &(rotary_data.gpio_trigger_event), &high_task_awoken);
    portYIELD_FROM_ISR(high_task_awoken);
}

static void button_init(my_button_config_t* button_cfg)
{
    button_event_set(button_cfg);
}

void rotary_init(rotary_cfg_t* rotary_cfg)
{
    //0. event & data initial
    rotary_data.gpio_trigger_event.type   = ROTARY_A_TRIGGER;
    rotary_data.gpio_num.trigger_gpio_num = rotary_cfg->rotary_gpio_cfg.trigger_gpio_num;
    rotary_data.gpio_num.another_gpio_num = rotary_cfg->rotary_gpio_cfg.another_gpio_num;
    rotary_data.rotary_cb                 = rotary_cfg->rotary_cb;

    //1. gpio initial
    gpio_config_t rotary_gpio_a_cfg = {
        .intr_type    = GPIO_INTR_ANYEDGE,
        .mode         = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ull << rotary_cfg->rotary_gpio_cfg.trigger_gpio_num,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
    };

    gpio_config_t rotary_gpio_b_cfg = {
        .intr_type    = GPIO_INTR_DISABLE,
        .mode         = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ull << rotary_cfg->rotary_gpio_cfg.another_gpio_num,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&rotary_gpio_a_cfg);
    gpio_config(&rotary_gpio_b_cfg);

    //2. register the isr
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    //3. bind gpio and isr
    gpio_isr_handler_add(rotary_cfg->rotary_gpio_cfg.trigger_gpio_num, rotary_gpio_trigger_isr_handler, (void*)(&(rotary_data.gpio_num)));

    //4. enable interrupt
    gpio_intr_enable(rotary_cfg->rotary_gpio_cfg.trigger_gpio_num);

    rotary_data.gpio_state.last_trigger_gpio = gpio_get_level(rotary_cfg->rotary_gpio_cfg.trigger_gpio_num);
    rotary_data.gpio_state.last_another_gpio = gpio_get_level(rotary_cfg->rotary_gpio_cfg.another_gpio_num);

    //5. button init
    button_init(&(rotary_cfg->button_cfg));
}

static void rotary_event_task(void *pvParameters)
{
    static rotary_event_t event;
    
    while (1) {
        if (xQueueReceive((QueueHandle_t)(rotary_data.rotary_event_queue), &event, portMAX_DELAY) == pdPASS) {

            if (event.type == ROTARY_A_TRIGGER) {
                // ESP_LOGE(TAG, "time %lu", event.timestamp - rotary_data.last_timestamp);
                if(event.timestamp - rotary_data.last_timestamp <= 5) {
                    continue;
                }
                rotary_data.gpio_state.current_trigger_gpio = event.trigger_gpio_value;
                rotary_data.gpio_state.current_another_gpio = event.another_gpio_value;
                rotary_data.last_timestamp = event.timestamp;
            } else {
                ESP_LOGE(TAG, "Event error");
                continue;
            }

            uint8_t transition = ((rotary_data.gpio_state.last_trigger_gpio) << 3)
                                 | ((rotary_data.gpio_state.last_another_gpio) << 2)
                                 | ((rotary_data.gpio_state.current_trigger_gpio) << 1)
                                 | (rotary_data.gpio_state.current_another_gpio);

            int8_t direction = transition_table[transition];

            if(direction != 0) {
                // ESP_LOGI(TAG, "direction: %d", direction);
                if(rotary_data.rotary_cb != NULL) {
                    rotary_data.rotary_cb(direction);
                }
            }
                

            // rotary_data.last_state     = current_state;
            rotary_data.gpio_state.last_trigger_gpio = rotary_data.gpio_state.current_trigger_gpio;
            rotary_data.gpio_state.last_another_gpio = rotary_data.gpio_state.current_another_gpio;
            rotary_data.last_direction = direction;
        }
    }
}

void rotary_start_task(void)
{
    // creat rotary queue
    rotary_data.rotary_event_queue = xQueueCreate(16, sizeof(rotary_event_t));
    if (rotary_data.rotary_event_queue == NULL) {
        ESP_LOGE(TAG, "queue creat failed");
        return;
    }
    
    // creat task
    xTaskCreatePinnedToCore(rotary_event_task, "rotary_task", 4096, NULL, 10, NULL, 0);
    ESP_LOGI(TAG, "rotary encoder switch task start");
}