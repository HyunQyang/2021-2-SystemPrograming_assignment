#include<sys/utsname.h>
#include<stdlib.h>
#include<stdio.h>
#include<getopt.h>
#include<string.h>

#define SIZ 32

int main(int argc,char *argv[]){
	struct utsname uts;
	int n;

	char s_buf[SIZ] = {0,};
	char n_buf[SIZ] = {0,};
	char v_buf[SIZ] = {0,};
	char m_buf[SIZ] = {0,};

	char* s_add;
	char* n_add;


	if(uname(&uts) == -1){
		perror("Error\n");
		exit(1);
	} 
	if(argc == 1){
	printf("systemSummary available options:\n");
	printf("-s: print OS name\n");
	printf("-n: print nodename(host name)\n");
	printf("-v: print release\n");
	printf("-m: print machine info\n");
	}
	while((n = getopt(argc,argv,"svnm")) != -1){
		switch(n){
			case 's':
				s_add = " machine";
				strncpy(s_buf,uts.sysname,strlen(uts.sysname));
				strncat(s_buf,s_add,strlen(s_add));
				break;

			case 'n':
				n_add = "named ";
				strncpy(n_buf,n_add,strlen(n_add));
				strncat(n_buf,uts.nodename,strlen(uts.nodename));
				break;
			case 'v':
				strncpy(v_buf,uts.release, strlen(uts.release));
				break;
			case 'm':
				strncpy(m_buf,uts.machine,strlen(uts.machine));
				break;
			}
		}

		printf("This is a %s %s %s %s.\n",m_buf,s_buf,v_buf,n_buf);

	}
