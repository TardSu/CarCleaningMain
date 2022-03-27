#include "./Application/application_config.h"

const unsigned char display7SegmentTable[] = //' '(0x20)-'Z'(0x5A), use 'A'-'Z' ,no 'a'-'z' allowed
{
//	 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x00,	0x00,	0x00,	0x00,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x74, 0x30, 0x0E, 0x00, 0x38, 0x00, 0x54, 0x5C,
	0x73, 0x67, 0x50, 0x6D, 0x00, 0x3E, 0x1C, 0x00, 0x76, 0x66, 0x5B
};

void UUencode(char *dat,char *uuencode){
	char str[64];
	int i,j,k,loop;
	unsigned int diff;
	memset(str,0x00,sizeof(str));
	memcpy(str,dat,dat[0]);
	loop = str[0] / 3;
	if((str[0] % 3) != 0){
		loop += 1;
	}
	
	for(i=0;i<loop;i++){
		diff = str[(i *3)];
		diff <<= 8;
		diff |= str[(i *3) + 1];
		diff <<= 8;
		diff |= str[(i *3) + 2];
		k = 0;
		for(j=18;j>=0;j-=6){
			if(((diff >> j)& 0x3F)  == 0){
				uuencode[(i *4) + k] = 0x60;
			}else{
				uuencode[(i *4) + k] = ((diff >> j)& 0x3F) + 0x20;
			}
			k++;
		}
	}
}

void Display7Segment(char *dat,unsigned char dot,unsigned char cmd1,unsigned char cmd2){
	char buf1[64];
	char buf2[64];
	int i;
	int len = strlen(dat);
	memset(buf1,0x00,sizeof(buf1));
	memset(buf2,0x00,sizeof(buf2));
	buf1[0] = len + 5;
	buf1[1] = DISPLAY_7SEG_COLUMN_0 | DISPLAY_7SEG_ROW_0;
	buf1[2] = cmd1;
	buf1[3] = cmd2;
	for(i=4;i<(len+4);i++){
		buf1[i] = display7SegmentTable[((dat[i-4] - 0x20) & 0x3F)] << 1;
		buf1[i] |= ((dot >> (i-4))& 0x01);
	}
	
	buf1[len+4] = buf1[0];
	for(i=1;i<(len+4);i++){
		buf1[len+4] = buf1[i]^buf1[len+4];
	}
	
	UUencode(buf1,buf2);

	memset(buf1,0x00,sizeof(buf1));
	memset(&buf1[0],0x01,1);
	memcpy(&buf1[1],buf2,strlen(buf2));
	memset(&buf1[strlen(buf2)+1],0x03,1);
	
	SoftSerial1SendString(buf1);
}

void Display7SegmentTime(time_t time){
	char str[16];
	sprintf(str,"%02d%02d",time.hour,time.min);
	Display7Segment(str,DISPLAY_7SEG_DOT_ON2,DISPLAY_7SEG_CMD_TIMER,0);
}

void Display7SegmentTimeSetting(time_t time){
	char str[16];
	sprintf(str,"%02d%02d",time.hour,time.min);
	Display7Segment(str,DISPLAY_7SEG_DOT_ON2,DISPLAY_7SEG_CMD_NORMAL,0);
}

void Display7SegmentMoney(double money){
	char str[16];
	int moneyint = money;
	if(money > 1000){
		sprintf(str,"%4d",999);
	}else{
		sprintf(str,"%4d",moneyint);
	}
	Display7Segment(str,DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_NORMAL,0);
}

void Display7SegmentMoneyBlink(double money){
	char str[16];
	int moneyint = money;
	if(money > 1000){
		sprintf(str,"%4d",999);
	}else{
		sprintf(str,"%4d",moneyint);
	}
	Display7Segment(str,DISPLAY_7SEG_DOT_OFF,DISPLAY_7SEG_CMD_BLINK,BLINK_AT1 | BLINK_AT2 | BLINK_AT3 | BLINK_AT4);
}

void Display7SegmentNameMenu(char *dat,unsigned char dot,unsigned char cmd1){
	char str[16];
	memcpy(str,dat,4);
	Display7Segment(str,dot,cmd1,0);
}

void Display7SegmentTimeEdit(time_t time,unsigned char dot,unsigned char cmd2){
	char str[16];
	sprintf(str,"%02d%02d",time.hour,time.min);
	Display7Segment(str,dot,DISPLAY_7SEG_CMD_BLINK,cmd2);
}

void Display7SegmentNumEdit(unsigned int dat,unsigned char dot,unsigned char cmd1){
	char str[16];
	sprintf(str,"%04d",dat);
	Display7Segment(str,dot,cmd1,0);
}
