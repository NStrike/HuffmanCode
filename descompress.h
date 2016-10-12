#ifndef DESCOMPRESS_H_
#define DESCOMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node Node;
int is_bit_set(unsigned char c, int i);
int set_bit(unsigned char c, int i);
int file_tree_size(FILE *file);
int file_trash_size(FILE *file);
Node* file_tree(FILE *file, int size);
Node* file_tree_builder(unsigned char **array);
Node* file_add_node(unsigned char letra);
void print_pre_order(Node *tree);
void decompress(FILE *fp, int tsize, int size_lixo, Node *raiz_da_arvre);
int start_descompress();


#endif /* DESCOMPRESS_H_ */
