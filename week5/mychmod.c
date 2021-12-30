#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char* argv[]){
	struct stat buf;
	char* modnum = NULL ;
	char* filename = NULL;
	char buffer[10] = {0,};
	

                 if((buf.st_mode & S_IRUSR) != 0)  buffer[0] += 'r';
		 else if((buf.st_mode & S_IRUSR) ==0)     buffer[0] += '-';
		 if((buf.st_mode & S_IWUSR) != 0 )  buffer[1] += 'w';
		 else buffer[1] +='-';
		 if((buf.st_mode & S_IXUSR) != 0) buffer[2] += 'x';
		 else if((buf.st_mode &S_IXUSR) == 0)    buffer[2] += '-';
		 if(buf.st_mode & S_IRGRP) buffer[3] += 'r';
		 else buffer[3] += '-';
	         if(buf.st_mode & S_IWGRP)  buffer[4] += 'w';
		 else buffer[4] +='-';
		 if(buf.st_mode & S_IXGRP) buffer[5] += 'x';
		 else buffer[5] += '-';
		 if(buf.st_mode & S_IROTH) buffer[6] += 'r';
		 else buffer[6] += '-';																											      if(buf.st_mode & S_IWOTH)  buffer[7] += 'w';
	         else buffer[7] +='-';
		 if(buf.st_mode & S_IXOTH) buffer[8] += 'x';
		 else buffer[8] += '-';

	if(argc == 2){
		filename = argv[0];
		
		/*if((buf.st_mode & S_IRUSR) != 0)  buffer[0] += 'r';
                else if((buf.st_mode & S_IRUSR) ==0)     buffer[0] += '-';
                if((buf.st_mode & S_IWUSR) != 0 )  buffer[1] += 'w';
                else buffer[1] +='-';
                if((buf.st_mode & S_IXUSR) != 0) buffer[2] += 'x';
                else if((buf.st_mode &S_IXUSR) == 0)    buffer[2] += '-';
                if(buf.st_mode & S_IRGRP) buffer[3] += 'r';
                else buffer[3] += '-';
                if(buf.st_mode & S_IWGRP)  buffer[4] += 'w';
                else buffer[4] +='-';
                if(buf.st_mode & S_IXGRP) buffer[5] += 'x';
                else buffer[5] += '-';
                if(buf.st_mode & S_IROTH) buffer[6] += 'r';
                else buffer[6] += '-';
                if(buf.st_mode & S_IWOTH)  buffer[7] += 'w';
                else buffer[7] +='-';
                if(buf.st_mode & S_IXOTH) buffer[8] += 'x';
                else buffer[8] += '-';
		*/
                printf("Permission: %s\n",buffer);
     		}

	if(argc ==3){

		printf("Permission (brfore): %s\n",buffer);
		modnum = argv[0];
		filename = argv[1]; 
		buffer[10] ={0,};
		printf("asdf: %s\n",buffer);






	}

}
