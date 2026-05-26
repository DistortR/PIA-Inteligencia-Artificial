#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/graph.h"

void initGraph(Graph *g) {
    g->head = NULL;
    g->nodeCount = 0;
}

Node *addNode(Graph *g, char *name, float heuristic) {

    if (findNode(g, name) != NULL) {
        printf("El nodo '%s' ya existe.\n", name);
        return NULL;
    }

    // Crear el nodo en memoria dinámica
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->heuristic = heuristic;
    newNode->children = NULL;
    newNode->next = NULL;

    if (g->head == NULL) {
        g->head = newNode;
    } else {
        Node *actual = g->head;
        while (actual->next != NULL)
            actual = actual->next;
        actual->next = newNode;
    }

    g->nodeCount++;
    return newNode;
}

Node *findNode(Graph *g, char *name) {
    Node *actual = g->head;
    while (actual != NULL) {
        if (strcmp(actual->name, name) == 0)
            return actual;
        actual = actual->next;
    }
    return NULL;
}

void addEdge(Graph *g, char *fromName, char *toName, float cost) {

    Node *from = findNode(g, fromName);
    Node *to = findNode(g, toName);

    if (from == NULL){
        printf("  [!] Nodo origen '%s' no existe.\n", fromName);
        return;
    }
    if (to == NULL){
        printf("  [!] Nodo destino '%s' no existe.\n", toName);
        return;
    }

    Child *newChild = (Child*)malloc(sizeof(Child));
    newChild->node = to;
    newChild->cost = cost;
    newChild->next = NULL;

    if (from->children == NULL) {
        from->children = newChild;
    } else {
        Child *actual = from->children;
        while (actual->next != NULL)
            actual = actual->next;
        actual->next = newChild;
    }
}

void printGraph(Graph *g) {
    if (g->head == NULL){
        printf("El grafo esta vacio.\n");
        return;
    }

    printf("\n========== GRAFO ACTUAL ==========\n");

    Node *node = g->head;
    while (node != NULL) {
        printf("\n  [%s] (h=%.1f)\n", node->name, node->heuristic);

        if (node->children == NULL){
            printf("    └── (sin hijos)\n");
        } else{
            Child* child = node->children;
            while (child != NULL) {
                printf("    %s── costo(%.1f) ──→ [%s]\n", child->next ? "├" : "└", child->cost, child->node->name);
                child = child->next;
            }
        }
        node = node->next;
    }
    printf("\n  Total de nodos: %d\n", g->nodeCount);
}

void freeGraph(Graph *g) {
    Node *node = g->head;
    while (node != NULL) {
        Child* child = node->children;
        while (child != NULL) {
            Child* tempChild = child;
            child = child->next;
            free(tempChild);
        }
        Node *tempNode = node;
        node = node->next;
        free(tempNode);
    }
    g->head = NULL;
    g->nodeCount = 0;
}

void defineGraph(Graph *g) {
    char name[50], fromName[50], toName[50];
    float heuristic, cost;
    int subOption, c;

    if (g->head != NULL) {
        printf("\nYa existe un grafo. ¿Desea reemplazarlo? (1=Si / 0=No) $");
        scanf("%d", &subOption);
        while ((c = getchar()) != '\n' && c != EOF);
        if (subOption != 1)
            return;
        freeGraph(g);
    }

    printf("\n-------- AGREGAR NODOS --------\n");
    printf("(Escribe 'esc' como nombre para terminar)\n\n");

    while (1) {
        printf("Nombre del nodo $");
        scanf("%s", name);
        if (strcmp(name, "esc") == 0)
            break;
        
        printf("Heuristica h(%s) $", name);
        scanf("%f", &heuristic);

        addNode(g, name, heuristic);
        printf("Nodo '%s' agregado\n\n", name);
    }

    if (g->nodeCount == 0) {
        printf("  No se agregaron nodos.\n");
        return;
    }

    printf("\n-------- AGREGAR ARISTAS --------\n");
    printf("(Escribe 'esc' para finalizar el proceso)\n\n");

    while (1) {
        printf("Nodo origen $");
        scanf("%s", fromName);
        if (strcmp(fromName, "esc") == 0)
            break;

        printf("Nodo destino $");
        scanf("%s", toName);

        printf("Costo $");
        scanf("%f", &cost);

        addEdge(g, fromName, toName, cost);
        printf("Arista '%s' -> '%s' (costo %.1f) agregada.\n\n", fromName, toName, cost);
    }

    printGraph(g);
}