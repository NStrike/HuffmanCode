#include <List_and_Tree.h>

//----------------------------------------------------------------------------------------------------------------- (TYPEDEFS)

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
    int treesize;
};

Manager* begin_fila ()
{
    Manager *newM = (Manager*) malloc (sizeof(Manager));
    newM->first = NULL;
    newM->treesize = 0;
    newM->size = 0;
    return newM;
}

//----------------------------------------------------------------------------------------------------------------- (ADICIONAR NÓS)

void addnode (Manager *m, char c, int f)
{
    Node *newN = (Node*) malloc (sizeof(Node));
    m->size++;
    newN->letra = c;
    newN->frequencia = f;
    newN->left = NULL;
    newN->right = NULL;
    if (m->first==NULL)
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

//----------------------------------------------------------------------------------------------------------------- (ADICIONAR NÓ COM A SOMA JÁ ORDENANDO)

void addnew (Manager *m, Node *newN)
{ 
    if (m->first==NULL)
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

//----------------------------------------------------------------------------------------------------------------- (IMPRIMIR A LISTA / VERIFICAÇÃO DE LEITURA)

void print_lista (Node *p)
{
    if (p!=NULL)
    {
        printf ("%d\t%d\n", p->letra, p->frequencia);
        print_lista (p->next);
    }
    return;
}

//----------------------------------------------------------------------------------------------------------------- (RETIRAR NÓ PARA SOMAR E MONTAR UM SÓ)

Node* retirar (Manager *Fila)
{
	Node *retirado;

	retirado = Fila->first;
	Fila->first = Fila->first->next;
	Fila->size--;

	return retirado;
}

//----------------------------------------------------------------------------------------------------------------- (MONTAR A ARVORE)

void Tree_Builder (Manager *Fila)
{
	Node *new;
	Node *filho1, *filho2;

	while(Fila->size > 1)
	{
		filho1 = retirar(Fila);
		filho2 = retirar(Fila);
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

//----------------------------------------------------------------------------------------------------------------- (CONTAR A ARVORE)

int treesize(Node *tree, int size)
{
	size++;

	if(tree->left != NULL)
	{
		size = treesize(tree->left, size);
	}

	if(tree->right != NULL)
	{
		size = treesize(tree->right, size);
	}

	return size;
}

//----------------------------------------------------------------------------------------------------------------- (IMPRIMIR EM PRÉ ORDEM)

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

//-----------------------------------------------------------------------------------------------------------------

int main ()
{
    Manager *m; 
    m = begin_fila();
    FILE *fp;
    fp = fopen("arquivo_de_entrada.txt", "r");
    char c;
    int i;	
    int contador_de_caracteres[256]={0};
    while ((c =fgetc(fp)) != EOF)
    {	
        contador_de_caracteres[c]++;
    }
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
    printf("\n");
    fclose (fp);
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------