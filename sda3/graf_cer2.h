/* BIC CODRUT EDUARD - 312CB */
#include <stdio.h>
typedef struct Edge {
    char* cityD;
    int nrTronsoane;
    int idx;
    int cost;
    int isReversed;
    struct Edge* next;
} Edge, *TEdge;

typedef struct {
    int idxEdge;
    int parentNode;
} Parent, *TParent;

typedef struct {
    int n;
    int noOfCities;
    char** cities;
    TParent* parents;
    TEdge* edges;
} Graf2, *TGraf2;

int getIndexForCity2(Graf2* graf, char* toFind);

TGraf2 initGraf2();

void dijkstra(TGraf2 graf, int start, int* distances);

void addEdge(TGraf2 graf, char* cityS, char* cityD, int cost, int idxEdge);

void showGraf2(TGraf2 graf);

void getEdgeByIdx(Graf2* graf, int idx, FILE* out);


