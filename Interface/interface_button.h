#ifndef __INTERFACE_BUTTON_H__
#define __INTERFACE_BUTTON_H__

typedef struct{
	unsigned char type;
	char ch;
} bt_res;

void ButtonInit(void);
void ButtonScan(void);
unsigned char ButtonGetMesCnt(void);
bt_res ButtonGetMes(void);
void ButtonPutMes(unsigned char type, char ch);

#endif
