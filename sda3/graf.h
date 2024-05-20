#include "lista.h"
#include <stdio.h>

typedef struct Route {
    char* cityD; // destination
    int nrTronsoane;
    TLista tronsoane;
    char isReversed;
    struct Route* next;
} Route, *TRoute;


typedef struct {
    int n;
    char** cities;
    int noOfCities;
    TRoute* routes;
} Graf;

int getIndexForCity(Graf* graf, char* toFind);

TRoute createRoute(char* cityD, int nrTronsoane, FILE* in);

Graf* initGraf();

void addRoute(Graf* graf, char* cityS, char* cityD, int nrTronsoane, FILE* in);

void addOneYear(Graf* graf);

