#include <stdio.h>
#include "graf.h"

void solve() {

}

int main() {
    int r, k, l;
    FILE *in, *out;
    Graf* graf = initGraf();

    in = fopen("txt.in", "r");
    fscanf(in, "%d %d %d", &r, &k, &l);

    for (int i = 0; i < r; i++) {
        char* cityS;
        char* cityD;
        int nrTronsoane;
        fscanf(in, "%s %s %d", cityS, cityD, &nrTronsoane);
        addRoute(graf, cityS, cityD, nrTronsoane, in);
    }

    for (int i = 0; i <= k; i++) {
        addOneYear(graf);
    }


    return 0;
}