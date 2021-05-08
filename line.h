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

// initialize grid size
int x_size, y_size, x_start, x_end, y_start, y_end;