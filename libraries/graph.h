#ifndef GRAPH_H
#define GRAPH_H

typedef struct Child {
    struct Node *node;
    float cost;
    struct Child *next;
} Child;

typedef struct Node {
    char name[50];
    float heuristic;
    Child *children;
    struct Node *next;
} Node;

typedef struct Graph {
    Node *head;
    int nodeCount;
} Graph;

void initGraph(Graph *g);
Node *addNode(Graph *g, char *name, float heuristic);
Node *findNode(Graph *g, char *name);
void addEdge(Graph *g, char *fromName, char *toName, float cost);
void printGraph(Graph *g);
void freeGraph(Graph *g);
void defineGraph(Graph *g);
void printGraphOptions();

#endif