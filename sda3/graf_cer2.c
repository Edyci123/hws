#include "graf_cer2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>


// initializeaza graful
TGraf2 initGraf2() {
    TGraf2 newGraf = malloc(sizeof(Graf2));
    newGraf->n = 0;
    newGraf->edges = NULL;
    newGraf->cities = NULL;
    newGraf->noOfCities = 0;
    newGraf->parents = NULL;

    return newGraf;
}

// creaza o muchie
TEdge createEdge(char* cityD, int cost, int idx) {
    TEdge newEdge = malloc(sizeof(Edge));
    newEdge->cityD = strdup(cityD);
    newEdge->cost = cost;
    newEdge->next = NULL;
    newEdge->idx = idx;
    newEdge->isReversed = 0;

    return newEdge;
}


// ia indexul dupa nume dintr un graf
int getIndexForCity2(Graf2 *graf, char *toFind) {
    if (graf == NULL) {
        return -1;
    }

    for (int i = 0; i < graf->noOfCities; i++) {
        if (!strcmp(graf->cities[i], toFind)) {
            return i;
        }
    }

    return -1;
}


// adauga o muhcie si inversa sa la un graf
void addEdge(Graf2* graf, char* cityS, char* cityD, int cost, int idxEdge) {
    int idx = getIndexForCity2(graf, cityS);
    TEdge edge = createEdge(cityD, cost, idxEdge);
    
    if (idx == -1) {
        graf->noOfCities++;
        graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
        graf->cities[graf->noOfCities - 1] = strdup(cityS);
        idx = graf->noOfCities - 1;
        graf->edges = realloc(graf->edges, graf->noOfCities * sizeof(TEdge));
        graf->edges[graf->noOfCities - 1] = edge;
    } else {
        edge->next = NULL;
        TEdge edge1 = graf->edges[idx];
        while (edge1->next != NULL) {
            edge1 = edge1->next;
        }
        edge1->next = edge;
    }

    idx = getIndexForCity2(graf, cityD);
    TEdge edge1 = createEdge(cityS, cost, idxEdge);
    edge1->isReversed = 1;


    if (idx == -1) {
        graf->noOfCities++;
        graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
        graf->cities[graf->noOfCities - 1] = strdup(cityD);
        idx = graf->noOfCities - 1;
        graf->edges = realloc(graf->edges, graf->noOfCities * sizeof(TEdge));
        graf->edges[graf->noOfCities - 1] = edge1;
    } else {
        edge1->next = graf->edges[idx];
        graf->edges[idx] = edge1;
    }
}


// face dijkstra pe graf si imi face vectorul de tati
void dijkstra(TGraf2 graf, int start, int* distances) {
    int* visited = malloc(graf->noOfCities * sizeof(int));;
    
    for (int i = 0; i < graf->noOfCities; i++) {
        visited[i] = 0;
    }
    distances[start] = 0;

    for (int i = 0; i < graf->noOfCities - 1; i++) {
        int minDist = INT_MAX, minIndex = -1;
        for (int j = 0; j < graf->noOfCities; j++) {
            if (visited[j] == 0 && distances[j] < minDist) {
                minDist = distances[j];
                minIndex = j;
            }
        }

        if (minIndex != -1) {
            int idx = minIndex;
            visited[idx] = 1;

            for (TEdge edge = graf->edges[idx]; edge != NULL; edge = edge->next) {
                int j = getIndexForCity2(graf, edge->cityD);
                // printf("%d %d %d %d %d\n", idx, j, distances[idx], distances[j], edge->cost);
                if (visited[j] == 0 && distances[idx] + edge->cost < distances[j]) {
                    graf->parents[j]->idxEdge = edge->idx;
                    graf->parents[j]->parentNode = idx;
                    distances[j] = distances[idx] + edge->cost;
                }
            }
        }
    }
    
}


// ia o muchie dypa numarul de ordine
void getEdgeByIdx(Graf2* graf, int idx, FILE* out) {
    for (int i = 0; i < graf->noOfCities; i++) {
        TEdge edge = graf->edges[i];
        while (edge) {
            if (edge->isReversed == 0 && edge->idx == idx) {
                fprintf(out, "%s %s\n", graf->cities[i], edge->cityD);
                return;
            }
            edge = edge->next;
        }
    }
    return;
}