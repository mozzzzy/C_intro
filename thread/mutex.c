#include "stdio.h"
#include "pthread.h"

pthread_mutex_t mutex;

void *func_thread(void) {
	pthread_mutex_lock(&mutex);
	printf("World\n");
	pthread_mutex_unlock(&mutex);

}

int main(void) {
	pthread_mutex_init(&mutex, NULL);
	
	pthread_t pthread;
	pthread_mutex_lock(&mutex);
	pthread_create( &pthread, NULL, (void*)func_thread, NULL);
	printf("Hello ");
	pthread_mutex_unlock(&mutex);

	pthread_join(pthread, NULL); // pthreadで作られたスレッドが終わるまで待つ

	return 0;
}
