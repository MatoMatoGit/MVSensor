
#define F_CPU 1000000UL

#include "notification.h"
#include "notification_table.h"

/* App. */
#include "sensor.h"

/* Drivers. */
#include "rgb_led.h"
#include "soft_timer.h"
#include "sleep.h"

/* Serial. */
#include "SoftwareSerial.h"

/* System libs. */
#include <util/delay.h>

/* Standard libs. */
#include <stdint.h>

static void INotificationRun(SoftTimer_t timer);

static NotificationMapping_t *INotificationMappingFromMoistureValue(uint32_t value);

static NotificationState_t CurrentState;
static SoftTimer_t MainTimer;

void NotificationInit(void)
{
	CurrentState = NOTIFICATION_STATE_DETECT_SOIL;
	RgbLedModeSet(RGB_LED_MODE_OFF);
	MainTimer = SoftTimerCreate(NOTIFICATION_STATE_TRANSITION_INTERVAL_MS, INotificationRun);
}

void NotificationStart(void)
{
	SoftTimerStart(MainTimer);
}

static void INotificationRun(SoftTimer_t timer)
{
	static uint32_t cal_time_start = 0;
	static uint8_t notification_idx = 0;
	static NotificationMapping_t *notification_mapping = NULL;
	
	uint32_t moisture_value = 0;

	/* Stop the timer to avoid nesting. */
	SoftTimerStop(MainTimer);
	
	switch(CurrentState) {
	case NOTIFICATION_STATE_DETECT_SOIL: {
		/* Set the LED color to red and turn it on. */
		RgbLedColorSet(RGB_LED_COLOR_RED);
		RgbLedModeSet(RGB_LED_MODE_ON);
		
		/* Read the sensor value and verify that it is above 
		 * the minimum value, indicating that the senor has 
		 * inserted in the soil. Only then transition to the
		 * calibration state. */
		moisture_value = SensorValueGet();
		if(moisture_value >= SENSOR_MIN_VALUE) {
			CurrentState = NOTIFICATION_STATE_CALIBRATE;
		}
		break;
	}
	case NOTIFICATION_STATE_CALIBRATE: {
		/* If the calibration start time is 0 the calibration cycle
		 * has been initiated. Set the calibration start time
		 * and turn off the LED. The timer is set to the calibration
		 * interval. */
		if(cal_time_start == 0) {
			cal_time_start = SoftTimerTotalTimeGet();
			notification_idx = 0;
			RgbLedModeSet(RGB_LED_MODE_OFF);
			SoftTimerPeriodSet(MainTimer, NOTIFICATION_CALIBRATION_INTERVAL_MS);
		
		/* If the total calibration time has been reached set the next state to notify and
		 * change the timer interval. */
		} else if(SoftTimerTotalTimeGet() >= (cal_time_start + CALIBRATION_PERIOD_S)) {
			SoftTimerPeriodSet(MainTimer, NOTIFICATION_STATE_TRANSITION_INTERVAL_MS);
			CurrentState = NOTIFICATION_STATE_NOTIFY_ON;
		}
		
		/* Set the next color for the LED and turn it on. */
		RgbLedColorSet(NotificationTable[notification_idx].color);
		RgbLedModeSet(RGB_LED_MODE_ON);
		
		/* Read the sensor and check if it is at least the minimum value.
		 * Adjust the 'perfect' moisture value. */
		moisture_value = SensorValueGet();
		if(moisture_value >= SENSOR_MIN_VALUE) {
			NotificationTable[MOISTURE_LEVEL_PERFECT].value = moisture_value;
		}
		
		/* Turn off the LED. */
		RgbLedModeSet(RGB_LED_MODE_OFF);
		
		/* Select the next LED color. */
		notification_idx++;
		if(notification_idx >= NOTIFICATION_COLOR_TABLE_SIZE) {
			notification_idx = 0;
		}
		break;
	}
	case NOTIFICATION_STATE_NOTIFY_ON: {
		//softSerialPrint("notify");
		
		/* Read the sensor value and map the value to
		 * a color and timing. */
		moisture_value = SensorValueGet();
		notification_mapping = INotificationMappingFromMoistureValue(moisture_value);
		
		//softSerialPrintInt(color);
		//softSerialPrintLn("");
		
		/* Turn on the LED. */
		RgbLedColorSet(notification_mapping->color);
		RgbLedModeSet(RGB_LED_MODE_ON);
		
		/* Set the timer to the notification time and transition to the 'Notify off' state. */
		SoftTimerPeriodSet(MainTimer, notification_mapping->time_notify);
		CurrentState = NOTIFICATION_STATE_NOTIFY_OFF;
		break;
	}
	case NOTIFICATION_STATE_NOTIFY_OFF: {
		/* Turn off the LED. */
		RgbLedModeSet(RGB_LED_MODE_OFF);
		
		/* Set the timer to the transition interval and transition to the 'Sleep' state. */
		SoftTimerPeriodSet(MainTimer, NOTIFICATION_STATE_TRANSITION_INTERVAL_MS);
		CurrentState = NOTIFICATION_STATE_SLEEP;
		break;
	}
	case NOTIFICATION_STATE_SLEEP: {
		
		//softSerialPrintLn("sleep");
		
		/* Go to sleep for the amount of time associated with the
		 * current moisture level. */
		SleepForDuration(notification_mapping->time_sleep);
		
		//softSerialPrintLn("awake");
		
		/* When woken up, transition back to the 'Notify on' state. */
		SoftTimerPeriodSet(MainTimer, NOTIFICATION_STATE_TRANSITION_INTERVAL_MS);
		CurrentState = NOTIFICATION_STATE_NOTIFY_ON;
		break;
	}

	default: {
		CurrentState = NOTIFICATION_STATE_NOTIFY_ON;
		break;
	}
	}
	
	/* Start the timer to transition to the next state. */
	SoftTimerStart(MainTimer);
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
