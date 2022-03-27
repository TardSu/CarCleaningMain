#ifndef __INTERFACE_SOFTSERIAL2_H__
#define __INTERFACE_SOFTSERIAL2_H__

void SoftSerial2Init(unsigned int buadrate);
unsigned char SoftSerial2IsRxReady(void);
char SoftSerial2GetRx(void);

void SoftSerial2SendString(char *c);
void SoftSerial2SendStringLength(char *c,unsigned char length);

#endif
