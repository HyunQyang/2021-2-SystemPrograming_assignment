#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(){
	struct hostent *hent;
	struct sockaddr_in addr;
	char s[64];
	int n;
	
	printf("insert hostname:");
	scanf("%s",s);
	
	
	hent = gethostbyname(s);
	if(!hent){
		printf("Not Found\n");
		exit(1);
	}
	else{
		for (n =0;hent->h_addr_list[n] != NULL; n++)
			printf("IP Address: %s\n",inet_ntoa(*(struct in_addr*)hent->h_addr_list[n]));
		
	}
	return 0;



}
