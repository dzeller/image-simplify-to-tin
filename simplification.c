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

// TODO
double linearlyInterpolate(Vertex* v1, Vertex* v2, Vertex* v3, int row, int col) {
  return 0.0;
}

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

/*     Vertex v3; */
/*     v3.row = row - 1; */
/*     v3.col = col - 1; */
/*     v3.value = get(g, v3.row, v3.col); */

/*     double fromTin = linearlyInterpolate(&v1, &v2, &v3, row, col); */
/*     return abs(fromTin - (double)get(g, row, col)); */
/* } */

/* TIN* simplify(TIN* tin, Grid* g, double epsilon) { */
/*     // Initialize TIN with 4 corner points */
/*     Triangle* bottomLeft = (Triangle *) malloc(sizeof(Triangle)); */
/*     initializeTriangle(bottomLeft, g, 0, 0, g.rows - 1, 0, g.rows - 1, g.cols - 1); */

/*     Triangle* topRight = (Triangle *) malloc(sizeof(Triangle)); */
/*     initializeTriangle(topRight, g, 0, 0, 0, g.cols - 1, g.rows - 1, g.cols - 1); */

/*     bottomLeft->t1 = topRight; */
/*     bottomLeft->t2 = NULL: */
/*     bottomLeft->t3 = NULL: */

/*     topRight->t1 = bottomLeft; */
/*     topRight->t2 = NULL: */
/*     topRight->t2 = NULL: */

/*     tin->triangle = upperLeft; */

/*     // Priority queue for storing points and errors */
/*     PriorityQueue* q = makeQueue(); */
    
/*     // Compute errors of all remaining grid points */
/*     for (row = 0; row < g->rows; row++) { */
/*         for (col = 0; col < g->cols; col++) { */
/*             if (get(g, row, col) != g->NODATA_value) { */
/*                 Vertex v = (Vertex *) malloc(sizeof(Vertex)); */
/*                 v->row = row; */
/*                 v->col = col; */
/*                 v->value = g->values[row][col]; */

/*                 int error = computeErrorInitialConfig(tin, g, row, col); */
/*                 Node* n = makeNode(error, (void *)v); */
/*                 insert(q, n); */
/*             } */
/*         } */
/*     } */
    
/*     Node* maxErrorNode = removeTop(p); */
/*     while (maxErrorNode->priority > epsilon) { */
/*         // Find point with largest error */
/*         Vertex* maxErrorVertex = (Vertex *)maxErrorNode->item; */

/*         // Add largest error point to TIN */
/*         // TODO implement findTriangleContainingVertex */
/*         // TODO when will seg faults happen? */
/*         // TODO double check the logic */
/*         Triangle* containsLargestErrorVertex = findTriangleContainingVertex(&tin, largestErrorVertex); */
/*         // TODO doesn't need to loop thru TIN */

/*         Triangle* newT1 = (Triangle *) malloc(sizeof(Triangle)); */
/*         Triangle* newT2 = (Triangle *) malloc(sizeof(Triangle)); */
/*         Triangle* newT3 = (Triangle *) malloc(sizeof(Triangle)); */

/*         // Initialize newT1 */
/*         newT1->v1 = maxErrorVertex; */
/*         newT1->v2 = containsLargestErrorVertex->v1; */
/*         newT1->v3 = containsLargestErrorVertex->v2; */

/*         containsLargestErrorVertex->t1->t1 = newT1; // TODO check assumption that t->t1->t1 == t  */
/*         newT1->t1 = containsLargestErrorVertex->t1; */
/*         newT1->t2 = newT2; */
/*         newT1->t3 = newT3; */

/*         // Initialize newT2 */
/*         newT2->v1 = maxErrorVertex; */
/*         newT2->v2 = containsLargestErrorVertex->v2; */
/*         newT2->v3 = containsLargestErrorVertex->v3; */

/*         containsLargestErrorVertex->t2->t2 = newT2; */
/*         newT2->t1 = newT1; */
/*         newT2->t2 = containsLargestErrorVertex->t2; */
/*         newT2->t3 = newT3; */

/*         // Initialize newT3 */
/*         newT3->v1 = maxErrorVertex; */
/*         newT3->v2 = containsLargestErrorVertex->v1; */
/*         newT3->v3 = containsLargestErrorVertex->v3; */

/*         containsLargestErrorVertex->t3->t3 = newT3; */
/*         newT3->t1 = newT1; */
/*         newT3->t2 = newT2; */
/*         newT3->t3 = containsLargestErrorVertex->t3; */

/*         tin->triangle = newT1; */
/*         free(containsLargestErrorVertex); */

/*         // Compute errors of all points whose errors have changed */
/*         // TODO */

/*         // Set maxError to the error of the vertex with highest error in q */
/*         maxErrorNode = removeTop(p); */
/*     } */
    
/*     return tin; */
/* } */

void splitTriangle(Triangle* t, Triangle** t1, Triangle** t2, Triangle** t3)
{
  Vertex* newVertex = removeTop(t->points);

  Triangle* newT1 = makeTriangleFromVertices(t->v1, t->v2, newVertex);
  Triangle* newT2 = makeTriangleFromVertices(newVertex, t->v2, t->v3);
  Triangle* newT3 = makeTriangleFromVertices(t->v1, newVertex, t->v3);

  // sets outside triangles
  newT1->t1 = t->t1;
  newT2->t2 = t->t2;
  newT3->t3 = t->t3;

  // sibling triangles
  newT1->t2 = newT2;
  newT1->t3 = newT3;

  newT2->t1 = newT1;
  newT2->t3 = newT3;

  newT3->t1 = newT1;
  newT3->t2 = newT2;

  // Setting outside triangles
  if(t->t1 != NULL){
    t->t1->t1 = newT1;
  }
  if(t->t2 != NULL){
    t->t2->t2 = newT2;
  }
  if(t->t3 != NULL){
    t->t3->t3 = newT3;
  }

  Vertex* temp = removeTop(t->points);
  int error = 0;

  while(temp != NULL){
    if(triangleContains(newT1, temp)){
      addItem(newT1->points, error, temp);
      continue;
    }
    else if(triangleContains(newT2, temp)){
      addItem(newT2->points, error, temp);
      continue;
    }
    else if(triangleContains(newT3, temp)){
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

  deleteQueue(t->points);
  free(t);

  (*t1) = newT1;
  (*t2) = newT2;
  (*t3) = newT3;
}

void triangulate(Triangle* t, double epsilon)
{
  // No points within triangle..
  if(t->points->size == 0) return;

  //Vertex* maxErrorPoint = t->points->array[0]->item;

  // TODO: we need an error function
  double error = 0;
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

// The main method
// TODO
int main(int argc, char** args) {
    
    //float epsilon = 0.0; //take from command line - TBU
    
    //TIN tin;
    Grid imageGrid;
    
    //allocate blocks of memory for image data
    imageGrid.data = (int**) malloc(imageGrid.rows * sizeof(int*));
    if (imageGrid.data == NULL) {
        printf("Could not allocate array.");
        exit(1);
    }
    for (int i = 0; i < imageGrid.rows; i++) {
        imageGrid.data[i] = (int*) malloc(imageGrid.cols * sizeof(int));
        if (imageGrid.data[i] == NULL) {
            printf("Could not allocate array.");
            exit(1);
        }
    }
    
    //call simplification method
    //TIN imageTIN = simplify(&tin, &imageGrid, epsilon);
    
    //free memory blocks allocated for image grid
    for (int i = 0; i < imageGrid.rows; i++)
        free(imageGrid.data[i]);
    free(imageGrid.data);
    
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
