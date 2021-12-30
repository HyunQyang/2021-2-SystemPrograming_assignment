#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	char mesg[] = "Just a string";
	int row,col;

	//printf("%d %d\n",row,col);
	initscr();
	srand(time(NULL));
	row = rand()%28;
	col = rand()%100;
	//printf("%d  %d\n",row,col);
	//getmaxyx(stdscr,row,col);
	//printf("%d %d\n",row,col);
	//move(row,col);
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

	mvprintw(row - 2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program agin");
	refresh();
	getch();
	endwin();

	return 0;
}
