typedef struct grid_struct{
  int rows;
  int cols;
  int xlowerLeft;
  int ylowerLeft;
  int cellsize;
  float noData;
  float** data;
} Grid;


Grid* readGrid(char* filename);

void freeGrid(Grid** grid);

void printGrid(Grid* grid);

void writeGrid(char* filename, Grid* toWrite);

void assertEquality(Grid* one, Grid* two);
