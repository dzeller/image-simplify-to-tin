//File: simplification.h
//Authors: Croteau, Imhoff, Zeller
//Date: 11/09/14

#include "PriorityQueue.h"

typedef struct _grid {
    int rows, cols;
    int xllcorner, yllcorner, cellsize, NODATA_value;
    int** data;
} Grid;

// typedef struct _color {
//     int r, g, b;
// } Color;

typedef struct _vertex {
    int row, col, value;    // Value will eventually be of type Color
} Vertex;

// t1 shares edge v1-v2, t2 shares edge v2-v3, t3 shares edge v3-v1
typedef struct _triangle {
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;    // Vertices of triangle

    struct _triangle* t1;
    struct _triangle* t2;
    struct _triangle* t3;  // Adjacent triangles

   PriorityQueue* points;
    int visited;           // For drawing
} Triangle;

typedef struct _tin {
    Triangle* triangle;    // Any triangle in the TIN
} TIN;

// Sets grid element at (row, col) to value
void set(Grid* g, int row, int col, int value) { g->data[row][col] = value; }

// Gets rid element at (row, col)
int get(Grid* g, int row, int col) { return g->data[row][col]; }
