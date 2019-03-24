/*
 * moisture.c
 *
 * Created: 16-03-2019 22:33:12
 *  Author: dorspi
 */ 
//#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
#define F_CPU 1000000UL
#include <util/delay.h>
//#endif

#include "moisture.h"
#include "adc.h"
#include "gpio_adc.h"
#include "gpio_moisture.h"

#define ADC_CH_MOISTURE_SENSOR 2

void MoistureInit(void)
{
//#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
	GpioMoistureInit();
//#endif
	GpioAdcInit();
	AdcInit();
}

uint32_t MoistureSensorReadSingle(void)
{
	uint32_t value = 0;

#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
	GpioMoisturePowerStateSet(1);
	_delay_ms(25);
#endif
	value = (uint32_t)AdcChannelRead(ADC_CH_MOISTURE_SENSOR);
#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
	GpioMoisturePowerStateSet(0);
#endif
	
	return value;
}

void MoistureSensorReadBurst(uint8_t n, uint32_t *values)
{
	#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
	GpioMoisturePowerStateSet(1);
	_delay_ms(25);
	#endif
	for(uint8_t i = 0; i < n; i++) {
		values[i] = (uint32_t)AdcChannelRead(ADC_CH_MOISTURE_SENSOR);
	}
	#ifdef MOISTURE_CONFIG_ENABLE_LOW_POWER_MODE
	GpioMoisturePowerStateSet(0);
	#endif
}