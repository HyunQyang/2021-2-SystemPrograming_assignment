#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<unistd.h>

int main(void){
	DIR *dp;
	struct dirent *dent;
	struct stat buf;
	char *cwd;
	char wd[BUFSIZ];
	int kind;
	int i=0;
	int j=0;
	char* aa[BUFSIZ];


	if((dp = opendir("week5")) == NULL){
		perror("open: week5");
		exit(1);
	}
	
	chdir("week5");
	printf("<Regular file>\n");
	 while((dent = readdir(dp))){
                lstat(dent->d_name,&buf);
                if(S_ISREG(buf.st_mode)){
                        if(dent->d_name[0] == '.') continue;
                        printf("%s\n",dent->d_name);
                }/*else{
			if(dent->d_name[0] =='.') continue;	       
			printf("%s\n",dent->d_name);
	 }*/
	 }
	 chdir("..");
	printf("<Directory>\n");
	
		opendir("week5");
		while((dent = readdir(dp))){
		lstat(dent->d_name,&buf);
		if(S_ISDIR(buf.st_mode)){
			if(dent->d_name[0] == '.') continue;
			printf("%s\n",dent->d_name);
		}

	}
	/*sprintf(path,"week5",dent->d_name);
	getcwd(wd,BUFSIZ);
	printf("%s\n",wd);
	stat(path,&buf);
	kind = buf.st_mode&S_IFMT;*/
	closedir(dp);

}


