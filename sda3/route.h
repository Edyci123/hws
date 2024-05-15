#include "lista.h"
#include <stdio.h>

typedef struct {
    char* cityS; // start
    char* cityD; // destination
    int nrTronsoane;
    TNode tronsoane;
} Route, *TRoute;


TRoute createRoute(char* cityS, char* cityD, int nrTronsoane, FILE* in);