/*
	compile : gcc pthread.c -o pthread.exe -lpthread
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct test_structure{
	int a;
	char b;
	char c[5];
}ts;


/*pass no data*/
void* test_thread_func1(void){
	sleep(1);
	printf("I'm test_thread_func1\n");
}

/*pass int data*/
void* test_thread_func2(void *int_data){
	sleep(1);
	printf("I'm test_thread_func2\n");
	printf("int_data = %d\n",*(int*) int_data);
}

/*pass char data*/
void* test_thread_func3(void *char_data){
	sleep(1);
	printf("I'm test_thread_func3\n");
	printf("char_data = %c\n",*(char*) char_data);
}

/*pass string data*/
void* test_thread_func4(void *str_data){
	sleep(1);
	printf("I'm test_thread_func4\n");
	printf("str_data = %s\n",(char*) str_data);
}

/*pass structure*/
void* test_thread_func5(void *structure){
	sleep(1);
	printf("I'm test_thread_func5\n");
	ts* s = (ts*) structure;
	printf("s->a = %d\n",s->a);
	printf("s->b = %c\n",s->b);
	printf("s->c = %s\n",s->c);
}


int main(){
	/*create thread test1 (pass no data)*/
	pthread_t test_thread1;
	printf("\ncreate thread\n");
	pthread_create(&test_thread1,NULL,(void *)test_thread_func1, NULL);
	pthread_join(test_thread1, NULL);

	/*create thread test2 (pass int data)*/
	int a = 12345;
	pthread_t test_thread2;
	printf("\ncreate thread\n");
	pthread_create(&test_thread2,NULL,(void *)test_thread_func2, &a);
	pthread_join(test_thread2, NULL);

	/*create thread test3 (pass char data)*/
	char b = 'x';
	pthread_t test_thread3;
	printf("\ncreate thread\n");
	pthread_create(&test_thread3,NULL,(void *)test_thread_func3, &b);
	pthread_join(test_thread3, NULL);

	/*create thread test4 (pass string data)*/	
	char c[5] = "HELLO";
	pthread_t test_thread4;
	printf("\ncreate thread\n");
	pthread_create(&test_thread4,NULL,(void *)test_thread_func4, c);
	pthread_join(test_thread4, NULL);

	/*create thread test5 (pass structure)*/	
	ts* d;
	int memsize = sizeof(ts);
	d = (ts*)malloc(memsize);
	d->a = 2468;
	d->b = 'y';
	strcpy(d->c,"hello");
	pthread_t test_thread5;
	printf("\ncreate thread\n");
	pthread_create(&test_thread5,NULL,(void *)test_thread_func5, d);
	pthread_join(test_thread5, NULL);
	
	return 0;
}
