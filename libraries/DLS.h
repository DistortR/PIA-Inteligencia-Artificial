#ifndef DLS_H
#define DLS_H
#include "../libraries/graph.h"

typedef struct StackDLS {
    Node *node;
    Node *parent;
    int depth;
    struct StackDLS *next;
} StackDLS;

void pushDLS(StackDLS **top, Node *node, Node *parent, int depth);
StackDLS *popDLS(StackDLS **top);
int isVisitedDLS(StackDLS *list, Node *node);
void addVisitedDLS(StackDLS **list, Node *node, Node *parent);
void printPathDLS(StackDLS *visited, Node *start, Node *goal);
void DLS(Node *start, Node *goal, int limit);

#endif