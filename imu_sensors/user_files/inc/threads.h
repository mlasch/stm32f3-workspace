#ifndef _THREADS_H
#define _THREADS_H

#include <cmsis_os.h>

void handlerThread(void const *arg);
void visioThread(void const *arg);
extern osThreadId handlerThread_id;
extern osThreadId visioThread_id;
extern osMutexId accelBuffer_mutex_id;

#endif	// _THREADS_H
