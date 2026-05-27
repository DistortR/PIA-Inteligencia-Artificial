#include <stdio.h>
#include <stdlib.h>
#include "../libraries/graph.h"
#include "../libraries/DFS.h"

// ─── Stack ────────────────────────────────────────────────────

void push(Stack **top, Node *node, Node *parent) {
    Stack *newItem = (Stack *)malloc(sizeof(Stack));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->next   = *top;
    *top = newItem;
}

Stack *pop(Stack **top) {
    if (*top == NULL) return NULL;
    Stack *item = *top;
    *top = (*top)->next;
    return item;
}

// ─── Lista de visitados ───────────────────────────────────────

int isVisitedDFS(Stack *list, Node *node) {
    Stack *current = list;
    while (current != NULL) {
        if (current->node == node) return 1;
        current = current->next;
    }
    return 0;
}

void addVisitedDFS(Stack **list, Node *node, Node *parent) {
    Stack *newItem = (Stack *)malloc(sizeof(Stack));
    newItem->node   = node;
    newItem->parent = parent;
    newItem->next   = *list;
    *list = newItem;
}

// ─── Reconstruir e imprimir camino ───────────────────────────

void printPathDFS(Stack *visited, Node *start, Node *goal) {
    Node *path[100];
    int length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;
        if (current == start) break;

        Stack *v = visited;
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

// ─── DFS principal ────────────────────────────────────────────

void DFS(Node *start, Node *goal) {
    if (start == NULL || goal == NULL) {
        printf("  [!] Nodo inicio o meta no valido.\n");
        return;
    }

    Stack *stack   = NULL;
    Stack *visited = NULL;

    push(&stack, start, NULL);

    printf("\n  Orden de visita: ");

    while (stack != NULL) {
        Stack *item   = pop(&stack);
        Node  *current = item->node;
        Node  *parent  = item->parent;
        free(item);

        // Si ya fue visitado, saltear
        if (isVisitedDFS(visited, current))
            continue;

        addVisitedDFS(&visited, current, parent);
        printf("[%s] ", current->name);

        if (current == goal) {
            printf("\n  Meta '%s' encontrada\n", goal->name);
            printPathDFS(visited, start, goal);

            // Liberar stack y visitados
            while (stack != NULL) { Stack *t = pop(&stack); free(t); }
            Stack *v = visited;
            while (v != NULL) { Stack *t = v; v = v->next; free(t); }
            return;
        }

        // Apilar hijos en orden inverso para explorar de izquierda a derecha
        Node *children[100];
        int count = 0;
        Child *child = current->children;
        while (child != NULL) {
            if (!isVisitedDFS(visited, child->node))
                children[count++] = child->node;
            child = child->next;
        }
        for (int i = count - 1; i >= 0; i--)
            push(&stack, children[i], current);
    }

    printf("\n  No se encontro camino de '%s' a '%s'.\n", start->name, goal->name);

    Stack *v = visited;
    while (v != NULL) { Stack *t = v; v = v->next; free(t); }
}