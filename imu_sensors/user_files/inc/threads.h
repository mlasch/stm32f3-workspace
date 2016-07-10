#ifndef _THREADS_H
#define _THREADS_H

#include <cmsis_os.h>

void handlerThread(void const *arg);
extern osThreadId handlerThread_id;


#endif	// _THREADS_H
