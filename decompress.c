#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
	char letra;
	struct Node* left;
	struct Node* right;

} Node;


Node* file_tree(FILE *file, int size);
Node* file_tree_builder(char **array);
Node* file_add_node(char letra);


int is_bit_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

int set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}

int file_tree_size(FILE *file)
{
	int size = 0, i;
	unsigned char byte1, byte2;

	fseek(file, 0, SEEK_SET);

	byte1 = getc(file);
	byte2 = getc(file);

	for(i = 4; i >= 0; i--)
	{
		if(is_bit_set(byte1,i))
		{
			size += pow(2,i+8);
		}

		printf("%d %d\n", i, size);
	}

	for(i = 7; i >= 0; i--)
	{
		if(is_bit_set(byte2,i))
		{
			size += pow(2,i);
		}

		printf("%d %d\n", i, size);
	}

	return size;
}

int file_trash_size(FILE *file)
{
	int size = 0, i;
	unsigned char byte;

	fseek(file, 0, SEEK_SET);

	byte = getc(file);

	for(i = 7; i >= 5 ; i--)
	{
		if(is_bit_set(byte,i))
		{
			size += pow(2,i-5);
		}

		printf("%d %d\n", i, size);
	}

	return size;
}

Node* file_tree(FILE *file, int size)
{
	int i;

	char *array;
	array = (char*) malloc(size*sizeof(char));

	fseek(file, 2, SEEK_SET);

	for (i = 0; i < size; i++)
	{
		array[i] = getc(file);
	}

	Node *tree = file_tree_builder(&array);

	return tree;
}

Node* file_tree_builder(char **array)
{
	printf("%c\n", **array);
	if (**array == '*')
	{
		Node *new = file_add_node(**array);
		*array = *array + 1;
		new->left = file_tree_builder(array);
		*array = *array + 1;
		new->right = file_tree_builder(array);

		return new;
	}

	else if (**array == '\\')
	{
		*array = *array + 1;
		Node *new = file_add_node(**array);
		*array = *array + 1;

		return new;
	}

	else
	{
		Node *new = file_add_node(**array);
		return new;
	}
}

Node* file_add_node(char letra)
{
	Node *new = (Node*) malloc(sizeof(Node));
	new->letra = letra;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void print_pre_order(Node *tree)
{

	if(tree->letra == '*' || tree->letra == '\\')
	{
		if(tree->left == NULL && tree->right == NULL)
		{
			printf("\\");
		}
	}

	printf("%c", tree->letra);

	if(tree->left != NULL)
	{
		print_pre_order(tree->left);
	}

	if(tree->right != NULL)
	{
		print_pre_order(tree->right);
	}
}
int main ()
{
    FILE *fp;
    fp = fopen("compressed.huff", "r");
    int sizelixo, sizetree;

    sizelixo = file_trash_size(fp);
    sizetree = file_tree_size(fp);
    printf("passa\n");

    printf("%d %d\n", sizelixo, sizetree);

    Node* tree = NULL;

    tree = file_tree(fp,sizetree);    
    print_pre_order(tree);
    fclose (fp);
    return 0;
}