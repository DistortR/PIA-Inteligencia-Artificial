#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/IDDFS.h"

void pushIDDFS(StackIDDFS **top, Node *node, Node *parent, int depth) {
    StackIDDFS *newItem = (StackIDDFS *)malloc(sizeof(StackIDDFS));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->depth  = depth;
    newItem->next   = *top;
    *top = newItem;
}

StackIDDFS *popIDDFS(StackIDDFS **top) {
    if (*top == NULL) return NULL;
    StackIDDFS *item = *top;
    *top = (*top)->next;
    return item;
}

int isVisitedIDDFS(StackIDDFS *list, Node *node) {
    StackIDDFS *current = list;
    while (current != NULL) {
        if (current->node == node) return 1;
        current = current->next;
    }
    return 0;
}

void addVisitedIDDFS(StackIDDFS **list, Node *node, Node *parent) {
    StackIDDFS *newItem = (StackIDDFS *)malloc(sizeof(StackIDDFS));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->depth  = 0;
    newItem->next   = *list;
    *list = newItem;
}

void printPathIDDFS(StackIDDFS *visited, Node *start, Node *goal) {
    Node *path[100];
    int length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;
        if (current == start) break;

        StackIDDFS *v = visited;
        current = NULL;
        while (v != NULL) {
            if (v->node == path[length - 1]) {
                current = v->parent;
                break;
            }
            v = v->next;
        }
    }

    printf("  Camino encontrado:\n  ");
    for (int i = length - 1; i >= 0; i--) {
        printf("[%s]", path[i]->name);
        if (i > 0) printf(" --> ");
    }
    printf("\n  Pasos: %d\n", length - 1);
}

//Iteracion DLS interna
// Retorna: 1 si encontro la meta, 0 si no encontro pero hay cutoff, -1 si no existe camino

int DLS_iteration(Node *start, Node *goal, int limit) {
    StackIDDFS *stack   = NULL;
    StackIDDFS *visited = NULL;
    int cutoff = 0;

    pushIDDFS(&stack, start, NULL, 0);

    printf("  [limite=%d] Visitados: ", limit);

    while (stack != NULL) {
        StackIDDFS *item    = popIDDFS(&stack);
        Node       *current = item->node;
        Node       *parent  = item->parent;
        int         depth   = item->depth;
        free(item);

        if (isVisitedIDDFS(visited, current))
            continue;

        addVisitedIDDFS(&visited, current, parent);
        printf("[%s] ", current->name);

        if (current == goal) {
            printf("\n  Meta '%s' encontrada!\n\n", goal->name);
            printPathIDDFS(visited, start, goal);

            while (stack != NULL) { StackIDDFS *t = popIDDFS(&stack); free(t); }
            StackIDDFS *v = visited;
            while (v != NULL) { StackIDDFS *t = v; v = v->next; free(t); }
            return 1;
        }

        if (depth >= limit) {
            cutoff = 1;
            continue;
        }

        Node *children[100];
        int count = 0;
        Child *child = current->children;
        while (child != NULL) {
            if (!isVisitedIDDFS(visited, child->node))
                children[count++] = child->node;
            child = child->next;
        }
        for (int i = count - 1; i >= 0; i--)
            pushIDDFS(&stack, children[i], current, depth + 1);
    }

    printf("\n");

    StackIDDFS *v = visited;
    while (v != NULL) { StackIDDFS *t = v; v = v->next; free(t); }

    return cutoff ? 0 : -1;
}

void IDDFS(Node *start, Node *goal, int maxDepth) {
    if (start == NULL || goal == NULL) {
        printf("  [!] Nodo inicio o meta no valido.\n");
        return;
    }

    printf("\n  Iniciando IDDFS desde '%s' hasta '%s'\n\n", start->name, goal->name);

    for (int limit = 0; limit <= maxDepth; limit++) {
        int result = DLS_iteration(start, goal, limit);

        if (result == 1)  return;           // encontrado
        if (result == -1) break;            // no existe camino
    }

    printf("  No se encontro camino dentro del limite maximo %d.\n", maxDepth);
}