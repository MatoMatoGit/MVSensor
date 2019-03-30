#include "sys_cfg.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "SoftwareSerial.h"

#include "moisture.h"
#include "rgb_led.h"
#include "notification.h"
#include "sensor.h"
#include "oc_timer.h"
#include "gpio_moisture.h"
#include "wdt.h"
#include "sleep.h"
#include "soft_timer.h"

#define SOFTSERIAL_TX_DDR	DDRB
#define SOFTSERIAL_TX_PORT	PORTB
#define SOFTSERIAL_TX_PIN	PINB0

int main(void)
{
	//DDRB |= (1 << PINB2);
	//PORTB &= ~(1 << PINB2);
	//PORTB |= (1 << SOFTSERIAL_TX_PIN);
	
	/* Initialize drivers. */
	SoftTimerInit();
	MoistureInit();
	RgbLedInit();
	//softSerialInit(&DDRB, &PORTB, NULL, SOFTWARE_SERIAL_RX_DISABLED, SOFTSERIAL_TX_PIN);
	//softSerialBegin(2400);
	
	/* Initialize app components. */
	SensorInit();
	NotificationInit();
	
	/* Start notification component. */
	NotificationStart();	

    while (1) 
    {
		/* Idle. */
    }
}