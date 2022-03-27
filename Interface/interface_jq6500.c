#include "./Application/application_config.h"

typedef enum{
	JQ6500_NULL = 0, JQ6500_LOOP_DISADLE, JQ6500_WAIT_LOOP_DISADLE,
	JQ6500_LOOP_ENADLE, JQ6500_WAIT_LOOP_ENADLE, JQ6500_WAIT_PLAY,
	JQ6500_PLAY,
} jq6500_st_t;

const unsigned char sound_lv_array[SND_MAX_VOL_LV + 1] ={
	SND_VOL_LV0,SND_VOL_LV1,SND_VOL_LV2,SND_VOL_LV3,
	SND_VOL_LV4,SND_VOL_LV5
};

jq6500_st_t jq6500_st;

char dataSerialJQ6500[8];

char jq6500_pause[4]={0x7E,0x02,0x0E,0xEF};
char jq6500_play[6]={0x7E,0x04,0x03,0x00,0x00,0xEF};
char jq6500_volume[5]={0x7E,0x03,0x06,0x00,0xEF};
char jq6500_loopone[5]={0x7E,0x03,0x11,0x02,0xEF};
char jq6500_looponestop[5]={0x7E,0x03,0x11,0x04,0xEF};

void JQ6500Listen(void){
	char c;
	while(SoftSerial2IsRxReady()){
		c = SoftSerial2GetRx();
//		SoftSerial2SendString(&c);
		if(c == 'O'){
			dataSerialJQ6500[0] = c;
		}else{
			if(dataSerialJQ6500[0] == 'O'){
				if(c == 'P'){ //STOP -->> Check OP
					AUDIO_POWER_PIN = 0;
				}else if(c == 'K'){ //OK -->> Check OK
					if((jq6500_st == JQ6500_WAIT_LOOP_DISADLE) || (jq6500_st == JQ6500_WAIT_LOOP_ENADLE)){
						jq6500_st = JQ6500_WAIT_PLAY;
					}
				}
			}
		}
	}
}

void JQ6500Task100ms(void){
	switch(jq6500_st){
		case JQ6500_LOOP_DISADLE:
			AUDIO_POWER_PIN = 1;
			SoftSerial2SendStringLength(jq6500_looponestop,5);
			jq6500_st = JQ6500_WAIT_LOOP_DISADLE;
		break;
		case JQ6500_LOOP_ENADLE:
			AUDIO_POWER_PIN = 1;
			SoftSerial2SendStringLength(jq6500_loopone,5);
			jq6500_st = JQ6500_WAIT_LOOP_ENADLE;
		break;
		case JQ6500_WAIT_PLAY:
			jq6500_st = JQ6500_PLAY;
		break;
		case JQ6500_PLAY:
			SoftSerial2SendStringLength(jq6500_play,6);
			jq6500_st = JQ6500_NULL;
		break;
		default:
		break;
	}
}

void JQ6500PlayOne(unsigned char index){
//	if(flag_silen_on == 0){
//		jq6500_play[4] = sound_country_array[cfg.country_sound] + index;
		jq6500_play[4] = index;
		jq6500_st = JQ6500_LOOP_DISADLE;
//	}
}

void JQ6500PlayLoopMelody(void){
//	if(flag_silen_on == 0){
//		if(cfg.melody_sound != 0){
//			jq6500_play[4] = sound_melody_array[cfg.melody_sound];
//			jq6500_st = JQ6500_LOOP_ENADLE;
//		}else{
//			JQ6500Puase();
//		}
//	}
}

void JQ6500PlayLoopSiren(void){
//	jq6500_play[4] = SND_LOOP_SIREN;
//	jq6500_st = JQ6500_LOOP_ENADLE;
}

void JQ6500PuaseLoopSiren(void){
//	SoftSerialSendStrTx2(jq6500_pause,4);
//	Clrb(AUDIO_ON_PRTC,AUDIO_ON_PIN);
}

void JQ6500Puase(void){
//	if(flag_silen_on == 0){
		SoftSerial2SendStringLength(jq6500_pause,4);
		AUDIO_POWER_PIN = 0;
//	}
}

void JQ6500Volume(unsigned char vol){
	if(vol > 5){
		jq6500_volume[3]= sound_lv_array[5];
	}else{
		jq6500_volume[3]= sound_lv_array[vol];
	}
	SoftSerial2SendStringLength(jq6500_volume,5);
}

