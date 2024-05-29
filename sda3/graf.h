/* BIC CODRUT EDUARD - 312CB */
#include "lista.h"
#include <stdio.h>

typedef struct Route {
    char* cityD; // destination
    int nrTronsoane;
    TLista tronsoane;
    char isReversed;
    struct Route* next;
    int isBad;
    int order;
} Route, *TRoute;


typedef struct {
    int n;
    int maxWear;
    char** cities;
    int noOfCities;
    TRoute* routes;
} Graf;

int getIndexForCity(Graf* graf, char* toFind);

TRoute createRoute(char* cityD, int nrTronsoane, int order, FILE* in);

Graf* initGraf(int wear);

void addRoute(Graf* graf, int order, char* cityS, char* cityD, int nrTronsoane, FILE* in);

void addOneYear(Graf* graf);

void showGraf(Graf* graf, FILE* out);

void freeGraf(Graf* graf);