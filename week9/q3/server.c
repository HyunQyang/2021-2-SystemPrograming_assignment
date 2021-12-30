#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<netdb.h>

#define PORTNUM 9006

int main(void){
	char e_buf[BUFSIZ];
	char i_buf[BUFSIZ];
	char t_buf[BUFSIZ];
	char msg[BUFSIZ];
	
	struct sockaddr_in sin,cli;
	int sd, ns, clientlen = sizeof(cli);
	struct hostent *hent;

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	//making socket and binding
	sd = socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr *)&sin, sizeof(sin));
	listen(sd,5);


	ns = accept(sd, (struct sockaddr *)&cli, &clientlen);
	while(1){
	//ns = accept(sd, (struct sockaddr *)&cli, &clientlen);
	memset(msg,'\0',sizeof(msg));
	sprintf(msg,"<Available Services>\n 1. Echo server<ECHO>\n 2.Get server info<SINFO>\n 3. Get server time<STIME>");
        send(ns,msg,sizeof(msg),0);	
	
        memset(msg,'\0',sizeof(msg));
        recv(ns,msg,sizeof(msg),0);
	if(strncmp(msg,"echo",sizeof(msg)) == 0){
		printf("[ECHO SERVER]\n");
		memset(msg,'\0',sizeof(msg));
		memset(e_buf,'\0',sizeof(e_buf));
		while(1){
			recv(ns,e_buf,sizeof(e_buf),0);
			send(ns,e_buf,strlen(e_buf)+1,0);
			memset(e_buf,'\0',sizeof(e_buf));
		}

		break;
	}
	//after client select sinfo
	if(strcmp(msg,"info") == 0){
		printf("[SINFO SERVER]\n");
		memset(i_buf,'\0',sizeof(i_buf));
		gethostname(i_buf,sizeof(i_buf));
		send(ns,i_buf,sizeof(i_buf),0);

		memset(i_buf,'\0',sizeof(i_buf));
		sprintf(i_buf,"%s",inet_ntoa(sin.sin_addr));
		send(ns,i_buf,sizeof(i_buf),0);

		memset(i_buf,'\0',sizeof(i_buf));
		sprintf(i_buf,"%d",PORTNUM);
		send(ns,i_buf,sizeof(i_buf),0);


		break;	
	}

	if (strcmp(msg,"stime") == 0){
		printf("[STIME SERVER]\n");
		memset(t_buf,'\0',BUFSIZ);
		time_t now;
                time(&now);
                sprintf(t_buf,"%s",ctime(&now));
                send(ns,t_buf,BUFSIZ,0);		
		break;
	}
	
	close(ns);	
}
close(sd);
return 0;
}





