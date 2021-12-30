#include<sys/types.h>
#include<signal.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<errno.h>

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
                  perror("semlock failed");
                  exit(1);
          }
          return 0;
  }
 
int main(int argc, char** argv){
	key_t key;
	int shmid;
	void *shmaddr;
	char buf[1024];
	char msg[1024];

	key = ftok("hellofile",1);
	shmid = shmget(key,1024,0);

	printf("========client=========\n");
	shmaddr = shmat(shmid,NULL,0);

	while(1){
		memset(buf,'\0',1024);
		printf("[insert]:");
		gets(buf);
		 if(strcmp(buf,"exit") == 0){
                          shmdt(shmaddr);
                          shmctl(shmid,IPC_RMID,NULL);
                          break;
                }
		printf("[me]: %s\n",buf);
		strcpy(shmaddr,buf);
		kill(atoi(argv[1]),SIGUSR1);
	
		sleep(2);
		memset(buf,'\0',1024);
		strcpy(buf,shmaddr);
		printf("[you]:%s\n",buf);
		}
	return 0;
}
