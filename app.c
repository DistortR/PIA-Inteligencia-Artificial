#include <stdio.h>
#include "modular/graph.c"
#include "libraries/graph.h"
#include "libraries/BFS.h"
#include "modular/BFS.c"
#include "libraries/UCS.h"
#include "modular/UCS.c"

void printOptions();

typedef struct Node Node;

int main(){
    int option=1, c;
    Graph g;
    initGraph(&g);

    while(option != 0){
        printOptions();
        scanf("%d", &option);
        while ((c = getchar()) != '\n' && c != EOF);

        switch(option){
            case 1:
                defineGraph(&g);
                break;

            case 2:
                printGraph(&g);
                break;
            
            case 3:
                if (g.head == NULL) {
                printf("No hay grafo definido.\n");
                break;
                }

                char startName[50], goalName[50];
                Node *start, *goal;

                printf("Nodo inicio $");
                scanf("%s", startName);
                printf("Nodo meta $");
                scanf("%s", goalName);

                start = findNode(&g, startName);
                goal  = findNode(&g, goalName);
                
                if (start == NULL)
                    printf("Nodo '%s' no existe.\n", startName);
                    else if
                        (goal == NULL) printf("Nodo '%s' no existe.\n", goalName);
                else
                    BFS(start, goal);
                break;

            case 4:
                //UCS();
                break;

            case 5:
                //DFS();
                break;

            case 6:
                //DLS();
                break;

            case 7:
                //IDDFS();
                break;
            
            case 8:
                //Greedy();
                break;

            case 9:
                //AStar();
                break;

            case 0: 
                printf("\nGoodBye :p");
                break;
        }
    }
}

void printOptions(){
    printf("\n======== OPCIONES ========\n");
    printf("1.- Definir Grafo\n");
    printf("2.- Imprimir Grafo\n");
    printf("3.- Busqueda por Amplitud\n");
    printf("4.- Busqueda por Costo Uniforme\n");
    printf("5.- Busqueda por Profundidad\n");
    printf("6.- Busqueda por Profundidad Limitada\n");
    printf("7.- Busqueda por Profundidad Iterativa\n");
    printf("8.- Busqueda Avara\n");
    printf("9.- Busqueda A*\n");
    printf("0. Salir\n");
    printf("Opcion $");
}