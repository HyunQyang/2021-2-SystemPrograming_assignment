#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 0
int main(int argc,char* argv[]){
	char* env = argv[1];
	char* dir = argv[2];
	char* val;
	if(argc != 3){
		printf("ERROR!\n");
		exit(EXIT_FAILURE);
	}
	
	val = getenv(env);
	int v = 1;
	if( val == NULL)
		printf("%s has not defined\n",env);
	else{
		int len = strlen(val);
		for( int i=0;i <= len-strlen(dir);i++){
			int v = strncmp(dir,val +i, strlen(dir));
			if( v == TRUE) {
				printf("%s has %s\n",env,dir);
				exit(EXIT_SUCCESS);
			}
		}
	}
		printf("%s does not have %s\n",env,dir);
	return 0;
}
