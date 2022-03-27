#ifndef __INTERFACE_EEPROM_H__
#define __INTERFACE_EEPROM_H__

#include <stdint.h>

typedef struct{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
} time_t;

typedef struct{
	time_t light_on;
	time_t light_off;
	time_t sound_day;
	time_t sound_night;
	
	unsigned int firmware_valid;
//	unsigned int min_oilx100;
	unsigned int min_price;
//	unsigned int bill_perbaht;
	unsigned int waste_money;
	
	unsigned int bahtpermsec_relay[6];

	unsigned char button_mode;
	unsigned char button_enable;
//	unsigned char flow_ct;
	unsigned char snd_lv_hi;
	unsigned char snd_lv_low;
//	unsigned char valve_drain_on;
//	unsigned char type_oil;
//	unsigned char type_sound;
//	unsigned char oil_terminate;
	
//	unsigned char country_mode;
//	unsigned char country_sound;
//	unsigned char melody_sound;
	
//	unsigned char timeout_off_battery;
//	unsigned char keypad_special;
//	
//	unsigned char status_lock_kiosk;
//	unsigned char flag_save_eeprom;
	unsigned char resv[76];
} cfg_t; //size 128 byte

void EEPROMInit(void);
void I2C_EEPROM_Write(uint16_t u16Address, uint8_t u8Data);
uint8_t I2C_EEPROM_Read(uint16_t u16Address);

void EPWriteLong(unsigned short ad, unsigned int len, char *data);
void EPReadLong(unsigned short ad, unsigned int len, char *data);

void ReadEEPROMConfig(cfg_t *cfg);
void WriteEEPROMConfig(cfg_t config);
void SetEEPROMConfigDefault(void);
	
#endif

