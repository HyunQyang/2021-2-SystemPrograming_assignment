#include<sys/types.h>
#include<sys/mman.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/sem.h>

void handler(int dummy){
	;
}

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int initsem(key_t semkey){
	union semun semunarg;
	int status =0,semid;

	semid = semget(semkey,1,IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1){
		if (errno == EEXIST)
			semid = semget(semkey,1,0);
	}
	else {
		semunarg.val = 1;
		status = semctl(semid,0,SETVAL,semunarg);
	}

	if(semid == -1 || status == -1){
		perror("initsem");
		return(-1);
	}
	return semid;
}

int semlock(int semid){
	struct sembuf buf;

	buf.sem_num =0;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid,&buf,1) == -1){
		perror("semlock failed");
		exit(1);
	}
	return 0;
}

int semunlock(int semid){
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid,&buf,1) == -1){
		perror("semluck failed");
		exit(1);
	}
	return 0;
}






int main(int argc,char** argv){
	key_t key;
	int shmid;
	void *shmaddr;
	char buf[1024];
	char *msg;
	sigset_t mask;

	key = ftok("hellofile",1);
	shmid = shmget(key,1024,IPC_CREAT|0777);

	sigfillset(&mask);
	sigdelset(&mask,SIGUSR1);
	sigset(SIGUSR1,handler);
	msg = argv[1];

	printf("==========server==========\n");
	sigsuspend(&mask);
	
	shmaddr = shmat(shmid,NULL,0);

	while(1){
		memset(buf,'\0',1024);
		strcpy(buf,shmaddr);
		printf("[you]: %s\n",buf);
		if( strcmp(buf,"exit") ==0){
			printf("exit\n");
			shmdt(shmaddr);
			break;
		}
		shmdt(shmaddr);
		shmid(key,1024,IPC_CREAT|0777);

		//writing message
		memset(buf,'\0',1024);
		
		printf("[insert]:");
		gets(msg);
		strcpy(shmaddr,msg);
		printf("[me]: %s\n",msg);
		if(strcmp(buf,"exit") ==0){
			printf("exit\n");
			shmdt(shmaddr);
			break;
		}

		sleep(3);
	}
	return 0;
}
