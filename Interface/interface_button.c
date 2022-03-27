#include "./Application/application_config.h"

typedef struct{
	unsigned char port;
	unsigned char pin;
	char ch;
} button_t;

const button_t button[BUTTON_NUM] ={
	{BUTT_SW1_NUM_PORT,BUTT_SW1_NUM_PIN,BT_RLY1},
	{BUTT_SW2_NUM_PORT,BUTT_SW2_NUM_PIN,BT_RLY2},
	{BUTT_SW3_NUM_PORT,BUTT_SW3_NUM_PIN,BT_RLY3},
	{BUTT_SW4_NUM_PORT,BUTT_SW4_NUM_PIN,BT_RLY4},
	{BUTT_SW5_NUM_PORT,BUTT_SW5_NUM_PIN,BT_RLY5},
	{BUTT_SW6_NUM_PORT,BUTT_SW6_NUM_PIN,BT_RLY6},
	
	{BUTT_UP_NUM_PORT,BUTT_UP_NUM_PIN,BT_UP},
	{BUTT_DOWN_NUM_PORT,BUTT_DOWN_NUM_PIN,BT_DOWN},
	{BUTT_MODE_NUM_PORT,BUTT_MODE_NUM_PIN,BT_MODE},
};

bt_res bt_res_buf[BUTTON_BUFFER_SIZE];

unsigned int press_val_old = 0;
unsigned char bt_res_ri = 0;
unsigned char bt_res_wi = 0;
unsigned char bt_res_cnt = 0;

void ButtonScan(void){
	int i;
	unsigned int press_val = 0;
	unsigned int buf1,buf2;
	unsigned char type;
	char ch;
	for(i=0;i<BUTTON_NUM;i++){
		if(GPIO_PIN_DATA(button[i].port,button[i].pin) == 0){
			press_val |= (1 << i);
		}
	}
	
	buf1 = press_val ^ press_val_old;
	buf2 = press_val & press_val_old;
	press_val_old = press_val;
	for(i=0; i<BUTTON_NUM; i++){
		if(buf1 & (1 << i)){ //a change occurs
			if(press_val & (1 << i)){
				type = STATUS_PRESS;
			}else{
				type = STATUS_RELEASE;
			}
			ch = button[i].ch;
			ButtonPutMes(type,ch);
		}
		if(buf2 & (1 << i)){ //a hold occurs
			ch = button[i].ch;
			ButtonPutMes(STATUS_HOLD,ch);
		}
	}
}

unsigned char ButtonGetMesCnt(void){
	return(bt_res_cnt);
}

bt_res ButtonGetMes(void){
	bt_res res;
	if(bt_res_cnt){
		res = bt_res_buf[bt_res_ri];
		if(bt_res_ri == BUTTON_BUFFER_SIZE-1){
			bt_res_ri = 0;
		}else{
			bt_res_ri++;
		}
		bt_res_cnt--;	
	}else{
		res.type = NULL;
		res.ch = ' ';
	}
	return (res);
}

void ButtonPutMes(unsigned char type, char ch){
	bt_res_buf[bt_res_wi].type = type;
	bt_res_buf[bt_res_wi].ch = ch;
	if(bt_res_wi == BUTTON_BUFFER_SIZE-1){
		bt_res_wi = 0;
	}else{
		bt_res_wi++;
	}
	bt_res_cnt++;
}
