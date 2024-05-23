typedef struct Edge {
    char* cityD;
    int nrTronsoane;
    int cost;
    struct Edge* next;
} Edge, *TEdge;

typedef struct {
    int n;
    int noOfCities;
    char** cities;
    TEdge* edges;
} Graf2, *TGraf2;

int getIndexForCity2(Graf2* graf, char* toFind);

TGraf2 initGraf2();

void dijkstra(TGraf2 graf);

void addEdge(TGraf2 graf, char* cityS, char* cityD, int cost);

void showGraf(TGraf2 graf);



