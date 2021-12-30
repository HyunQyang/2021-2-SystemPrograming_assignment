#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
		if( argc != 2){
		       printf("ERROR\n");
	       		exit(1);
		}
		int time =0;
		time = atoi(argv[1]);
		sleep(time);
		
}
