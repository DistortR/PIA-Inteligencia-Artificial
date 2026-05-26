#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libraries/graph.h"
#include "../libraries/BFS.h"

// ─── Cola ────────────────────────────────────────────────────

void enqueue(Queue **head, Queue **tail, Node *node) {
    Queue *newItem = (Queue *)malloc(sizeof(Queue));
    newItem->node = node;
    newItem->next = NULL;

    if (*tail == NULL) {
        *head = *tail = newItem;
    } else {
        (*tail)->next = newItem;
        *tail = newItem;
    }
}

Node *dequeue(Queue **head, Queue **tail) {
    if (*head == NULL) return NULL;

    Queue *temp = *head;
    Node  *node = temp->node;
    *head = (*head)->next;

    if (*head == NULL)
        *tail = NULL;

    free(temp);
    return node;
}

bool isVisited(Visited *list, Node *node) {
    Visited *current = list;
    while (current != NULL) {
        if (current->node == node)
            return true;
        current = current->next;
    }
    return false;
}

void addVisited(Visited **list, Node *node, Node *parent) {
    Visited *newItem = (Visited *)malloc(sizeof(Visited));
    newItem->node = node;
    newItem->parent = parent;
    newItem->next = *list;
    *list = newItem;
}

void printPath(Visited *list, Node *start, Node *goal) {
    Node *path[100];
    int   length = 0;

    Node *current = goal;
    while (current != NULL) {
        path[length++] = current;

        if (current == start) break;

        Visited *v = list;
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

void BFS(Node *start, Node *goal) {
    if (start == NULL || goal == NULL) {
        printf("  [!] Nodo inicio o meta no valido.\n");
        return;
    }

    Queue *qHead = NULL;
    Queue *qTail = NULL;
    Visited *visited = NULL;

    enqueue(&qHead, &qTail, start);
    addVisited(&visited, start, NULL);

    printf("\n  Orden de visita: ");

    while (qHead != NULL) {
        Node *current = dequeue(&qHead, &qTail);
        printf("[%s] ", current->name);

        if (current == goal) {
            printf("\n  Meta '%s' encontrada\n", goal->name);
            printPath(visited, start, goal);

            while (qHead != NULL) 
                dequeue(&qHead, &qTail);
            Visited *v = visited;
            while (v != NULL){
                Visited *t = v; v = v->next;
                free(t);
            }
            return;
        }

        Child *child = current->children;
        while (child != NULL) {
            if (!isVisited(visited, child->node)) {
                enqueue(&qHead, &qTail, child->node);
                addVisited(&visited, child->node, current);
            }
            child = child->next;
        }
    }

    printf("\nNo se encontro camino de '%s' a '%s'.\n", start->name, goal->name);
    
    Visited *v = visited;
    while (v != NULL) { Visited *t = v; v = v->next; free(t); }
}