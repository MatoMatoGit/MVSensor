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

volatile uint8_t wdt = 1;

void WdtCallback(void);
void Blink(SoftTimer_t tmr);

int main(void)
{
	//DDRB |= (1 << PINB2);
	
	//SoftTimerInit();
	//SoftTimer_t timer = SoftTimerCreate(1000, Blink);
	//SoftTimerStart(timer);
	//WdtInit(WDT_CYCLES_512K, WdtCallback);
	//PORTB &= ~(1 << PINB2);
	MoistureInit();
	RgbLedInit();
	SensorInit();
	NotificationInit();
	//PORTB |= (1 << SOFTSERIAL_TX_PIN);
	
	//softSerialInit(&DDRB, &PORTB, NULL, SOFTWARE_SERIAL_RX_DISABLED, SOFTSERIAL_TX_PIN);
	//softSerialBegin(2400);
	
    while (1) 
    {
		//if(wdt == 0) {
		//	return 0;
		//}
		
		//PORTB |= (1 << PINB2);
		//_delay_ms(100);
		//PORTB &= ~(1 << PINB2);
		//wdt = 0;
		INotificationRun();
		
			
		//EnterSleep();
    }
}

void Blink(SoftTimer_t tmr)
{
	PORTB ^= (1 << PINB2);
}

void WdtCallback(void)
{
	if(wdt == 0) {
		wdt = 1;	
	}
}