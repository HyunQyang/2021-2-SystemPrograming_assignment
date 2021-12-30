#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fp;
	int a;

	fp = popen("ls / | grep s","w");
	
	fprintf(fp,"Terminal:");
	
	pclose(fp);
	return 0;
	}	
