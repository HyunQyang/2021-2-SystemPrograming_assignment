#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/un.h>
#include<fcntl.h>
#include<dirent.h>

#define SOCKET_NAME    "hsocket"
int main(){
	char buf1[BUFSIZ];
	char buf2[BUFSIZ];
	char buf3[BUFSIZ];
	char msg[BUFSIZ];
	char *cwd;
	struct sockaddr_un ser,cli;
	int sd, nsd,len,clen;
	int fd,i,n;
	DIR *dirp;
	struct dirent *dent;

	if((sd = socket(AF_UNIX,SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}	
	memset((char *)&ser,0,sizeof(struct sockaddr_un));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path,SOCKET_NAME);
	len = sizeof(ser.sun_family) +strlen(ser.sun_path);

	if(bind(sd,(struct sockaddr *)&ser,len)){
		perror("bind");
		exit(1);
	}
	if(listen(sd,5)<0){
		perror("listen");
		exit(1);
	}


	printf("waiting......\n");

	if((nsd = accept(sd,(struct sockaddr *)&cli,&clen)) == -1){
		perror("accept");
		exit(1);
	}

	//초기화
	memset(buf1,'\0',sizeof(buf3));
	memset(buf2,'\0',sizeof(buf2));
	memset(msg,'\0',sizeof(msg));
	memset(buf3,'\0',sizeof(buf3));
	
	//recieving
	if(recv(nsd,buf1,sizeof(buf1),0) == -1){
		perror("recv");
		exit(1);
	}
	printf("file path:%s\n",buf1);
	
	if(recv(nsd,buf2,sizeof(buf2),0) == -1){
		perror("recv");
		exit(1);
	}
	printf("file name: %s\n",buf2);


	if((dirp =opendir(buf1)) == NULL ){
		strcpy(buf3,"File not exist!!");
		perror("no path");
		send(nsd,buf3,sizeof(buf3),0);
		exit(1);	
	}
	
	//파일 읽기
	while((dent = readdir(dirp))){
		if((strcmp((dent->d_name),buf2))==0){
			chdir(buf1);

			if(fd = open(buf2,O_RDWR) ==-1){
				perror("open");
				exit(1);
			}

			n = lseek(fd,0,SEEK_END);

			if (n > 16)	n = 16;
			else 	n = n;

			lseek(fd,0,SEEK_SET);
		
			read(fd,buf3,n);
			break;
		}
	}
	
	close(sd);
	close(nsd);
	}
