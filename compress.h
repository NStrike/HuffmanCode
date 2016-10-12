#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct manager Manager;

typedef struct array_hash Array_hash;
typedef struct hash Hash;

Manager* begin_fila ();
Hash* begin_hash();
void alocar_posicao_hash (Hash *ht, unsigned int id);
void copiar_codigo (int *v1, int *v2, int k);
void addnode (Manager *m, unsigned int c, int f);
void addnew (Manager *m, Node *newN);
void print_lista (Node *p);
Node* retirar (Manager *Fila);
void Tree_Builder (Manager *Fila);
int treesize(Node *tree, int size);
void percorrer_arvore(int *codigo_binario, Node *tree, Hash *hash_de_binarios, int k);
void compress_print_pre_order(Node *tree,  FILE *out);
int compress_set_bit(unsigned char c, int i);
int newbites(FILE *in, FILE *out, Hash *bits);
void  set_trash(FILE *out, int size);
void compress(FILE *fp, Node *tree, int tsize, Hash *hash);
int start_compress();

#endif /* COMPRESS_H_ */
