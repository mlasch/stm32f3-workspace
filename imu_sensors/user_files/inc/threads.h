#ifndef _THREADS_H
#define _THREADS_H

#include <cmsis_os.h>

struct acceleration {
	int16_t x;
	int16_t y;
	int16_t z;
};

struct orientation {
	int16_t x;
	int16_t y;
	int16_t z;
};

void handlerThread(void const *arg);
void gyroHandlerThread(void const *arg);
void visioThread(void const *arg);
extern osThreadId handlerThread_id, gyroHandlerThread_id;
extern osThreadId visioThread_id;
extern osMutexId accelBuffer_mutex_id, gyroBuffer_mutex_id;

#endif	// _THREADS_H
