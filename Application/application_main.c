#include "./Application/application_config.h"

//typedef enum{
//	TEST_NULL = 0, TEST_OUTPUT_PUMP_ON, TEST_OUTPUT_PUMP_OFF,
//	TEST_OUTPUT_VALVE_OIL_ON, TEST_OUTPUT_VALVE_OIL_OFF,
//	TEST_OUTPUT_VALVE_DRAIN_ON, TEST_OUTPUT_VALVE_DRAIN_OFF,
//	TEST_OUTPUT_LAMP_LIGHT_ON, TEST_OUTPUT_LAMP_LIGHT_OFF,
//	TEST_OUTPUT_POWER_BANK_ON, TEST_OUTPUT_POWER_BANK_OFF,
//	TEST_OUTPUT_POWER_COIN_ON, TEST_OUTPUT_POWER_COIN_OFF,
//	TEST_OUTPUT_POWER_BATT_ON, TEST_OUTPUT_POWER_BATT_OFF,
//	TEST_OUTPUT_RS485_CTRL_ON, TEST_OUTPUT_RS485_CTRL_OFF,
//	TEST_INPUT_DOOR,  TEST_INPUT_DOOR_CHK,
//	TEST_INPUT_POWER_TYPE, TEST_INPUT_POWER_TYPE_CHK,
//	TEST_INPUT_OIL_LOW, TEST_INPUT_OIL_LOW_CHK,
//	TEST_INPUT_ADC_BAT, TEST_INPUT_ADC_BAT_CHK,
//	TEST_INPUT_FLOW, TEST_INPUT_FLOW_CHK,
//	TEST_DISPLAY_RIGHT, TEST_DISPLAY_LEFT,	
//} cmd_test_t;

//typedef enum{
//	EDIT_ST_NOT_STARTED = 0, EDIT_ST_STARTED, EDIT_ST_DONE
//} edit_st_t;

//typedef enum{
//	CMD_NULL = 0, CMD_SEND_TRANSACTION, CMD_TIME_REQUIRED, CMD_SET_PRICE,CMD_SETOIL_INTANK,
//	CMD_CLEAR_MONEYINBOX, CMD_SET_CALIBRATION, CMD_SET_CONFIG, CMD_ERROR_DISPENSING, CMD_OIL_LOW, 
//	CMD_POWER_MONITOR, CMD_DOOR_MONITOR, CMD_MONEYBOX_MONITOR, CMD_TEST,
//} cmd_type_t;

//typedef enum{
//	KIOSK_NORMAL = 0, KIOSK_DISPENSING, KIOSK_ERROR_FLOW,
//	KIOSK_OIL_LOW, KIOSK_LOCK_BY_SERVER, KIOSK_LOCK_BY_COMU_ERROR,
//	KIOSK_LOCK_BY_MEMBER_OFFLINE, KIOSK_LOCK_BY_KIOSK_GETWAY,
//} kiosk_status_t;

//const unsigned char sound_country_array[SND_MAX_COUNTRY + 1] ={
//	SND_COUNTRY_THA,SND_COUNTRY_LAO,SND_COUNTRY_MYA,
//	SND_COUNTRY_CAM,SND_COUNTRY_VIE,SND_COUNTRY_IDN,
//	SND_COUNTRY_ENG,
//};

//const unsigned char sound_melody_array[SND_MAX_MELODY + 1] ={
//	0,SND_LOOP_MELODY_1,SND_LOOP_MELODY_2,SND_LOOP_MELODY_3,
//	SND_LOOP_MELODY_4,SND_LOOP_MELODY_5,
//};

//const unsigned char sound_lv_array[SND_MAX_VOL_LV + 1] ={
//	SND_VOL_LV0,SND_VOL_LV1,SND_VOL_LV2,SND_VOL_LV3,
//	SND_VOL_LV4,SND_VOL_LV5
//};

char name_menu_table1[DISPLAY_MENU_SETTING_MAX + 1][4] ={
	"E-01", "E-02",	"E-03", "E-04", "E-05", "E-06",
	"E-07", "E-08", "E-09", "E-10", "E-11", "E-12",
	"E-13", "E-14", "E-15", "E-16",
};

typedef enum{
	STATUS_BT_STANDBY = 0, STATUS_BT_DISPENSING, STATUS_BT_PAUSE,
} status_bt_t;

volatile unsigned char time_1ms_cnt;
volatile unsigned char time_10ms_cnt;
volatile unsigned char time_100ms_cnt;
volatile unsigned char time_500ms_cnt;

unsigned char time_1ms_flag;
unsigned char time_10ms_flag;
unsigned char time_100ms_flag;
unsigned char time_500ms_flag;

//volatile unsigned int time_1ms_cnt_flow;
//volatile unsigned char update_display_flag;
//volatile unsigned char oilcheckflow;
//volatile unsigned int cnt_read_dat;
//volatile unsigned int cnt_readsensor_dat;

//edit_t edit;
//op_st_t op_st;
//edit_st_t edit_st;
//profile_t profile;
cfg_t ee_config;

trans_t trans;
runsell_t runsell;
time_t time;
time_t time_edit;
//date_t date;

//backup_t backup_trans;
//cmd_type_t cmd_type;
//cmd_test_t cmd_test = TEST_NULL;
//kiosk_status_t kiosk_status = KIOSK_NORMAL;
//kiosk_status_t kiosk_status_dispensing = KIOSK_NORMAL;
status_bt_t status_bt_relay[BUTTON_NUM-3] = {STATUS_BT_STANDBY,STATUS_BT_STANDBY,STATUS_BT_STANDBY,STATUS_BT_STANDBY,STATUS_BT_STANDBY,STATUS_BT_STANDBY};


//double money_used;
//double oil_dispensed;
//double oil_dispensed_buf;
//double flow_new_buf;
//double max_money_save;
//double adc_voltage;
//double oil_level_sensor;

int money_temp;
double money_user;
//int money_display;
//int strlengthSerialSendFlag;

uint32_t chipUID[4];
//unsigned int time_beep;
//unsigned int max_receive_money;
//unsigned int flow_cycle;
//unsigned int flow_cycle_preset;
//unsigned int pluse_time_out;
unsigned int cnt_10ms;
unsigned int cnt_100ms;
unsigned int cnt_100ms_waste_money;
//unsigned int cnt_100ms_valve_drain;
//unsigned int time_cnt_batt_off;
//unsigned int time_task_serial_send_flag = 0;
//unsigned int time_task_serialsensor_send_flag = 0;
//unsigned int time_cnt_serial_commu = 0;
//unsigned int sensor_device_total = 0;
unsigned int buf1 = 0;

unsigned int total_time_relay[BUTTON_NUM-3];
unsigned int time_user_relay[BUTTON_NUM-3];
//unsigned int money_user_relay[BUTTON_NUM-3];


//unsigned char index_trans[EP_TRANS_SAVE_TABLE];
//char dataSerialSensorRead[512];
//char dataSerialRead[512];
//char dataSerialSend[512];
//char dataSerialSendFlag[512];
//char dataSerialSensorSendFlag[512];
//char edit_str[DISP_DIGIT+1];

//char dataSerialRev[8];

char button_key_array[BUTTON_NUM-3] = {BT_RLY1,BT_RLY2,BT_RLY3,BT_RLY4,BT_RLY5,BT_RLY6};

unsigned char money_coin1;
unsigned char money_coin2;
unsigned char money_coin5;
unsigned char money_coin10;
unsigned char money_bank20;
unsigned char money_bank50;
unsigned char money_bank100;
unsigned char money_bank500;
unsigned char money_bank1000;

//unsigned char cnt_dat_rev;
//unsigned char beep_flag;
//unsigned char current_digit;
//unsigned char cnt_pause_pump;
//unsigned char cnt_pause_human;
//unsigned char test1_toggle = 0;
//unsigned char start_cnt_pluse = 0;
//unsigned char keyin_baht_lite = 0;
//unsigned char power_main_or_batt = 0;
//unsigned char read_dat_ok = 0;
//unsigned char readsensor_dat_ok = 0;
//unsigned char write_dat_ok = 0;
//unsigned char flag_power;
//unsigned char flag_flow_ls = 0;
//unsigned char flag_first_air = 0;
//unsigned char flag_bt_yellow = 0;
//unsigned char flag_bt_white = 0;
unsigned char flag_bt_mode = 0;
unsigned char flag_bt_down = 0;
//unsigned char flag_bt_red = 0;
//unsigned char flag_bt_cal = 0;
//unsigned char flag_low_oil = 0;
//unsigned char flag_update_start = 0;
//unsigned char flag_power_off = 0;
unsigned char flag_sel_menu = 0;
unsigned char flag_silen_on = 0;
unsigned char flag_time_edit = 0;
//unsigned char flag_door_on = 0;
//unsigned char flag_member_offline_online = 0;
//unsigned char flag_moneybox_on = 0;
//unsigned char flag_settime_edit = 0;
//unsigned char flag_settime_server = 0;
//unsigned char flag_start_check_commu = 0;
//unsigned char flag_start_check_device_id = 0;
//unsigned char flag_off_valve_drain = 0;
//unsigned char time_check_silen_on = 0;
//unsigned char time_check_silen_off = 0;
unsigned char button_used;

//unsigned char time_check_door_on = 0;
//unsigned char time_check_door_off = 0;
//unsigned char time_check_moneybox_on = 0;
//unsigned char time_check_moneybox_off = 0;

//unsigned char time_check_power;
//unsigned char cnt_serial_send_flag = 0;
//unsigned char cnt_trans_save = 0;
//unsigned char send_trans_backup = 0;

//unsigned char cnt_read_device_total = 0;

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################             App Init All          ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void SysTick_Handler(void){
	time_1ms_cnt++;
	time_1ms_flag = 1;
	if(time_1ms_cnt >= 10){
		time_1ms_cnt = 0;
		time_10ms_cnt++;
		time_10ms_flag = 1;
		if(time_10ms_cnt >= 10){
			time_10ms_cnt = 0;
			time_100ms_cnt++;
			time_100ms_flag = 1;
			if(time_100ms_cnt >= 5){
				time_100ms_cnt = 0;
				time_500ms_cnt++;
				time_500ms_flag = 1;
			}
		}
	}
}

void AppTimerTask(void){
	if(time_1ms_flag){
		AppTask1ms();
		time_1ms_flag = 0;
	}
	if(time_10ms_flag){
		AppTask10ms();
		time_10ms_flag = 0;
	}
	if(time_100ms_flag){
		AppTask100ms();
    time_100ms_flag = 0;
	}
	if(time_500ms_flag){
		AppTask500ms();
		time_500ms_flag = 0;
	}
}

//void AppDelay1ms(unsigned int n){
//	unsigned char x;
//	while(n){
//		x = time_1ms_cnt;
//		while(x == time_1ms_cnt);
//		n--;
//	}
//}

void SYS_Init(void){
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init System Clock                                                                                       */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Unlock protected registers */
	SYS_UnlockReg();

	/* Enable HIRC clock (Internal RC 22.1184MHz) */
	CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

	/* Wait for HIRC clock ready */
	CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

	/* Select HCLK clock source as HIRC and and HCLK clock divider as 1 */
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

	/* Enable HXT clock (external XTAL 12MHz) and LXT-32KHz */
	CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_LXTEN_Msk);

	/* Wait for HXT clock ready */
	CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk | CLK_STATUS_LXTSTB_Msk);

//	/* Set core clock as PLL_CLOCK from PLL*/
//	CLK_SetCoreClock(PLL_CLOCK);
	/* Set core clock as PLL_CLOCK from PLL and SysTick source to HCLK/2*/
	CLK_SetCoreClock(PLL_CLOCK);
	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HXT);
		
	/* Waiting for PLL clock ready */
	CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

	/* Enable peripheral clock */
  CLK_EnableModuleClock(UART0_MODULE);
	CLK_EnableModuleClock(UART1_MODULE);
	CLK_EnableModuleClock(UART2_MODULE);
	CLK_EnableModuleClock(UART3_MODULE);
	CLK_EnableModuleClock(TMR0_MODULE);
	CLK_EnableModuleClock(TMR1_MODULE);
	CLK_EnableModuleClock(TMR2_MODULE);
	CLK_EnableModuleClock(PWM1_MODULE);
	CLK_EnableModuleClock(RTC_MODULE);
	CLK_EnableModuleClock(I2C0_MODULE);
	CLK_EnableModuleClock(SC0_MODULE);
	CLK_EnableModuleClock(EADC_MODULE);
	
	/* Peripheral clock source */
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
	CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
	CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
	
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HXT, 0);
	CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_HXT, 0);

	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL, CLK_CLKDIV0_HCLK(2));
	CLK_SetModuleClock(PWM1_MODULE, CLK_CLKSEL2_PWM1SEL_PCLK1, NULL);

	CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL3_SC0SEL_HIRC, CLK_CLKDIV1_SC0(1));

	CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(8));

	/* Update System Core Clock */
	/* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
	SystemCoreClockUpdate();
	
	/*---------------------------------------------------------------------------------------------------------*/
	/* Init I/O Multi-function                                                                                 */
	/*---------------------------------------------------------------------------------------------------------*/
	/* Set GPD multi-function pins for UART0 RXD and TXD */
	SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk);
	SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA3MFP_UART0_RXD | SYS_GPA_MFPL_PA2MFP_UART0_TXD);
	SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
	SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB2MFP_UART1_RXD | SYS_GPB_MFPL_PB3MFP_UART1_TXD);
	SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk);
	SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_UART2_RXD | SYS_GPB_MFPL_PB1MFP_UART2_TXD);
	SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA8MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk);
	SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA8MFP_UART3_TXD | SYS_GPA_MFPH_PA9MFP_UART3_RXD);
	
	/* Set PC multi-function pins for PWM1 Channel 0 and 2 */
	SYS->GPE_MFPL = (SYS->GPE_MFPL & (~SYS_GPE_MFPL_PE2MFP_Msk));
	SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_PWM1_CH1;
	
	/* Set GPE multi-function pins for I2C0 SDA and SCL */
	SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE12MFP_Msk | SYS_GPE_MFPH_PE13MFP_Msk);
	SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE12MFP_I2C0_SCL | SYS_GPE_MFPH_PE13MFP_I2C0_SDA);

	/* Set GPA multi-function pins for SC UART mode */
	SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk);
	SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA0MFP_SC0_CLK | SYS_GPA_MFPL_PA1MFP_SC0_DAT);
	
	/* Configure the GPB0 - GPB3 ADC analog input pins.  */
	SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB12MFP_Msk);
	SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB11MFP_EADC_CH8 | SYS_GPB_MFPH_PB12MFP_EADC_CH9);
	/* Disable the GPB11 - GPB12 digital input path to avoid the leakage current. */
	GPIO_DISABLE_DIGITAL_PATH(PB, 0x1800);
		
	FMC_Open();
	chipUID[0] = FMC_ReadUID(0);
	chipUID[1] = FMC_ReadUID(1);
	chipUID[2] = FMC_ReadUID(2);
	FMC_Close();
	
	/* Lock protected registers */
	SYS_LockReg();
}

void HardwareIOInit(void){
	GPIO_SetMode(BUTT_SW1_PORT, BUTT_SW1_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(BUTT_SW2_PORT, BUTT_SW2_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(BUTT_SW3_PORT, BUTT_SW3_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(BUTT_SW4_PORT, BUTT_SW4_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(BUTT_SW5_PORT, BUTT_SW5_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(BUTT_SW6_PORT, BUTT_SW6_BIT, GPIO_MODE_INPUT);

	GPIO_SetMode(SWITCH_DOOR_PORT, SWITCH_DOOR_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(SWITCH_SHOCK_PORT, SWITCH_SHOCK_BIT, GPIO_MODE_INPUT);
	
	GPIO_SetMode(LEVEL_SENSOR1_PORT, LEVEL_SENSOR1_BIT, GPIO_MODE_INPUT);
	GPIO_SetMode(LEVEL_SENSOR2_PORT, LEVEL_SENSOR2_BIT, GPIO_MODE_INPUT);
	
	GPIO_SetMode(LED_BLINK_PORT, LED_BLINK_BIT, GPIO_MODE_OUTPUT);

	GPIO_SetMode(BILL_PWR_PORT, BILL_PWR_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(COIN_PWR_PORT, COIN_PWR_BIT, GPIO_MODE_OUTPUT);
	
	GPIO_SetMode(RELAY_CH1_PORT, RELAY_CH1_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RELAY_CH2_PORT, RELAY_CH2_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RELAY_CH3_PORT, RELAY_CH3_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RELAY_CH4_PORT, RELAY_CH4_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RELAY_CH5_PORT, RELAY_CH5_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RELAY_CH6_PORT, RELAY_CH6_BIT, GPIO_MODE_OUTPUT);
	
	GPIO_SetMode(FRONT_LED1_PORT, FRONT_LED1_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(FRONT_LED2_PORT, FRONT_LED2_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(FRONT_LED3_PORT, FRONT_LED3_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(FRONT_LED4_PORT, FRONT_LED4_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(FRONT_LED5_PORT, FRONT_LED5_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(FRONT_LED6_PORT, FRONT_LED6_BIT, GPIO_MODE_OUTPUT);
	
	GPIO_SetMode(QR_TRIGGER_PORT, QR_TRIGGER_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(LDO_POWER_PORT, LDO_POWER_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(AUDIO_POWER_PORT, AUDIO_POWER_BIT, GPIO_MODE_OUTPUT);
	
	GPIO_SetMode(LAMP_IO_PORT, LAMP_IO_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(STATUS_IO_PORT, STATUS_IO_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(SIREN_IO_PORT, SIREN_IO_BIT, GPIO_MODE_OUTPUT);
	
	LED_BLINK_PIN = 0;
	
	BILL_PWR_PIN = 0;
	COIN_PWR_PIN = 0;
	
	RELAY_CH1_PIN = 0;
	RELAY_CH2_PIN = 0;
	RELAY_CH3_PIN = 0;
	RELAY_CH4_PIN = 0;
	RELAY_CH5_PIN = 0;
	RELAY_CH6_PIN = 0;
	
	FRONT_LED1_PIN = 0;
	FRONT_LED2_PIN = 0;
	FRONT_LED3_PIN = 0;
	FRONT_LED4_PIN = 0;
	FRONT_LED5_PIN = 0;
	FRONT_LED6_PIN = 0;
	
	QR_TRIGGER_PIN = 0;
	LDO_POWER_PIN = 1;
	AUDIO_POWER_PIN = 0;
	
	LAMP_IO_PIN = 0;
	STATUS_IO_PIN = 0;
	SIREN_IO_PIN = 0;
}

void AppCarCleaningInit(void){
	SYS_Init();
	if(SysTick_Config(SystemCoreClock / 1000)){ while (1);}

	HardwareIOInit();
	ScrPageInit();
	BuzzerInit();
	SoftSerial1Init(9600);	//Display 7-Segment
	SoftSerial2Init(9600);	//JQ6500 Audio
	UART_Open(UART0, 9600);	//Esp32	
	UART_Open(UART1, 9600);	// Coin
	UART_SetLine_Config(UART1,9600,UART_WORD_LEN_8,UART_PARITY_EVEN,UART_STOP_BIT_1);
	UART_Open(UART2, 9600);	// Bank
	UART_SetLine_Config(UART2,9600,UART_WORD_LEN_8,UART_PARITY_EVEN,UART_STOP_BIT_1);
	UART_Open(UART3, 9600);	// LCD Display
	SCUART_Open(SC0, 9600);	// QR Reader
	RTCInit();
	EEPROMInit();
	EADCInit();
	BuzzBeep(1);
	ScrPage(AppScrInitDo,AppScrInitTask10ms,AppScrInitTask100ms);
}

void AppWhileLoop(void){
	ESP32Listen();
	LCDDisplayListen();
	QRReaderListen();
	UCAListen();
	TK77Listen();
	JQ6500Listen();
//	SensorListen();
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################             Timer Task            ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void AppTask1ms(void){

}

void AppTask10ms(void){
	unsigned int buf_coin = 0;
	unsigned int buf_bank = 0;
	
	UCATask10ms();
	buf_coin = UCAGetValCoin();
	if(buf_coin != 0){
		money_temp += buf_coin;
		switch(buf_coin){
			case 1:
				money_coin1 += 1;
			break;
			case 2:
				money_coin2 += 1;
			break;
			case 5:
				money_coin5 += 1;
			break;
			case 10:
				money_coin10 += 1;
			break;
			default:
			break;
		}
	}

	TK77Task10ms();
	buf_bank = TK77GetValBill();
	if(buf_bank != 0){
		money_temp += buf_bank;
		switch(buf_bank){
			case 20:
				money_bank20 += 1;
			break;
			case 50:
				money_bank50 += 1;
			break;
			case 100:
				money_bank100 += 1;
			break;
			case 500:
				money_bank500 += 1;
			break;
			case 1000:
				money_bank1000 += 1;
			break;
			default:
			break;
		}
	}
	
	ScrTask10ms();
}

void AppTask100ms(void){
	bt_res bres;
	ButtonScan();
	while(ButtonGetMesCnt()){
		bres = ButtonGetMes();
		if(bres.type != NULL){
			if(bres.type == STATUS_PRESS){
				BuzzBeep(1);
			}
			ScrButtonDo(bres.type,bres.ch);
		}
	}

	ScrTask100ms();
	JQ6500Task100ms();
}

void AppTask500ms(void){
	LED_BLINK_PIN ^= 1;
	RTCGetTime(&time);
	LampSchedule(0);
	SoundSchedule(0);
//	if(time_500ms_cnt & 1){
//		UART_WRITE(UART0,'1');
//	}
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################       EADC interrupt handler      ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void ADC00_IRQHandler(void){
	unsigned int adc8,adc9;
	adc8 = EADC_GET_CONV_DATA(EADC, 0);
	adc8 = adc8;
	adc9 = EADC_GET_CONV_DATA(EADC, 1);
	adc9 = adc9;
	EADC_CLR_INT_FLAG(EADC, 0x1);      /* Clear the A/D ADINT0 interrupt flag */
}

void EADCInit(void){
	/* Set the ADC internal sampling time, input mode as single-end and enable the A/D converter */
	EADC_Open(EADC, EADC_CTL_DIFFEN_SINGLE_END);
	EADC_SetInternalSampleTime(EADC, 6);
	
	/* Configure the sample 0 module for analog input channel 8 and enable ADINT0 trigger source */
	EADC_ConfigSampleModule(EADC, 0, EADC_ADINT0_TRIGGER, 8);
	/* Configure the sample 1 module for analog input channel 9 and enable ADINT0 trigger source */
	EADC_ConfigSampleModule(EADC, 1, EADC_ADINT0_TRIGGER, 9);
	
	/* Clear the A/D ADINT0 interrupt flag for safe */
	EADC_CLR_INT_FLAG(EADC, 0x1);

	/* Enable the sample module 4 interrupt */
	EADC_ENABLE_INT(EADC, 0x1);//Enable sample module  A/D ADINT0 interrupt.
	EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, (0x1 << 0));//Enable sample module 4 interrupt.
	NVIC_EnableIRQ(ADC00_IRQn);
	EADC_START_CONV(EADC, (0x1 << 0));
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################        Function Serial Oil        ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void ESP32Listen(void){
	unsigned char c;
	while(UART_IS_RX_READY(UART0)){
		c = UART_READ(UART0);
		UART_WRITE(UART0,c);
//		SCUART_WRITE(SC0,c);
//		if(c == 'A'){
//			SYS_UnlockReg();
//			SYS_ResetChip();
//			SYS_LockReg();
//		}
	}
}

void LCDDisplayListen(void){
	unsigned char c;
	while(UART_IS_RX_READY(UART3)){
		c = UART_READ(UART3);
		UART_WRITE(UART3,c);
//		if(c == 'A'){
//			aaa++;
//			UART_WRITE(UART3,0x6E);
//			UART_WRITE(UART3,0x30);
//			UART_WRITE(UART3,0x2E);
//			UART_WRITE(UART3,0x76);
//			UART_WRITE(UART3,0x61);
//			UART_WRITE(UART3,0x6C);
//			UART_WRITE(UART3,0x3D);
//			UART_WRITE(UART3,0x35);
//			UART_WRITE(UART3,48+aaa);
//			UART_WRITE(UART3,0xFF);
//			UART_WRITE(UART3,0xFF);
//			UART_WRITE(UART3,0xFF);
//		}
	}
}

void QRReaderListen(void){
//	unsigned char c;
	while(SCUART_IS_RX_READY(SC0)){
//		c = SCUART_READ(SC0);
//		SCUART_WRITE(SC0,c);
		UART_WRITE(UART0,SCUART_READ(SC0));
	}
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################        Function On-Off Light      ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
unsigned char _chk_time1_more(time_t *time1, time_t *time2){
	if(time1->hour > time2->hour){
		return(1);
	}
	if(time1->hour < time2->hour){
		return(2);
	}
	if(time1->min > time2->min){
		return(1);
	}
	if(time1->min < time2->min){
		return(2);
	}
	if(time1->sec > time2->sec){
		return(1);
	}
	if(time1->sec < time2->sec){
		return(2);
	}
	return(0);
}

void LampSchedule(unsigned char force_chk){
	unsigned char res1,res2,res;
	if((force_chk == 1) || ((time.sec == 0))){
		res = _chk_time1_more(&ee_config.light_on,&ee_config.light_off);
		res1 = _chk_time1_more(&time,&ee_config.light_on);
		res2 = _chk_time1_more(&time,&ee_config.light_off);
		if(res == 1){ //on > off
			if((res1 == 1) || (res2 == 2)){ //(time > on) || (time < off)
				LAMP_IO_PIN = 1;
			}else{
				LAMP_IO_PIN = 0;
			}
			return;
		}
		if(res == 2){ //off > on
			if((res1 == 1) && (res2 == 2)){ //(time > on) && (time < off)
				LAMP_IO_PIN = 1;
			}else{
				LAMP_IO_PIN = 0;
			}
			return;
		}
		LAMP_IO_PIN = 1;	//always on
	}
}

void SoundSchedule(unsigned char force_chk){
	static unsigned char active_sound = 0;
	unsigned char res1,res2,res;
	if((force_chk == 1) || ((time.sec == 0))){
		if(force_chk == 1){
			active_sound = 2;
		}
		res = _chk_time1_more(&ee_config.sound_day,&ee_config.sound_night);
		res1 = _chk_time1_more(&time,&ee_config.sound_day);
		res2 = _chk_time1_more(&time,&ee_config.sound_night);
		if(res == 1){ //on > off
			if((res1 == 1) || (res2 == 2)){ //(time > on) || (time < off)
				if(active_sound != 1){
					JQ6500Volume(ee_config.snd_lv_hi); 	// sound lv hight
					active_sound = 1;
				}
			}else{
				if(active_sound != 0){
					JQ6500Volume(ee_config.snd_lv_low);	// sound lv low
					active_sound = 0;
				}
			}
			return;
		}
		if(res == 2){ //off > on
			if((res1 == 1) && (res2 == 2)){ //(time > on) && (time < off)
				if(active_sound != 1){
					JQ6500Volume(ee_config.snd_lv_hi);	// sound lv hight
					active_sound = 1;
				}
			}else{
				if(active_sound != 0){
					JQ6500Volume(ee_config.snd_lv_low);	// sound lv low
					active_sound = 0;
				}
			}
			return;
		}
		
		if(active_sound != 1){
			JQ6500Volume(ee_config.snd_lv_hi); //always on
			active_sound = 1;
		}
	}
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################             Function All          ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void PowerOnOffBankCoin(unsigned char state){
	BILL_PWR_PIN = state;
	COIN_PWR_PIN = state;
}

void OnOffChannelRelay(unsigned char ch,unsigned char state){
	if(ch == 0){
		RELAY_CH1_PIN = state;
		FRONT_LED1_PIN = state;
		LAMP_IO_PIN = state;
	}else if(ch == 1){
		RELAY_CH2_PIN = state;
		FRONT_LED2_PIN = state;
		STATUS_IO_PIN = state;
	}else if(ch == 2){
		RELAY_CH3_PIN = state;
		FRONT_LED3_PIN = state;
		SIREN_IO_PIN = state;
	}else if(ch == 3){
		RELAY_CH4_PIN = state;
		FRONT_LED4_PIN = state;
	}else if(ch == 4){
		RELAY_CH5_PIN = state;
		FRONT_LED5_PIN = state;
	}else if(ch == 5){
		RELAY_CH6_PIN = state;
		FRONT_LED6_PIN = state;
	}
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################            App Screen All         ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
//###########################################################################
void AppScrInitTask10ms(void){

}

void AppScrInitTask100ms(void){
	cnt_100ms++;
	if(cnt_100ms == 5){
		ScrPage(AppScrStandbyDo,AppScrStandbyTask10ms,AppScrStandbyTask100ms);
//		ScrPage(AppScrTestDo,AppScrTestTask10ms,AppScrTestTask100ms);
		JQ6500PlayOne(SND_INDEX_1);
	}
}

void AppScrInitDo(unsigned char acction,unsigned char type,char key){
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			ReadEEPROMConfig(&ee_config);
////			ReadEEPROMProfile();
			if(ee_config.firmware_valid != FIRMWARE_VALUE_VALID){
				SetEEPROMConfigDefault();
//				SetEEPROMTransectionDefault();
//				SetEEPROMRunSellDefault();
			}

////			EEPROMClearChipAll(); //Test
////			SetEEPROMProfileDefault(); //Test
////			SetEEPROMRunSellDefault(); //Test
////			ReadEEPROMConfig(); //Test
//			ReadEEPROMTransection();
//			ReadEEPROMRunSell();
//			ReadEEPROMTransactionAllIndex();

//			if(cfg.timeout_off_battery < CFG_TIMEOUT_OFF_BATTERY){
//				cfg.timeout_off_battery = CFG_TIMEOUT_OFF_BATTERY;
//			}
			RTCGetTime(&time);
			LampSchedule(1);
			SoundSchedule(1);
		break;
		case ACTION_BUTTON:
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrStandbyTask10ms(void){
	
}

void AppScrStandbyTask100ms(void){
	if(runsell.money_in_box != money_temp){
		cnt_100ms_waste_money = 0;
		money_user += (money_temp - runsell.money_in_box);
		runsell.money_in_box = money_temp;
		Display7SegmentMoney(money_user);
		ScrPage(AppScrCheckDispenserDo,AppScrCheckDispenserTask10ms,AppScrCheckDispenserTask100ms);
	}else{
		cnt_100ms++;
		if(cnt_100ms == 5){
			cnt_100ms = 0;
			Display7SegmentTime(time);
		}
	}
	
	if((cnt_100ms_waste_money > 0) && (money_user > 0)){
		cnt_100ms_waste_money++;
		if(cnt_100ms_waste_money >= (ee_config.waste_money*10)){
			ScrPage(AppScrStandbyDo,AppScrStandbyTask10ms,AppScrStandbyTask100ms);
		}
	}
}

void AppScrStandbyDo(unsigned char acction,unsigned char type,char key){
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			money_temp = 0;
			money_user = 0;

			cnt_100ms_waste_money = 0;
		
			status_bt_relay[0] = STATUS_BT_STANDBY;
			status_bt_relay[1] = STATUS_BT_STANDBY;
			status_bt_relay[2] = STATUS_BT_STANDBY;
			status_bt_relay[3] = STATUS_BT_STANDBY;
			status_bt_relay[4] = STATUS_BT_STANDBY;
			status_bt_relay[5] = STATUS_BT_STANDBY;

			total_time_relay[0] = 0;
			total_time_relay[1] = 0;
			total_time_relay[2] = 0;
			total_time_relay[3] = 0;
			total_time_relay[4] = 0;
			total_time_relay[5] = 0;

			time_user_relay[0] = 0;
			time_user_relay[1] = 0;
			time_user_relay[2] = 0;
			time_user_relay[3] = 0;
			time_user_relay[4] = 0;
			time_user_relay[5] = 0;
			
			TK77Start();
			UCAStart();
			PowerOnOffBankCoin(BILL_COIN_ON);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_MODE :
					if(type == STATUS_PRESS){
						flag_bt_mode = 0;
//					}else if(type == STATUS_RELEASE){
//						if(flag_bt_mode == 0xFF){
//							flag_sel_menu = 0;
//						}
//						flag_bt_mode = 0;
					}else{
						if(flag_bt_mode == BUTTON_TIME_HOLD*10){
							flag_bt_mode = 0xFF;
							BuzzBeep(10);
							TK77Stop();
							UCAStop();
							PowerOnOffBankCoin(BILL_COIN_OFF);
							ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
						}else if(flag_bt_mode <= BUTTON_TIME_HOLD*10){
							flag_bt_mode++;
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrCheckDispenserTask10ms(void){
	
}

void AppScrCheckDispenserTask100ms(void){
	if(runsell.money_in_box != money_temp){
		money_user += (money_temp - runsell.money_in_box);
		runsell.money_in_box = money_temp;
		Display7SegmentMoney(money_user);
	}
}

void AppScrCheckDispenserDo(unsigned char acction,unsigned char type,char key){
	char i;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			button_used = 0;
			Display7SegmentMoney(money_user);
		break;
		case ACTION_BUTTON:
			if(type == STATUS_RELEASE){
//				if(cfg.button_mode == CFG_BUTTON_MODE_SINGLE){
					for(i=0;i<BUTTON_NUM-3;i++){
						if(key == button_key_array[i]){
							if(money_user >= ee_config.min_price){
								button_used |= (1 << i);
								status_bt_relay[i] = STATUS_BT_DISPENSING;
								OnOffChannelRelay(i,RELAY_CTL_ON);
								Display7SegmentMoneyBlink(money_user);
								ScrPage(AppScrDispenserDo,AppScrDispenserTask10ms,AppScrDispenserTask100ms);
							}else{
								
							}
						}
					}
				}else{
					
				}
//			}else{
//				
//			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrDispenserTask10ms(void){
	
}

void AppScrDispenserTask100ms(void){
	char i;
	unsigned int time_buf;
	unsigned int check_dot;
	double money_buf;
	if(runsell.money_in_box != money_temp){
		money_user += (money_temp - runsell.money_in_box);
		runsell.money_in_box = money_temp;
		check_dot = (money_user * 10);
		check_dot %= 10;
		if(check_dot != 0){
			check_dot = money_user + 1;
			if(button_used){
				Display7SegmentMoneyBlink(check_dot);
			}else{
				Display7SegmentMoney(check_dot);
			}
		}else{
			if(button_used){
				Display7SegmentMoneyBlink(money_user);
			}else{
				Display7SegmentMoney(money_user);
			}
		}
	}
	
	if(money_user > 0.0){
		if(status_bt_relay[0] == STATUS_BT_DISPENSING){
			time_user_relay[0]++;
			time_buf = (ee_config.bahtpermsec_relay[0] / 10);
			if(time_user_relay[0] >= time_buf){
				total_time_relay[0] += time_user_relay[0];
				time_user_relay[0] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}

		if(status_bt_relay[1] == STATUS_BT_DISPENSING){
			time_user_relay[1]++;
			time_buf = (ee_config.bahtpermsec_relay[1] / 10);
			if(time_user_relay[1] >= time_buf){
				total_time_relay[1] += time_user_relay[1];
				time_user_relay[1] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}

		if(status_bt_relay[2] == STATUS_BT_DISPENSING){
			time_user_relay[2]++;
			time_buf = (ee_config.bahtpermsec_relay[2] / 10);
			if(time_user_relay[2] >= time_buf){
				total_time_relay[2] += time_user_relay[2];
				time_user_relay[2] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}

		if(status_bt_relay[3] == STATUS_BT_DISPENSING){
			time_user_relay[3]++;
			time_buf = (ee_config.bahtpermsec_relay[3] / 10);
			if(time_user_relay[3] >= time_buf){
				total_time_relay[3] += time_user_relay[3];
				time_user_relay[3] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}

		if(status_bt_relay[4] == STATUS_BT_DISPENSING){
			time_user_relay[4]++;
			time_buf = (ee_config.bahtpermsec_relay[4] / 10);
			if(time_user_relay[4] >= time_buf){
				total_time_relay[4] += time_user_relay[4];
				time_user_relay[4] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}

		if(status_bt_relay[5] == STATUS_BT_DISPENSING){
			time_user_relay[5]++;
			time_buf = (ee_config.bahtpermsec_relay[4] / 10);
			if(time_user_relay[5] >= time_buf){
				total_time_relay[5] += time_user_relay[5];
				time_user_relay[5] = 0;
				
				money_buf = money_user - 0.10;
				if(money_buf < 0.10){
					money_user = 0;
				}else{
					money_user = money_buf;
				}
				
				check_dot = (money_user * 10);
				check_dot %= 10;
				if(check_dot == 0){
					if(button_used){
						Display7SegmentMoneyBlink(money_user);
					}else{
						Display7SegmentMoney(money_user);
					}
				}
			}
		}
				
		if(money_user <= 0){
			money_temp = 0;
			runsell.money_in_box = 0;
			money_user = 0;
			button_used = 0;
			Display7SegmentMoney(0);
			for(i=0;i<BUTTON_NUM-3;i++){
				status_bt_relay[i] = STATUS_BT_STANDBY;
				OnOffChannelRelay(i,RELAY_CTL_OFF);
			}
			ScrPage(AppScrCheckDispenserDo,AppScrCheckDispenserTask10ms,AppScrCheckDispenserTask100ms);
		}
	}
}

void AppScrDispenserDo(unsigned char acction,unsigned char type,char key){
	char i;
	unsigned int check_dot;
	unsigned char button_bit;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
		break;
		case ACTION_BUTTON:
			if(type == STATUS_RELEASE){
				if(ee_config.button_mode == CFG_BUTTON_MODE_SINGLE){
					for(i=0;i<BUTTON_NUM-3;i++){
						if(key == button_key_array[i]){
							if(money_user >= 0.0){
								if(button_used == 0){
									button_used |= (1 << i);
									status_bt_relay[i] = STATUS_BT_DISPENSING;
									OnOffChannelRelay(i,RELAY_CTL_ON);
									
									check_dot = (money_user * 10);
									check_dot %= 10;
									if(check_dot != 0){
										check_dot = money_user + 1;
										Display7SegmentMoneyBlink(check_dot);
									}else{
										Display7SegmentMoneyBlink(money_user);
									}
								}else{
									button_bit = (1 << i);
									if((button_bit & button_used)){
										if(status_bt_relay[i] == STATUS_BT_DISPENSING){
											button_used = 0;
											status_bt_relay[i] = STATUS_BT_PAUSE;
											OnOffChannelRelay(i,RELAY_CTL_OFF);
																				
											check_dot = (money_user * 10);
											check_dot %= 10;
											if(check_dot != 0){
												check_dot = money_user + 1;
												Display7SegmentMoney(check_dot);
											}else{
												Display7SegmentMoney(money_user);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuSettingTask10ms(void){

}

void AppScrMenuSettingTask100ms(void){

}

void AppScrMenuSettingDo(unsigned char acction,unsigned char type,char key){
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			Display7SegmentNameMenu(&name_menu_table1[flag_sel_menu][0],DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_PRESS){
						if(flag_sel_menu >= DISPLAY_MENU_SETTING_MAX){
							flag_sel_menu = 0;
						}else{
							flag_sel_menu++;
						}
						Display7SegmentNameMenu(&name_menu_table1[flag_sel_menu][0],DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL);
					}
				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						if(flag_sel_menu > 0){
							flag_sel_menu--;
						}else{
							flag_sel_menu = DISPLAY_MENU_SETTING_MAX;
						}
						Display7SegmentNameMenu(&name_menu_table1[flag_sel_menu][0],DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL);
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						if(flag_sel_menu == 0){
							ScrPage(AppScrMenuE01SettingDo,AppScrMenuE01SettingTask10ms,AppScrMenuE01SettingTask100ms);
						}else if(flag_sel_menu == 1){
							ScrPage(AppScrMenuE02SettingDo,AppScrMenuE02SettingTask10ms,AppScrMenuE02SettingTask100ms);
						}else if(flag_sel_menu == 2){
							ScrPage(AppScrMenuE03SettingDo,AppScrMenuE03SettingTask10ms,AppScrMenuE03SettingTask100ms);
						}else if(flag_sel_menu == 3){
							ScrPage(AppScrMenuE04SettingDo,AppScrMenuE04SettingTask10ms,AppScrMenuE04SettingTask100ms);
						}else if(flag_sel_menu == 4){
							ScrPage(AppScrMenuE05SettingDo,AppScrMenuE05SettingTask10ms,AppScrMenuE05SettingTask100ms);
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuE01SettingTask10ms(void){
	
}

void AppScrMenuE01SettingTask100ms(void){
	cnt_100ms++;
	if(cnt_100ms == 15){
		Display7Segment("    ",DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL,0);
	}else if(cnt_100ms == 20){
		Display7SegmentMoney(trans.money_bank);
	}else if(cnt_100ms == 40){
		Display7Segment("    ",DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL,0);
	}else if(cnt_100ms == 45){
		Display7SegmentMoney(trans.money_total);
	}else if(cnt_100ms == 75){
		Display7Segment("    ",DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL,0);
	}else if(cnt_100ms == 80){
		Display7SegmentMoney(trans.money_coin);
		cnt_100ms = 0;
	}
}

void AppScrMenuE01SettingDo(unsigned char acction,unsigned char type,char key){
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			trans.money_coin = 10;
			trans.money_bank = 20;
			trans.money_total = 30;
			Display7SegmentMoney(trans.money_coin);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :

				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						flag_bt_down = 0;
					}else if(type == STATUS_RELEASE){
						if(flag_bt_down == 0xFF){
							trans.money_coin = 0;
							trans.money_bank = 0;
							trans.money_total = 0;
						}
						flag_bt_down = 0;
					}else{
						if(flag_bt_down == BUTTON_TIME_HOLD*10){
							flag_bt_down = 0xFF;
							BuzzBeep(10);
						}else if(flag_bt_down <= BUTTON_TIME_HOLD*10){
							flag_bt_down++;
						}
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuE02SettingTask10ms(void){
	
}

void AppScrMenuE02SettingTask100ms(void){
	cnt_100ms++;
	if(flag_time_edit == 0){
		if(cnt_100ms == 5){
			cnt_100ms = 0;
			Display7SegmentTimeSetting(time);
		}
	}
}

void AppScrMenuE02SettingDo(unsigned char acction,unsigned char type,char key){
	unsigned char buf_hi,buf_lo;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			
			flag_bt_mode = 0xFF;
			flag_time_edit = 0;
			Display7SegmentTimeSetting(time);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							buf_hi = time_edit.hour / 10;
							if(buf_hi >= 2){
								time_edit.hour %= 10;
							}else{
								time_edit.hour += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}else if(flag_time_edit == 2){
							buf_hi = time_edit.hour / 10;
							if(buf_hi == 2){
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 3){
									time_edit.hour = 20;
								}else{
									time_edit.hour += 1;
								}
							}else{
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 9){
									time_edit.hour = buf_hi * 10;
								}else{
									time_edit.hour += 1;
								}
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 3){
							buf_hi = time_edit.min / 10;
							if(buf_hi >= 5){
								time_edit.min %= 10;
							}else{
								time_edit.min += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 4){
							buf_hi = time_edit.min % 10;
							if(buf_hi >= 9){
								buf_lo = time_edit.min / 10;
								time_edit.min = buf_lo * 10;
							}else{
								time_edit.min += 1;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}
					}
				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							flag_time_edit = 2;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 2){
							flag_time_edit = 3;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 3){
							flag_time_edit = 4;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}else if(flag_time_edit == 4){
							flag_time_edit = 1;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						flag_bt_mode = 0;
					}else if(type == STATUS_RELEASE){
						if(flag_bt_mode != 0xFF){
							if(flag_time_edit != 0 ){
								ScrPage(AppScrMenuE02SettingDo,AppScrMenuE02SettingTask10ms,AppScrMenuE02SettingTask100ms);
							}else{
								ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
							}
						}
					}else{
						if(flag_bt_mode == BUTTON_TIME_HOLD*10){
							flag_bt_mode = 0xFF;
							BuzzBeep(10);
							if(flag_time_edit == 0){
								flag_time_edit = 1;
								time_edit = time;
								Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
							}else{
								cnt_100ms = 0;
								flag_time_edit = 0;
								time_edit.sec = 0;
								RTCSetTime(time_edit);
								Display7SegmentTimeSetting(time_edit);
							}
						}else if(flag_bt_mode <= BUTTON_TIME_HOLD*10){
							flag_bt_mode++;
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuE03SettingTask10ms(void){
	
}

void AppScrMenuE03SettingTask100ms(void){

}

void AppScrMenuE03SettingDo(unsigned char acction,unsigned char type,char key){
	unsigned char buf_hi,buf_lo;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
			
			flag_bt_mode = 0xFF;
			flag_time_edit = 0;
			time_edit = ee_config.light_on;
			Display7SegmentTimeSetting(time_edit);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							buf_hi = time_edit.hour / 10;
							if(buf_hi >= 2){
								time_edit.hour %= 10;
							}else{
								time_edit.hour += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}else if(flag_time_edit == 2){
							buf_hi = time_edit.hour / 10;
							if(buf_hi == 2){
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 3){
									time_edit.hour = 20;
								}else{
									time_edit.hour += 1;
								}
							}else{
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 9){
									time_edit.hour = buf_hi * 10;
								}else{
									time_edit.hour += 1;
								}
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 3){
							buf_hi = time_edit.min / 10;
							if(buf_hi >= 5){
								time_edit.min %= 10;
							}else{
								time_edit.min += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 4){
							buf_hi = time_edit.min % 10;
							if(buf_hi >= 9){
								buf_lo = time_edit.min / 10;
								time_edit.min = buf_lo * 10;
							}else{
								time_edit.min += 1;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}
					}
				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							flag_time_edit = 2;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 2){
							flag_time_edit = 3;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 3){
							flag_time_edit = 4;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}else if(flag_time_edit == 4){
							flag_time_edit = 1;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						flag_bt_mode = 0;
					}else if(type == STATUS_RELEASE){
						if(flag_bt_mode != 0xFF){
							if(flag_time_edit != 0 ){
								ScrPage(AppScrMenuE03SettingDo,AppScrMenuE03SettingTask10ms,AppScrMenuE03SettingTask100ms);
							}else{
								ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
							}
						}
					}else{
						if(flag_bt_mode == BUTTON_TIME_HOLD*10){
							flag_bt_mode = 0xFF;
							BuzzBeep(10);
							if(flag_time_edit == 0){
								flag_time_edit = 1;
								time_edit = ee_config.light_on;
								Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
							}else{
								cnt_100ms = 0;
								flag_time_edit = 0;
								ee_config.light_on = time_edit;
								WriteEEPROMConfig(ee_config);
								Display7SegmentTimeSetting(ee_config.light_on);
							}
						}else if(flag_bt_mode <= BUTTON_TIME_HOLD*10){
							flag_bt_mode++;
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuE04SettingTask10ms(void){
	
}

void AppScrMenuE04SettingTask100ms(void){

}

void AppScrMenuE04SettingDo(unsigned char acction,unsigned char type,char key){
	unsigned char buf_hi,buf_lo;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
					
			flag_bt_mode = 0xFF;
			flag_time_edit = 0;
			time_edit = ee_config.light_off;
			Display7SegmentTimeSetting(time_edit);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_RELEASE){
						if(flag_time_edit == 1){
							buf_hi = time_edit.hour / 10;
							if(buf_hi >= 2){
								time_edit.hour %= 10;
							}else{
								time_edit.hour += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}else if(flag_time_edit == 2){
							buf_hi = time_edit.hour / 10;
							if(buf_hi == 2){
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 3){
									time_edit.hour = 20;
								}else{
									time_edit.hour += 1;
								}
							}else{
								buf_lo = time_edit.hour % 10;
								if(buf_lo >= 9){
									time_edit.hour = buf_hi * 10;
								}else{
									time_edit.hour += 1;
								}
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 3){
							buf_hi = time_edit.min / 10;
							if(buf_hi >= 5){
								time_edit.min %= 10;
							}else{
								time_edit.min += 10;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 4){
							buf_hi = time_edit.min % 10;
							if(buf_hi >= 9){
								buf_lo = time_edit.min / 10;
								time_edit.min = buf_lo * 10;
							}else{
								time_edit.min += 1;
							}
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}
					}
				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							flag_time_edit = 2;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT2);
						}else if(flag_time_edit == 2){
							flag_time_edit = 3;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT3);
						}else if(flag_time_edit == 3){
							flag_time_edit = 4;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT4);
						}else if(flag_time_edit == 4){
							flag_time_edit = 1;
							Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
						}
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						flag_bt_mode = 0;
					}else if(type == STATUS_RELEASE){
						if(flag_bt_mode != 0xFF){
							if(flag_time_edit != 0 ){
								ScrPage(AppScrMenuE04SettingDo,AppScrMenuE04SettingTask10ms,AppScrMenuE04SettingTask100ms);
							}else{
								ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
							}
						}
					}else{
						if(flag_bt_mode == BUTTON_TIME_HOLD*10){
							flag_bt_mode = 0xFF;
							BuzzBeep(10);
							if(flag_time_edit == 0){
								flag_time_edit = 1;
								time_edit = ee_config.light_off;
								Display7SegmentTimeEdit(time_edit,DISPLAY_7SEG_DOT_ON2,BLINK_AT1);
							}else{
								cnt_100ms = 0;
								flag_time_edit = 0;
								ee_config.light_off = time_edit;
								WriteEEPROMConfig(ee_config);
								Display7SegmentTimeSetting(ee_config.light_off);
							}
						}else if(flag_bt_mode <= BUTTON_TIME_HOLD*10){
							flag_bt_mode++;
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrMenuE05SettingTask10ms(void){
	
}

void AppScrMenuE05SettingTask100ms(void){

}

void AppScrMenuE05SettingDo(unsigned char acction,unsigned char type,char key){
	unsigned int buf_hi,buf_lo;
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
		
			flag_bt_mode = 0xFE;
		
			flag_time_edit = 0;
			buf1 = ee_config.min_price;
			Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL);
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_RELEASE){
						if(flag_time_edit == 1){
							buf1 += 1000;
							if(buf1 >= 10000){
								buf1 -= 10000;
							}
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT1);
						}else if(flag_time_edit == 2){
							buf_hi = ((buf1 / 100) % 10 ) * 100;
							buf_lo = buf_hi + 100;
							if(buf_lo >= 1000){
								buf1 -= 900;
							}else{
								buf1 += 100;
							}
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT2);
						}else if(flag_time_edit == 3){
							buf_hi = (buf1 / 10) % 10;
							if(buf_hi >= 9){
								buf1 -= 90;
							}else{
								buf1 += 10;
							}
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT3);
						}else if(flag_time_edit == 4){
							buf_hi = buf1 % 10;
							if(buf_hi >= 9){
								buf1 -= 9;
							}else{
								buf1 += 1;
							}
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT4);
						}
					}
				break;
				case BT_DOWN :
					if(type == STATUS_PRESS){
						if(flag_time_edit == 1){
							flag_time_edit = 2;
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT2);
						}else if(flag_time_edit == 2){
							flag_time_edit = 3;
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT3);
						}else if(flag_time_edit == 3){
							flag_time_edit = 4;
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT4);
						}else if(flag_time_edit == 4){
							flag_time_edit = 1;
							Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT1);
						}
					}
				break;
				case BT_MODE :
					if(type == STATUS_PRESS){
						flag_bt_mode = 0;
					}else if(type == STATUS_RELEASE){
						if(flag_bt_mode == 0xFF){
							if(flag_time_edit == 0){
								flag_time_edit = 1;
								Display7SegmentNumEdit(buf1,DISPLAY_7SEG_DOT_OFF,BLINK_AT1);
							}else{
								ee_config.min_price = buf1;
								WriteEEPROMConfig(ee_config);
								ScrPage(AppScrMenuE05SettingDo,AppScrMenuE05SettingTask10ms,AppScrMenuE05SettingTask100ms);
							}
						}else{
							if(flag_bt_mode != 0xFE){
								if(flag_time_edit != 0){
									ScrPage(AppScrMenuSettingDo,AppScrMenuSettingTask10ms,AppScrMenuSettingTask100ms);
								}else{
									flag_time_edit = 0;
									Display7SegmentNumEdit(ee_config.min_price,DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL);
								}
							}else{
								flag_bt_mode = 0;
							}
						}
						flag_bt_mode = 0;
					}else{
						if(flag_bt_mode == BUTTON_TIME_HOLD*10){
							flag_bt_mode = 0xFF;
							BuzzBeep(10);
						}else if(flag_bt_mode <= BUTTON_TIME_HOLD*10){
							flag_bt_mode++;
						}
					}
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
}

//###########################################################################

//###########################################################################
void AppScrTestTask10ms(void){
	
}

void AppScrTestTask100ms(void){
//	if(SWITCH_DOOR_PIN == 0){
//		OnOffChannelRelay(1,RELAY_CTL_ON);
//	}else{
//		OnOffChannelRelay(1,RELAY_CTL_OFF);
//	}
//	
//	if(SWITCH_SHOCK_PIN == 0){
//		OnOffChannelRelay(2,RELAY_CTL_ON);
//	}else{
//		OnOffChannelRelay(2,RELAY_CTL_OFF);
//	}
//	
//	if(LEVEL_SENSOR1_PIN == 0){
//		OnOffChannelRelay(3,RELAY_CTL_ON);
//	}else{
//		OnOffChannelRelay(3,RELAY_CTL_OFF);
//	}
//	
//	if(LEVEL_SENSOR2_PIN == 0){
//		OnOffChannelRelay(4,RELAY_CTL_ON);
//	}else{
//		OnOffChannelRelay(4,RELAY_CTL_OFF);
//	}
}

void AppScrTestDo(unsigned char acction,unsigned char type,char key){
	switch(acction){
		case ACTION_INIT:
			cnt_10ms = 0;
			cnt_100ms = 0;
		break;
		case ACTION_BUTTON:
			switch(key){
				case BT_UP :
					if(type == STATUS_RELEASE){
//						OnOffChannelRelay(cnt_100ms,RELAY_CTL_ON);
////						PowerOnOffBankCoin(BILL_COIN_ON);
//						if(cnt_100ms < 6 ){
//							cnt_100ms++;
//						}
////						JQ6500PlayOne(SND_INDEX_1);
//						AUDIO_POWER_PIN = 0;
					}
				break;
				case BT_DOWN :
					if(type == STATUS_RELEASE){
//						if(cnt_100ms > 0 ){
//							cnt_100ms--;
//						}
//						OnOffChannelRelay(cnt_100ms,RELAY_CTL_OFF);
////						PowerOnOffBankCoin(BILL_COIN_OFF);
//						
//						AUDIO_POWER_PIN = 1;
					}
				break;
				case BT_MODE :
					if(type == STATUS_RELEASE){
//						SCUART_Write(SC0,(uint8_t *)"$$$$#99900035;%%%%",18);
//						OnOffChannelRelay(1,RELAY_CTL_OFF);
//						JQ6500PlayOne(SND_INDEX_1);
						QR_TRIGGER_PIN ^= 1;
					}
				break;
				default:
				break;
			}

		break;
		default:
		break;
	}
}

//###########################################################################
