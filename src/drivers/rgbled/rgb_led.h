/*
 * rgb_led.h
 *
 *  Created on: 3 jan. 2018
 *      Author: Dorus
 */

#ifndef RGB_LED_H_
#define RGB_LED_H_

#include <stdint.h>

#define RGB_LED_OK	0
#define RGB_LED_ERR	-1

typedef enum {
	RGB_LED_COLOR_RED,
	RGB_LED_COLOR_GREEN,
	RGB_LED_COLOR_BLUE,
	RGB_LED_COLOR_VIOLET,
	RGB_LED_COLOR_YELLOW,
	RGB_LED_COLOR_AQUA,
	RGB_LED_COLOR_WHITE
}RgbLedColor_t;

typedef enum {
	RGB_LED_MODE_OFF = 0,
	RGB_LED_MODE_ON,
}RgbLedMode_t;

/* Init RGB LED, sets color to RGB_LED_COLOR_OFF. */
int8_t RgbLedInit(void);

/* Set RGB LED color. */
void RgbLedColorSet(RgbLedColor_t color);

/* Get current RGB LED color. */
RgbLedColor_t RgbLedColorGet(void);

/* Set RGB LED mode; off, constant (on) */
int8_t RgbLedModeSet(RgbLedMode_t mode);

/* Get current RGB LED mode. */
RgbLedMode_t RgbLedModeGet(void);

#endif /* RGB_LED_H_ */
