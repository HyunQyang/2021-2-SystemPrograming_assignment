#include<unistd.h>
#include<signal.h>
#include<stdio.h>

int main(){
	sigset_t new;
	int i;

	sigemptyset(&new);
	sigaddset(&new,SIGINT);
	sigprocmask(SIG_BLOCK,&new,(sigset_t *)NULL);

	for ( i=0; i<10; i++){
		printf("Hallym Software\n");
		sleep(1);
	}

	sigprocmask(SIG_UNBLOCK,&new,(sigset_t *)NULL);

	return 0;
}
