#ifndef DFS_H
#define DFS_H
#include "../libraries/graph.h"

typedef struct Stack {
    Node *node;
    Node *parent;
    struct Stack *next;
} Stack;

void push(Stack **top, Node *node, Node *parent);
Stack *pop(Stack **top);
int isVisitedDFS(Stack *list, Node *node);
void addVisitedDFS(Stack **list, Node *node, Node *parent);
void printPathDFS(Stack *visited, Node *start, Node *goal);
void DFS(Node *start, Node *goal);

#endif