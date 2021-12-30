#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<sys/types.h>

int main(int argc, char* argv[]){

        if(argc !=4){
                printf("ERROR\n");
                exit(1);
        }


        FILE *fp;
        int n;;
        long cur;
        char buf[1024];
        char bufnew[1024];
        char* filename = argv[1];
        char* start_pos = argv[2];
        int start_pos_int =0;
        int char0_int1 = -1;
        if( isalpha(start_pos[0]) >0){
         char0_int1 = 0;
        }
        else{
                start_pos_int = atoi(start_pos);
                char0_int1 = 1;
        }
        int  offset = atoi(argv[3]);

       if((fp = fopen(filename,"r")) == NULL) {
                perror("fopen : unix.txt");
                exit(1);
        }

        cur = ftell(fp);            
       printf("Offset cur = %ld\n", (long)cur);


        if( char0_int1 == 1){
                if(start_pos_int >=0){
                        fseek(fp,start_pos_int,SEEK_CUR);
                }else{
                        fseek(fp,start_pos_int,SEEK_END);
                }
        } else {
              if( strcmp(start_pos,"begin") ==0){
                        rewind(fp);
                } else if (strcmp(start_pos,"mid") ==0){
                        fseek(fp,(0+SEEK_END)/2,SEEK_CUR);
                }else if (strcmp(start_pos,"end") ==0){
                        fseek(fp,start_pos_int,SEEK_END);
                }

        cur =ftell(fp);
        printf("<now> offset cur = %ld\n",(long)cur);

        n= fread(buf,sizeof(char),offset,fp);
        buf[n] = '\0';
        int m=0;
        if( n<offset){
                rewind(fp);
                m = fread(buf,sizeof(char),offset -n,fp);
                bufnew[m] = '\0';
              strncat(buf, strlen(bufnew));
        }

        printf("Read= %s\n",buf);


	}
}




