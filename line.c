#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

struct pixels {
	int x_pos;
	int y_pos;
	int is_line;

};
int height = 25;
int width = 25;

void draw( int x_size, int y_size, struct pixels *pixel );
void plot( int x, int y, int x_size, int y_size, struct pixels *pixel );
int argtoint( char *arg );

int main(int argc, char **argv)
{
	if(argc!=7)
	{
		printf("Usage: line size_x size_y x0 y0 x1 y1 ");
		return 1;
	}

	int x_size = argtoint(argv[1]);
	int y_size = argtoint(argv[2]);

	struct pixels pixel[x_size*y_size];

	int offset = 0;
	for(int i=0;i<y_size;i++)
	{
		for(int j=0;j<y_size;j++)
		{
		//	printf("%d %d %d\n", i, j, offset);
			pixel[offset].y_pos = i;
			pixel[offset].x_pos = j;
		//	printf("%d    %d ", i, pixels[offset].y_pos);
			offset++;
		}
	}

	int x0 = argtoint(argv[3]);
	int y0 = argtoint(argv[4]);
	int x1 = argtoint(argv[5]);
	int y1 = argtoint(argv[6]);
	int dx = x1-x0;
	int dy = y1-y0;

	for(int i=0;i<(x_size*y_size);i++)
	{
		pixel[i].is_line = 0;
	}
	for(int x=x0;x<x1;x++)
	{
		int y = y1 + dy * (x-x1) / dx;
		//printf("(%d, %d)\n", x, y);
		plot(x, y, x_size, y_size, pixel);
	}
	draw( x_size, y_size, pixel );
	return 0;
}

void draw(int x_size, int y_size, struct pixels *pixel)
{
	for(int i=0;i<(x_size*y_size);i++)
	{
		if(pixel[i].is_line == 0)
		{
			if(pixel[i].x_pos == width-1)
			{
				printf(" .\n");
			}else {
				printf(" . ");
			}
		}else {
			if(pixel[i].x_pos == width-1)
			{
				printf(" *\n");
			}else {
				printf(" * ");
			}
		}
	}
}

void plot(int x, int y, int x_size, int y_size, struct pixels *pixel)
{
	for(int i=0;i<(x_size*y_size);i++)
	{
		if(pixel[i].x_pos == x && pixel[i].y_pos == y)
		{
			//printf("(%d %d)\n", pixel[i].x_pos, pixel[i].y_pos);
			pixel[i].is_line=1;
		}
	}
}

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