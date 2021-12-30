#include<unistd.h>
#include<signal.h>
//#include<siginfo.h>
#include<stdio.h>

void handler( int signo)
{
	printf("At handler: Wake up!\n");
}

int main(void)
{
	sigset_t set;
	void (*hand)(int);
	int i;

	sigfillset(&set);
	sigdelset(&set,SIGINT);
	sigdelset(&set,SIGALRM);
	sigprocmask(SIG_BLOCK,&set,(sigset_t *)NULL);
	
	hand = signal(SIGALRM,handler);
	for(i =0; i<5; i++){
		alarm(2);
		printf("Pause ...\n");
		pause();
	}
	printf("Bye~\n");
	sigprocmask(SIG_UNBLOCK,&set,(sigset_t *)NULL);
	return 0;
}
