#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/DLS.h"

void pushDLS(StackDLS **top, Node *node, Node *parent, int depth) {
    StackDLS *newItem = (StackDLS *)malloc(sizeof(StackDLS));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->depth  = depth;
    newItem->next   = *top;
    *top = newItem;
}

StackDLS *popDLS(StackDLS **top) {
    if (*top == NULL) return NULL;
    StackDLS *item = *top;
    *top = (*top)->next;
    return item;
}

int isVisitedDLS(StackDLS *list, Node *node) {
    StackDLS *current = list;
    while (current != NULL) {
        if (current->node == node) return 1;
        current = current->next;
    }
    return 0;
}

void addVisitedDLS(StackDLS **list, Node *node, Node *parent) {
    StackDLS *newItem = (StackDLS *)malloc(sizeof(StackDLS));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->depth  = 0;
    newItem->next   = *list;
    *list = newItem;
}

void printPathDLS(StackDLS *visited, Node *start, Node *goal) {
    Node *path[100];
    int length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;
        if (current == start) break;

        StackDLS *v = visited;
        current = NULL;
        while (v != NULL) {
            if (v->node == path[length - 1]) {
                current = v->parent;
                break;
            }
            v = v->next;
        }
    }

    printf("\n  Camino encontrado:\n  ");
    for (int i = length - 1; i >= 0; i--) {
        printf("[%s]", path[i]->name);
        if (i > 0) printf(" --> ");
    }
    printf("\n  Pasos: %d\n", length - 1);
}

void DLS(Node *start, Node *goal, int limit) {
    if (start == NULL || goal == NULL) {
        printf("  [!] Nodo inicio o meta no valido.\n");
        return;
    }

    StackDLS *stack   = NULL;
    StackDLS *visited = NULL;
    int cutoff = 0; // hubo alguna rama cortada por el limite?

    pushDLS(&stack, start, NULL, 0);

    printf("\n  Limite de profundidad: %d\n", limit);
    printf("  Orden de visita: ");

    while (stack != NULL) {
        StackDLS *item    = popDLS(&stack);
        Node     *current = item->node;
        Node     *parent  = item->parent;
        int       depth   = item->depth;
        free(item);

        if (isVisitedDLS(visited, current))
            continue;

        addVisitedDLS(&visited, current, parent);
        printf("[%s](d=%d) ", current->name, depth);

        if (current == goal) {
            printf("\n  Meta '%s' encontrada en profundidad %d\n", goal->name, depth);
            printPathDLS(visited, start, goal);

            while (stack != NULL) { StackDLS *t = popDLS(&stack); free(t); }
            StackDLS *v = visited;
            while (v != NULL) { StackDLS *t = v; v = v->next; free(t); }
            return;
        }

        if (depth >= limit) {
            cutoff = 1;
            continue; // rama cortada, no expandir hijos
        }

        // Apilar hijos en orden inverso
        Node *children[100];
        int count = 0;
        Child *child = current->children;
        while (child != NULL) {
            if (!isVisitedDLS(visited, child->node))
                children[count++] = child->node;
            child = child->next;
        }
        for (int i = count - 1; i >= 0; i--)
            pushDLS(&stack, children[i], current, depth + 1);
    }

    if (cutoff)
        printf("\n  No se encontro camino dentro del limite %d (hay ramas cortadas).\n", limit);
    else
        printf("\n  No existe camino de '%s' a '%s'.\n", start->name, goal->name);

    StackDLS *v = visited;
    while (v != NULL) { StackDLS *t = v; v = v->next; free(t); }
}