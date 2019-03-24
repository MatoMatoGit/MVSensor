#include "sys_cfg.h"

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "adc.h"
#include "filter.h"
#include "SoftwareSerial.h"

#define ADC_CH_MOISTURE_SENSOR 3
#define ADC_FILTER_N 15

#define SOFTSERIAL_TX_DDR	DDRB
#define SOFTSERIAL_TX_PORT	PORTB
#define SOFTSERIAL_TX_PIN	PINB4

int main(void)
{
	DDRB |= (1 << PINB2) | (1 << PINB1);
	DDRB &= ~(1 << SOFTSERIAL_TX_PIN);
	
    PORTB |= (1 << PINB2);
	PORTB &= ~(1 << PINB1);
	PORTB |= (1 << SOFTSERIAL_TX_PIN);
	
	
	
	FilterDataType_t adc_filter_buf[ADC_FILTER_N];
	
	Filter_t adc_filter = {
		.n = ADC_FILTER_N,
		.buffer = adc_filter_buf
	};
	FilterDataType_t adc_val = 0;
	FilterDataType_t adc_filter_val = 0;
	
	AdcInit();
	FilterInit(&adc_filter);
	softSerialInit(&DDRB, &PORTB, NULL, SOFTWARE_SERIAL_RX_DISABLED, SOFTSERIAL_TX_PIN);
	softSerialBegin(2400);
	
    while (1) 
    {
		/*PORTB ^= (1 << PINB2);
		_delay_ms(500);
		PORTB ^= (1 << PINB1); 
		_delay_ms(500);*/
		
		adc_val = AdcChannelRead(ADC_CH_MOISTURE_SENSOR);
		adc_filter_val = adc_val;
		
		softSerialPrint("Raw:");
		softSerialPrintInt(adc_val);
		softSerialPrintLn("");
		
		FilterIn(&adc_filter, adc_val);
		FilterOut(&adc_filter, &adc_filter_val);
		
		softSerialPrint("Filt:");
		softSerialPrintInt(adc_filter_val);
		softSerialPrintLn("");
		
		if(adc_filter_val < 100) {
			PORTB &= ~(1 << PINB1);	
			PORTB &= ~(1 << PINB2);	
		} else if(adc_filter_val >= 100 && adc_filter_val < 300) {
			PORTB |= (1 << PINB1);
			PORTB &= ~(1 << PINB2);
		} else if(adc_filter_val >= 300 && adc_filter_val < 500) {
			PORTB &= ~(1 << PINB1);
			PORTB |= (1 << PINB2);
		} else if(adc_filter_val >= 500 && adc_filter_val < 1024) {
			PORTB |= (1 << PINB1);
			PORTB |= (1 << PINB2);
		}
		
		_delay_ms(100);
    }
}

