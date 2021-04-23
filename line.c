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

int draw( struct pixels *pixel );

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
	for(int i=0;i<625;i++)
	{
		pixel[i].is_line = 0;
	}
	return draw( pixel );
}

int draw(struct pixels *pixel)
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
		}
	}
	return 0;
}