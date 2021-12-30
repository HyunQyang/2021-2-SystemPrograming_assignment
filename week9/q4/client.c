#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9007

int main(void){
	int sd;
	char buf[BUFSIZ];
	struct sockaddr_in sin;

	memset((char *)&sin,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	sd = socket(AF_INET,SOCK_STREAM,0);
	connect(sd,(struct sockaddr *)&sin,sizeof(sin));
	memset(buf,'\0',sizeof(buf));
	while(1){
		printf("[insert your message]\n");
		gets(buf);
		
		send(sd,buf,sizeof(buf),0);
		printf("[client]: %s\n",buf);
		if(strcmp(buf,"quit") == 0){
			break;
		}
		memset(buf,'\0',sizeof(buf));
		recv(sd,buf,sizeof(buf),0);
		printf("[server]: %s\n",buf);
	}
	close(sd);

	return 0;
}

