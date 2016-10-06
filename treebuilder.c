#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------------------(Declarações)

typedef struct node Node;
typedef struct manager Manager;

typedef struct node2 Node2;
typedef struct hash Hash;

Manager* begin_fila ();

void addnode (Manager *m, char c, int f);

void addnew (Manager *m, Node *newN);

Node* retirar (Manager *Fila);

void Tree_Builder (Manager *Fila);

int treesize(Node *tree, int size);

void print_pre_order(Node *tree);

//-----------------------------------------------------------------------------------------------------------------(Declarações)

//-----------------------------------------------------------------------------------------------------------------(Typedefs da árvore)

struct node
{
    char letra;
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

//-----------------------------------------------------------------------------------------------------------------(Typedefs da árvore)

//-----------------------------------------------------------------------------------------------------------------(Typedefs da Hash)

struct node2
{
    int codigo_final[40];
};

struct hash
{
    Node2 *array[256];
};

//-----------------------------------------------------------------------------------------------------------------(Typedefs da Hash)

//-----------------------------------------------------------------------------------------------------------------(Alocando a Fila)

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

void alocar_posicao_hash (Hash *ht, int id)
{
    if (ht->array[id]==NULL)
    {
        Node2 *p = (Node2*) malloc (sizeof (Node2));
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

void addnode (Manager *m, char c, int f)
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
    return;
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
    return;
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

//-----------------------------------------------------------------------------------------------------------------(Imprimir em pré ordem)

//-----------------------------------------------------------------------------------------------------------------(Main)

int main ()
{
    Hash *ht;
    ht = begin_hash();
    // Criando e alocando a Hash
    Manager *m;
    m = begin_fila();
    // Criando e alocando a Lista
    FILE *fp;
    // Criando ponteiro pra um arquivo
    fp = fopen("arquivo_de_entrada.txt", "r");
    // Abrindo arquivo
    char c;
    // Variável para ler cada caracterer presente no texto
    int i;
    // Variável para for
    int contador_de_caracteres[256]={0};
    // Array com todas posições na tabela ASCII para contar a frequência
    while ((c = fgetc(fp)) != EOF)
    {
        contador_de_caracteres[c]++;
        alocar_posicao_hash (ht, c);
    }
    //----------------------------------------------------------//
    for (i=0; i<256; i++)
    {
        if (contador_de_caracteres[i]!=0)
        {
            addnode (m, (char)i, contador_de_caracteres[i]);
        }
    }
    Tree_Builder(m);
    print_pre_order(m->first);
    m->size = treesize(m->first,0);
    //----------------------------------------------------------//
    int codigo_binario[40]={0};
    // um array que vai salvar o código binario de cada caractere presente no texto
    percorrer_arvore(codigo_binario, m->first, ht, 0);
    //-----------------------------------------------------------//
    /*  int i2;
    printf("\n");
    for (i=0; i<256; i++)
    {
        if(ht->array[i] != NULL)
        {
            printf ("%c  ", i);
            for (i2=0; ht->array[i]->codigo_final[i2] != -1; i2++)
            {
                printf("%d", ht->array[i]->codigo_final[i2]);
            }
            printf("\n");
        }
    }  */
    //-----------------------------------------------------------//
    fclose (fp);
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------(Main)
