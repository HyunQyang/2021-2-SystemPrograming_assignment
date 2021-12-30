#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>


int main(){
	int pd,n,pd2;
	int check = 0;
	char msg[BUFSIZ] = "error";
	DIR *dirp;
	struct dirent *file;
	char *cwd;
	char emsg[] = "error";

	//이전에 사용된 FIFO 파이프 삭제.
	system("rm -f ONE_FIFO");
	memset(msg,'\0',BUFSIZ);
	printf("=======Server========\n");
	mkfifo("./ONE_FIFO",0777); // 읽기 전용 fifo생성 
	mkfifo("./TWO_FIFO",0777);// 쓰기 전용 fifo 생성
	//클라이언트한테 받아옴.
	while(1)
	{
		pd = open("./ONE_FIFO",O_RDONLY);
		read(pd,msg,BUFSIZ);
		
		printf("msg : %s\n",msg);
		//exit를 받아온 경우 종료.
		if( strcmp(msg,"exit") == 0){
			printf("[Client]:%s\n",msg);
			close(pd);
			break;
		}
		else {
			cwd = getcwd(NULL,BUFSIZ);
			if((dirp = opendir(cwd)) == NULL){
				printf("error");
				break;
			}
			while( (file = readdir(dirp))!= NULL){
				//파일 있.
				if( (strcmp(file->d_name,msg)) == 0 )
				{
					printf("[FILE FOUND]\n");
					check++;
					break;
				}
				// 파일 없음		
				else{
					printf("[FILE NOT FOUND]\n");
				}
				
			}
			
			if(check == 1)
			{
					close(pd);
					pd2 = open("./TWO_FIFO",O_WRONLY);
					write(pd2,msg,strlen(msg)+1);
					close(pd2);
			}
			else
			{
				close(pd);
				pd2 = open("./TWO_FIFO",O_WRONLY);
				write(pd2,emsg,strlen(emsg) + 1);
				close(pd2);
			}
			check = 0;

		}
		close(pd);	
	}


}
