#include "graf2.h"
#include <stdlib.h>
#include <string.h>

TRoute createRoute(char* cityD, int cost) {
    TRoute route = (TRoute)malloc(sizeof(Route));

    route->cityD = strdup(cityD);
    route->cost = cost;

    return route;
}

int getIndexForCity(Graf* graf, char* toFind) {
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


Graf* initGraf() {
    Graf* newGraf = malloc(sizeof(Graf));
    newGraf->n = 0;
    newGraf->routes = NULL;
    newGraf->cities = NULL;
    newGraf->noOfCities = 0;

    return newGraf;
}

void addRoute(Graf* graf, char* cityS, char* cityD, int cost) {
    if (graf == NULL) {
        graf = initGraf();
    }
    int idx = getIndexForCity(graf, cityS);
    TRoute route = createRoute(cityD, cost);
    if (idx == -1) {
       graf->noOfCities++;
       graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
       graf->cities[graf->noOfCities - 1] = strdup(cityS);
       idx = graf->noOfCities - 1;
       graf->routes = realloc(graf->routes, graf->noOfCities * sizeof(TRoute));
       graf->routes[graf->noOfCities - 1] = route;
    }
    idx = getIndexForCity(graf, cityD);
    TRoute routeD = createRoute(cityS, cost);
    if (idx == -1) {
       graf->noOfCities++;
       graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
       graf->cities[graf->noOfCities - 1] = strdup(cityD);
       idx = graf->noOfCities - 1;
       graf->routes = realloc(graf->routes, graf->noOfCities * sizeof(TRoute));
       graf->routes[graf->noOfCities - 1] = routeD;
    }
}

TRoute getRoutesForCity(Graf* graf, char* toFind) {
    int idx = getIndexForCity(graf, toFind);
    return graf->routes[idx];
}