#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc,char *argv[]){
	int fd;
	pid_t pid;
	caddr_t addr;
	int i;
	struct stat statbuf;

	if(argc !=2){
		fprintf(stderr,"Usage: %s filename\n",argv[0]);
		exit(1);
	}
	if(stat(argv[1],&statbuf) ==-1){
		perror("stat");
		exit(1);
	}
	fd = open(argv[1],O_RDWR);

	addr = mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,\
			MAP_SHARED,fd,(off_t)0);
	if(addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	close(fd);
	
	switch(pid = fork())
	{
		case -1:
			perror("fork");
			exit(1);
			break;
		//child process
		case 0:
			srand(time(NULL));
			int crandom;
			for ( i=0; i<100;i++)
			{
				crandom = rand()%100;
				addr[crandom] = 'c';
				sleep(1);
			}
			break;
		//parent process
		default:
			srand(time(NULL));
			int prandom;
			for( i=0; i< 100; i++){
				prandom = rand()%100;
				addr[prandom] = 'p';
				sleep(1);
			}

	}
	return 0;
}





















