#include "route.h"
#include <stdlib.h>
#include <string.h>

TRoute createRoute(char* cityS, char* cityD, int nrTronsoane, FILE* in) {
    TRoute route = (TRoute)malloc(sizeof(Route));
    if (route == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    route->cityS = strdup(cityS);
    route->cityD = strdup(cityD);
    route->nrTronsoane = nrTronsoane;
    route->tronsoane = NULL;

    for (int i = 0; i < nrTronsoane; i++) {
        int value;
        if (fscanf(in, "%d", &value) != 1) {
            printf("Error reading tronsoane from file\n");
            free(route->cityS);
            free(route->cityD);
            free(route);
            exit(1);
        }
        insertList(&(route->tronsoane), value);
    }

    return route;
}