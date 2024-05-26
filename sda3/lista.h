/* BIC CODRUT EDUARD - 312CB */
typedef struct Node {
    float info;
    struct Node* prev;
    struct Node* next;
} Node, *TNode;

typedef struct {
    TNode start;
    TNode end;
} Lista, *TLista;

TNode createNode(float value);
void insertList(TLista list, float value);
void freeList(TLista list);
void insertListStart(TLista list, float value);
TLista copyList(TLista list);