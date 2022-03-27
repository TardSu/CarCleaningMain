#ifndef __INTERFACE_UCA_H__
#define __INTERFACE_UCA_H__

void UCAListen(void);
void UCAStop(void);
void UCAStart(void);
void UCATask10ms(void);

void UCASendReadStatus(void);
unsigned char UCAGetReadStatus(char *dat);
unsigned int UCAGetValCoin(void);

#endif
