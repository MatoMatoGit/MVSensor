
#define F_CPU 1000000UL

#include "notification.h"
#include "notification_table.h"

#include "rgb_led.h"
#include "sensor.h"
#include "soft_timer.h"

#include "../SoftwareSerial.h"

#include <util/delay.h>
#include <stdint.h>

//static void INotificationRun(void);

static NotificationMapping_t *INotificationMappingFromMoistureValue(uint32_t value);

static NotificationState_t CurrentState;
static SoftTimer_t MainTimer;

void NotificationInit(void)
{
	CurrentState = NOTIFICATION_STATE_MEASURING;
	RgbLedModeSet(RGB_LED_MODE_OFF);
	//MainTimer = SoftTimerCreate(250, INotificationRun);
}

void NotificationStart(void)
{
	SoftTimerStart(MainTimer);
}

void INotificationRun(void)
{
	static uint32_t moisture_value = 0;
	NotificationMapping_t *notification_mapping = NULL;
	
	switch(CurrentState) {
	case NOFICATION_STATE_CALIBRATING: {
		break;
	}
	case NOTIFICATION_STATE_MEASURING: {
		moisture_value = SensorValueGet();
		//softSerialPrint("measure");
		//softSerialPrintInt(moisture_value);
		//softSerialPrintLn("");
		CurrentState = NOTIFICATION_STATE_NOTIFYING;
		break;
	}
	case NOTIFICATION_STATE_NOTIFYING: {
		//softSerialPrint("notify");
		notification_mapping = INotificationMappingFromMoistureValue(moisture_value);
		//softSerialPrintInt(color);
		//softSerialPrintLn("");
		RgbLedColorSet(notification_mapping->color);
		RgbLedModeSet(RGB_LED_MODE_ON);
		_delay_ms(NOTIFICATION_DURATION_MS);
		RgbLedModeSet(RGB_LED_MODE_OFF);
		
		CurrentState = NOTIFICATION_STATE_WAITING;
		break;
	}
	case NOTIFICATION_STATE_WAITING: {
		//softSerialPrintLn("wait");
		_delay_ms(NOTIFICATION_INTERVAL_MS);
		CurrentState = NOTIFICATION_STATE_MEASURING;
		break;
	}

	default: {
		CurrentState = NOTIFICATION_STATE_MEASURING;
		break;
	}
	}
}

static NotificationMapping_t *INotificationMappingFromMoistureValue(uint32_t value)
{
	uint8_t i = 0;
	uint8_t idx = 0;
	
	for(; i < NOTIFICATION_COLOR_TABLE_SIZE; i++) {
		if(NotificationTable[i].value <= value) {
			idx = i;
		}
	}
	
	return &NotificationTable[idx];
}
