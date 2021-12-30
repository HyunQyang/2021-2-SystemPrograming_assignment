#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
//void func1(Number *no1);
//void func2(Number *no1);


typedef struct Number{
	char* name;
	int n1;
	int n2;
}Number;


void func1(Number *no1){
	pthread_mutex_lock(&mutex1);
	pthread_mutex_lock(&mutex2);
	no1->n1++;
	pthread_mutex_unlock(&mutex2);
	sleep(1);
	pthread_mutex_unlock(&mutex1);
}


void func2 (Number *no1){
	no1->n2--;
	func1(no1);
}



void *threading(void *args){
	int i;
	Number* no = (Number*) args;
	for(i =0;i<10; i++){
		func2(no);
		sleep(1);
		printf("%s , a = %d, b = %d\n ",no->name,no->n1,no->n2);
		
	}	
	return args;
}


int main(){
	pthread_t thread1,thread2;
	Number no1 = {.name = "Thread",.n1 = 0, .n2 = 10};	
	
	
	pthread_create(&thread1,NULL,threading,(void*)&no1);
	pthread_create(&thread2,NULL,threading,(void*)&no1);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	return 0;
}

