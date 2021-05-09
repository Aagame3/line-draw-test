#include "line.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ndraw(int row, int col, struct pixels *pixel);

int main(int argc, char **argv)
{
	//char inpt[80];
	int row, col;
	int x_start = argtoint(argv[1]);
	int y_start = argtoint(argv[3]);
	int x_end = argtoint(argv[2]);
	int y_end = argtoint(argv[4]);

	initscr();
	getmaxyx(stdscr,row,col);
	// get a struct big enough
	struct pixels pixel[row*col];
	//pixel = NULL;
	//getch();
	init(row, col, x_start, y_start, x_end, y_end, pixel );
	ndraw(row, col, pixel);
	getch();
	//mvprintw(1,1,"%d", pixel[1].x_pos);
	//getch();
	//char out[row*col];
	//memset(out, '.', row*col);
	//getstr(inpt);
	//mvprintw(0, 0, out);

	//getch();
	endwin();

	return 0;
}

void ndraw(int row, int col, struct pixels *pixel)
{
	move(0,0);
	for(int i=0;i<(row*col);i++)
	{
		if(pixel[i].is_line ==0)
			addch('.');
		else
			addch('*');
	}
}
