#include <stdio.h>
#include "modular/graph.c"
#include "libraries/graph.h"
#include "libraries/BFS.h"
#include "modular/BFS.c"
#include "libraries/UCS.h"
#include "modular/UCS.c"
#include "libraries/DFS.h"
#include "modular/DFS.c"

void printOptions();
void loadDefaultGraph(Graph *g);

typedef struct Node Node;

//HOLAAAAAA YAEL

int main(){
    int option=1, c;
    Graph g;
    initGraph(&g);
    loadDefaultGraph(&g);
    printf("Grafo predeterminado cargado.\n");

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
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameUCS[50], goalNameUCS[50];
                Node *startUCS, *goalUCS;

                printf("Nodo inicio $");
                scanf("%s", startNameUCS);
                printf("Nodo meta $");
                scanf("%s", goalNameUCS);

                startUCS = findNode(&g, startNameUCS);
                goalUCS  = findNode(&g, goalNameUCS);

                if (startUCS == NULL)
                    printf("Nodo '%s' no existe.\n", startNameUCS);
                else if (goalUCS == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameUCS);
                else
                    UCS(&g, startUCS, goalUCS);
                break;

            case 5:
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameDFS[50], goalNameDFS[50];
                Node *startDFS, *goalDFS;

                printf("Nodo inicio $");
                scanf("%s", startNameDFS);
                printf("Nodo meta $");
                scanf("%s", goalNameDFS);

                startDFS = findNode(&g, startNameDFS);
                goalDFS  = findNode(&g, goalNameDFS);

                if (startDFS == NULL)
                    printf("Nodo '%s' no existe.\n", startNameDFS);
                else if (goalDFS == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameDFS);
                else
                    DFS(startDFS, goalDFS);
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
void loadDefaultGraph(Graph *g) {
    
    addNode(g, "A", 10.0);
    addNode(g, "B", 3.0);
    addNode(g, "C", 9.0);
    addNode(g, "D", 5.0);
    addNode(g, "E", 3.0);
    addNode(g, "F", 3.0);
    addNode(g, "G", 8.0);
    addNode(g, "H", 7.0);
    addNode(g, "I", 0.0);

    addEdge(g, "A", "B", 3.0);
    addEdge(g, "A", "D", 3.0);
    addEdge(g, "A", "C", 8.0);
    addEdge(g, "B", "D", 5.0);
    addEdge(g, "B", "E", 2.0);
    addEdge(g, "D", "E", 3.0);
    addEdge(g, "C", "E", 3.0);
    addEdge(g, "C", "G", 5.0);
    addEdge(g, "D", "C", 3.0);
    addEdge(g, "E", "H", 3.0);
    addEdge(g, "F", "H", 3.0);
    addEdge(g, "F", "I", 2.0);
    addEdge(g, "H", "I", 4.0);
    addEdge(g, "H", "G", 2.0);
    addEdge(g, "G", "I", 4.0);
}