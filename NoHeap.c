
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10000

// Dados da fila : nome e prioridade de cada elemento da fila.
typedef struct Element
{
	int id;
	int priority;

}element;

typedef struct Priority_queue
{
    int current_size;//quanto já usou do array.
    element data[MAX];

}pq;

pq* create()
{
	  pq *queue = (pq*) malloc(sizeof(pq));
    queue->current_size = 0;

    return queue;
}

int enqueue(pq *queue,int n,int p)
{
	int comparaes = 1;
   if(queue->current_size >=  MAX)
   {
   	  printf("Fila cheia!\n");
   }
   else
   {
   	  int i = queue->current_size-1;
   	  // O fim do array é o inicio da fila,então que tiver maior prioridade irá para o final do array
   	  while(i>=0 && queue->data[i].priority >= p)
   	  {
         queue->data[i+1] = queue->data[i];
         i--;
         comparaes++;
   	  }
      //copia nome e prioridade digitados na entrada para a struct element
   	  queue->data[i+1].id = n;
   	  queue->data[i+1].priority = p;
   	  queue->current_size++;
   }

   return comparaes;
}

void dequeue(pq *queue)
{
	if(queue->current_size == 0)
	{
		printf("Fila vazia!\n");
	}
	else
	{
		// como é um array e não tem como eliminar quem sair da fila,basta diminuir o  current_size a cada dequeue
		printf("Nome: %s - Prioridade: %d\n",queue->data[queue->current_size-1].id,queue->data[queue->current_size-1].priority);
		queue->current_size--;
	}
}

void swap (int *p, int *q)
{
    int x;
    x=*p;
    p[0]=*q;
    q[0]=x;
    //printf ("TROCOU: %d - %d\n\n", p[0], q[0]);
    return;
}
void quicksort(int *v, int size)
{
    if (size <= 1)
    {
        return;
    }
    else
    {
        int j=size/2;
        int pivot = v[j];
        int i;
        int w;
        int a = 0;
        int b = size - 1;

        while (a < b)
        {
            while (v[a] <= v[j] && a<j) a++;

            while (v[b] >= v[j] && b>j) b--;


            if (a < b && v[a]!=v[b])
            {
                if (a==j)   j=b;
                else if (b==j)   j=a;
                swap(&v[a], &v[b]);
            }
        }
        quicksort(v, b);
        quicksort(v+a, size - a);
    }
}


int main()
{
  FILE *out;
  out = fopen("NoHeap.txt","w");
  int i,p,counter, contador[1000];
  pq *queue = create();

    srand(time(NULL));

    for(counter = 0; counter < 1000; counter++)// vai receber uma string e sua respectiva prioridade. ex: tonho 10
    {
      contador[counter] = enqueue(queue,rand() % 1000,rand() % 1000);
    }

    quicksort(contador,1000);

    for(counter = 0; counter < 1000; counter++)
    {
    	i = contador[counter];
    	fprintf(out, "%d,", i);
    }

  fclose(out);
  return 0;
}
