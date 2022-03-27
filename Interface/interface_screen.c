#include "./Application/application_config.h"

scr_t scr;

void func_do_null(unsigned char acction,unsigned char type,char key){
	
}

void func_task_null(void){

}

void ScrPageInit(void){
	scr.do_ = func_do_null;
	scr.task10ms = func_task_null;
	scr.task100ms = func_task_null;
}

void ScrPage(void (*func_do)(unsigned char acction,unsigned char type,char key),void (*func_task10ms)(void),void (*func_task100ms)(void)){
	scr.do_ = func_do;
	scr.task10ms = func_task10ms;
	scr.task100ms = func_task100ms;
	scr.do_(ACTION_INIT,STATUS_NULL,STATUS_NULL);
}

void ScrButtonDo(unsigned char type,char key){
	scr.do_(ACTION_BUTTON,type,key);
}

//void ScrKeypadDo(unsigned char type,char key){
//	scr.do_(ACTION_KEYPAD,type,key);
//}

void ScrTask10ms(){
	scr.task10ms();
}

void ScrTask100ms(){
	scr.task100ms();
}
