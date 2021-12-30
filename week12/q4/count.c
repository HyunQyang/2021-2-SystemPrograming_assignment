#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
	int fd;
	caddr_t  addr;
	int i;
	int pwin,cwin;
	int count;
	struct stat statbuf;
	count =0;// using count 'p'
	pwin = 0;
	cwin =0;
	if(argc != 2){
		fprintf(stderr,"Usage : %s filename=n",argv[0]);
		exit(1);
	}
	stat(argv[1],&statbuf);		
	fd = open(argv[1],O_RDONLY);

	addr = mmap(NULL,statbuf.st_size,PROT_READ,MAP_SHARED,fd,(off_t)0);
	
	printf("result....\n");
	//counting p.
	for (i =0; i<100; i++){
		if(addr[i] == 'p')
			count++;
	}
	printf("number of P:%d\n",count);
	printf("number of C:%d\n",100 -count);

	if(count > 50){
		printf("parent win!\n");
		pwin--;
		return pwin;
	}
	else if(count == 50)    printf("Even!!");
	else{
		printf("Child win!!\n");
		cwin++;
		return cwin;
	}
	
	
}
