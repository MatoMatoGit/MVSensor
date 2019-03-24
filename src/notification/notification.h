#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#define NOTIFICATION_INTERVAL_MS 5e3
#define NOTIFICATION_DURATION_MS 1000

typedef enum {
	NOFICATION_STATE_CALIBRATING = 0,
	NOTIFICATION_STATE_MEASURING,
	NOTIFICATION_STATE_NOTIFYING,
	NOTIFICATION_STATE_WAITING,
}NotificationState_t;

void NotificationInit(void);

void NotificationStart(void);

void INotificationRun(void);

#endif