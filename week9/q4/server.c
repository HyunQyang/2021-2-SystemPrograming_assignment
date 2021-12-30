#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9007

int main(void){
	char buf[BUFSIZ];
	struct sockaddr_in sin,cli;
	int sd, ns, clientlen = sizeof(cli);
	int n;

	sd = socket(AF_INET,SOCK_STREAM,0);

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd,(struct sockaddr *)&sin,sizeof(sin));
	listen(sd,5);

	while(1){
		ns = accept(sd,(struct sockaddr *)&cli, &clientlen);

		switch(fork()){
			case 0:
				printf("[ECHO SERVER]\n");
				close(sd);
				while(1){
					memset(buf,'\0',sizeof(buf));
					recv(ns,buf,sizeof(buf),0);
					send(ns,buf,sizeof(buf),0);
					if( strcmp(buf,"quit") ==0){
						exit(1);
					}
				}
				close(ns);
			}
	}
	return 0;
}

