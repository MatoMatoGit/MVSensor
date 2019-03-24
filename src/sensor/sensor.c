/*
 * sensor.c
 *
 * Created: 16-03-2019 22:47:46
 *  Author: dorspi
 */ 

#include "sensor.h"

#include "oc_timer.h"
#include "moisture.h"
#include "filter.h"

#include "../SoftwareSerial.h"

static void OcTimerCallback(void);

static FilterDataType_t moisture_filter_buf[SENSOR_FILTER_DEPTH];

static Filter_t moisture_filter = {
	.n = SENSOR_FILTER_DEPTH,
	.buffer = moisture_filter_buf
};

void SensorInit(void)
{
	FilterInit(&moisture_filter);
	OcTimerInit(244);
	OcTimerCallbackRegister(OcTimerCallback);
	OcTimerStart();
}

uint32_t SensorValueGet(void)
{
	uint32_t value = 0;
	
	FilterOut(&moisture_filter, &value);
	
	return value;
}

static void OcTimerCallback(void)
{
	uint32_t value = MoistureSensorReadSingle();
	FilterIn(&moisture_filter, value);
	//softSerialPrintInt(value);
	//softSerialPrintLn("");
}