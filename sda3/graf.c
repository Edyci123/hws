#include "graf.h"
#include <stdlib.h>
#include <string.h>

TRoute createRoute(char* cityD, int nrTronsoane, FILE* in) {
    TRoute route = (TRoute)malloc(sizeof(Route));

    route->cityD = strdup(cityD);
    route->nrTronsoane = nrTronsoane;
    route->tronsoane = malloc(sizeof(Lista));
    route->isReversed = 0;

    for (int i = 0; i < nrTronsoane; i++) {
        int value;
        fscanf(in, "%d", &value);
        insertList(route->tronsoane, value);
    }

    return route;
}

TRoute createRouteWithList(char* cityD, int nrTronsoane, TLista list) {
    TRoute route = (TRoute)malloc(sizeof(Route));

    route->cityD = strdup(cityD);
    route->nrTronsoane = nrTronsoane;
    route->tronsoane = malloc(sizeof(Lista));
    route->isReversed = 0;

    route->tronsoane = list;

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

TRoute createInverseOfRoute(TRoute route, char* city) {
    TRoute newRoute = malloc(sizeof(Route));
    newRoute->cityD = strdup(city);
    newRoute->nrTronsoane = route->nrTronsoane;
    newRoute->tronsoane = malloc(sizeof(Lista));
    route->isReversed = 1;

    TNode node = route->tronsoane->start;

    for (int i = 0; i < route->nrTronsoane; i++) {
        insertListStart(newRoute->tronsoane, node->info);
        node = node->next;
    }

    return newRoute;
}

void addRoute(Graf* graf, char* cityS, char* cityD, int nrTronsoane, FILE* in) {
    if (graf == NULL) {
        graf = initGraf();
    }
    int idx = getIndexForCity(graf, cityS);
    TRoute route = createRoute(cityD, nrTronsoane, in);
    if (idx == -1) {
       graf->noOfCities++;
       graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
       graf->cities[graf->noOfCities - 1] = strdup(cityS);
       idx = graf->noOfCities - 1;
       graf->routes = realloc(graf->routes, graf->noOfCities * sizeof(TRoute));
       graf->routes[graf->noOfCities - 1] = route;
    }
    idx = getIndexForCity(graf, cityD);
    TRoute routeD = createInverseOfRoute(route, cityS);
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

int findMaxRoute(Graf* graf, char* city) {
    int res = 0;

    int idx = getIndexForCity(graf, city);
    TRoute route = graf->routes[idx];

    while (route) {
        if (route->tronsoane[0].start->info > res) {
            res = route->tronsoane[0].start->info;
        }
        route = route->next;
    }
    
    return res;
}

void addOneYear(Graf* graf) {
    TRoute* route = malloc(graf->noOfCities * sizeof(TRoute));

    for (int i = 0; i < graf->noOfCities; i++) {
        TRoute currentRoute = graf->routes[i];
        route[i] = malloc(sizeof(Route));
        route[i]->isReversed = currentRoute->isReversed;
        route[i]->nrTronsoane = currentRoute->nrTronsoane;
        route[i]->cityD = currentRoute->cityD;
        route[i]->tronsoane = copyList(currentRoute->tronsoane);
        while (currentRoute) {
            if (currentRoute->isReversed == 1) {
                currentRoute = currentRoute->next;
                continue;
            }
            for (int i = 0; i < currentRoute->nrTronsoane; i++) {
                TLista tronson = currentRoute->tronsoane;
                TLista routeTronson = route[i]->tronsoane;
                TNode currentTronson = tronson->start;
                TNode currentRouteTronson = routeTronson->start;
                while (currentTronson) {
                    int maxi = 0;
                    if (currentTronson->prev == NULL) {
                        maxi = findMaxRoute(graf, graf->cities[i]);
                    } else {
                        maxi = currentTronson->prev->info;
                    }
                    if (currentTronson->next == NULL) {
                        int val = findMaxRoute(graf, currentRoute->cityD);
                        if (val > maxi) {
                            maxi = val;
                        }
                    } else {
                        if (maxi < currentTronson->next->info) {
                            maxi = currentTronson->next->info;
                        }
                    }
                    if (currentTronson->info == 0) {
                        currentRouteTronson->info = maxi / 2;
                    } else {
                        currentRouteTronson->info = currentTronson->info * 2;
                    }

                    
                    currentTronson = currentTronson->next;
                    currentRouteTronson = currentRouteTronson->next;

                }
            }
        }
    }
    graf->routes = route;
}