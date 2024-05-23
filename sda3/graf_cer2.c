#include "graf_cer2.h"
#include <stdlib.h>
#include <string.h>

TGraf2 initGraf2() {
    TGraf2 newGraf = malloc(sizeof(Graf2));
    newGraf->n = 0;
    newGraf->edges = NULL;
    newGraf->cities = NULL;
    newGraf->noOfCities = 0;

    return newGraf;
}

TEdge createEdge(char* cityD, int cost) {
    TEdge newEdge = malloc(sizeof(Edge));
    newEdge->cityD = strdup(cityD);
    newEdge->cost = cost;

    return newEdge;
}

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

void addEdge(TGraf2 graf, char* cityS, char* cityD, int cost) {
    int idx = getIndexForCity2(graf, cityS);
    TEdge edge = createEdge(cityD, cost);

    if (idx != -1) {
        graf->noOfCities++;
        graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
        graf->cities[graf->noOfCities - 1] = strdup(cityS);
        idx = graf->noOfCities - 1;
        graf->edges = realloc(graf->edges, graf->noOfCities * sizeof(TEdge));
        graf->edges[graf->noOfCities - 1] = edge;
    } else {
        edge->next = NULL;
        TEdge edge1 = graf->edges[idx];
        while (edge1->next) {
            edge1 = edge1->next;
        }
        edge1->next = edge;
    }

    idx = getIndexForCity2(graf, cityD);
    TEdge edge1 = createEdge(cityS, cost);

    if (idx != -1) {
        graf->noOfCities++;
        graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
        graf->cities[graf->noOfCities - 1] = strdup(cityS);
        idx = graf->noOfCities - 1;
        graf->edges = realloc(graf->edges, graf->noOfCities * sizeof(TEdge));
        graf->edges[graf->noOfCities - 1] = edge1;
    } else {
        edge1->next = graf->edges[idx];
        graf->edges[idx] = edge1;
    }
}
