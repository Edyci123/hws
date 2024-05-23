#include <stdio.h>
#include "graf.h"
#include "graf_cer2.h"
#include <stdlib.h>

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

        freeGraf(graf);

    } else {

    }
    


    return 0;
}