#ifndef GREEDY_H
#define GREEDY_H

#include "../libraries/graph.h"

typedef struct GreedyPQ {
    Node *node;
    Node *parent;
    float h;
    struct GreedyPQ *next;
} GreedyPQ;

typedef struct GreedyExplored {
    Node *node;
    Node *parent;
    struct GreedyExplored *next;
} GreedyExplored;

void insertGreedyPQ(GreedyPQ **head, Node *node, Node *parent);
GreedyPQ *extractMinGreedy(GreedyPQ **head);
int isGreedyExplored(GreedyExplored *list, Node *node);
void addGreedyExplored(GreedyExplored **list, Node *node, Node *parent);
void printPathGreedy(GreedyExplored *list, Node *start, Node *goal);
void Greedy(Node *start, Node *goal);

#endif
