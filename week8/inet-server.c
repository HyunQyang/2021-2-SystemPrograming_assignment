#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORTNUM 9000
int main(){
	char buf[BUFSIZ];
	char nbuf[BUFSIZ];
	char prev;
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli),nread;
	int rlen;

	if((sd = socket(AF_INET,SOCK_STREAM,0))== -1) {
		perror("socket");
		exit(1);
	}


	memset((char *)&sin,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sd,(struct sockaddr *)&sin,sizeof(sin))){
		perror("bind");
		exit(1);
	}

	if(listen(sd,5)){
		perror("listen");
		exit(1);
	}
	
	if((ns = accept(sd, (struct sockaddr *)&cli,&clientlen)) ==-1){
		perror("accept");
		exit(1);
	}
	
	while(1){
		
		memset(nbuf,'\0',sizeof(nbuf));
		if(recv(ns,nbuf,sizeof(nbuf),0) == -1){
			perror("recv");
			exit(1);
		}
		printf("%s\n",nbuf);
		memset(nbuf,'\0',sizeof(nbuf));	
		sprintf(buf,"Server recieved Messege");
		if(send(ns,buf,strlen(buf)+1,0) == -1){
			perror("send");
			exit(1);
		}
		memset(buf,'\0',sizeof(buf));
	}
	close(ns);
	close(sd);

	return 0;
}
	
