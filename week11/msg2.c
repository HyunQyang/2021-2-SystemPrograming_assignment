#include<sys/msg.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct mymsgbuf{
	long mtype;
	char mtext[BUFSIZ];
};

int main(){
	struct mymsgbuf inmsg;
	key_t key;
	int msgid,len;
	char msg[BUFSIZ];

	key = ftok("keyfile",1);
	inmsg.mtype = 1;	
	printf("========================Start chatting===============\n");
	printf("Want to exit? plz insert 'EXIT'\n");


	while(1)
	{
		memset(msg,'\0',BUFSIZ);
		printf("insert yout message:");
		gets(msg);
		
		if(strcmp(msg,"EXIT") == 0){
			printf("close program\n");
			break;

		}
		strcpy(inmsg.mtext,msg);

	       	if(strlen(msg) != 0){
			memset(msg,'\0',BUFSIZ);
			msgsnd(msgid,(void *)&inmsg,BUFSIZ,IPC_NOWAIT);
			printf("[me]:%s\n",inmsg.mtext);
			memset(inmsg.mtext,'\0',BUFSIZ);
		}
		else if((len = msgrcv(msgid,&inmsg,BUFSIZ,0,0)) > 0) {
			printf("[other]:%s\n",inmsg.mtext);
			memset(inmsg.mtext,'\0',BUFSIZ);

		}

	}	

}
