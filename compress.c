#include "compress.h"

struct node
{
    unsigned char letra;
    int frequencia;
    Node *next;
    Node *left;
    Node *right;
};

struct manager
{
    Node *first;
    int size;
};

struct array_hash
{
    unsigned int codigo_final[40];
};

struct hash
{
    Array_hash *array[256];
};


Manager* begin_fila ()
{
    Manager *newM = (Manager*) malloc (sizeof(Manager));
    newM->first = NULL;
    newM->size = 0;
    return newM;
}

//-----------------------------------------------------------------------------------------------------------------(Alocando a Fila)

//-----------------------------------------------------------------------------------------------------------------(Alocando a Hash)

Hash* begin_hash()
{
    Hash *ht = (Hash*) malloc (sizeof (Hash));
    int i;
    for (i=0; i<256; i++)   ht->array[i] = NULL;
    return ht;
}

//-----------------------------------------------------------------------------------------------------------------(Alocando a Hash)

//-----------------------------------------------------------------------------------------------------------------(Alocando um nó na posição esoclhida da Hash)

void alocar_posicao_hash (Hash *ht, unsigned int id)
{
    if (ht->array[id]==NULL)
    {
        Array_hash *p = (Array_hash*) malloc (sizeof (Array_hash));
        ht->array[id] = p;
        ht->array[id]->codigo_final[0] = -1;
    }
    return;
}

//-----------------------------------------------------------------------------------------------------------------(Alocando um nó na posição esoclhida da Hash)

//-----------------------------------------------------------------------------------------------------------------(Copiar o array com o char para a Hash)

void copiar_codigo (int *v1, int *v2, int k)
{
    int i;
    for (i = 0; i < k; i++)
    {
        v1[i] = v2[i];
    }
    v1[i] = -1;
    return;
}

//-----------------------------------------------------------------------------------------------------------------(Copiar o array com o char para a Hash)

//-----------------------------------------------------------------------------------------------------------------(Adicionando Nós na Fila)

void addnode (Manager *m, unsigned int c, int f)
{
    Node *newN = (Node*) malloc (sizeof(Node));
    m->size++;
    newN->letra = c;
    newN->frequencia = f;
    newN->left = NULL;
    newN->right = NULL;
    if (m->first == NULL)
    {
        newN->next = NULL;
        m->first = newN;
    }
    else
    {
        if (m->first->frequencia >= f)
        {
            newN->next = m->first;
            m->first = newN;
        }
        else
        {
            Node *p;
            p = m->first;
            while (p->next != NULL && p->next->frequencia < f) p = p->next;
            if (p->next == NULL)
            {
                newN->next = NULL;
                p->next = newN;
            }
            else
            {
                newN->next = p->next;
                p->next = newN;
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------(Adicionando Nós na Fila)

//-----------------------------------------------------------------------------------------------------------------(Adicionando Nó na fila já ordenando)

void addnew (Manager *m, Node *newN)
{
    if (m->first == NULL)
    {
        newN->next = NULL;
        m->first = newN;
    }
    else
    {
        if (m->first->frequencia >= newN->frequencia)
        {
            newN->next = m->first;
            m->first = newN;
        }
        else
        {
            Node *p;
            p = m->first;
            while (p->next != NULL && p->next->frequencia < newN->frequencia) p = p->next;
            if (p->next == NULL)
            {
                newN->next = NULL;
                p->next = newN;
            }
            else
            {
                newN->next = p->next;
                p->next = newN;
            }
        }
    }
    m->size++;
}

//-----------------------------------------------------------------------------------------------------------------(Adicionando Nó na fila já ordenando)

//-----------------------------------------------------------------------------------------------------------------(Imprimir a lista / Verificação de leitura)

void print_lista (Node *p)
{
    if (p!=NULL)
    {
        printf ("%d\t%d\n", p->letra, p->frequencia);
        print_lista (p->next);
    }
    return;
}

//-----------------------------------------------------------------------------------------------------------------(Imprimir a lista / Verificação de leitura)

//-----------------------------------------------------------------------------------------------------------------(Retira o nó da fila)

Node* retirar (Manager *Fila)
{
    Node *retirado;

    retirado = Fila->first;
    Fila->first = Fila->first->next;
    Fila->size--;

    return retirado;
}

//-----------------------------------------------------------------------------------------------------------------(Retira o nó da fila)

//-----------------------------------------------------------------------------------------------------------------(Montar a árvore)

void Tree_Builder (Manager *Fila)
{
    Node *new;
    Node *filho1, *filho2;

    while(Fila->size > 1)
    {
        filho1 = retirar(Fila);
        filho1->next = NULL;
        filho2 = retirar(Fila);
        filho2->next = NULL;
        new = (Node*)malloc(sizeof(Node));
        new->letra = '*';
        new->next = NULL;
        new->frequencia = filho1->frequencia + filho2->frequencia;
        new->left = filho1;
        new->right = filho2;
        addnew(Fila, new);
    }

    return;
}

//-----------------------------------------------------------------------------------------------------------------(Montar a Árvore)

//-----------------------------------------------------------------------------------------------------------------(Contar a Árvore)

int treesize(Node *tree, int size)
{
    size++;
    if(tree->left != NULL && tree->right != NULL)
    {
        size = treesize(tree->left, size);
        size = treesize(tree->right, size);
    }

    else
    {
        if(tree->letra == '*' || tree->letra == '\\')
        {
            size++;
        }
    }

    return size;
}

//-----------------------------------------------------------------------------------------------------------------(Contar a Árvore)

//-----------------------------------------------------------------------------------------------------------------(Percorrer a árvore salvando o caminho)

void percorrer_arvore(int *codigo_binario, Node *tree, Hash *hash_de_binarios, int k)
{
    // o K tem que começar em 0 ao ser chamado na função.
    // código binário é o código que vai ser montado ao percorrer a árvore de forma recursiva.
    // tree é a árvore que contem a frequencia dos caracteres presentes no texto.
    // hash de binários é a hash onde será salva a nova sequencia binária de cada caractere do texto.
    if(tree->left == NULL && tree->right == NULL)  //Verificando se é folha
    {
        if (k == 0)
        {
            //
            hash_de_binarios->array[tree->letra]->codigo_final[0] = 0;
            hash_de_binarios->array[tree->letra]->codigo_final[1] = -1;
        }
        else
        {
            copiar_codigo (hash_de_binarios->array[tree->letra]->codigo_final, codigo_binario, k);
            //salvando a nova combinação binária na hash, na posição do caractere que está na folha
        }
        return;
    }
    else
    {
        if(tree->left != NULL) // só por segurança colocamos essa verificação
        {
            codigo_binario[k] = 0;
            percorrer_arvore(codigo_binario, tree->left, hash_de_binarios, k+1);
        }
        if(tree->right != NULL)  // só por segurança colocamos essa verificação
        {
            codigo_binario[k] = 1;
            percorrer_arvore(codigo_binario, tree->right, hash_de_binarios, k+1);
        }
        return;
    }
}

//-----------------------------------------------------------------------------------------------------------------(Percorrer a árvore salvando o caminho)

//-----------------------------------------------------------------------------------------------------------------(Imprimir em pré ordem)

void compress_print_pre_order(Node *tree,  FILE *out)
{
    fseek(out , 0 , SEEK_END);

    if(tree->left == NULL && tree->right == NULL)
    {
        if(tree->letra == '*' || tree->letra == '\\')
        {
            fprintf(out , "%c" , '\\');
        }
    }

    fprintf(out ,"%c", tree->letra);

    if(tree->left != NULL)
    {
        compress_print_pre_order(tree->left,out);
    }

    if(tree->right != NULL)
    {
        compress_print_pre_order(tree->right,out);
    }
}

//-----------------------------------------------------------------------------------------------------------------(Imprimir em pré ordem)

int compress_set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}


int newbites(FILE *in, FILE *out, Hash *bits)
{

    fseek(in , 0 , SEEK_SET);
    fseek(out , 0 , SEEK_END);
    unsigned char mask = 0;
    unsigned int current_char;
    int size_mask = 7, i;

    while((current_char = getc(in)) != EOF)//pega o char da entrada
    {

        for(i = 0; bits->array[current_char]->codigo_final[i] != -1; size_mask-- , i++) // tranfere o novo bit correspondente pra mask
        {
            //printf("%d", bits->array[current_char]->codigo_final[i]);
            if(size_mask < 0)// se mask ficar completa print no arquivo, e reseta o size da mask
            {
                fprintf(out , "%c", mask);
                size_mask = 7;
            }

            mask = mask << 1;

            if(bits->array[current_char]->codigo_final[i] == 1)// vai setando na mask os bit ver a função no slide do marcio mas acho que tem no meu code de decompress
            {
                mask = compress_set_bit(mask,0);
            }
        }
        //printf("\n");
    }

    if(size_mask != 7)// caso ele não complete o bit tem q printar o bite com o lixo
    {
        mask = mask << size_mask+1;
        fprintf(out , "%c", mask);
        return size_mask+1;
    }
    else
    {
        return 0;
    }

}

void  set_trash(FILE *out, int size)
{
    fseek(out , 0 , SEEK_SET);
    unsigned char mask = fgetc(out);

    if(size >= 4)
    {
        mask = compress_set_bit(mask,7);
    }

    if(size  == 2 ||  size  == 3 ||  size  == 6 ||  size  == 7)
    {
        mask = compress_set_bit(mask,6);
    }

    if(size%2)
    {
        mask = compress_set_bit(mask,5);
    }


    fseek(out , 0 , SEEK_SET);
        fprintf(out, "%c", mask);

}

void compress(FILE *fp, Node *tree, int tsize, Hash *hash)
{
    FILE *file_compress;

    file_compress = fopen("compr.huff","wb+");

    if(tsize <= 255)
    {
        fprintf(file_compress, "%c%c", 0, tsize);
    }

    else
    {
        fprintf(file_compress, "%c%c", (tsize-255), tsize);
    }

    compress_print_pre_order(tree,file_compress);

    int trash = newbites(fp,file_compress,hash);

    set_trash(file_compress,trash);

    fclose(fp);
    fclose(file_compress);
  }


//-----------------------------------------------------------------------------------------------------------------(Main)

int start_compress()
{
    Hash *ht;
    ht = begin_hash();
    // Criando e alocando a Hash
    Manager *m;
    m = begin_fila();
    // Criando e alocando a Lista
    FILE *fp;
    // Criando ponteiro pra um arquivo
    fp = fopen("exit_file.txt", "rb");
    // Abrindo arquivo
    unsigned int c;
    // Variável para ler cada caracterer presente no texto
    int contador_de_caracteres[256]={0};
    // Array com todas posições na tabela ASCII para contar a frequência
    while ((c = getc(fp)) != EOF)
    {
        contador_de_caracteres[c]++;
        alocar_posicao_hash (ht, c);
    }
    //----------------------------------------------------------//
    int i;
    // Variável para for
    for (i=0; i<256; i++)
    {
        if (contador_de_caracteres[i] != 0)
        {
            addnode (m, i, contador_de_caracteres[i]);
        }
    }
    Tree_Builder(m);
    m->size = treesize(m->first,0);
    //----------------------------------------------------------//
    int codigo_binario[40]={0};
    // um array que vai salvar o código binario de cada caractere presente no texto

    percorrer_arvore(codigo_binario, m->first, ht, 0);

    compress(fp,m->first,m->size,ht);

    return 1;
}