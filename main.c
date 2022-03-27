#include "./Application/application_config.h"

int main(void){
	AppCarCleaningInit();
	while(1){
		AppTimerTask();
		AppWhileLoop();
	}
}
