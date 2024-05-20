typedef struct Node {
    int info;
    struct Node* prev;
    struct Node* next;
} Node, *TNode;

typedef struct {
    TNode start;
    TNode end;
} Lista, *TLista;

TNode createNode(int value);
void insertList(TLista list, int value);
void freeList(TLista list);
void insertListStart(TLista list, int value);
TLista copyList(TLista list);