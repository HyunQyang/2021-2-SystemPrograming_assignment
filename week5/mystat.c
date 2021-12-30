#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[]){
	struct stat buf;
	int kind;
	char* name = argv[1];
	char buffer[10];
	stat(name,&buf);
	
	printf("FIlename:%s\n",                name );
	printf("inode number:%d\n",		(int)buf.st_ino);
	if(S_ISREG(buf.st_mode))	printf("Filetype: regular type\n");
	if(S_ISDIR(buf.st_mode)) 	printf("Filetype: directory\n");
	printf("Permission:%o\n"	,(unsigned int)buf.st_mode);	
	printf("Number of links:%d\n",		(unsigned int)buf.st_nlink);
	printf("Size:%d\n",	(int)buf.st_size);


}

