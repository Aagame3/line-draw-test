#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

//basic struct of data every point has
struct pixels {
	
	int x_pos;
	int y_pos;

	//wether to draw as a line or as a star
	int is_line;

};

// function prototypes
void draw( int x_size, int y_size, struct pixels *pixel );
void plot( int x, int y, int x_size, int y_size, struct pixels *pixel );
int argtoint( char *arg );

int main(int argc, char **argv)
{
	//basic error checking
	if(argc!=7)
	{
		printf("Usage: line size_x size_y x0 y0 x1 y1 ");
		return 1;
	}

	// initialize grid size
	int x_size = argtoint(argv[1]);
	int y_size = argtoint(argv[2]);

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

	// get coordinates for the line beginning and the line end
	int x0 = argtoint(argv[3]);
	int y0 = argtoint(argv[4]);
	int x1 = argtoint(argv[5]);
	int y1 = argtoint(argv[6]); 
	int dx = x1-x0;
	int dy = y1-y0;
	//error stuff is needed for the Bresenham's line algorithm
	float deltaerr = abs(dy/dx);
	float err = 0.0;
	int y = y0;

	//loop trough all the x-coordinates of the line and calculate the correct y-value
	//with the Bresenham's algorithm. Straight from wikipedia
	for(int x=x0;x<x1;x++)
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