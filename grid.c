#include "stdio.h"
#include "stdlib.h"
#include "grid.h"
#include "assert.h"

// Takes a string filename and a pointer to an non-malloc'd grid pointer
Grid* readGrid(char* filename)
{
  FILE* f;
  char line[100];
  int nrows, ncols; //, xll, yll, cellsize;
  //float noData;

  f=fopen(filename, "r");
  if (f==NULL) {
    printf("No file with that name found\n");
    exit(1);
  }

  fscanf(f, "%s%d", line, &ncols);
  fscanf(f, "%s%d", line, &nrows);

  Grid* grid = malloc(sizeof(Grid));
  grid->rows = nrows/3;
  grid->cols = ncols/3;

  /* fscanf(f, "%s%d", line, &xll); */
  /* fscanf(f, "%s%d", line, &yll); */
  /* fscanf(f, "%s%d", line, &cellsize); */
  /* fscanf(f, "%s%f", line, &noData); */

  /* grid->xlowerLeft = xll; */
  /* grid->ylowerLeft = yll; */
  /* grid->cellsize = cellsize; */
  /* grid->noData = noData; */

  grid->data = malloc(nrows*sizeof(float*));
  assert(grid->data);

  int i = 0;
  while(i < nrows) {
    grid->data[i] = malloc(ncols*sizeof(float));
    assert(grid->data[i]);
    i++;
  }

  i = 0;
  int j = 0;

  while(i < grid->rows){
    while(j < grid->cols){
      float value = 0;
      int r, g, b;
      fscanf(f, "%d", &r);
      fscanf(f, "%d", &g);
      fscanf(f, "%d", &b);
      value = 0.2126*r + 0.7152*g + 0.0722*b;

      grid->data[i][j] = value;
      j++;
    }
    i++;
    j = 0;
  }

  fclose(f);
  printf("read in file\n");
  return grid;
 }

void writeGrid(char* filename, Grid* toWrite)
{
  FILE* f;

  f = fopen(filename, "w+");
  assert(f);

  fprintf(f, "ncols %d\n", toWrite->cols);
  fprintf(f, "nrows %d\n", toWrite->rows);
  fprintf(f, "xllcorner %d\n", toWrite->xlowerLeft);
  fprintf(f, "yllcorner %d\n", toWrite->ylowerLeft);
  fprintf(f, "cellsize %d\n", toWrite->cellsize);
  fprintf(f, "NODATA_value %f\n", toWrite->noData);

  int i = 0;
  int j = 0;
  while(i < toWrite->rows){
    while(j < toWrite->cols){
      fprintf(f, "%f ", toWrite->data[i][j]);
      j++;
    }
    fprintf(f, "\n");
    i++;
    j = 0;
  }

  fclose(f);
}

void freeGrid(Grid** grid)
{
  Grid* freeGrid = *grid;
  
  for(int i=0; i<freeGrid->rows; i++){
    free(freeGrid->data[i]);
  }
  free(freeGrid->data);
  free(freeGrid);
  *grid = NULL;
}

void printGrid(Grid* grid)
{
  int i = 0;
  int j = 0;

  while(i < grid->rows){
    while(j < grid->cols){
      printf("%f ", grid->data[i][j]);
      j++;
    }
    i++;
    j=0;
    printf("\n");
  }
}


void assertEquality(Grid* one, Grid* two)
{
  printf("%d %d\n", one->cols, two->cols);
  printf("%d %d\n", one->rows, two->rows);
  assert(one->cols == two->cols);
  assert(one->rows == two->rows);
  assert(one->xlowerLeft == two->xlowerLeft);
  assert(one->ylowerLeft == two->ylowerLeft);
  assert(one->cellsize == two->cellsize);
  assert(one->noData == two->noData);

  int y = 0;
  int x = 0;

  while(y < one->rows){
    while(x < one->cols){
      assert(one->data[y][x] == two->data[y][x]);
      x++;
    }
    y++;
    x=0;
  }
  printf("the grids are equivalent\n");
}
