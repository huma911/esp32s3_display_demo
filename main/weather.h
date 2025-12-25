#ifndef _WEATHER_H_
#define _WEATHER_H_

typedef struct
{
    int high_temperature;
    int low_temperature;
    char code_day[4];
} weather_data_t;

void weather_start(void);

extern char location_city_data[32];
extern char location_ip_data[32];
extern weather_data_t weather_pasre_data[3];

#endif