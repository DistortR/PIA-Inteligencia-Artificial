#ifndef UCS_H
#define UCS_H
#include "../libraries/graph.h"

typedef struct PQNode {
    Node *node;
    Node *parent;
    float cost;
    struct PQNode *next;
} PQNode;

typedef struct Explored {
    Node *node;
    Node *parent;
    float cost;
    struct Explored *next;
} Explored;

void insertPQ(PQNode **head, Node *node, Node *parent, float cost);
PQNode *extractMin(PQNode **head);
int isExplored(Explored *list, Node *node);
void addExplored(Explored **list, Node *node, Node *parent, float cost);
void printPathUCS(Explored *list, Node *start, Node *goal, float totalCost);
void UCS(Graph *g, Node *start, Node *goal);

#endif