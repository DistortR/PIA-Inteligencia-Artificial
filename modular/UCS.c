#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/UCS.h"

void insertPQ(PQNode **head, Node *node, Node *parent, float cost) {
    PQNode *newItem = (PQNode *)malloc(sizeof(PQNode));
    newItem->node = node;
    newItem->parent = parent;
    newItem->cost = cost;
    newItem->next = NULL;

    // Insertar en orden ascendente de costo
    if (*head == NULL || cost < (*head)->cost) {
        newItem->next = *head;
        *head = newItem;
        return;
    }

    PQNode *current = *head;
    while (current->next != NULL && current->next->cost <= cost)
        current = current->next;

    newItem->next = current->next;
    current->next = newItem;
}

PQNode *extractMin(PQNode **head) {
    if (*head == NULL) return NULL;
    PQNode *min = *head;
    *head = (*head)->next;
    return min;
}

// Lista de explorados
int isExplored(Explored *list, Node *node) {
    Explored *current = list;
    while (current != NULL) {
        if (current->node == node) return 1;
        current = current->next;
    }
    return 0;
}

void addExplored(Explored **list, Node *node, Node *parent, float cost) {
    Explored *newItem = (Explored *)malloc(sizeof(Explored));
    newItem->node = node;
    newItem->parent = parent;
    newItem->cost = cost;
    newItem->next = *list;
    *list = newItem;
}

// Reconstruir e imprimir camino 
void printPathUCS(Explored *list, Node *start, Node *goal, float totalCost) {
    Node *path[100];
    int length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;
        if (current == start)
            break;

        Explored *e = list;
        current = NULL;
        while (e != NULL) {
            if (e->node == path[length - 1]) {
                current = e->parent;
                break;
            }
            e = e->next;
        }
    }

    printf("\nCamino encontrado:\n  ");
    for (int i = length - 1; i >= 0; i--) {
        printf("[%s]", path[i]->name);
        if (i > 0)
            printf(" --> ");
    }
    printf("\nCosto total: %.1f\n", totalCost);
    printf("Pasos: %d\n", length - 1);
}

//
void UCS(Graph *g, Node *start, Node *goal) {
    if (start == NULL || goal == NULL) {
        printf("Nodo inicio o meta no valido.\n");
        return;
    }

    PQNode *pq = NULL;
    Explored *explored = NULL;

    insertPQ(&pq, start, NULL, 0.0);

    printf("\nOrden de expansion: ");

    while (pq != NULL) {
        PQNode *current = extractMin(&pq);
        Node *node = current->node;
        float cost = current->cost;
        Node *parent = current->parent;
        free(current);

        // Si ya fue explorado con menor costo, ignorar
        if (isExplored(explored, node))
            continue;

        addExplored(&explored, node, parent, cost);
        printf("[%s, g=%.1f] ", node->name, cost);

        // Meta encontrada
        if (node == goal) {
            printf("\nMeta '%s' encontrada\n", goal->name);
            printPathUCS(explored, start, goal, cost);

            // Liberar cola y explorados
            while (pq != NULL){
                PQNode *t = extractMin(&pq);
                free(t);
            }
            Explored *e = explored;
            while (e != NULL){
                Explored *t = e; e = e->next;
                free(t);
            }
            return;
        }

        // Expandir vecinos
        Child *child = node->children;
        while (child != NULL) {
            if (!isExplored(explored, child->node))
                insertPQ(&pq, child->node, node, cost + child->cost);
            child = child->next;
        }
    }

    printf("\nNo se encontro camino de '%s' a '%s'.\n", start->name, goal->name);

    Explored *e = explored;
    while (e != NULL) { Explored *t = e; e = e->next; free(t); }
}