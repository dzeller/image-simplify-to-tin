//File: simplification.c
//Authors: Croteau, Imhoff, Zeller
//Date: 11/09/14

#include "simplification.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


int triangleContains(Triangle* t, Vertex* point);

Triangle* makeTriangle(int row1, int col1, int val1,
		       int row2, int col2, int val2,
		       int row3, int col3, int val3)
{
  Triangle* t = malloc(sizeof(Triangle));
  t->t1 = NULL;
  t->t2 = NULL;
  t->t3 = NULL;
  t->visited = 0;
  t->points = makeQueue();

  Vertex* v1 = malloc(sizeof(Vertex));
  v1->row = row1;
  v1->col = col1;
  v1->value = val1;

  Vertex* v2 = malloc(sizeof(Vertex));
  v2->row = row2;
  v2->col = col2;
  v2->value = val2;

  Vertex* v3 = malloc(sizeof(Vertex));
  v3->row = row3;
  v3->col = col3;
  v3->value = val3;

  t->v1 = v1;
  t->v2 = v2;
  t->v3 = v3;

  return t;
}

Triangle* makeTriangleFromVertices(Vertex* v1, Vertex* v2, Vertex* v3)
{
  Triangle* t = malloc(sizeof(Triangle));
  t->t1 = NULL;
  t->t2 = NULL;
  t->t3 = NULL;
  t->visited = 0;
  t->points = makeQueue();

  t->v1 = v1;
  t->v2 = v2;
  t->v3 = v3;
  return t;
}

Vertex* makeVertex(Grid* g, int row, int col)
{
  Vertex* v = malloc(sizeof(Vertex));
  v->row = row;
  v->col = col;
  v->value = get(g, row, col);
  return v;
}

/* void initializeTriangle(Triangle *t, Grid* g, int row1, int col1, int row2, int col2, int row3, int col3) { */
/*     // First vertex */
/*     t.triangle.v1 = (Vertex *) malloc(sizeof(Vertex)); */
/*     t.triangle.v1.row = row1; */
/*     t.triangle.v1.col = col1; */
/*     t.triangle.v1.value = get(g, row1, col1); */
/*     set(g, row1, col1, g->NODATA_value); */
    
/*     // Second vertex */
/*     t.triangle.v2 = (Vertex *) malloc(sizeof(Vertex)); */
/*     t.triangle.v2.row = row2; */
/*     t.triangle.v2.col = col2; */
/*     t.triangle.v2.value = get(g, row2, col2); */
/*     set(g, row2, col2, g->NODATA_value); */
    
/*     // Third vertex */
/*     t.triangle.v3 = (Vertex *) malloc(sizeof(Vertex)); */
/*     t.triangle.v3.row = row3; */
/*     t.triangle.v3.col = col3; */
/*     t.triangle.v3.value = get(g, row3, col3); */
/*     set(g, row3, col3, g->NODATA_value); */
/* } */

/* double computeErrorInitialConfig(TIN* tin, Grid* g, int row, int col) { */
/*     Vertex v1; */
/*     v1.row = 0; */
/*     v1.col = 0; */
/*     v1.value = get(g, v1.row, v1.col); */

/*     Vertex v2; */
/*     if (row > col) { */
/*         v2.row = row - 1; */
/*         v2.col = 0; */
/*     } else { */
/*         v2.row = 0; */
/*         v2.col = col - 1; */
/*     } */
/*     v2.value = get(g, v2.row, v2.col); */

double linearlyInterpolate(Vertex* a, Vertex* b, Vertex* c, int row, int col) 
{
    double abx = b->col - a->col;
    double aby = b->row - a->row;
    double abz = b->value - a->value;

    double acx = c->col - a->col;
    double acy = c->row - a->row;
    double acz = c->value - a->value;

    double crossx = aby*acz - abz*acy;
    double crossy = abz*acx - abx*acz;
    double crossz = abx*acy - aby*acx;
    double d = -(crossx*a->col + crossy*a->row + crossz*a->value);

    return (-crossx*col - crossy*row - d) / crossz;
}

double calcError(Triangle* t, Vertex* v)
{
  Vertex* v1 = t->v1;
  Vertex* v2 = t->v2;
  Vertex* v3 = t->v3;

  double fromTin = linearlyInterpolate(v1, v2, v3, v->row, v->col);

  return abs(fromTin - v->value);
}

void splitTriangle(Triangle* t, Triangle** t1, Triangle** t2, Triangle** t3)
{
  Vertex* newVertex = removeTop(t->points);

  // The new *children* triangles
  Triangle* newT1 = makeTriangleFromVertices(t->v1, t->v2, newVertex);
  Triangle* newT2 = makeTriangleFromVertices(newVertex, t->v2, t->v3);
  Triangle* newT3 = makeTriangleFromVertices(t->v1, newVertex, t->v3);

  // links to outside triangles
  newT1->t1 = t->t1;
  newT2->t2 = t->t2;
  newT3->t3 = t->t3;

  // links to sibling triangles
  newT1->t2 = newT2;
  newT1->t3 = newT3;

  newT2->t1 = newT1;
  newT2->t3 = newT3;

  newT3->t1 = newT1;
  newT3->t2 = newT2;

  // Link outside triangles to new triangles
  if(t->t1 != NULL){
    t->t1->t1 = newT1;
  }
  if(t->t2 != NULL){
    t->t2->t2 = newT2;
  }
  if(t->t3 != NULL){
    t->t3->t3 = newT3;
  }

  // Want to loop throught all trianges in old triangle and
  // sort into appropriate new triangles
  Vertex* temp = removeTop(t->points);
  double error;

  while(temp != NULL){
    if(triangleContains(newT1, temp)){
      error = calcError(newT1, temp);
      addItem(newT1->points, error, temp);
      continue;
    }
    else if(triangleContains(newT2, temp)){
      error = calcError(newT2, temp);
      addItem(newT2->points, error, temp);
      continue;
    }
    else if(triangleContains(newT3, temp)){
      error = calcError(newT3, temp);
      addItem(newT3->points, error, temp);
      continue;
    }
    else{
      // If this is happening something is broken
      printf("Bad things happening...\n");
      assert(0);
    }
    temp = removeTop(t->points);
  }

  // Free the memory from old triangle that isn't useful anymore
  deleteQueue(t->points);
  // And then the actual triangle
  free(t);

  // Pass new triangles to calling function
  (*t1) = newT1;
  (*t2) = newT2;
  (*t3) = newT3;
}

void triangulate(Triangle* t, double epsilon)
{
  // No points within triangle..
  if(t->points->size == 0) return;

  Vertex* maxErrorPoint = t->points->array[0]->item;

  // TODO: we need an error function
  double error = calcError(t, maxErrorPoint);
  //all points within triangle are below epsilon
  if(error < epsilon) return;

  Triangle* t1;
  Triangle* t2;
  Triangle* t3;

  splitTriangle(t, &t1, &t2, &t3);

  triangulate(t1, epsilon);
  triangulate(t2, epsilon);
  triangulate(t3, epsilon);
}

void preTriangulate(Grid* g, double epsilon)
{
  Vertex* v1 = makeVertex(g, 0, 0);
  Vertex* v2 = makeVertex(g, g->rows - 1, 0);
  Vertex* v3 = makeVertex(g, 0, g->cols - 1);
  Vertex* v4 = makeVertex(g, g->rows - 1, g->cols - 1);

  Triangle* one = makeTriangleFromVertices(v1, v2, v4);
  Triangle* two = makeTriangleFromVertices(v1, v3, v4);

  one->t3 = two;
  two->t3 = one;

  one->points = makeQueue();
  two->points = makeQueue();

  Vertex* tempV;
  double tempE;

  for(int row=0; row < g->rows; row++){
    for(int col=0; col < g->cols; col++){
      // Ignore the four corner vertices. Ugly Ugly Ugly
      if((row==0 && col==0) ||
	 (row==0 && col==(g->cols-1)) ||
	 (row==(g->rows-1) && col==0) ||
	 (row==(g->rows-1) && col==(g->cols-1))){
	continue;
      }

      tempV = makeVertex(g, row, col);

      if(triangleContains(one, tempV)){
	tempE = calcError(one, tempV);
	addItem(one->points, tempE, (void*)tempV);
      }
      else if(triangleContains(two, tempV)){
	tempE = calcError(two, tempV);
	addItem(two->points, tempE, (void*)tempV);
      }
      else{
	printf("Bad things happening..\n");
	assert(0);
      }
    }
  }
  printf("Pretriangulation done\n");
  triangulate(one, epsilon);
  printf("Triangulated the first one\n");
  triangulate(two, epsilon);
}

// The main method
// TODO
int main(int argc, char** args)
{
    float epsilon = 0.0; //take from command line - TBU

    //TIN tin;
    Grid* imageGrid = readGrid("puppy.txt");

    preTriangulate(imageGrid, 50);
    //call simplification method
    //TIN imageTIN = simplify(&tin, &imageGrid, epsilon);

    //free memory blocks allocated for image grid
    freeGrid(&imageGrid);

    //done
    return 0;
}

float triangleArea(Vertex* v1, Vertex* v2, Vertex* v3)
{
  return abs(v1->col * (v2->row - v3->row) + v2->col * (v3->row - v1->row) +
	     v3->col * (v1->row - v2->row)) / 2.0;
}

int triangleContains(Triangle* t, Vertex* point)
{
  float triArea = triangleArea(t->v1, t->v2, t->v3);

  float areaWithPoint = (triangleArea(t->v1, t->v2, point) +
			 triangleArea(t->v2, t->v3, point) +
			 triangleArea(t->v3, t->v1, point));

  if(triArea == areaWithPoint){
    return 1;
  }

  return 0;
}
