#ifndef __INTERFACE_SOFTSERIAL1_H__
#define __INTERFACE_SOFTSERIAL1_H__

void SoftSerial1Init(unsigned int buadrate);
unsigned char SoftSerial1IsRxReady(void);
char SoftSerial1GetRx(void);

void SoftSerial1SendString(char *c);
void SoftSerial1SendStringLength(char *c,unsigned char length);

#endif
