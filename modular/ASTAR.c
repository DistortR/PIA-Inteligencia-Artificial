#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/ASTAR.h"

void insertAStarPQ(AStarPQ **head, Node *node, Node *parent, float g) {
    AStarPQ *newItem = (AStarPQ *)malloc(sizeof(AStarPQ));
    newItem->node = node;
    newItem->parent = parent;
    newItem->g = g;
    newItem->h = node->heuristic;
    newItem->f = g + node->heuristic;
    newItem->next = NULL;

    if (*head == NULL || newItem->f < (*head)->f) {
        newItem->next = *head;
        *head = newItem;
        return;
    }

    AStarPQ *current = *head;
    while (current->next != NULL && current->next->f <= newItem->f)
        current = current->next;

    newItem->next = current->next;
    current->next = newItem;
}

AStarPQ *extractMinAStar(AStarPQ **head) {
    if (*head == NULL)
        return NULL;
    AStarPQ *min = *head;
    *head = (*head)->next;
    return min;
}

int isAStarExplored(AStarExplored *list, Node *node) {
    AStarExplored *current = list;
    while (current != NULL) {
        if (current->node == node)
            return 1;
        current = current->next;
    }
    return 0;
}

void addAStarExplored(AStarExplored **list, Node *node, Node *parent, float g) {
    AStarExplored *newItem = (AStarExplored *)malloc(sizeof(AStarExplored));
    newItem->node = node;
    newItem->parent = parent;
    newItem->g = g;
    newItem->next = *list;
    *list = newItem;
}

void printPathAStar(AStarExplored *list, Node *start, Node *goal, float totalG) {
    Node *path[100];
    int   length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;
        if (current == start) break;

        AStarExplored *e = list;
        current          = NULL;
        while (e != NULL) {
            if (e->node == path[length - 1]) {
                current = e->parent;
                break;
            }
            e = e->next;
        }
    }

    printf("\n  Camino encontrado:\n  ");
    for (int i = length - 1; i >= 0; i--) {
        printf("[%s]", path[i]->name);
        if (i > 0) printf(" --> ");
    }

    printf("\n\n  Detalle del camino:\n");
    for (int i = length - 1; i >= 0; i--) {
        AStarExplored *e = list;
        float g = 0.0;
        while (e != NULL) {
            if (e->node == path[i]) { g = e->g; break; }
            e = e->next;
        }
        printf("  [%s] g=%.1f  h=%.1f  f=%.1f\n",
            path[i]->name, g, path[i]->heuristic, g + path[i]->heuristic);
    }
    printf("\n  Costo real total (g): %.1f\n", totalG);
    printf("  Pasos: %d\n", length - 1);
}

void AStar(Node *start, Node *goal) {
    if (start == NULL || goal == NULL) {
        printf("[!] Nodo inicio o meta no valido.\n");
        return;
    }

    AStarPQ *pq = NULL;
    AStarExplored *explored = NULL;

    insertAStarPQ(&pq, start, NULL, 0.0);

    printf("\nOrden de expansion (por f=g+h): ");

    while (pq != NULL) {
        AStarPQ *current = extractMinAStar(&pq);
        Node *node    = current->node;
        Node *parent  = current->parent;
        float g = current->g;
        free(current);

        if (isAStarExplored(explored, node))
            continue;

        addAStarExplored(&explored, node, parent, g);
        printf("[%s, f=%.1f] ", node->name, g + node->heuristic);

        if (node == goal) {
            printf("\nMeta '%s' encontrada!\n", goal->name);
            printPathAStar(explored, start, goal, g);

            while (pq != NULL) {
                AStarPQ *t = extractMinAStar(&pq);
                free(t);
            }
            AStarExplored *e = explored;
            while (e != NULL) {
                AStarExplored *t = e;
                e = e->next;
                free(t);
            }
            return;
        }

        Child *child = node->children;
        while (child != NULL) {
            if (!isAStarExplored(explored, child->node))
                insertAStarPQ(&pq, child->node, node, g + child->cost);
            child = child->next;
        }
    }

    printf("\n[!] No se encontro camino de '%s' a '%s'.\n", start->name, goal->name);
    AStarExplored *e = explored;
    while (e != NULL) {
        AStarExplored *t = e;
        e = e->next;
        free(t);
    }
}
