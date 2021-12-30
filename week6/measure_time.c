#include<stdio.h>
#include<stdlib.h>
#include<sys/times.h>
#include<limits.h>
#include<time.h>

#define SIZ 100000
void func_O1(int *arr){
	int len = sizeof(arr);
}
void func_ON(int *arr){
	long int sum =0;
	for(int i=0;i<SIZ;i++) 
		sum+=arr[i];
}
void func_ON2(int *arr){
	long int sum =0;
	for(int i =0; i<SIZ;i++)
		for(int i=0; i<SIZ;i++)
			sum += arr[i];
}
int main(){
	int arr[SIZ];
	int i=0;
	for(i =0; i<SIZ;i++) arr[i] = i;
	time_t t;
	struct tms mytms;
	clock_t t1,t2;
	clock_t n_t1,n_t2;
	clock_t n2_t1,n2_t2;

	if((t1 = times(&mytms)) == -1){
		perror("times 1");
		exit(1);
	}
	
	func_O1(arr);

       	if((t2 = times(&mytms)) == -1){
                perror("times 1");
                exit(1);
        }
	

	 if((n_t1 = times(&mytms)) == -1){
                perror("n_times 1");
                exit(1);
        }
	func_ON(arr);

	 if((n_t2 = times(&mytms)) == -1){
                perror("times 1");
                exit(1);
        }


	
	 if((n2_t1 = times(&mytms)) == -1){
                perror("n_times 1");
                exit(1);
        }
        	func_ON2(arr);

         if((n2_t2 = times(&mytms)) == -1){
                perror("times 1");
                exit(1);
        }






	//printf("%ld\n",CLOCKS_PER_SEC);
	printf("%ld, %ld, %ld\n",t1,t2,(t2-t1));

	 printf("%ld, %ld, %ld\n",n_t1,n_t2,(n_t2-n_t1));
	 printf("%ld, %ld, %ld\n",n2_t1,n2_t2,(n2_t2-n2_t1));
	
	printf("func_O1 takes %f sec\n", (double)(t2-t1));
	printf("func_ON takes %f sec\n",(double)(n_t2 - n_t1));
	printf("func_ON2 takes %f sec\n",(double)(n2_t2 - n2_t1));
	printf("%ld\n",CLOCKS_PER_SEC);

}
