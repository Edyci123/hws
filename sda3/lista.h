typedef struct Node {
    int info;
    struct Node* next;
} Node, *TNode;

typedef struct {
    TNode start;
    TNode end;
} Lista, *TLista;

TNode createNode(int value);