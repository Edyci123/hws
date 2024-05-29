/* BIC CODRUT EDUARD - 312CB */
#include <stdio.h>
#include "graf.h"
#include "graf_cer2.h"
#include <stdlib.h>
#include <limits.h>

void solve() {

}

int main(int argc, char* argv[]) {
    int r, k, l;
    FILE *in, *out;
    

    char* a = argv[argc - 1];
    int task = atoi(a);  

    in = fopen("tema3.in", "r");
    out = fopen("tema3.out", "w");
    
    if (task == 1) {
        fscanf(in, "%d %d %d", &r, &k, &l);
        
        Graf* graf = initGraf(l);

        for (int i = 0; i < r; i++) {
            char* cityS = malloc(sizeof(char) * 100);
            char* cityD = malloc(sizeof(char) * 100);
            int nrTronsoane;
            fscanf(in, "%s %s %d", cityS, cityD, &nrTronsoane);
            addRoute(graf, i, cityS, cityD, nrTronsoane, in);
        }

        for (int i = 0; i < k; i++) {
            addOneYear(graf);
        }

        showGraf(graf, out);

        // freeGraf(graf);

    } else {
        char* startCity = malloc(100 * sizeof(char));
        fscanf(in, "%s", startCity);
        int k, m;
        fscanf(in, "%d %d", &k, &m);

        TGraf2 graf = initGraf2();
        for (int i = 0; i < m; i++) {
            char* cityS = malloc(sizeof(char) * 100);
            char* cityD = malloc(sizeof(char) * 100);
            int cost;
            fscanf(in, "%s %s %d", cityS, cityD, &cost);
            addEdge(graf, cityS, cityD, cost, i);
        }


        int start = getIndexForCity2(graf, startCity);
        int *distances = malloc(graf->noOfCities * sizeof(int));
        graf->parents = malloc(graf->noOfCities * sizeof(TParent));
        for (int i = 0; i < graf->noOfCities; i++) {
            distances[i] = INT_MAX;
            graf->parents[i] = malloc(sizeof(Parent));
        }

        dijkstra(graf, start, distances);
        // printf("%d\n", graf->noOfCities);
        int* allowed = calloc(sizeof(int), 100);
        int nr = 0;
        for (int i = 0; i < graf->noOfCities; i++) {
            if (distances[i] != 0) {
                allowed[graf->parents[i]->idxEdge] = 1;
                nr++;
            }
        }
        while (nr > k) {
            int maxDistance = 0;
            int maxIdx = 0;
            for (int i = 0; i < graf->noOfCities; i++) {
                if (allowed[graf->parents[i]->idxEdge] && maxDistance < distances[i]) {
                    maxDistance = distances[i];
                    maxIdx = graf->parents[i]->idxEdge;
                }
            }
            allowed[maxIdx] = 0;
            nr--;
        }

        fprintf(out, "%d \n", nr);
        for (int i = 0; i < m; i++) {
            if (allowed[i]) {
                getEdgeByIdx(graf, i, out);
            }
        }
    }
    


    return 0;
}