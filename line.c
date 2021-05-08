#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "line.h"




int main(int argc, char **argv)
{
	//basic error checking
	if(argc==7)
	{
		// initialize grid size
		x_size = argtoint(argv[1]);
		y_size = argtoint(argv[2]);


		// get coordinates for the line beginning and the line end
		x_start = argtoint(argv[3])-1;
		y_start = argtoint(argv[4])-1;
		x_end = argtoint(argv[5])-1;
		y_end = argtoint(argv[6])-1; 
	} else 
	{
		x_size = 25;
		y_size = 25;

		x_start = 5;
		y_start = 5;
		x_end = 15;
		y_end = 20; 
	}



	// get a struct big enough
	struct pixels pixel[x_size*y_size];


	//not sure how this works but it gets the job done
	//loops every pixel and add coordinate pair and an initial is_line value
	int offset = 0;
	for(int i=0;i<y_size;i++)
	{
		for(int j=0;j<y_size;j++)
		{
			pixel[offset].y_pos = i;
			pixel[offset].x_pos = j;
			pixel[offset].is_line = 0;
			offset++;
		}
	}


	int dx = x_end-x_start;
	int dy = y_end-y_start;
	//error stuff is needed for the Bresenham's line algorithm
	float deltaerr = abs(dy/dx);
	float err = 0.0;
	int y = y_start;

	//loop trough all the x-coordinates of the line and calculate the correct y-value
	//with the Bresenham's algorithm. Straight from wikipedia
	for(int x=x_start;x<x_end;x++)
	{
		plot(x, y, x_size, y_size, pixel);
		err = err + deltaerr;
		if (err >= 0.5)
		{
			y = y + copysignf(1.0, dy);
			err = err - 1.0;
		}
	}

	draw( x_size, y_size, pixel );
	return 0;
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
void plot(int x, int y, int x_size, int y_size, struct pixels *pixel)
{
	for(int i=0;i<(x_size*y_size);i++)
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