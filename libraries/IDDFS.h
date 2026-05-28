#ifndef IDDFS_H
#define IDDFS_H
#include "../libraries/graph.h"

typedef struct StackIDDFS {
    Node *node;
    Node *parent;
    int depth;
    struct StackIDDFS *next;
} StackIDDFS;

void pushIDDFS(StackIDDFS **top, Node *node, Node *parent, int depth);
StackIDDFS *popIDDFS(StackIDDFS **top);
int isVisitedIDDFS(StackIDDFS *list, Node *node);
void addVisitedIDDFS(StackIDDFS **list, Node *node, Node *parent);
void printPathIDDFS(StackIDDFS *visited, Node *start, Node *goal);
int DLS_iteration(Node *start, Node *goal, int limit);
void IDDFS(Node *start, Node *goal, int maxDepth);

#endif