#include "./Application/application_config.h"

#ifndef SOFTSERIAL2_BYTE_FIFO
#define SOFTSERIAL2_BYTE_FIFO							16
#endif

//Tx
typedef enum{
	SOFTSER2_TX_END = 0,
	SOFTSER2_TX_DELAY,
	SOFTSER2_TX_START,
	SOFTSER2_TX_DATA,
	SOFTSER2_TX_STOP,
} emunSoftSer2Tx;
emunSoftSer2Tx emunSoftSer2StateTx;
char tx2DataBuffer[SOFTSERIAL2_BYTE_FIFO];
unsigned int tx2LenghtDataBuffer;
unsigned char bitDataTx2Set;
unsigned char timeSamplingBitDataTx2;

//Rx
typedef enum{
	SOFTSER2_RX_START,
	SOFTSER2_RX_DATA,
	SOFTSER2_RX_STOP,
} emunSoftSer2Rx;
emunSoftSer2Rx emunSoftSer2StateRx;
char rx2DataBuffer[SOFTSERIAL2_BYTE_FIFO];
unsigned char rx2LenghtDataBuffer;
unsigned char timeSamplingBitDataRx2;
unsigned char bitDataRx2Set;
unsigned char bitAddDataRx2;
unsigned char bitMaskRx2;

void TMR2_IRQHandler(void){
	if(TIMER_GetIntFlag(TIMER2) == 1){
		TIMER_ClearIntFlag(TIMER2);		/* Clear Timer0 time-out interrupt flag */	
		// Tx
		if(tx2LenghtDataBuffer){
			switch(emunSoftSer2StateTx){
				case SOFTSER2_TX_DELAY : //delay bit
					if(--timeSamplingBitDataTx2 > 0){
						SOFT_SERIAL2_TX_PIN = 1;
					}else{
						timeSamplingBitDataTx2 = 4;
						emunSoftSer2StateTx = SOFTSER2_TX_START;
					}
				break;
				case SOFTSER2_TX_START : //start bit
					if(--timeSamplingBitDataTx2 > 0){
						SOFT_SERIAL2_TX_PIN = 0;
					}else{
						bitDataTx2Set = 0;
						timeSamplingBitDataTx2 = 4;
						emunSoftSer2StateTx = SOFTSER2_TX_DATA;
					}
				break;				
				case SOFTSER2_TX_DATA : //data bit
					if(--timeSamplingBitDataTx2 > 0){
						if(bitDataTx2Set < 8){
							if((tx2DataBuffer[0] >> bitDataTx2Set) & 1){
								SOFT_SERIAL2_TX_PIN = 1;
							}else{
								SOFT_SERIAL2_TX_PIN = 0;
							}
						}else{//set stop bit
							SOFT_SERIAL2_TX_PIN = 1;
							timeSamplingBitDataTx2 = 3;
							emunSoftSer2StateTx = SOFTSER2_TX_STOP;
						}
					}else{
						bitDataTx2Set++;
						timeSamplingBitDataTx2 = 4;
					}
				break;
				case SOFTSER2_TX_STOP : //end data
					if(--timeSamplingBitDataTx2 > 0){
						SOFT_SERIAL2_TX_PIN = 1;
					}else{
						if(tx2LenghtDataBuffer){
							memmove(&tx2DataBuffer[0], &tx2DataBuffer[1], sizeof(tx2DataBuffer) - sizeof(*tx2DataBuffer));
							tx2LenghtDataBuffer--;
							timeSamplingBitDataTx2 = 4;
							emunSoftSer2StateTx = SOFTSER2_TX_START;
						}else{
							emunSoftSer2StateTx = SOFTSER2_TX_END;
						}
					}
				break;
				default:
				break;
			}
		}

		// Rx
		switch(emunSoftSer2StateRx){
			case SOFTSER2_RX_START :
				if(SOFT_SERIAL2_RX_PIN == 0){
					bitDataRx2Set = 0;
					bitAddDataRx2 = 0;
					bitMaskRx2 = 1;
					timeSamplingBitDataRx2 = 5;
					emunSoftSer2StateRx = SOFTSER2_RX_DATA;
				}
			break;
			case SOFTSER2_RX_DATA :
				if(--timeSamplingBitDataRx2 <= 0){
					if(SOFT_SERIAL2_RX_PIN == 1){
						bitAddDataRx2 |= bitMaskRx2;
					}
					bitMaskRx2 <<= 1;
					bitDataRx2Set++;
					if(bitDataRx2Set > 8){
						timeSamplingBitDataRx2 = 1;
						emunSoftSer2StateRx = SOFTSER2_RX_STOP;
					}else{
						timeSamplingBitDataRx2 = 4;
					}
				}
			break;
			case SOFTSER2_RX_STOP :
				if(--timeSamplingBitDataRx2 <= 0){
					if(SOFT_SERIAL2_RX_PIN == 1){
						if(rx2LenghtDataBuffer < SOFTSERIAL2_BYTE_FIFO){
							rx2DataBuffer[rx2LenghtDataBuffer] = bitAddDataRx2;
							rx2LenghtDataBuffer++;
						}
					}
					emunSoftSer2StateRx = SOFTSER2_RX_START;
				}
			break;
			default:
			break;
		}
	}
}

void SoftSerial2Init(unsigned int buadrate){	
	GPIO_SetMode(SOFT_SERIAL2_TX_PORT, SOFT_SERIAL2_TX_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(SOFT_SERIAL2_RX_PORT, SOFT_SERIAL2_RX_BIT, GPIO_MODE_INPUT);
	SOFT_SERIAL2_TX_PIN = 1;
	
	tx2LenghtDataBuffer = 0;
	rx2LenghtDataBuffer = 0;
	emunSoftSer2StateTx = SOFTSER2_TX_END;
	emunSoftSer2StateRx = SOFTSER2_RX_START;
	
	/* Open Timer0 in periodic mode, enable interrupt and 1 interrupt tick per second */
	TIMER_Open(TIMER2, TIMER_PERIODIC_MODE, 38500);
	TIMER_EnableInt(TIMER2);
	/* Enable Timer0 ~ Timer3 NVIC */
	NVIC_EnableIRQ(TMR2_IRQn);	
	/* Start Timer0 ~ Timer3 counting */
	TIMER_Start(TIMER2);
}

unsigned char SoftSerial2IsRxReady(void){
	return(rx2LenghtDataBuffer);
}

char SoftSerial2GetRx(void){
	char dat;
	rx2LenghtDataBuffer--;
	dat = rx2DataBuffer[0];
	memmove(&rx2DataBuffer[0], &rx2DataBuffer[1], sizeof(rx2DataBuffer) - sizeof(*rx2DataBuffer));
	return(dat);
}

unsigned char SoftSerial2IsTxEmpty(void){
	if(tx2LenghtDataBuffer < SOFTSERIAL2_BYTE_FIFO){
		return(1);
	}else{
		return(0);
	}
}

void SoftSerial2SendChar(char c){
	if(tx2LenghtDataBuffer <= 0){
		timeSamplingBitDataTx2 = 4;
		emunSoftSer2StateTx = SOFTSER2_TX_DELAY;
	}
	tx2DataBuffer[tx2LenghtDataBuffer] = c;
	tx2LenghtDataBuffer++;
}

void SoftSerial2SendString(char *c){
	char i = 0;
	while(c[i]){
		if(SoftSerial2IsTxEmpty()){
			SoftSerial2SendChar(c[i++]);
		}
	}
}

void SoftSerial2SendStringLength(char *c,unsigned char length){
	char i = 0;
	while(length){
		if(SoftSerial2IsTxEmpty()){
			SoftSerial2SendChar(c[i++]);
			length--;
		}
	}
}
