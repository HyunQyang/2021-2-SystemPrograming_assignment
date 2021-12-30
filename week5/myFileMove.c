#include<stdio.h>
#include<stdlib.h>
int main(){
	if(rename("src.txt","dst.txt")){
		perror("src.txt");
		exit(1);
	}


}
