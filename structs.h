#pragma once

typedef struct node_ {
    double priority;
    void* item;
} Node;

typedef struct pQueue_ {
    Node** array;
    int arraySize;

    int size;
} PriorityQueue;

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
