#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>



typedef struct StudentInfo{
	char name[BUFSIZ];
	char major[BUFSIZ];
	char univ[BUFSIZ];
}StudentInfo;

void *start_thread(void *stu){
	int i;
	StudentInfo* sstu = (StudentInfo*)stu;
	for( int i = 0; i < 10; i++ ){
//		sleep(1);
		printf("[INFO]: %s, %s, %s\n",sstu->name,sstu->major,sstu->univ);
//		sleep(1);
	}
	return stu;
}

int main(){
	int n;
	pthread_t thing1,thing2;
	StudentInfo stu1 = { .name = "Bradd Pitt", .major = "Computer Engineering", .univ = "Holly University"};
	StudentInfo stu2 = {"Angelina Jollie","Computer Science","Wood University"};
	pthread_create(&thing1,NULL,start_thread,(void *)&stu1);
	pthread_create(&thing2,NULL,start_thread,(void *)&stu2);

	pthread_join(thing1,NULL);
	pthread_join(thing2,NULL);


	return 0;
}
