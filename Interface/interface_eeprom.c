#include "./Application/application_config.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t g_u8DeviceAddr = 0x50;
uint8_t g_au8TxData[3];
uint8_t g_u8RxData;
uint8_t g_u8DataLen;
volatile uint8_t g_u8EndFlag = 0;

typedef void (*I2C_FUNC)(uint32_t u32Status);
static I2C_FUNC s_I2CHandlerFn = NULL;

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C0_IRQHandler(void){
	uint32_t u32Status;
	u32Status = I2C_GET_STATUS(I2C0);
	if(I2C_GET_TIMEOUT_FLAG(I2C0)){
		/* Clear I2C0 Timeout Flag */
		I2C_ClearTimeoutFlag(I2C0);
	}else{
		if(s_I2CHandlerFn != NULL)
			s_I2CHandlerFn(u32Status);
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Initial Function                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
//__INLINE void I2C_PIN_Init(void)
//{
//    /* Set GPA multi-function pins for I2C1 SDA and SCL */
//    SYS->GPC_MFPL &= ~SYS_GPC_MFPL_PC4MFP_Msk;
//    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC4MFP_I2C1_SCL;

//    SYS->GPE_MFPL &= ~SYS_GPE_MFPL_PE0MFP_Msk;
//    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE0MFP_I2C1_SDA;


//    /* Enable I2C1 module clock */
//    CLK_EnableModuleClock(I2C1_MODULE);

//}

void EEPROMInit(void){
	//    I2C_PIN_Init();
	/* Open I2C module and set bus clock */
	I2C_Open(I2C0, 400000);

	/* Get I2C0 Bus Clock */
	//    printf("I2C clock %d Hz\n", I2C_GetBusClockFreq(I2C_EEPROM));

	/* Enable I2C interrupt */
	I2C_EnableInt(I2C0);
	NVIC_EnableIRQ(I2C0_IRQn);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Rx Callback Function                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_MasterRx(uint32_t u32Status){
	if(u32Status == 0x08){                       /* START has been transmitted and prepare SLA+W */
		I2C_SET_DATA(I2C0, (g_u8DeviceAddr << 1));    /* Write SLA+W to Register I2CDAT */
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x18){                  /* SLA+W has been transmitted and ACK has been received */
		I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen++]);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x20){                  /* SLA+W has been transmitted and NACK has been received */
		I2C_STOP(I2C0);
		I2C_START(I2C0);       
	}else if(u32Status == 0x28){                  /* DATA has been transmitted and ACK has been received */
		if(g_u8DataLen != 2){
			I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen++]);
			I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
		}else{
			I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI);
		}
	}else if(u32Status == 0x10){                  /* Repeat START has been transmitted and prepare SLA+R */
		I2C_SET_DATA(I2C0, ((g_u8DeviceAddr << 1) | 0x01));   /* Write SLA+R to Register I2CDAT */
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x40){                  /* SLA+R has been transmitted and ACK has been received */
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x58){                  /* DATA has been received and NACK has been returned */
		g_u8RxData = (unsigned char) I2C_GET_DATA(I2C0);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI);
		g_u8EndFlag = 1;
	}else{
			/* TO DO */
//        printf("Status 0x%x is NOT processed\n", u32Status);
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Tx Callback Function                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_MasterTx(uint32_t u32Status){
	if(u32Status == 0x08){                       /* START has been transmitted */
		I2C_SET_DATA(I2C0, g_u8DeviceAddr << 1);    /* Write SLA+W to Register I2CDAT */
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x18){                  /* SLA+W has been transmitted and ACK has been received */
		I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen++]);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	}else if(u32Status == 0x20){                  /* SLA+W has been transmitted and NACK has been received */
		I2C_STOP(I2C0);
		I2C_START(I2C0); 
	}else if(u32Status == 0x28){                  /* DATA has been transmitted and ACK has been received */
		if(g_u8DataLen != 3){
			I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen++]);
			I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
		}else{
			I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI);
			g_u8EndFlag = 1;
		}
	}else{
	/* TO DO */
	//        printf("Status 0x%x is NOT processed\n", u32Status);
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Write I2C EEPROM                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_EEPROM_Write(uint16_t u16Address, uint8_t u8Data){
	g_au8TxData[0] = u16Address >> 8;
	g_au8TxData[1] = u16Address & 0xFF;
	g_au8TxData[2] = u8Data;

	g_u8DataLen = 0;
	g_u8EndFlag = 0;

	/* I2C function to write data to slave */
	s_I2CHandlerFn = (I2C_FUNC)I2C_MasterTx;

	/* I2C as master sends START signal */
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	/* Wait I2C Tx Finish */
	while(g_u8EndFlag == 0);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Read I2C EEPROM                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t I2C_EEPROM_Read(uint16_t u16Address){
	g_au8TxData[0] = u16Address >> 8;
	g_au8TxData[1] = u16Address & 0xFF;

	g_u8DataLen = 0;
	g_u8EndFlag = 0;

	/* I2C function to write data to slave */
	s_I2CHandlerFn = (I2C_FUNC)I2C_MasterRx;

	/* I2C as master sends START signal */
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	/* Wait I2C Tx Finish */
	while(g_u8EndFlag == 0);

	return g_u8RxData;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Write Long I2C EEPROM                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
void EPWriteLong(unsigned short ad, unsigned int len, char *data){
	unsigned int wr_cnt = 0;
	uint16_t wr_ad = ad;
	while(wr_cnt < len){
		I2C_EEPROM_Write(wr_ad,data[wr_cnt]);
		wr_cnt++;
		wr_ad += wr_cnt;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Read Long I2C EEPROM                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
void EPReadLong(unsigned short ad, unsigned int len, char *data){
	unsigned int rd_cnt = 0;
	uint16_t rd_ad = ad;
	while(rd_cnt < len){
		data[rd_cnt] = I2C_EEPROM_Read(rd_ad);
		rd_cnt++;
		rd_ad += rd_cnt;
	}
}

//###########################################################################
//###########################################################################
//##################                                   ######################
//##################            EEprom Config          ######################
//##################                                   ######################
//###########################################################################
//###########################################################################
void ReadEEPROMConfig(cfg_t *cfg){
	char str[EP_CFG_SIZE + 8];
//	int ss,jj;
//	ss = sizeof(cfg_t);
//	jj = ss;
//	jj++;
	memset(cfg,0,sizeof(cfg_t));
	EPReadLong(EP_CFG_START,EP_CFG_SIZE,str);
	memcpy(cfg,str,sizeof(cfg_t));
}

void WriteEEPROMConfig(cfg_t config){
	char str[EP_CFG_SIZE + 8];
//	int ss,jj;
//	ss = sizeof(cfg_t);
//	jj = ss;
//	jj++;
	memset(str,0,sizeof(str));
	memcpy(str,&config,sizeof(cfg_t));
	EPWriteLong(EP_CFG_START,EP_CFG_SIZE,str);
}

void SetEEPROMConfigDefault(void){
	cfg_t cfg;
	cfg.firmware_valid = FIRMWARE_VALUE_VALID;
	cfg.light_on.hour = 18;
	cfg.light_on.min = 0;
	cfg.light_on.sec = 0;
	cfg.light_off.hour = 8;
	cfg.light_off.min = 0;
	cfg.light_off.sec = 0;
	cfg.min_price = 1;
	
	cfg.bahtpermsec_relay[0] = 300;
	cfg.bahtpermsec_relay[1] = 300;
	cfg.bahtpermsec_relay[2] = 300;
	cfg.bahtpermsec_relay[3] = 300;
	cfg.bahtpermsec_relay[4] = 300;
	cfg.bahtpermsec_relay[5] = 300;
	
	cfg.sound_day.hour = 8;
	cfg.sound_day.min = 0;
	cfg.sound_day.sec = 0;
	cfg.sound_night.hour = 18;
	cfg.sound_night.min = 0;
	cfg.sound_night.sec = 0;
	cfg.waste_money = 0;
	cfg.snd_lv_hi = 5;
	cfg.snd_lv_low = 3;
	
	cfg.button_mode = CFG_BUTTON_MODE_SINGLE;
	cfg.button_enable = 0;
	
	memset(cfg.resv,0,sizeof(cfg.resv));
	WriteEEPROMConfig(cfg);
}
