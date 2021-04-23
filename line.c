#include <stdlib.h>
#include <stdio.h>
#include <math.h>



struct pixels {
	int x_pos;
	int y_pos;
	int is_line;

};
int height = 25;
int width = 25;

void draw( struct pixels *pixel );
void plot(int x, int y, struct pixels *pixel);

int main()
{
	struct pixels pixel[25*25];

	int offset = 0;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<height;j++)
		{
		//	printf("%d %d %d\n", i, j, offset);
			pixel[offset].y_pos = i;
			pixel[offset].x_pos = j;
		//	printf("%d    %d ", i, pixels[offset].y_pos);
			offset++;
		}
	}
/* 	offset=0;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<height;j++)
		{
		//	printf("%d ", i);
			
			offset++;
		}
	} */
	int x0 = 2;
	int y0 = 5;
	int x1 = 20;
	int y1 = 15;
	int dx = x1-x0;
	int dy = y1-y0;

	for(int i=0;i<625;i++)
	{
		pixel[i].is_line = 0;
	}
	for(int x=x0;x<x1;x++)
	{
		int y = y1 + dy * (x-x1) / dx;
		printf("(%d, %d)\n", x, y);
		plot(x, y, pixel);
	}
	draw( pixel );
	return 0;
}

void draw(struct pixels *pixel)
{
	for(int i=0;i<625;i++)
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

void plot(int x, int y, struct pixels *pixel)
{
	for(int i=0;i<625;i++)
	{
		if(pixel[i].x_pos == x && pixel[i].y_pos == y)
		{
			printf("(%d %d)\n", pixel[i].x_pos, pixel[i].y_pos);
			pixel[i].is_line=1;
		}
	}
}