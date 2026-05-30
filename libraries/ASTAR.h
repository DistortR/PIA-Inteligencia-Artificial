#ifndef ASTAR_H
#define ASTAR_H

#include "../libraries/graph.h"

typedef struct AStarPQ {
    Node *node;
    Node *parent;
    float g;
    float h;
    float f;
    struct AStarPQ *next;
} AStarPQ;

typedef struct AStarExplored {
    Node *node;
    Node *parent;
    float g;
    struct AStarExplored *next;
} AStarExplored;

void insertAStarPQ(AStarPQ **head, Node *node, Node *parent, float g);
AStarPQ *extractMinAStar(AStarPQ **head);
int isAStarExplored(AStarExplored *list, Node *node);
void addAStarExplored(AStarExplored **list, Node *node, Node *parent, float g);
void printPathAStar(AStarExplored *list, Node *start, Node *goal, float totalG);
void AStar(Node *start, Node *goal);

#endif
