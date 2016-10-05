#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct manager Manager;

Manager* begin_fila ();

void addnode (Manager *m, char c, int f);

void addnew (Manager *m, Node *newN);

Node* retirar (Manager *Fila);

void Tree_Builder (Manager *Fila);

int treesize(Node *tree, int size);

void print_pre_order(Node *tree);

