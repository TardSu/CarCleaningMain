#include "./Application/application_config.h"

typedef enum{
	UCA_SER_NULL = 0, UCA_SER_PULL, UCA_SER_DATA,
} uca_ser_t;

typedef enum{
	UCA_NULL = 0, UCA_GET_COIN, UCA_WAIT_READ,
	UCA_SEND_VER, UCA_GET_VER,
} uca_st_t;

uca_ser_t uca_ser = UCA_SER_NULL;
uca_st_t uca_st_new = UCA_NULL;
uca_st_t uca_st_old = UCA_NULL;

const unsigned int uca_coin_ch[] =  {0,1,2,5,10,2,1,0};
char uca_ser_dat[32];
uint8_t uca_send_dat[128];
char uca_upgrad_paht[32];
char str_uca_str[160];

unsigned char cnt_uca_ser_dat;
unsigned char start_uca;

unsigned int cnt_uca_time;
unsigned int val_coin_uca;
unsigned int block_ubgrade_uca;

void UCAListen(void){
	unsigned char c;
	while(UART_IS_RX_READY(UART1)){
		c = UART_READ(UART1);
//		UART_WRITE(UART1,c);
		if(uca_ser == UCA_SER_PULL){
			if(c == 0x90){
				uca_ser_dat[0] = c;
				cnt_uca_ser_dat = 1;
			}else{
				if(cnt_uca_ser_dat >= 1){
					uca_ser_dat[cnt_uca_ser_dat] = c;
					cnt_uca_ser_dat++;
					if(uca_ser_dat[1] == cnt_uca_ser_dat){
						uca_ser = UCA_SER_DATA;
					}
				}
			}
		}else if(uca_ser == UCA_SER_DATA){
			if(c == 0x90){
				uca_ser_dat[0] = c;
				cnt_uca_ser_dat = 1;
				uca_ser = UCA_SER_PULL;
			}
		}
	}
}

unsigned char checksum(char *dat,unsigned char len){
	unsigned int i,chk_sum = 0;
	for(i=0;i<len-1;i++)
		chk_sum += dat[i];
	i = chk_sum % 256;
	return (unsigned char)i;
}

void UCAStop(void){
	start_uca = 0;
	uca_ser = UCA_SER_PULL;
}

void UCASendReadStatus(void){
	uca_st_new = UCA_SEND_VER;
	uca_ser = UCA_SER_PULL;
}

unsigned char UCAGetReadStatus(char *dat){
	if(uca_st_new == UCA_WAIT_READ){
		memcpy(dat,&uca_ser_dat[3],10);
		return 1;
	}else{
		dat[0] = 0;
		dat[1] = 0;
	}
	return 0;
}

void UCAStart(void){
	start_uca = 1;
	val_coin_uca = 0;
	uca_ser = UCA_SER_PULL;
	uca_st_new = UCA_GET_COIN;
}

unsigned int UCAGetValCoin(void){
	if(uca_st_new == UCA_WAIT_READ){
		uca_ser = UCA_SER_PULL;
		uca_st_new = UCA_GET_COIN;
		return val_coin_uca;
	}
	return 0;
}

void UCATask10ms(void){
	unsigned char chk_sum;
	if(start_uca == 1){
		cnt_uca_time++;
		switch(uca_st_new){
			case UCA_SEND_VER:
				memset(uca_send_dat,0,sizeof(uca_send_dat));
				uca_send_dat[0] = 0x90;
				uca_send_dat[1] = 0x05;
				uca_send_dat[2] = 0x11;
				uca_send_dat[3] = 0x03;
				uca_send_dat[4] = 0xA9;
				uca_st_new = UCA_GET_VER;
				uca_ser = UCA_SER_PULL;
				memset(uca_ser_dat,0,sizeof(uca_ser_dat));
//				SerialSendStrTx2(COIN_SER,uca_send_dat,5);
				UART_Write(UART1,uca_send_dat, 5);
			break;
			case UCA_GET_VER:
				if(uca_ser == UCA_SER_DATA){
					chk_sum = checksum(uca_ser_dat,cnt_uca_ser_dat);
					if((chk_sum == uca_ser_dat[cnt_uca_ser_dat - 1])&&(uca_ser_dat[2] == 0x11)){
						uca_st_new = UCA_WAIT_READ;
					}
				}
			break;
			case UCA_GET_COIN:
				if(uca_ser == UCA_SER_DATA){
					chk_sum = checksum(uca_ser_dat,cnt_uca_ser_dat);
					if((chk_sum == uca_ser_dat[cnt_uca_ser_dat - 1])&&(uca_ser_dat[2] == 0x12)){
						val_coin_uca = uca_coin_ch[uca_ser_dat[3]];
						uca_st_new = UCA_WAIT_READ;
					}
				}
			break;
			case UCA_WAIT_READ:
				// wait read data coin;
			break;
			default:
			break;
		}
	}
}
