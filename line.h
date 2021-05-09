#ifndef LINE_DOT_H
#define LINE_DOT_H
#include <stdlib.h>
//basic struct of data every point has
struct pixels {
	
	int x_pos;
	int y_pos;
	int is_line;

};

// function prototypes
void init(int, int, int, int, int, int, struct pixels*);
void draw( int x_size, int y_size, struct pixels *pixel );
void plot( int x, int y, size_t len, struct pixels *pixel );
int argtoint( char *arg );
void drawline(int x_start, int y_start, int x_end, int y_end, size_t len, struct pixels* pixel);


#endif