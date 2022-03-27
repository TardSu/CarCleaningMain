#include "./Application/application_config.h"

typedef enum{
	TK77_NULL = 0, TK77_START, TK77_PULL, TK77_ACCEPT,
	TK77_ACK, TK77_WAIT_READ, TK77_STOP,
} tk77_st_t;

tk77_st_t tk77_st = TK77_NULL;
unsigned char tk77_data[4];
unsigned char state_tk77;
unsigned char cnt_tk77_data;
unsigned int cnt_tk77_time;
unsigned int valBill_tk77;
const unsigned int tk77_bills[] =  {20,50,100};
void TK77Listen(void){
	unsigned char c;
	while(UART_IS_RX_READY(UART2)){
		c = UART_READ(UART2);
//		UART_WRITE(UART1,c);
		switch(tk77_st){	
			case TK77_START :
				if(c == 0x80){
					cnt_tk77_data = 0;
					memset(tk77_data,0,4);
				}else{
					if((c >= 0x20)&&(c <= 0x2F)){
						cnt_tk77_data = 0;
						memset(tk77_data,0,4);
					}
				}
				tk77_data[cnt_tk77_data] = c;
				cnt_tk77_data++;
				if(cnt_tk77_data > 3){
					cnt_tk77_data = 0;
				}
			break;
			case TK77_PULL :
				if(c == 0x81){
					cnt_tk77_data = 0;
					memset(tk77_data,0,4);
				}else{
					if((c >= 0x20)&&(c <= 0x2F)){
						cnt_tk77_data = 0;
						memset(tk77_data,0,4);
					}
				}
				tk77_data[cnt_tk77_data] = c;
				cnt_tk77_data++;
				if(cnt_tk77_data > 3){
					cnt_tk77_data = 0;
				}
			break;
				case TK77_ACCEPT :
				if((c == 0x10)||(c == 0x11)){
					cnt_tk77_data = 0;
					memset(tk77_data,0,4);
				}else{
					if((c >= 0x20)&&(c <= 0x2F)){
						cnt_tk77_data = 0;
						memset(tk77_data,0,4);
					}
				}
				tk77_data[cnt_tk77_data] = c;
				cnt_tk77_data++;
				if(cnt_tk77_data > 3){
					cnt_tk77_data = 0;
				}
			break;
			default:
			break;
		}
	}
}

void TK77Stop(void){
	memset(tk77_data,0,4);
	state_tk77 = 0;
	cnt_tk77_time = 0;
	cnt_tk77_data = 0;
	tk77_st = TK77_STOP;
}

void TK77Start(void){
	memset(tk77_data,0,4);
	state_tk77 = 1;
	cnt_tk77_time = 0;
	cnt_tk77_data = 0;
	tk77_st = TK77_START;
}

unsigned int TK77GetValBill(void){
	unsigned int bu = 0;
	if(tk77_st == TK77_WAIT_READ){
		bu = valBill_tk77;
		valBill_tk77 = 0;
		cnt_tk77_data = 0;
		cnt_tk77_time = 0;
		tk77_st = TK77_PULL;
		return bu;
	}
	return 0;
}

void TK77Task10ms(void){
	if(state_tk77 == 1){
		cnt_tk77_time++;
		switch(tk77_st){
			case TK77_START:
				if(cnt_tk77_time >= 50){
					if((tk77_data[0]==0x80)&&(tk77_data[1]==0x8F)){
						cnt_tk77_time = 0;
						tk77_st = TK77_ACK;
					}else{
						cnt_tk77_time = 0;
					}
				}
			break;
			case TK77_ACK:
				if(cnt_tk77_time >= 50){
					cnt_tk77_time = 0;
					tk77_st = TK77_PULL;
					UART_WRITE(UART2,0x02);
				}
			break;
			case TK77_PULL:
				if(tk77_data[0] == 0x81){
					if((tk77_data[1] >= 0x40)&&(tk77_data[1] <= 0x42)){
						cnt_tk77_time = 0;
						tk77_st = TK77_ACCEPT;
						valBill_tk77 = tk77_bills[tk77_data[1] - 0x40];
						UART_WRITE(UART2,0x02);
					}else{
						if(cnt_tk77_time >= 100){
							cnt_tk77_data = 0;
							cnt_tk77_time = 0;
							memset(tk77_data,0,4);
							tk77_st = TK77_ACCEPT;
							UART_WRITE(UART2,0x0F);
						}
					}
				}
			break;
			case TK77_ACCEPT:
				if(tk77_data[0] == 0x10){
					cnt_tk77_time = 0;
					tk77_st = TK77_WAIT_READ;
				}else if(tk77_data[0] == 0x2A){
					cnt_tk77_time = 0;
					tk77_st = TK77_WAIT_READ;
				}else if(tk77_data[0] == 0x11){
					cnt_tk77_data = 0;
					cnt_tk77_time = 0;
					memset(tk77_data,0,4);
					valBill_tk77 = 0;
					tk77_st = TK77_PULL;
				}else{
					if((tk77_data[0] >= 0x20)&&(tk77_data[0] <= 0x2F)){
						cnt_tk77_data = 0;
						cnt_tk77_time = 0;
						memset(tk77_data,0,4);
						valBill_tk77 = 0;
						tk77_st = TK77_PULL;
					}
				}
			break;
			default:
			break;
		}
	}
}
