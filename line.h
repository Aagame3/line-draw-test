#ifndef LINE_DOT_H
#define LINE_DOT_H
//basic struct of data every point has
struct pixels {
	
	int x_pos;
	int y_pos;
	int is_line;

};

// function prototypes
void init(int, int, int, int, int, int, struct pixels*);
void draw( int x_size, int y_size, struct pixels *pixel );
void plot( int x, int y, int x_size, int y_size, struct pixels *pixel );
int argtoint( char *arg );



#endif