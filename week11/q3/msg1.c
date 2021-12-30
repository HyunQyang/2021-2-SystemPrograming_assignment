#include<sys/msg.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct mymsgbuf{
	long mtype;
	char mtext[BUFSIZ];
};

int main(){
	key_t key,key2;
	int msgid, msgid2,len;
	char msg[BUFSIZ];
	struct mymsgbuf mesg;

	key = ftok("keyfile",1);
	msgid = msgget(key,IPC_CREAT|0777);
	mesg.mtype = 1;
	
	printf("==================Start chatting====================\n");
	printf("Want to exit? plz insert 'EXIT'\n");
	//메시지 받아오기.
	while(1)
	{
		memset(msg,'\0',BUFSIZ);
		printf("insert your message:");
		gets(msg);
		// insert EXIT -> close program.
		if( strcmp(msg,"EXIT") == 0){
			printf("Close Program\n");
			break;
		}
		strcpy(mesg.mtext,msg);

		//메시지 전송.
		 if(strlen(msg)!=0){
			memset(msg,'\0',BUFSIZ);
			msgsnd(msgid,(void *)&mesg,BUFSIZ, IPC_NOWAIT);
			printf("[me]:%s\n",mesg.mtext);
			memset(mesg.mtext,'\0',BUFSIZ);
		}
		//메시지 수신.
		else if(( len =  msgrcv(msgid,&mesg,BUFSIZ,0,0)>0)) {
			printf("[other]:%s\n",mesg.mtext);
			memset(mesg.mtext,'\0',BUFSIZ);
		}


	
	}
	return 0;
}
