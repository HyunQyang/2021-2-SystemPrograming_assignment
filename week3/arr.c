#include<stdio.h>
#include<stdlib.h>


int main(){
	int size=10;
	int n=0;
	int* arr;
	int sum=0;
	int i=0;
	int size1;
	int debug =0;

	arr = (int*)malloc(sizeof(int)*size);
	printf("n=%d, size =%d, sum=%d\n",n,size,sum);
	printf("=============================================\n");
	
	for(i=0;i<100;i++){		
		arr[n]=i+1;
		n++;
		sum = sum+arr[i];
		if(n==size){
			arr=(int*)realloc(arr,sizeof(int)*size*2);
			size1 =size;
			size *=2;
#ifdef DEBUG
			printf("Size up: %d => %d\n",size1,size);
#endif
		}	
	}
	printf("n= %d,size= %d,sum = %d\n",n,size,sum);
	printf("=========================================\n");	
	sum=0;

	for(i=100;i>11;i--){
		arr[i-1] =0;
		n--;
		//printf("%d\n",arr[i]);
		sum= sum+arr[i];	
		if(n<=(size/4)){
			arr=(int*)realloc(arr,sizeof(int)*size/2);
			size1 =size;
			size/=2;
#ifdef DEBUG
			printf("Size down:%d => %d\n",size1,size);
#endif
		}
	}
	printf("n=%d , size = %d , sum= %d\n",n,size,sum);
	printf("========================================\n");

	for(i=0;i<10;i++){
		sum = sum+arr[i];
	}
	printf("n= %d , size= %d , sum= %d\n",n,size,sum);
	free(arr);	
}
