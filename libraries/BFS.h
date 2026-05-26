#ifndef BFS_H
#define BFS_H
#include "../libraries/graph.h"
#include <stdbool.h>

typedef struct Queue {
    Node *node;
    struct Queue *next;
} Queue;

typedef struct Visited {
    Node *node;
    Node *parent;
    struct Visited *next;
} Visited;

void enqueue(Queue **head, Queue **tail, Node *node);
Node *dequeue(Queue **head, Queue **tail);
bool isVisited(Visited *list, Node *node);
void addVisited(Visited **list, Node *node, Node *parent);
void printPath(Visited *list, Node *start, Node *goal);
void BFS(Node *start, Node *goal);

#endif