#ifndef NOTIFICATION_TABLE_H_
#define NOTIFICATION_TABLE_H_

#include "rgb_led.h"

#include <stdint.h>

#define NOTIFICATION_COLOR_TABLE_SIZE 5

#define SEC_TO_MSEC(sec) (sec * 1000)
#define MIN_TO_MSEC(min) SEC_TO_MSEC(min * 60)

typedef struct {
	uint32_t value;
	RgbLedColor_t color;
	uint32_t time_wait;
	uint32_t time_notify;
}NotificationMapping_t;

/*
NotificationMapping_t NotificationTable[NOTIFICATION_COLOR_TABLE_SIZE] = {
	{.value = 20, .color = RGB_LED_COLOR_RED, .time_wait = SEC_TO_MSEC(30), .time_notify = 500},
	{.value = 100, .color = RGB_LED_COLOR_VIOLET, .time_wait = SEC_TO_MSEC(60), .time_notify = 1500},
	{.value = 200, .color = RGB_LED_COLOR_GREEN, .time_wait = SEC_TO_MSEC(300), .time_notify = SEC_TO_MSEC(10)},
	{.value = 300, .color = RGB_LED_COLOR_AQUA, .time_wait = SEC_TO_MSEC(300), .time_notify = SEC_TO_MSEC(10)},
	{.value = 450, .color = RGB_LED_COLOR_BLUE, .time_wait = SEC_TO_MSEC(300), .time_notify = SEC_TO_MSEC(10)},
};
*/


NotificationMapping_t NotificationTable[NOTIFICATION_COLOR_TABLE_SIZE] = {
	{.value = 20, .color = RGB_LED_COLOR_RED, .time_wait = SEC_TO_MSEC(1), .time_notify = 200},
	{.value = 100, .color = RGB_LED_COLOR_VIOLET, .time_wait = SEC_TO_MSEC(2), .time_notify = 500},
	{.value = 200, .color = RGB_LED_COLOR_GREEN, .time_wait = SEC_TO_MSEC(5), .time_notify = SEC_TO_MSEC(1)},
	{.value = 300, .color = RGB_LED_COLOR_AQUA, .time_wait = SEC_TO_MSEC(5), .time_notify = SEC_TO_MSEC(1)},
	{.value = 400, .color = RGB_LED_COLOR_BLUE, .time_wait = SEC_TO_MSEC(5), .time_notify = SEC_TO_MSEC(1)},
};


/*
NotificationMapping_t NotificationTable[NOTIFICATION_COLOR_TABLE_SIZE] = {
	{.value = 20, .color = RGB_LED_COLOR_RED},
	{.value = 100, .color = RGB_LED_COLOR_VIOLET},
	{.value = 200, .color = RGB_LED_COLOR_AQUA},
	{.value = 250, .color = RGB_LED_COLOR_GREEN},
	{.value = 300, .color = RGB_LED_COLOR_BLUE},
};
*/

#endif