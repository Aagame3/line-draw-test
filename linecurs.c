#include "line.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ndraw(int row, int col, struct pixels *pixel);

int main(int argc, char **argv)
{	int row, col;
	int x_start;
	int y_start;
	int x_end;
	int y_end;

	initscr();
	printw("Give first coordinate ");
	scanw("%d%d", &x_start, &y_end);
	printw("Give second coordinate ");
	scanw("%d%d",&x_end, &y_end);

	getmaxyx(stdscr,row,col);
	// get a struct big enough
	struct pixels pixel[row*col];
	init(row, col, x_start, y_start, x_end, y_end, pixel );
	ndraw(row, col, pixel);
	getch();
		endwin();

	return 0;
}

void ndraw(int row, int col, struct pixels *pixel)
{
	move(0,0);
	for(int i=0;i<(row*col);i++)
	{
		if(pixel[i].is_line == 0) {
			addch('.');
		} else {
			addch('*');
		}
	}
}
