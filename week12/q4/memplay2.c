#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[]){
	int fd;
	int i;
	pid_t pid;
	caddr_t addr;
	int crand;
	int prand;
	struct stat statbuf;

	if(argc != 2){
		fprintf(stderr,"Usage: %s filname\v",argv[0]);
		exit(1);
	}
	if(stat(argv[1],&statbuf) == -1){
		perror("stat");
		exit(1);
	}
	fd = open(argv[1],O_RDWR);

	addr = mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,\
			MAP_SHARED,fd,(off_t)0);
	if (addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	printf("=========game start=============\n");
	switch(pid = fork())
	{
		case -1: // error상황
			perror("fork");
			exit(1);
			break;
		case 0: //child 프로세스.
			srand(time(NULL));
		/*	for( i = 0; i< 50; i++){
				addr[i] = 'c';
				sleep(1);
			}*/
			
			for ( i = 0; i<100; i++){
				//crand = rand()%50 +2;
				addr[i]  = 'c'; 
				sleep(1);
			}
			
			break;
			

		default: // parent 프로세스.
			srand(time(NULL));
			for ( i = 0; i < 100; i++)
			{
				prand = rand()%100;
				addr[prand] = 'p';
				sleep(1);
			}
			break;
	}


	return 0;
}
	
