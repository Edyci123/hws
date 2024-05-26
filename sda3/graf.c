#include "graf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creaza o ruta care are ca destinatie orasul cityD
TRoute createRoute(char* cityD, int nrTronsoane, int order, FILE* in) {
    TRoute route = (TRoute)malloc(sizeof(Route));
    route->cityD = strdup(cityD);
    route->nrTronsoane = nrTronsoane;
    route->tronsoane = malloc(sizeof(Lista));
    route->isReversed = 0;
    route->next = NULL;
    route->isBad = 0;
    route->order = order;

    for (int i = 0; i < nrTronsoane; i++) {
        int value;
        fscanf(in, "%d", &value);
        insertList(route->tronsoane, value);
    }

    return route;
}

// ia indexul pentru un oras, intr un graf comparand numele
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

// initializeaza graful, si seteaza uzura maxima
Graf* initGraf(int wear) {
    Graf* newGraf = malloc(sizeof(Graf));
    newGraf->n = 0;
    newGraf->routes = NULL;
    newGraf->cities = NULL;
    newGraf->noOfCities = 0;
    newGraf->maxWear = wear;

    return newGraf;
}

// face o ruta inversa, fiind neorientat
TRoute createInverseOfRoute(TRoute route, char* city) {
    TRoute newRoute = malloc(sizeof(Route));
    newRoute->cityD = strdup(city);
    newRoute->nrTronsoane = route->nrTronsoane;
    newRoute->tronsoane = malloc(sizeof(Lista));

    TNode node = route->tronsoane->start;
    newRoute->isReversed = 1;
    newRoute->next = NULL;
    newRoute->isBad = 0;
    newRoute->order = route->order;

    for (int i = 0; i < route->nrTronsoane; i++) {
        insertListStart(newRoute->tronsoane, node->info);
        node = node->next;
    }

    return newRoute;
}


// copiaza contentul unei rute in alta noua
TRoute copyRoute(TRoute route) {
    TRoute newRoute = malloc(sizeof(Route));
    newRoute->cityD = strdup(route->cityD);
    newRoute->nrTronsoane = route->nrTronsoane;
    newRoute->tronsoane = malloc(sizeof(Lista));

    TNode node = route->tronsoane->start;
    newRoute->isReversed = route->isReversed;
    newRoute->next = NULL;
    newRoute->isBad = route->isBad;
    newRoute->order = route->order;

    for (int i = 0; i < route->nrTronsoane; i++) {
        insertList(newRoute->tronsoane, node->info);
        node = node->next;
    }

    return newRoute;
}

// adauga o ruta si inversa ei
void addRoute(Graf* graf, int order, char* cityS, char* cityD, int nrTronsoane, FILE* in) {
    int idx = getIndexForCity(graf, cityS);
    TRoute route = createRoute(cityD, nrTronsoane, order, in);
    if (idx == -1) {
       graf->noOfCities++;
       graf->cities = realloc(graf->cities, graf->noOfCities * sizeof(char*));
       graf->cities[graf->noOfCities - 1] = strdup(cityS);
       idx = graf->noOfCities - 1;
       graf->routes = realloc(graf->routes, graf->noOfCities * sizeof(TRoute));
       graf->routes[graf->noOfCities - 1] = route;
    } else {
        route->next = NULL;
        TRoute route1 = graf->routes[idx];
        while (route1->next) {
            route1 = route1->next;
        }
        route1->next = route;
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
    } else {
        routeD->next = graf->routes[idx];
        graf->routes[idx] = routeD;
    }
}

// gaseste uzura maxima de pe primul tronson de pe toate muhciile care sunt adiacente la nodul cu numele city;
float findMaxRoute(Graf* graf, char* city) {
    float res = 0;

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

void freeRoute(TRoute route) {
    if (route == NULL) {
        return;
    }

    TRoute route1 = route->next;
    free(route);
    // freeList(route->tronsoane);
    freeRoute(route1);
}

void freeRoutes(TRoute* routes, int nr) {
    for (int i = 0; i < nr; i++) {
        freeRoute(routes[i]);
    }
    free(routes);
}


// adauga un an de uzura
void addOneYear(Graf* graf) {
    TRoute* route = malloc(graf->noOfCities * sizeof(TRoute));

    for (int i = 0; i < graf->noOfCities; i++) {
        TRoute route1 = NULL;
        TRoute route2 = NULL;
        TRoute route3 = NULL;
        TRoute gRoute = graf->routes[i];
        while (gRoute) {
            route2 = copyRoute(gRoute);
            if (route3 != NULL) {
                route3->next = route2;
            }

            TNode gTronson = gRoute->tronsoane->start;
            TNode tronson = route2->tronsoane->start;
            float sum = 0;
            while (gTronson) {

                float max = 0;
                if (gTronson->prev == NULL) {
                    max = findMaxRoute(graf, graf->cities[i]);
                } else {
                    max = gTronson->prev->info;
                }

                if (gTronson->next == NULL) {
                    float max1 = findMaxRoute(graf, route2->cityD);
                    max = max > max1 ? max : max1;
                } else  {
                    float max1 = gTronson->next->info;
                    max = max > max1 ? max : max1;
                }

                if (gTronson->info == 0) {
                    tronson->info = max / 2.0;
                } else {
                    tronson->info = gTronson->info * 2.0;
                    if (tronson->info > 100) {
                        tronson->info = 100;
                    }
                }

                sum += tronson->info;
                
                gTronson = gTronson->next;
                tronson = tronson->next; 
            }

            if (sum / route2->nrTronsoane >= graf->maxWear) {
                route2->isBad = 1;
            } else {
                route2->isBad = 0;
            }

            if (route1 == NULL) {
                route1 = route2;
            }

            route3 = route2;
            route2 = route2->next;
            gRoute = gRoute->next;
        }
        
        route[i] = route1;
    }

    freeRoutes(graf->routes, graf->noOfCities);

    graf->routes = route;
}

void showRoute(TRoute route, char* cityS, FILE* out) {
    fprintf(out, "%s %s %d ", cityS, route->cityD, route->nrTronsoane);
    TNode node = route->tronsoane->start;
    while (node) {
        fprintf(out, "%.2f ", node->info);
        node = node->next;
    }
    fprintf(out, "\n");
}

// afiseaza graful
void showGraf(Graf* graf, FILE* out) {
    int len = 0;
    int len1 = 0;
    int* listOfGoodRoutes = malloc(25 * sizeof(int));
    char** citiesS = malloc(25 * sizeof(char));
    TRoute* routes = malloc(25 * sizeof(TRoute));
    for (int i = 0; i < graf->noOfCities; i++) {
        TRoute route = graf->routes[i];       
        while (route) {
            if (route->isReversed == 0) {
                routes[route->order] = copyRoute(route);
                citiesS[route->order] = strdup(graf->cities[i]);
                len1++;
            }
            route = route->next;
           
        }
    } 

    for (int i = 0; i < len1; i++) {
        showRoute(routes[i], citiesS[i], out);
        if (routes[i]->isBad == 0) {
            listOfGoodRoutes[len] = i + 1;
            len++;
        }
        free(citiesS[i]);
    } 
    
    for (int i = 0; i < len; i++) {
        fprintf(out, "%d ", listOfGoodRoutes[i]);
    }
    free(listOfGoodRoutes);
    freeRoutes(routes, len1);
    free(citiesS);
}

void freeGraf(Graf* graf) {
    // freeRoutes(graf->routes, graf->noOfCities);
    for (int i = 0; i < graf->noOfCities; i++) {
        free(graf->cities[i]);
    }
    free(graf->cities);
    free(graf);
}