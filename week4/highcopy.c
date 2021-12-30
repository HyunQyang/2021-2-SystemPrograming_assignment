#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

int main(int argc,char* argv[]){
	int c;
	char* opt_arg_char = NULL;
        char* opt = NULL;
        int opt_arg_int   =0;
	char* firstfile=NULL;
	char* secondfile = NULL;	

	if(argc == 3 ){
		firstfile= argv[1];
		secondfile = argv[2];
	}
	else if( argc == 5){
		opt = argv[1];
		assert( strlen(opt) == 2);
		assert( opt[0] == '-');
		assert( opt[1] == 'd');

		opt_arg_char = argv[2];
		opt_arg_int = atoi(opt_arg_char);
		firstfile = argv[3];
		secondfile = argv[4];
	}
	else{
		printf("ERROR");
		exit(1);
	}
	
	int n=0;
	char buf[20];


	FILE* rfp = fopen(firstfile,"r");
	assert( rfp != NULL);

	FILE* wfp = fopen(secondfile,"w");
	assert(wfp != NULL);


	while (( c =fgetc(rfp)) != EOF) {
		if( isalpha(c)>0)
                 c = c - (char)opt_arg_int;
		fputc(c,wfp);
        }
        if(n==-1) perror("Read");

	fclose(rfp);
	fclose(wfp);

}
