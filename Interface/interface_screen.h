#ifndef __INTERFACE_SCREEN_H__
#define __INTERFACE_SCREEN_H__

typedef struct{
	void (*do_)(unsigned char acction,unsigned char type,char key); //do function
	void (*task10ms)(void); //do every 10 ms
	void (*task100ms)(void); //do every 100 ms
} scr_t;

void ScrPageInit(void);
void ScrPage(void (*func_do)(unsigned char acction,unsigned char type,char key),void (*func_task10ms)(void),void (*func_task100ms)(void));
void ScrButtonDo(unsigned char type,char key);
//void ScrKeypadDo(unsigned char type,char key);
void ScrTask10ms(void);
void ScrTask100ms(void);

#endif
