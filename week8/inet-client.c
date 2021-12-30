#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9000

int main(){
	int sd;
	char buf[256];
	struct sockaddr_in sin;
	char msg[256];
	int len = strlen(msg)+1;

	if((sd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sd,(struct sockaddr *)&sin,sizeof(sin))){
		perror("connect");
		exit(1);
	}

	while(1){
		memset(msg,'\0',sizeof(msg));
		printf("Insert message\n");
		gets(msg);
		
		if(send(sd,msg,sizeof(msg)+1,0) == -1){
			perror("send");
			exit(1);
		}
		memset(buf,'\0',sizeof(buf));
		if(recv(sd,buf,sizeof(buf),0) ==-1){
			perror("recieve");
			exit(1);
		}
		printf("From Server :%s\n",buf);
		memset(buf,'\0',sizeof(buf));


		if(strcmp(msg,"exit")==0){
			break;
		}	
		}
	close(sd);

	return 0;

}
