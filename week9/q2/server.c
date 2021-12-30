#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#define PORTNUM 9005

int main(void){
	char buf[BUFSIZ];
	struct sockaddr_in sin,cli;
	int sd,clientlen = sizeof(cli);

	sd = socket(AF_INET, SOCK_DGRAM,0);

	memset((char *)&sin,'\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd,(struct sockaddr *)&sin, sizeof(sin));
	//
	memset(buf,'\0',BUFSIZ);
	recvfrom(sd,buf,sizeof(buf),0, (struct sockaddr *)&cli,&clientlen);
	printf("RECIEVED:%s\n",buf);
	memset(buf,'\0',BUFSIZ);
	printf("IP address: %s\n",inet_ntoa(sin.sin_addr));
	time_t now;
	time(&now);
	sprintf(buf,"%s",ctime(&now));
	printf("MSG2TRANSMIT: %s\n",buf);
	sendto(sd,buf,strlen(buf)+1,0,(struct sockaddr *)&cli,sizeof(cli));

	close(sd);

	return 0;
}
