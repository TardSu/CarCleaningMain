#include "./Application/application_config.h"

S_RTC_TIME_DATA_T sWriteRTC, sReadRTC;

void RTCInit(void){	
//	sWriteRTC.u32Year       = 2022;
//	sWriteRTC.u32Month      = 3;
//	sWriteRTC.u32Day        = 18;
//	sWriteRTC.u32DayOfWeek  = RTC_TUESDAY;
//	sWriteRTC.u32Hour       = 17;
//	sWriteRTC.u32Minute     = 04;
//	sWriteRTC.u32Second     = 00;
//	sWriteRTC.u32TimeScale  = RTC_CLOCK_24;
//	RTC_SetDateAndTime(&sWriteRTC);

//	RTC_Open(&sWriteRTC);
	RTC_Open(NULL);
}

void RTCGetTime(time_t *time){
	RTC_GetDateAndTime(&sReadRTC);
	time->hour = sReadRTC.u32Hour;
	time->min = sReadRTC.u32Minute;
	time->sec = sReadRTC.u32Second;
}

void RTCSetTime(time_t time){
	RTC_SetTime(time.hour, time.min, time.sec, RTC_CLOCK_24, RTC_AM);
}
