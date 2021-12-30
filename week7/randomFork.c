#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(int argc,char* argv[]){

	if(argc !=2 ){
		printf("ERROR: please give 2 args\n");
		exit(1);
	}
	pid_t pid;
	double p;
	double prob;
	pid_t pid4wait;
	int status;

	prob = atof(argv[1]);

	printf("Prob: %f\n",prob);
	srand(time(0));
	

	while( (p = rand()/(RAND_MAX*1.0)) <= prob){
		pid = fork();
		printf("MY PID: %d, MY Parent PID: %d \n",(int)getpid(),(int)getppid());
		if( pid > 0){
			pid4wait = wait(&status);
			printf("Waited PID: %d\n",pid4wait);
		}	

	}
}


