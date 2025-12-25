#include <string.h>

#include "esp_log.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spiffs.h"

#include "cJSON.h"

#include "weather.h"

#include "wifi_manager.h"

#include "custom.h"

#define TAG "weather"

#define WEATHER_PRIVATE_KEY     "SvVs1aWH49cPKIxCW"
#define WEATHER_LOCATION_CITY   "guangzhou"

#define WEATHER_DATA_BUFF_LEN   (1024)

static uint8_t weather_data_buffer[WEATHER_DATA_BUFF_LEN];
static int16_t weather_data_length = 0;

char location_city_data[32];
char location_ip_data[32];
weather_data_t weather_pasre_data[3];


static void weather_image_spiffs_init(void)
{
    //定义挂载点
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/weather_icon",       //挂载点
        .partition_label = "weather_icon",  //分区名称
        .max_files = 5,                     //最大打开的文件数
        .format_if_mount_failed = false     //挂载失败是否执行格式化
        };
    //挂载spiffs
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));
}

static esp_err_t http_client_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:    //错误事件
            //ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:    //连接成功事件
            //ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:    //发送头事件
            //ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:    //接收头事件
            //ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
            printf("%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:    //接收数据事件
            {
                size_t copy_len = 0;
                ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
                printf("HTTP_EVENT_ON_DATA data=%.*s\r\n", evt->data_len,(char*)evt->data);
                if(evt->data_len > WEATHER_DATA_BUFF_LEN - weather_data_length)
                {
                    copy_len = WEATHER_DATA_BUFF_LEN - weather_data_length;
                }
                else
                {
                    copy_len = evt->data_len;
                }
                memcpy(&weather_data_buffer[weather_data_length],evt->data,copy_len);
                weather_data_length += copy_len;
            }
            break;
        case HTTP_EVENT_ON_FINISH:    //会话完成事件
            weather_data_length = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:    //断开事件
            //ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            weather_data_length = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            //ESP_LOGI(TAG, "HTTP_EVENT_REDIRECT");
            break;
    }
    return ESP_OK;
}

static esp_err_t pasre_weather(char* weather_js)
{
    cJSON *weather_data = cJSON_Parse(weather_js);

    if(weather_data == NULL) {
        ESP_LOGE(TAG, "Received invalid weather JSON.");
        return ESP_FAIL;
    }

    cJSON *results_js = cJSON_GetObjectItem(weather_data, "results");

    if(results_js == NULL) {
        ESP_LOGE(TAG, "Parse weather JSON failed.");
        return ESP_FAIL;
    }

    cJSON *results_child_js = results_js->child;

    cJSON *location_js = cJSON_GetObjectItem(results_child_js, "location");
    if(location_js == NULL) {
        ESP_LOGE(TAG, "Parse weather JSON location failed.");
        return ESP_FAIL;
    } else {
        cJSON *name_js = cJSON_GetObjectItem(location_js, "name");
        if(name_js == NULL) {
            ESP_LOGE(TAG, "Parse weather JSON location name failed.");
            return ESP_FAIL;
        } else {
            char location_city[48];
            snprintf(location_city, sizeof(location_city), "%s", cJSON_GetStringValue(name_js));
            ESP_LOGI(TAG, "weather location city: %s.", location_city);
        }
    }

    cJSON *daily_js = cJSON_GetObjectItem(results_child_js, "daily");

    if(daily_js == NULL) {
        ESP_LOGE(TAG, "Parse weather JSON child failed.");
        return ESP_FAIL;
    } else {
        cJSON *daily_child_js = daily_js->child;

        Day_Type weather_pasre_data_index = DAY_TODAY;

        while(daily_child_js) {
            cJSON *high_temp_js = cJSON_GetObjectItem(daily_child_js, "high");
            cJSON *low_temp_js = cJSON_GetObjectItem(daily_child_js, "low");
            cJSON *code_day_js = cJSON_GetObjectItem(daily_child_js, "code_day");

            if(weather_pasre_data_index < 3) {
                sscanf(cJSON_GetStringValue(high_temp_js), "%d", &(weather_pasre_data[weather_pasre_data_index].high_temperature));
                sscanf(cJSON_GetStringValue(low_temp_js), "%d", &(weather_pasre_data[weather_pasre_data_index].low_temperature));
                snprintf(weather_pasre_data[weather_pasre_data_index].code_day, 4, "%s", cJSON_GetStringValue(code_day_js));

                ESP_LOGI(TAG, "day[%d]: high temperature: %d, low temperature: %d, code day: %s", weather_pasre_data_index, weather_pasre_data[weather_pasre_data_index].high_temperature, weather_pasre_data[weather_pasre_data_index].low_temperature, weather_pasre_data[weather_pasre_data_index].code_day);
            }
            weather_pasre_data_index++;
            daily_child_js = daily_child_js->next;
        }

        char image_path[32];

        snprintf(image_path, sizeof(image_path), "/weather_icon/%s.png", weather_pasre_data[DAY_TODAY].code_day);
        set_weather_parameter(custom_ui, DAY_TODAY, image_path, weather_pasre_data[DAY_TODAY].low_temperature, weather_pasre_data[DAY_TODAY].high_temperature);

        snprintf(image_path, sizeof(image_path), "/weather_icon/%s.png", weather_pasre_data[DAY_TOMORROW].code_day);
        set_weather_parameter(custom_ui, DAY_TOMORROW, image_path, weather_pasre_data[DAY_TOMORROW].low_temperature, weather_pasre_data[DAY_TOMORROW].high_temperature);
        
        snprintf(image_path, sizeof(image_path), "/weather_icon/%s.png", weather_pasre_data[DAY_AFTER_TOMORROW].code_day);
        set_weather_parameter(custom_ui, DAY_AFTER_TOMORROW, image_path, weather_pasre_data[DAY_AFTER_TOMORROW].low_temperature, weather_pasre_data[DAY_AFTER_TOMORROW].high_temperature);
    }

    cJSON_Delete(weather_data);
    return ESP_OK;
}

static esp_err_t weather_http_connect(void)
{
    static char url[256];

    snprintf(url, sizeof(url), "http://api.seniverse.com/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=3", WEATHER_PRIVATE_KEY, location_city_data);

    esp_http_client_config_t config =
    {
        .url = url,
        .event_handler = http_client_event_handler,
    };
    //初始化结构体
    esp_http_client_handle_t http_client = esp_http_client_init(&config);	//initial http connection

    memset(weather_data_buffer, 0, WEATHER_DATA_BUFF_LEN);
    weather_data_length = 0;

    esp_err_t err  = esp_http_client_perform(http_client);

    pasre_weather((char *)weather_data_buffer);

    esp_http_client_cleanup(http_client);
    return err;
}

static esp_err_t pasre_location(char* location_js)
{
    cJSON *location_data = cJSON_Parse(location_js);

    if(location_data == NULL) {
        ESP_LOGE(TAG, "Received invalid location JSON.");
        return ESP_FAIL;
    }

    cJSON *city_js = cJSON_GetObjectItem(location_data, "city");

    if(city_js == NULL) {
        ESP_LOGE(TAG, "Parse location JSON failed.");
        return ESP_FAIL;
    } else {
        snprintf(location_city_data, sizeof(location_city_data), "%s", cJSON_GetStringValue(city_js));
        ESP_LOGI(TAG, "local city: %s", location_city_data);
    }

    set_location_parameter(custom_ui, location_city_data);

    cJSON_Delete(location_data);
    return ESP_OK;
}

static esp_err_t location_http_connect(void)
{
    static char url[256];

    // snprintf(url, sizeof(url), "http://whois.pconline.com.cn/ipJson.jsp?json=true");    //http://ip-api.com/json/?lang=en; https://ipwhois.app/json/?lang=en
    snprintf(url, sizeof(url), "http://ip-api.com/json/%s?lang=en", location_ip_data);

    esp_http_client_config_t config =
    {
        .url = url,
        .event_handler = http_client_event_handler,
    };
    //初始化结构体
    esp_http_client_handle_t http_client = esp_http_client_init(&config);	//initial http connection

    memset(weather_data_buffer, 0, WEATHER_DATA_BUFF_LEN);
    weather_data_length = 0;

    esp_err_t err  = esp_http_client_perform(http_client);

    pasre_location((char *)weather_data_buffer);

    esp_http_client_cleanup(http_client);
    return err;
}

static esp_err_t pasre_IP(char* IP_js)
{
    cJSON *ip_data = cJSON_Parse(IP_js);

    if(ip_data == NULL) {
        ESP_LOGE(TAG, "Received invalid IP JSON.");
        return ESP_FAIL;
    }

    cJSON *ip_js = cJSON_GetObjectItem(ip_data, "ip");

    if(ip_js == NULL) {
        ESP_LOGE(TAG, "Parse IP JSON failed.");
        return ESP_FAIL;
    } else {
        snprintf(location_ip_data, sizeof(location_ip_data), "%s", cJSON_GetStringValue(ip_js));
        ESP_LOGI(TAG, "local IP: %s", location_ip_data);
    }

    cJSON_Delete(ip_data);
    return ESP_OK;
}

static esp_err_t IP_http_connect(void)
{
    static char url[256];

    snprintf(url, sizeof(url), "http://whois.pconline.com.cn/ipJson.jsp?json=true");

    esp_http_client_config_t config =
    {
        .url = url,
        .event_handler = http_client_event_handler,
    };
    //初始化结构体
    esp_http_client_handle_t http_client = esp_http_client_init(&config);	//initial http connection

    memset(weather_data_buffer, 0, WEATHER_DATA_BUFF_LEN);
    weather_data_length = 0;

    esp_err_t err  = esp_http_client_perform(http_client);

    pasre_IP((char *)weather_data_buffer);

    esp_http_client_cleanup(http_client);
    return err;
}

static void weather_task(void *param)
{
    while (1)
    {
        if(!wifi_manager_is_connect()) {
            vTaskDelay(pdTICKS_TO_MS(3000));
        } else {
            ESP_LOGI(TAG, "Try to get location and weather.");
            IP_http_connect();          //get real IP
            location_http_connect();    //get city
            weather_http_connect();     //get weather
            vTaskDelay(pdTICKS_TO_MS(3600 * 1000));
        }
    }
    
}

void weather_start(void)
{
    weather_image_spiffs_init();
    xTaskCreatePinnedToCore(weather_task, "weather", 4096, NULL, 2, NULL, 1);
}