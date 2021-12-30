#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9001

int main(void){
	//선언부
	char buf[BUFSIZ];
	char msg[BUFSIZ];
	struct sockaddr_in sin, cli;
	int sd,ns,clientlen,a;

	
	// socket on
	memset((char *)&sin,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	//socket open.
	sd = socket(AF_INET, SOCK_STREAM,0);

	bind(sd,(struct sockaddr *)&sin, sizeof(sin));

	listen(sd,5);
	
	ns = accept(sd,(struct sockaddr *)&cli,&clientlen);




	printf("do you want to quit? plz insert [QUIT]\n");
	//sending and receiving msg
	while(1){

		memset(buf,'\0',sizeof(buf));
        	//insert and sending.
               	gets(buf,BUFSIZ);
		printf("ME: %s\n",buf);
                send(ns,buf,sizeof(buf),0);
		if(strcmp(buf,"quit") == 0){
			break;
		}
		memset(msg,'\0',sizeof(msg));
                recv(ns,msg,sizeof(msg),0);
                printf("YOU: %s\n",msg);
		if(strcmp(msg,"quit") == 0){
                        break;
                }

	}
	close(ns);
	close(sd);
	return 0;

}
