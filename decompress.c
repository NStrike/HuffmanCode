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
	}

	for(i = 7; i >= 0; i--)
	{
		if(is_bit_set(byte2,i))
		{
			size += pow(2,i);
		}
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

	printf("%d", tree->letra);

	if(tree->left != NULL)
	{
		print_pre_order(tree->left);
	}

	if(tree->right != NULL)
	{
		print_pre_order(tree->right);
	}
}

void decompress(FILE *fp, int tsize, int size_lixo, Node *raiz_da_arvre)
{
	FILE *file_decompress;

	file_decompress  = fopen("exit_file.txt","w+");

	fseek(fp , 0 , SEEK_END);
	int numero_de_bit_arquivo = ftell(fp);

	unsigned  char char_bite_corrente;
	int bite_corrente, bits;

	Node *find_pointer = raiz_da_arvre;

	fseek(fp , 2+tsize , SEEK_SET);

	for(bite_corrente = 2+tsize ; bite_corrente < numero_de_bit_arquivo-1 ; bite_corrente++)
	{
		char_bite_corrente = fgetc(fp);

		for(bits = 7 ; bits >= 0 ; bits--)
		{
			if(is_bit_set(char_bite_corrente,bits))
			{
				find_pointer = find_pointer->right;
			}

			else
			{
				find_pointer = find_pointer->left;
			}

			if(find_pointer->left == NULL && find_pointer->right == NULL)
			{
				fprintf(file_decompress ,"%c", find_pointer->letra);
				find_pointer = raiz_da_arvre;
			}
		}
	}

	char_bite_corrente = fgetc(fp);

	for(bits = 7 ; bits >= size_lixo ; bits--)
	{
		if(is_bit_set(char_bite_corrente,bits))
		{
			find_pointer = find_pointer->right;
		}

		else
		{
			find_pointer = find_pointer->left;
		}

		if(find_pointer->left == NULL && find_pointer->right == NULL)
		{
			fprintf(file_decompress , "%c", find_pointer->letra);
			find_pointer = raiz_da_arvre;
		}
	}

	fclose(file_decompress);
}

int main ()
{
    FILE *fp;
    fp = fopen("compressed_file.huff", "rb");
    int sizelixo, sizetree;

    sizelixo = file_trash_size(fp);
    sizetree = file_tree_size(fp);

    Node* tree = NULL;

    tree = file_tree(fp,sizetree);

    decompress(fp,sizetree,sizelixo,tree);

    fclose (fp);
    return 0;
}
