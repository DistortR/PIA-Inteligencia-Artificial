#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/GREEDY.h"

void insertGreedyPQ(GreedyPQ **head, Node *node, Node *parent) {
    GreedyPQ *newItem = (GreedyPQ *)malloc(sizeof(GreedyPQ));
    newItem->node = node;
    newItem->parent = parent;
    newItem->h = node->heuristic;
    newItem->next = NULL;

    if (*head == NULL || node->heuristic < (*head)->h) {
        newItem->next = *head;
        *head = newItem;
        return;
    }

    GreedyPQ *current = *head;
    while (current->next != NULL && current->next->h <= node->heuristic)
        current = current->next;

    newItem->next  = current->next;
    current->next  = newItem;
}

GreedyPQ *extractMinGreedy(GreedyPQ **head) {
    if (*head == NULL)
        return NULL;
    GreedyPQ *min = *head;
    *head = (*head)->next;
    return min;
}

int isGreedyExplored(GreedyExplored *list, Node *node) {
    GreedyExplored *current = list;
    while (current != NULL) {
        if (current->node == node)
            return 1;
        current = current->next;
    }
    return 0;
}

void addGreedyExplored(GreedyExplored **list, Node *node, Node *parent) {
    GreedyExplored *newItem = (GreedyExplored *)malloc(sizeof(GreedyExplored));
    newItem->node = node;
    newItem->parent = parent;
    newItem->next = *list;
    *list = newItem;
}

void printPathGreedy(GreedyExplored *list, Node *start, Node *goal) {
    Node *path[100], *current = goal;
    int   length = 0;

    while (current != NULL) {
        path[length++] = current;
        if (current == start)
            break;

        GreedyExplored *e = list;
        current = NULL;
        while (e != NULL) {
            if (e->node == path[length - 1]) {
                current = e->parent;
                break;
            }
            e = e->next;
        }
    }

    printf("\nCamino encontrado:\n");
    for (int i = length - 1; i >= 0; i--) {
        printf("[%s](h=%.1f)", path[i]->name, path[i]->heuristic);
        if (i > 0)
            printf(" --> ");
    }
    printf("\nPasos: %d\n", length - 1);
}

// ─── Greedy principal ────────────────────────────────────────

void Greedy(Graph *g, Node *start, Node *goal) {
    if (start == NULL || goal == NULL) {
        printf("[!] Nodo inicio o meta no valido.\n");
        return;
    }

    GreedyPQ *pq = NULL;
    GreedyExplored *explored = NULL;

    insertGreedyPQ(&pq, start, NULL);

    printf("\nOrden de expansion (por h(n)): ");

    while (pq != NULL) {
        GreedyPQ *current = extractMinGreedy(&pq);
        Node *node = current->node;
        Node *parent = current->parent;
        free(current);

        if (isGreedyExplored(explored, node))
            continue;

        addGreedyExplored(&explored, node, parent);
        printf("[%s, h=%.1f] ", node->name, node->heuristic);

        if (node == goal) {
            printf("\nMeta '%s' encontrada!\n", goal->name);
            printPathGreedy(explored, start, goal);

            while (pq != NULL) {
                GreedyPQ *t = extractMinGreedy(&pq);
                free(t);
            }
            GreedyExplored *e = explored;
            while (e != NULL) {
                GreedyExplored *t = e;
                e = e->next;
                free(t);
            }
            return;
        }

        Child *child = node->children;
        while (child != NULL) {
            if (!isGreedyExplored(explored, child->node))
                insertGreedyPQ(&pq, child->node, node);
            child = child->next;
        }
    }

    printf("\n[!] No se encontro camino de '%s' a '%s'.\n", start->name, goal->name);
    GreedyExplored *e = explored;
    while (e != NULL) {
        GreedyExplored *t = e;
        e = e->next;
        free(t);
    }
}
