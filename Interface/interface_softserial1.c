#include "./Application/application_config.h"

#ifndef SOFTSERIAL1_BYTE_FIFO
#define SOFTSERIAL1_BYTE_FIFO							16
#endif

//Tx
typedef enum{
	SOFTSER1_TX_END = 0,
	SOFTSER1_TX_DELAY,
	SOFTSER1_TX_START,
	SOFTSER1_TX_DATA,
	SOFTSER1_TX_STOP,
} emunSoftSer1Tx;
emunSoftSer1Tx emunSoftSer1StateTx;
char tx1DataBuffer[SOFTSERIAL1_BYTE_FIFO];
unsigned int tx1LenghtDataBuffer;
unsigned char bitDataTx1Set;
unsigned char timeSamplingBitDataTx1;

//Rx
typedef enum{
	SOFTSER1_RX_START,
	SOFTSER1_RX_DATA,
	SOFTSER1_RX_STOP,
} emunSoftSer1Rx;
emunSoftSer1Rx emunSoftSer1StateRx;
char rx1DataBuffer[SOFTSERIAL1_BYTE_FIFO];
unsigned char rx1LenghtDataBuffer;
unsigned char timeSamplingBitDataRx1;
unsigned char bitDataRx1Set;
unsigned char bitAddDataRx1;
unsigned char bitMaskRx1;

void TMR1_IRQHandler(void){
	if(TIMER_GetIntFlag(TIMER1) == 1){
		TIMER_ClearIntFlag(TIMER1);		/* Clear Timer0 time-out interrupt flag */	
		// Tx
		if(tx1LenghtDataBuffer){
			switch(emunSoftSer1StateTx){
				case SOFTSER1_TX_DELAY : //delay bit
					if(--timeSamplingBitDataTx1 > 0){
						SOFT_SERIAL1_TX_PIN = 1;
					}else{
						timeSamplingBitDataTx1 = 4;
						emunSoftSer1StateTx = SOFTSER1_TX_START;
					}
				break;
				case SOFTSER1_TX_START : //start bit
					if(--timeSamplingBitDataTx1 > 0){
						SOFT_SERIAL1_TX_PIN = 0;
					}else{
						bitDataTx1Set = 0;
						timeSamplingBitDataTx1 = 4;
						emunSoftSer1StateTx = SOFTSER1_TX_DATA;
					}
				break;				
				case SOFTSER1_TX_DATA : //data bit
					if(--timeSamplingBitDataTx1 > 0){
						if(bitDataTx1Set < 8){
							if((tx1DataBuffer[0] >> bitDataTx1Set) & 1){
								SOFT_SERIAL1_TX_PIN = 1;
							}else{
								SOFT_SERIAL1_TX_PIN = 0;
							}
						}else{//set stop bit
							SOFT_SERIAL1_TX_PIN = 1;
							timeSamplingBitDataTx1 = 3;
							emunSoftSer1StateTx = SOFTSER1_TX_STOP;
						}
					}else{
						bitDataTx1Set++;
						timeSamplingBitDataTx1 = 4;
					}
				break;
				case SOFTSER1_TX_STOP : //end data
					if(--timeSamplingBitDataTx1 > 0){
						SOFT_SERIAL1_TX_PIN = 1;
					}else{
						if(tx1LenghtDataBuffer){
							memmove(&tx1DataBuffer[0], &tx1DataBuffer[1], sizeof(tx1DataBuffer) - sizeof(*tx1DataBuffer));
							tx1LenghtDataBuffer--;
							timeSamplingBitDataTx1 = 4;
							emunSoftSer1StateTx = SOFTSER1_TX_START;
						}else{
							emunSoftSer1StateTx = SOFTSER1_TX_END;
						}
					}
				break;
				default:
				break;
			}
		}

		// Rx
		switch(emunSoftSer1StateRx){
			case SOFTSER1_RX_START :
				if(SOFT_SERIAL1_RX_PIN == 0){
					bitDataRx1Set = 0;
					bitAddDataRx1 = 0;
					bitMaskRx1 = 1;
					timeSamplingBitDataRx1 = 5;
					emunSoftSer1StateRx = SOFTSER1_RX_DATA;
				}
			break;
			case SOFTSER1_RX_DATA :		
				if(--timeSamplingBitDataRx1 <= 0){
					if(SOFT_SERIAL1_RX_PIN == 1){
						bitAddDataRx1 |= bitMaskRx1;
					}
					bitMaskRx1 <<= 1;
					bitDataRx1Set++;
					if(bitDataRx1Set > 8){
						timeSamplingBitDataRx1 = 1;
						emunSoftSer1StateRx = SOFTSER1_RX_STOP;
					}else{
						timeSamplingBitDataRx1 = 4;
					}
				}
			break;
			case SOFTSER1_RX_STOP :
				if(--timeSamplingBitDataRx1 <= 0){
					if(SOFT_SERIAL1_RX_PIN == 1){
						if(rx1LenghtDataBuffer < SOFTSERIAL1_BYTE_FIFO){
							rx1DataBuffer[rx1LenghtDataBuffer] = bitAddDataRx1;
							rx1LenghtDataBuffer++;
						}
					}
					emunSoftSer1StateRx = SOFTSER1_RX_START;
				}
			break;
			default:
			break;
		}
	}
}

void SoftSerial1Init(unsigned int buadrate){	
	GPIO_SetMode(SOFT_SERIAL1_TX_PORT, SOFT_SERIAL1_TX_BIT, GPIO_MODE_OUTPUT);
	GPIO_SetMode(SOFT_SERIAL1_RX_PORT, SOFT_SERIAL1_RX_BIT, GPIO_MODE_INPUT);
	SOFT_SERIAL1_TX_PIN = 1;
	
	tx1LenghtDataBuffer = 0;
	rx1LenghtDataBuffer = 0;
	emunSoftSer1StateTx = SOFTSER1_TX_END;
	emunSoftSer1StateRx = SOFTSER1_RX_START;
	
	/* Open Timer0 in periodic mode, enable interrupt and 1 interrupt tick per second */
	TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 38500);
	TIMER_EnableInt(TIMER1);
	/* Enable Timer0 ~ Timer3 NVIC */
	NVIC_EnableIRQ(TMR1_IRQn);	
	/* Start Timer0 ~ Timer3 counting */
	TIMER_Start(TIMER1);
}

unsigned char SoftSerial1IsRxReady(void){
	return(rx1LenghtDataBuffer);
}

char SoftSerial1GetRx(void){
	char dat;
	rx1LenghtDataBuffer--;
	dat = rx1DataBuffer[0];
	memmove(&rx1DataBuffer[0], &rx1DataBuffer[1], sizeof(rx1DataBuffer) - sizeof(*rx1DataBuffer));
	return(dat);
}

unsigned char SoftSerial1IsTxEmpty(void){
	if(tx1LenghtDataBuffer < SOFTSERIAL1_BYTE_FIFO){
		return(1);
	}else{
		return(0);
	}
}

void SoftSerial1SendChar(char c){
	if(tx1LenghtDataBuffer <= 0){
		timeSamplingBitDataTx1 = 4;
		emunSoftSer1StateTx = SOFTSER1_TX_DELAY;
	}
	tx1DataBuffer[tx1LenghtDataBuffer] = c;
	tx1LenghtDataBuffer++;
}

void SoftSerial1SendString(char *c){
	char i = 0;
	while(c[i]){
		if(SoftSerial1IsTxEmpty()){
			SoftSerial1SendChar(c[i++]);
		}
	}
}

void SoftSerial1SendStringLength(char *c,unsigned char length){
	char i = 0;
	while(length){
		if(SoftSerial1IsTxEmpty()){
			SoftSerial1SendChar(c[i++]);
			length--;
		}
	}
}
