/* main.c - Application main entry point */

/*
 * Copyright (c) 2017 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "TimeLib.h"
#include "StandardLib.h"
#include "TimerSettings.h"
#include "StandardLibObserved.h"
#include "UtilLib.h"
#include "ExtraLib.h"
#include "BasicLib.h"
#include "Automation_FOUR_POSITION.h"
#include "AutomationTimer_FOUR_POSITION.h"

#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"


const char *TIMER_2 = "timer_2";
const char *TIMER_1 = "timer_1";

static const char * const TAG = "impulse_switch";
static int I1 = 0;
static int I2 = 0;
static int I3 = 0;

#define BUTTON_I1 GPIO_NUM_26		// Pin 26.
#define BUTTON_I2 GPIO_NUM_32		// Pin 32.
#define BUTTON_I3 GPIO_NUM_39		// Pin 39.
#define GPIO_Q1 GPIO_NUM_19
#define GPIO_Q2 GPIO_NUM_23
#define GPIO_Q3 GPIO_NUM_33
#define GPIO_Q4 GPIO_NUM_25






/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{



    ESP_LOGI(TAG, "Initializing...");

    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_reset_pin(GPIO_Q1);
    gpio_reset_pin(GPIO_Q2);
    gpio_reset_pin(GPIO_Q3);
    gpio_reset_pin(GPIO_Q4);
    gpio_reset_pin(BUTTON_I1);
    gpio_reset_pin(BUTTON_I2);
    gpio_reset_pin(BUTTON_I3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_Q1, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q3, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q4, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_I1, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_I2, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_I3, GPIO_MODE_INPUT);
    gpio_set_level(GPIO_Q1, 0); //set to 0 at Reset.
    gpio_set_level(GPIO_Q2, 0); //set to 0 at Reset.
    gpio_set_level(GPIO_Q3, 0); //set to 0 at Reset.
    gpio_set_level(GPIO_Q4, 0); //set to 0 at Reset.







	FOUR_POSITION_SWITCH SWITCH;
	FOUR_POSITION_TOF    TIMER;
	VALVE_WITH_FLOAT     VALVE;
	TIMER.PT = 3000;


    while (true) {
    	I1 = !gpio_get_level(BUTTON_I1);
    	I2 = !gpio_get_level(BUTTON_I2);
    	I3 = !gpio_get_level(BUTTON_I3);



    	SWITCH.I1 = I1;
    	SWITCH.I2 = I2;
    	SWITCH.I3 = I3;
    	SWITCH();
    	TIMER.IN = SWITCH.State;
    	TIMER();
    	VALVE.State = TIMER.OUT;
    	VALVE();




    	gpio_set_level(GPIO_Q1, VALVE.Q1);
        gpio_set_level(GPIO_Q2, VALVE.Q2);
        gpio_set_level(GPIO_Q3, VALVE.Q3);
        gpio_set_level(GPIO_Q4, VALVE.Q4);


        vTaskDelay(100 / portTICK_PERIOD_MS); // 100ms cycle for Test.

    }
}
