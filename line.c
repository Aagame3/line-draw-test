#include "line.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <ncurses.h>
#include <limits.h>




void init(int x_size, int y_size, int x_start, int y_start, int x_end, int y_end, struct pixels* pixel )
{
	size_t len = x_size*y_size;

	//loops every pixel and add coordinate pair and an initial is_line value
	int offset = 0;
	for(int i=0;i<x_size;i++)
	{
		for(int j=0;j<y_size;j++)
		{
			pixel[offset].y_pos = i;
			pixel[offset].x_pos = j;
			pixel[offset].is_line = 0;
			offset++;
		}
	}
	drawline(x_start, y_start, x_end, y_end, len, pixel);

	return;
}

void drawline(int x_start, int y_start, int x_end, int y_end, size_t len, struct pixels* pixel)
{
    int dx, dy, p, x, y;
 
	dx=x_end-x_start;
	dy=y_end-y_start;
 
	x=x_start;
	y=y_start;
 
	p=2*dy-dx;
 
	while(x<x_end)
	{
		if(p>=0)
		{
			plot(x,y,len, pixel);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			plot(x,y,len, pixel);
			p=p+2*dy;
		}
		x=x+1;
	}
}
//function to draw the grid and if it draws a dot or a line
//lots of if statements for \n printing. Could probably be
//improved upon
void draw(int x_size, int y_size, struct pixels *pixel)
{
	for(int i=0;i<(x_size*y_size);i++)
	{
		if(pixel[i].is_line == 0)
		{
			if(pixel[i].x_pos == x_size-1)
			{
				printf(" .\n");
			}else {
				printf(" . ");
			}
		}else {
			if(pixel[i].x_pos == x_size-1)
			{
				printf(" *\n");
			}else {
				printf(" * ");
			}
		}
	}
}

//This is a function that searches the pixels with the correct coordinate pair
//to draw as a line
void plot(int x, int y, size_t len, struct pixels *pixel)
{
	for(int i=0;i<len;i++)
	{
		if(pixel[i].x_pos == x && pixel[i].y_pos == y)
		{
			pixel[i].is_line=1;
		}		
	}
}

// Helper function to convert args to int as needed by the program
//has some error checking
int argtoint(char *arg)
{
	char *p;
	long arg_long = strtol(arg, &p, 10);
	if (*p != '\0' || errno != 0)
		return 1; 
	if (arg_long < INT_MIN || arg_long > INT_MAX) 
    	return 1;
	int ret = arg_long;
	return ret;
}