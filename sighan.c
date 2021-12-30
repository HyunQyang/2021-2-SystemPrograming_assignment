#include<signal.h>
#include<stdio.h>
#include<unistd.h>
//#include<siginfo.h>
#include<stdlib.h>

void handler(int signo) {
	printf("Handler Signal Number : %d\n",signo);
	psignal(signo,"SIGQUIT handler is called");
}

int main(void){
	void (*hand)(int);

	hand = signal(SIGQUIT,handler);
	printf("Waiting\n");
	pause();
	printf("End=n");
	return 0;
}
