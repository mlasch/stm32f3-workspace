#include <stm32f3xx.h>
#include <cmsis_os.h>

#include <lsm303dlhc.h>
#include <threads.h>

osThreadId handlerThread_id;
osThreadId visioThread_id;

osMutexId accelBuffer_mutex_id;

void handlerThread(void const *arg) {
	osEvent event;
	
	while(1) {
		event = osSignalWait(0x01, osWaitForever);
		
		osMutexWait(accelBuffer_mutex_id, osWaitForever);
		readAccel();	
		osMutexRelease(accelBuffer_mutex_id);
	}
}

void visioThread(void const *arg) {
	static int16_t x = 0;
	static int16_t y = 0;
	static int16_t z = 0;
	
	while(1) { 
		osMutexWait(accelBuffer_mutex_id, osWaitForever);
		x = accelBuffer[0] | (accelBuffer[1] << 8);
		y = accelBuffer[2] | (accelBuffer[3] << 8);
		z = accelBuffer[4] | (accelBuffer[5] << 8);
		osMutexRelease(accelBuffer_mutex_id);
		
		if (x > 10 || y > 10 || z > 10) {
			
		}
		
		osThreadYield();
	}
}
