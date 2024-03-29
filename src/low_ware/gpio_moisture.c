/*
 * gpio_moisture.c
 *
 * Created: 16-03-2019 22:42:28
 *  Author: dorspi
 */

#include "gpio_moisture.h"

#include <avr/io.h>

#define MOISTURE_DDR	DDRB
#define MOISTURE_PORT	PORTB
#define MOISTURE_PIN	PINB3

void GpioMoistureInit(void)
{
	MOISTURE_DDR |= (1 << MOISTURE_PIN);
}


void GpioMoisturePowerStateSet(uint8_t state)
{
	if(state) {
		MOISTURE_PORT |= (1 << MOISTURE_PIN);
	} else {
		MOISTURE_PORT &= ~(1 << MOISTURE_PIN);
	}
}