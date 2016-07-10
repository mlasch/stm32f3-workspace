#include <stm32f3xx.h>
#include <cmsis_os.h>

#include <lsm303dlhc.h>
#include <threads.h>

osThreadId handlerThread_id;

void handlerThread(void const *arg) {
	osEvent event;
	
	while(1) {
		event = osSignalWait(0x01, osWaitForever);
		
		readAccel();	
	}
}
