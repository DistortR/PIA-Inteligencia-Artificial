#include <stdio.h>
#include "modular/graph.c"
#include "libraries/graph.h"
#include "libraries/BFS.h"
#include "modular/BFS.c"
#include "libraries/UCS.h"
#include "modular/UCS.c"
#include "libraries/DFS.h"
#include "modular/DFS.c"
#include "libraries/DLS.h"
#include "modular/DLS.c"
#include "libraries/IDDFS.h"
#include "modular/IDDFS.c"
#include "libraries/GREEDY.h"
#include "modular/GREEDY.c"
#include "libraries/ASTAR.h"
#include "modular/ASTAR.c"

void printOptions();
void loadDefaultGraph(Graph *g);

typedef struct Node Node;

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
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameDLS[50], goalNameDLS[50];
                int limitDLS;
                Node *startDLS, *goalDLS;

                printf("Nodo inicio $");
                scanf("%s", startNameDLS);
                printf("Nodo meta $");
                scanf("%s", goalNameDLS);
                printf("Limite de profundidad $");
                scanf("%d", &limitDLS);

                startDLS = findNode(&g, startNameDLS);
                goalDLS  = findNode(&g, goalNameDLS);

                if (startDLS == NULL)
                    printf("Nodo '%s' no existe.\n", startNameDLS);
                else if (goalDLS == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameDLS);
                else
                    DLS(startDLS, goalDLS, limitDLS);
                break;

            case 7:
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameIDDFS[50], goalNameIDDFS[50];
                int maxDepthIDDFS;
                Node *startIDDFS, *goalIDDFS;

                printf("Nodo inicio $");
                scanf("%s", startNameIDDFS);
                printf("Nodo meta $");
                scanf("%s", goalNameIDDFS);
                printf("Profundidad maxima $");
                scanf("%d", &maxDepthIDDFS);

                startIDDFS = findNode(&g, startNameIDDFS);
                goalIDDFS  = findNode(&g, goalNameIDDFS);

                if (startIDDFS == NULL)
                    printf("Nodo '%s' no existe.\n", startNameIDDFS);
                else if (goalIDDFS == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameIDDFS);
                else
                    IDDFS(startIDDFS, goalIDDFS, maxDepthIDDFS);
                break;
            
            case 8:
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameGreedy[50], goalNameGreedy[50];
                Node *startGreedy, *goalGreedy;

                printf("Nodo inicio $");
                scanf("%s", startNameGreedy);
                printf("Nodo meta $");
                scanf("%s", goalNameGreedy);

                startGreedy = findNode(&g, startNameGreedy);
                goalGreedy  = findNode(&g, goalNameGreedy);

                if (startGreedy == NULL)
                    printf("Nodo '%s' no existe.\n", startNameGreedy);
                else if (goalGreedy == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameGreedy);
                else
                    Greedy(&g, startGreedy, goalGreedy);
                break;

            case 9:
                if (g.head == NULL) {
                    printf("No hay grafo definido.\n");
                    break;
                }

                char startNameAS[50], goalNameAS[50];
                Node *startAS, *goalAS;

                printf("Nodo inicio $");
                scanf("%s", startNameAS);
                printf("Nodo meta $");
                scanf("%s", goalNameAS);

                startAS = findNode(&g, startNameAS);
                goalAS  = findNode(&g, goalNameAS);

                if (startAS == NULL)
                    printf("Nodo '%s' no existe.\n", startNameAS);
                else if (goalAS == NULL)
                    printf("Nodo '%s' no existe.\n", goalNameAS);
                else
                    AStar(&g, startAS, goalAS);
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