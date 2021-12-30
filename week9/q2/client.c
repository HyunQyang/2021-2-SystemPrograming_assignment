#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9005
int main(void){
	int sd,n;
	char buf[BUFSIZ];
	struct sockaddr_in sin;

	sd = socket(AF_INET,SOCK_DGRAM,0);

	memset((char *)&sin,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port =htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(buf,'\0',BUFSIZ);
	sprintf(buf,"TIME-REQUEST.");
	sendto(sd,buf,strlen(buf)+1,0,(struct sockaddr *)&sin,sizeof(sin));

	memset(buf,'\0',BUFSIZ);
	recvfrom(sd,buf,sizeof(buf),0,NULL,NULL);
	printf("RECV: %s\n",buf);

	close(sd);

	return 0;
}
