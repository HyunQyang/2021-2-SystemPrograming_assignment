#include<stdio.h>

extern int add(int a,int b);
extern int sub(int a,int b);
extern int mul(int a,int b);

int main(){
	int sum=0;
	int s=0;
	int a=0;
	int b=0;

	printf("<Calculator Menu>\n1. Add\n2.Sub\n3. Mul\nEnter :");
	scanf("%d",&s);
	if(s ==1){
		printf("Enter two numbers:");
		scanf("%d%d",&a,&b);
		sum=add(a,b);
		printf("Result : %d+%d = %d",a,b,sum);

	}
	else if(s==2){
		printf("Enter two numbers:");
                scanf("%d%d",&a,&b);
                sum=sub(a,b);
                printf("Result : %d-%d = %d",a,b,sum);
	}
	else if(s==3){
		printf("Enter two numbers:");
                scanf("%d%d",&a,&b);
                sum=mul(a,b);
                printf("Result : %d*%d = %d",a,b,sum);
	}

}
