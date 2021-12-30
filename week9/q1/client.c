#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define PORTNUM 9001

int main(void){
	int sd,strc;
	char buf[BUFSIZ];
	char msg[BUFSIZ];
	struct sockaddr_in sin;
	char *quit;


	quit = "quit";
	

	memset((char *)&sin ,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	sd = socket(AF_INET, SOCK_STREAM,0);
	
	connect(sd,(struct sockaddr *)&sin, sizeof(sin));

	printf("if you want to quit plz insert [QUIT]\n");
	while(1){
		memset(buf,'\0',sizeof(buf));
	        recv(sd,buf,sizeof(buf),0);
        	printf("YOU: %s\n",buf);

		if(strcmp(buf,"quit") ==0){
                        break;
                }
                memset(msg,'\0',sizeof(msg));
                gets(msg,BUFSIZ);
		printf("ME: %s\n",msg);
                send(sd,msg,sizeof(msg),0);
		
		if(strcmp(msg,"quit") == 0){
			break;
		}		
	}
	close(sd);

	return 0;
}


