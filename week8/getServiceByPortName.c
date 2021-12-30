#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
	struct servent *port;
	int a;
	int n=0;
	char portnum[BUFSIZ];

	setservent(0);

	printf("insert port number:");
	scanf("%d",&n);
	port = getservbyport(htons(n),"tcp");
	
	printf("Name: %s\n",port->s_name);

/*	
	printf("asdf\n");
	scanf("%s",portnum);
	port = getservbyname(portnum,"tcp");
	printf("Name=%s port=%d",port->s_name,port->s_port);
*/


	endservent();
	
	return 0;
}

