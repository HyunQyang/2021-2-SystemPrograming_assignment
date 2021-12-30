#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define PORTNUM 9006

int main(void){
	int sd,n;
	char buf[BUFSIZ];
	char msg[BUFSIZ];
	struct sockaddr_in sin;



	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	sd = socket(AF_INET,SOCK_STREAM,0);
	connect(sd,(struct sockaddr *)&sin,sizeof(sin));
	

	memset(buf,'\0',sizeof(buf));
	memset(msg,'\0',sizeof(msg));
	recv(sd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	
	printf("[select server]:");
	gets(msg);
	send(sd,msg,sizeof(msg),0);

	if(strcmp(msg,"echo") == 0 ){
		memset(buf,'\0',sizeof(buf));
		while(1){
			printf("[insert message]\n");
			gets(buf);
			
			send(sd,buf,sizeof(buf) +1,0);
			printf("send: %s\n",buf);
			if(strcmp("quit",buf) == 0){
                                break;
                        }
			memset(buf,'\0',sizeof(buf));
			recv(sd,buf,sizeof(buf),0);
			printf("recv: %s\n",buf);
			memset(buf,'\0',sizeof(buf));
		}	
	}

	if(strcmp(msg,"info") ==0){

			memset(buf,'\0',sizeof(buf));
			recv(sd,buf,sizeof(buf),0);
			printf("[HOST]:%s\n",buf);

			memset(buf,'\0',sizeof(buf));
                        recv(sd,buf,sizeof(buf),0);
                        printf("[IP ADDRESS]:%s\n",buf);

			memset(buf,'\0',sizeof(buf));
                        recv(sd,buf,sizeof(buf),0);
                        printf("[PORT NUMBER]:%s\n",buf);
	}




	if(strcmp(msg,"stime") == 0){
		memset(buf,'\0',sizeof(buf));
		recv(sd,buf,sizeof(buf),0);
		printf("[SERVER TIME]: %s\n",buf);
	}



	close(sd);

	return 0;
}


