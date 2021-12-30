#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	struct timeval tv;
	int n;
	srand(time(NULL));
	printf("Hello world begins\n");
	n = (rand()%20)+10;
	sleep(n);
		printf("Hello world ends\n");

	

}


