#ifndef __APPLICATION_MAIN_H__
#define __APPLICATION_MAIN_H__

//#include "../drv_lpc175x/rtc_lpc175x_v1_00.h"

//#define DISP_DIGIT														6

//typedef struct{
//	unsigned char upper_nlower; 			//1=upper,0=lower
//	unsigned char right_nleft; 				//1=right,0=left
//	unsigned char max[DISP_DIGIT]; 		//[0][1][2][3][4][5]
//	unsigned char min[DISP_DIGIT]; 		//[0][1][2][3][4][5]
//	unsigned char num[DISP_DIGIT+1]; 	//[0][1][2][3][4][5], put integer value not char
//	unsigned char dot;
//	unsigned char begin; 							//first digit to edit (0 - DIGIT-1)
//	unsigned char end; 								//last digit to edit
//	void (*shift_exception)(void);
//	void (*up_exception)(void);
//	void (*done)(void);
//} edit_t;

//typedef enum{
//	OP_ST_WAIT_MONEY = 0,
//	OP_ST_DISPENSING,
//	OP_ST_PAUSE,
//	OP_ST_FINISHED,
//} op_st_t;

//typedef struct{
//	double sell_price;
//	unsigned int flow_1liter;
//	
//	unsigned char flag_save_eeprom;
//	unsigned char resv[19];
//} profile_t; //size 32 byte

typedef struct{
//	double oil_n_tank;
//	double money_n_box;
//	double oil_n_sell;
	
	unsigned int money_coin1;
	unsigned int money_coin2;
	unsigned int money_coin5;
	unsigned int money_coin10;
	unsigned int money_bank20;
	unsigned int money_bank50;
	unsigned int money_bank100;
	unsigned int money_bank500;
	unsigned int money_bank1000;
	
	unsigned int money_coin;
	unsigned int money_bank;
	unsigned int money_propay;
	unsigned int money_total;
	
	unsigned char resv[61];
} trans_t; //size 128 byte

typedef struct{
//	double oil_n_run;
//	double litre_keyin_run;
	double money_user;
	
	unsigned int money_in_box;
//	unsigned int runsell_valid;
//	unsigned int litre_keyin;
//	
//	unsigned char payment_type;
//	unsigned char money_coin1;
//	unsigned char money_coin2;
//	unsigned char money_coin5;
//	unsigned char money_coin10;
//	unsigned char money_bank20;
//	unsigned char money_bank50;
//	unsigned char money_bank100;
//	unsigned char money_bank500;
//	unsigned char money_bank1000;
//	unsigned char member_id[13];
//	
//	unsigned char resv[9];
} runsell_t; //size 64 byte

//typedef struct{
//	double sell_price;
//	double oil_n_run;
//	double oil_n_tank;
//	double money;
//	double oil_level_sensor;
//	
//	time_t2 time;
//	date_t date;

//	unsigned int data_valid;
//	
//	unsigned char count_trans;
//	unsigned char country_mode;
//	unsigned char type_oil;
//	unsigned char error;
//	unsigned char cnt_pause_pump;
//	unsigned char cnt_pause_human;
//	unsigned char payment_type;
//	unsigned char money_coin1;
//	unsigned char money_coin2;
//	unsigned char money_coin5;
//	unsigned char money_coin10;
//	unsigned char money_bank20;
//	unsigned char money_bank50;
//	unsigned char money_bank100;
//	unsigned char money_bank500;
//	unsigned char money_bank1000;
//	unsigned char flag_settime_server;
//	unsigned char member_id[13];
//	unsigned char resv[3];
//} backup_t; //size 128 byte , used 96 byte only
	
void AppTimerTask(void);
//void AppDelay1ms(unsigned int n);
void AppCarCleaningInit(void);
void AppWhileLoop(void);
void AppTask1ms(void);
void AppTask10ms(void);
void AppTask100ms(void);
void AppTask500ms(void);

//void show_oil_n_tank_realtime(double oil);
//void show_money_temp_new(int money);
//void show_money_used_new(double money);
//void show_float_low_right_2digit(double val);
//void show_price(void);

void LampSchedule(unsigned char force_chk);
void SoundSchedule(unsigned char force_chk);

//void OilVendingOff_Pump_Valve(void);
//void EINTInit(void);
//void BuzzInit(void);
void EADCInit(void);
//void BuzzBeep(unsigned char beep);
//void StateBankCoin(unsigned char state);
//void JQ6500Listen(void);
//void JQ6500Task100ms(void);
//void JQ6500PlayOne(unsigned char index);
//void JQ6500Puase(void);
//void JQ6500PlayLoopMelody(void);
//void JQ6500PlayLoopSiren(void);
//void JQ6500PuaseLoopSiren(void);
void ESP32Listen(void);
void LCDDisplayListen(void);
void QRReaderListen(void);
//void SensorListen(void);
//void OilTask10ms(void);
//void SensorTask10ms(void);
//void OilCmdTransactionEEPROM(unsigned char index);
//void OilCmdSetPowerMonitor(void);
//void OilCmdSetDoorMonitor(unsigned char status);
//void OilCmdSetMoneyboxMonitor(unsigned char status);
//void OilCmdTest(unsigned char type,double num);
//void SensorCmdCheckDeviceID(void);
//void SensorCmdReadDataDeviceID(unsigned char id);

void AppScrInitTask10ms(void);
void AppScrInitTask100ms(void);
void AppScrInitDo(unsigned char acction,unsigned char type,char key);

void AppScrStandbyTask10ms(void);
void AppScrStandbyTask100ms(void);
void AppScrStandbyDo(unsigned char acction,unsigned char type,char key);

void AppScrCheckDispenserTask10ms(void);
void AppScrCheckDispenserTask100ms(void);
void AppScrCheckDispenserDo(unsigned char acction,unsigned char type,char key);

void AppScrDispenserTask10ms(void);
void AppScrDispenserTask100ms(void);
void AppScrDispenserDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuSettingTask10ms(void);
void AppScrMenuSettingTask100ms(void);
void AppScrMenuSettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE01SettingTask10ms(void);
void AppScrMenuE01SettingTask100ms(void);
void AppScrMenuE01SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE02SettingTask10ms(void);
void AppScrMenuE02SettingTask100ms(void);
void AppScrMenuE02SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE03SettingTask10ms(void);
void AppScrMenuE03SettingTask100ms(void);
void AppScrMenuE03SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE04SettingTask10ms(void);
void AppScrMenuE04SettingTask100ms(void);
void AppScrMenuE04SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE05SettingTask10ms(void);
void AppScrMenuE05SettingTask100ms(void);
void AppScrMenuE05SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE06Setting10ms(void);
void AppScrMenuE06Setting100ms(void);
void AppScrMenuE06SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE07Setting10ms(void);
void AppScrMenuE07Setting100ms(void);
void AppScrMenuE07SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE08Setting10ms(void);
void AppScrMenuE08Setting100ms(void);
void AppScrMenuE08SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE09Setting10ms(void);
void AppScrMenuE09Setting100ms(void);
void AppScrMenuE09SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE10Setting10ms(void);
void AppScrMenuE10Setting100ms(void);
void AppScrMenuE10SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE11Setting10ms(void);
void AppScrMenuE11Setting100ms(void);
void AppScrMenuE11SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE12Setting10ms(void);
void AppScrMenuE12Setting100ms(void);
void AppScrMenuE12SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE13Setting10ms(void);
void AppScrMenuE13Setting100ms(void);
void AppScrMenuE13SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE14Setting10ms(void);
void AppScrMenuE14Setting100ms(void);
void AppScrMenuE14SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE15Setting10ms(void);
void AppScrMenuE15Setting100ms(void);
void AppScrMenuE15SettingDo(unsigned char acction,unsigned char type,char key);

void AppScrMenuE16Setting10ms(void);
void AppScrMenuE16Setting100ms(void);
void AppScrMenuE16SettingDo(unsigned char acction,unsigned char type,char key);



void AppScrTestTask10ms(void);
void AppScrTestTask100ms(void);
void AppScrTestDo(unsigned char acction,unsigned char type,char key);

#endif
