#include "lista.h"
#include <stdio.h>

typedef struct Route {
    char* cityD; // destination
    int cost;
    struct Route* next;
} Route, *TRoute;


typedef struct {
    int n;
    char** cities;
    int noOfCities;
    TRoute* routes;
} Graf;

int getIndexForCity(Graf* graf, char* toFind);

TRoute createRoute(char* cityD, int cost);

Graf* initGraf();

void addRoute(Graf* graf, char* cityS, char* cityD, int cost);

void addOneYear(Graf* graf);

