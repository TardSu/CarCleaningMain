#ifndef __INTERFACE_RTC_H__
#define __INTERFACE_RTC_H__

void RTCInit(void);
void RTCGetTime(time_t *time);
void RTCSetTime(time_t time);
	
#endif
