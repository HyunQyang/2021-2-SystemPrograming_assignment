#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>

int main(){
	int pd,n,pd2;
	char inmsg[BUFSIZ];
	char msg[BUFSIZ];
	char dmsg[] = "download_";	
	char cmsg[] = "cat ";
	char emsg[] = "Close program.";


	memset(inmsg,'\0',BUFSIZ);
	printf("===========CLIENT==========\n");

	while(1){

		memset(inmsg,'\0',BUFSIZ);
		printf("insert message:");
		gets(inmsg);
	
		pd = open("./ONE_FIFO",O_WRONLY);
		write(pd,inmsg,strlen(inmsg)+1);
		//exit를 입력한  경우.
		if( strcmp(inmsg,"exit") == 0 ){
			write(pd,emsg,BUFSIZ);
			printf("%s\n",emsg);
			close(pd);
			break;
		}	
		//exit 안 입력.
		else{	
			close(pd);
			pd2 = open("./TWO_FIFO",O_RDONLY);
			read(pd2,msg,BUFSIZ);
				
			printf("inmsg : %s\n",msg);
			//서버에서 없다
			if ( strcmp(msg,"error") ==0){
				printf("file does not exist\n");
				memset(msg,'\0',BUFSIZ);
				
//				break;
			}
			else{
				printf("[server]:%s\n",msg);
				strcat(dmsg,msg);
				rename(msg,dmsg);
				strcat(cmsg,dmsg);
				system(cmsg);
				memset(dmsg,'\0',sizeof(dmsg));
				strcpy(dmsg,"download_");
				memset(cmsg,'\0',sizeof(cmsg));
				strcpy(cmsg,"cat ");	
							
			}
			close(pd2);
		}
	}
	
	}	
	
	
	
	
	
	
