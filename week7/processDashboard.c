#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ncurses.h>
#define SIZ 32

int main(int argc,char* argv[]){
        int row,col;
        int cnt = 5;
	int n;
        char buf[SIZ] ={0,};
        initscr();
        getmaxyx(stdscr,row,col); 


	while(( n = getopt(argc,argv,"r:")) != -1){
		switch(n){
			case 'r':
				cnt = atoi(argv[2]);
				break;
		}
	}
        while(TRUE){
                mvprintw(0,0,"<Process Dashboard>");
                mvprintw(1,0," ");
                sprintf(buf ,"* RUnning Process (%d):",cnt);
                mvprintw(2,0,"%s",buf);
		system("./pids.sh > pids.txt");
		FILE* fp = fopen("pids.txt","r");
		int i = 0;
		while(fgets(buf,BUFSIZ,fp)){
			mvprintw(3+i,0,"%d",buf);
			memset(buf,'\0',SIZ);
			i+=1;
			if( i  >= cnt) break;
		}
		for(;i<=cnt;i++){
			 mvprintw(3+i,0,"               ");
		}

		fclose(fp);
                refresh();
		sleep(1);
        }
        endwin();



        return 0;



}

