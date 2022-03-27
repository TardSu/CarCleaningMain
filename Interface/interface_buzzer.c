#include "./Application/application_config.h"

uint8_t beep_flag;
uint32_t time_beep;

void TMR0_IRQHandler(void){
	if(TIMER_GetIntFlag(TIMER0) == 1){
		TIMER_ClearIntFlag(TIMER0);		/* Clear Timer0 time-out interrupt flag */
		if(beep_flag == 10){
			time_beep++;
			if(time_beep >= 300){
				PWM_DisableOutput(PWM1, PWM_CH_1_MASK);
				beep_flag = 0;
				time_beep = 0;
			}
		}else if(beep_flag > 0){
			time_beep++;
			if(time_beep >= 100){
				if(beep_flag > 0){
					time_beep = 0;
					PWM_EnableOutput(PWM1, PWM_CH_1_MASK);
				}else{
					PWM_DisableOutput(PWM1, PWM_CH_1_MASK);
					beep_flag = 0;
					time_beep = 0;
				}
			}else if(time_beep == 50){
				PWM_DisableOutput(PWM1, PWM_CH_1_MASK);
				beep_flag--;
			}
		}
	}
}

void BuzzerInit(void){
	/* Open Timer0 in periodic mode, enable interrupt and 1 interrupt tick per second */
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000); // 1 mSec
	TIMER_EnableInt(TIMER0);
	/* Enable Timer0 ~ Timer3 NVIC */
	NVIC_EnableIRQ(TMR0_IRQn);	
	/* Start Timer0 ~ Timer3 counting */
	TIMER_Start(TIMER0);
	
	/* Set PWM1 channel 0 output configuration */
	PWM_ConfigOutputChannel(PWM1, 1, 2000, 5);
	/* Enable PWM Output path for PWM1 channel 0 */
	PWM_DisableOutput(PWM1, PWM_CH_1_MASK);
	/* Enable Timer for PWM1 channel 0 */
	PWM_Start(PWM1, PWM_CH_1_MASK);
}

void BuzzBeep(uint8_t beep){
	PWM_DisableOutput(PWM1, PWM_CH_1_MASK);
	time_beep = 0;
	beep_flag = beep;
	PWM_EnableOutput(PWM1, PWM_CH_1_MASK);
}
