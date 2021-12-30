#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

//구조체 구현부.
typedef struct Account{
        int saving;
        int balance;
        int amount;
}Account;

//함수 선언부
void disburse_money(Account *account);
void withdraw(Account *account);
pthread_mutex_t mutex_lock1;


//함수 구현부.
void  disburse_money(Account *account){
        pthread_mutex_lock(&mutex_lock1);
        account->saving = account->saving - account->amount;
         if( account->saving != account->balance)        perror("saving and balance not match");
	else printf("Fuction works!!\n");
        pthread_mutex_unlock(&mutex_lock1);                                
}

void  withdraw( Account *account){            
        const int balance = account->balance;
        const int amount = account->amount;
        if(balance < amount){
                perror("Error");
        }                                      
        account->balance = balance - amount;    
        disburse_money(account);               
}


//스레드 함수.
void *start_thread(void *acc){  
        int i;
        Account* ac = (Account*)acc;    
        withdraw(ac);
 printf("saving: %d, balance: %d, amount: %d\n",ac->saving,ac->balance,ac->amount);
        return acc;
}
int main(){
        pthread_t thing1,thing2;
        Account account = {.saving=10000,.balance=10000, .amount =3000};
        printf("[현재 계좌]  saving: %d, balance: %d, amount: %d\n",account.saving,account.balance,account.amount);

        pthread_create(&thing1,NULL,start_thread,(void *)&account);
        pthread_create(&thing2,NULL,start_thread,(void *)&account);

        pthread_join(thing1,NULL);
        pthread_join(thing2,NULL);
        return 0;
}
