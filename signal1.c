#include<signal.h>
#include<stdio.h>

int main(){
	sigset_t st;

	sigemptyset(&st);

	sigfillset(&st);

	if( sigismember(&st,SIGBUS)){
		printf("SIGBUS is set\n");
	}
	else	printf("SIGBUS is not set\n");

	return 0;
}
