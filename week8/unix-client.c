#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/un.h>
#include<fcntl.h>

#define SOCKET_NAME "hsocket"

int main(){
	char buf1[BUFSIZ];
	char msg[BUFSIZ];
	char buf2[BUFSIZ];
	char buf3[BUFSIZ];
	struct sockaddr_un ser, cli;
	int sd, nsd, len, clen;
	int fd;



	if((sd = socket(AF_UNIX,SOCK_STREAM,0)) ==-1){
		perror("socket");
		exit(1);
	}
	memset((char *)&ser, 0, sizeof(struct sockaddr_un));
	ser.sun_family =AF_UNIX;
	strcpy(ser.sun_path,SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	if(connect(sd,(struct sockaddr *)&ser,len)<0){
		perror("bind");
		exit(1);
	}
	//send and recv
	
	//sending
	memset(buf1,'\0',sizeof(buf1));
	printf("[Insert File path]\n");
	scanf("%s",buf1);
	if(send(sd,buf1,sizeof(buf1),0) == -1){
		perror("send");
		exit(1);
	}
	memset(buf2,'\0',sizeof(buf2));
	printf("[File Name]\n");
	scanf("%s",buf2);
	if(send(sd,buf2,sizeof(buf2),0) ==-1){
		perror("send");
		exit(1);
	}



	//recieving
	memset(msg,'\0',sizeof(msg));
	if(recv(sd,msg,sizeof(msg),0) ==-1){
		perror("recv");
		exit(1);
	}

	if((strcmp(msg,"File not exist!!")) != 0){
		fd = open(buf1,O_CREAT| O_WRONLY,0774);
		memset(buf3,'\0',sizeof(buf3));
		write(fd,buf3,16);	
		close(fd);
	}
	else{
		printf("%s\n",msg);
	}	
	close(sd);
	

	return 0;

}



