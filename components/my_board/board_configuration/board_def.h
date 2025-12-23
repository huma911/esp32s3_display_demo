/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2021 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _CUSTOMER_BOARD_DEFINITION_H_
#define _CUSTOMER_BOARD_DEFINITION_H_

/**
 * @brief LED Function Definition
 */
#define GREEN_LED_GPIO              (-1)
#define BLUE_LED_GPIO               (-1)
#define RED_LED_GPIO                (-1)

/**
 * @brief Rotary Encoder Switch Function Definition
 */
#define ROTARY_ES_A_GPIO            (GPIO_NUM_1)
#define ROTARY_ES_B_GPIO            (GPIO_NUM_2)
#define ROTARY_BUTTON_GPIO          (GPIO_NUM_45)


/**
 * @brief LCD Screen Function Definition
 */
#if defined(CONFIG_CUSTOMER_BOARD_DISPLAY_ST7796)
#define FUNC_LCD_SCREEN_EN          (1)
#define LCD_GPIO_BL                 (GPIO_NUM_13)
#define LCD_GPIO_RST                (GPIO_NUM_8)
#define LCD_GPIO_CS                 (GPIO_NUM_12)
// LCD SPI Pins
#define LCD_GPIO_DC                 (GPIO_NUM_11)
#define LCD_GPIO_CLK                (GPIO_NUM_10)
#define LCD_GPIO_MOSI               (GPIO_NUM_18)
#define LCD_GPIO_MISO               (GPIO_NUM_NC)
// LCD I80 Pins
#define LCD_GPIO_DCX                (GPIO_NUM_11)
#define LCD_GPIO_WR                 (GPIO_NUM_10)
#define LCD_GPIO_D0                 (GPIO_NUM_18)
#define LCD_GPIO_D1                 (GPIO_NUM_17)
#define LCD_GPIO_D2                 (GPIO_NUM_16)
#define LCD_GPIO_D3                 (GPIO_NUM_15)
#define LCD_GPIO_D4                 (GPIO_NUM_7)
#define LCD_GPIO_D5                 (GPIO_NUM_6)
#define LCD_GPIO_D6                 (GPIO_NUM_5)
#define LCD_GPIO_D7                 (GPIO_NUM_4)
// The LCD pixel number in horizontal and vertical
#define LCD_H_RES                   (480)   //number of horizontal pixels
#define LCD_V_RES                   (320)   //number of vertical pixels
#define LCD_SWAP_XY                 (true)
#define LCD_MIRROR_X                (false)
#define LCD_MIRROR_Y                (false)
#define LCD_COLOR_INV               (true)
#elif defined(CONFIG_CUSTOMER_BOARD_DISPLAY_ST7789)
#define FUNC_LCD_SCREEN_EN          (1)
#define LCD_GPIO_BL                 (GPIO_NUM_13)
#define LCD_GPIO_RST                (GPIO_NUM_8)
#define LCD_GPIO_CS                 (GPIO_NUM_12)
// LCD SPI Pins
#define LCD_GPIO_DC                 (GPIO_NUM_10)
#define LCD_GPIO_CLK                (GPIO_NUM_11)
#define LCD_GPIO_MOSI               (GPIO_NUM_18)
#define LCD_GPIO_MISO               (GPIO_NUM_NC)
// LCD I80 Pins
#define LCD_GPIO_DCX                (GPIO_NUM_11)
#define LCD_GPIO_WR                 (GPIO_NUM_10)
#define LCD_GPIO_D0                 (GPIO_NUM_18)
#define LCD_GPIO_D1                 (GPIO_NUM_17)
#define LCD_GPIO_D2                 (GPIO_NUM_16)
#define LCD_GPIO_D3                 (GPIO_NUM_15)
#define LCD_GPIO_D4                 (GPIO_NUM_7)
#define LCD_GPIO_D5                 (GPIO_NUM_6)
#define LCD_GPIO_D6                 (GPIO_NUM_5)
#define LCD_GPIO_D7                 (GPIO_NUM_4)
// The LCD pixel number in horizontal and vertical
#define LCD_H_RES                   (320)   //number of horizontal pixels
#define LCD_V_RES                   (240)   //number of vertical pixels
#define LCD_SWAP_XY                 (true)
#define LCD_MIRROR_X                (true)
#define LCD_MIRROR_Y                (false)
#define LCD_COLOR_INV               (false)
#else
#endif

#endif
