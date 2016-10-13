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

typedef struct Priority_queue_heap
{
    int current_size;//quanto já usou do array.
    element data[MAX];

}pqh;

pqh* create()
{
	pqh *queue = (pqh*) malloc(sizeof(pqh));
    queue->current_size = 0;

    return queue;
}

int get_parent_index(pqh *queue,int i)
{
	return i/2;
}
int get_left_index(pqh *queue,int i)
{
	return 2*i;
}
int get_right_index(pqh *queue,int i)
{
	return 2*i + 1;
}

int enqueue(pqh *queue,int n,int p)
{
	int comparaes = 1;
	if(queue->current_size >= MAX)
	{
		printf("Fila cheia!\n");
	}
	else
	{   queue->current_size++;
		queue->data[queue->current_size].id = n;
		queue->data[queue->current_size].priority = p;

		int key_index = queue->current_size;
		int parent_index = get_parent_index(queue,queue->current_size);

		while(parent_index >= 1 && queue->data[key_index].priority > queue->data[parent_index].priority)
		{
           element aux;
           aux = queue->data[parent_index];
           queue->data[parent_index] = queue->data[key_index];
           queue->data[key_index] = aux;

           key_index = parent_index;
           parent_index = get_parent_index(queue,key_index);
           comparaes++;
		}
	}

	return comparaes;
}

void max_heapify(pqh *queue,int i)
{
	int largest;
	int left_index = get_left_index(queue,i);
	int right_index = get_right_index(queue,i);

	if(left_index <= queue->current_size && queue->data[left_index].priority > queue->data[i].priority)
	{
		largest = left_index;
	}
	else
    {
    	largest = i;
    }

    if(right_index <= queue->current_size && queue->data[right_index].priority > queue->data[largest].priority )
    {
    	largest = right_index;
    }

    if(queue->data[i].priority != queue->data[largest].priority)
    {
    	element aux;
    	aux = queue->data[i];
    	queue->data[i] = queue->data[largest];
    	queue->data[largest]= aux;

    	max_heapify(queue,largest);
    }
}

void dequeue(pqh *queue)
{
	if(queue->current_size == 0)
	{
		printf("Fila de priridade com heap vazia!\n");
	}
	else
	{
	    queue->data[1] = queue->data[queue->current_size];
	    queue->current_size--;
	    max_heapify(queue,1);
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
  out = fopen("Heap.txt", "wb");
  int i,p,counter = 1000, contador[1001];
  pqh *queue = create();

  srand(time(NULL));

  while(counter)// vai receber uma string e sua respectiva prioridade. ex: tonho 10
  {
    contador[counter] = enqueue(queue,rand() % 1000,rand() % 1000);
    counter--;
  }

  quicksort(contador,1000);

  while(counter <= 1000)
  {
	 i = contador[counter];
	 fprintf(out, "%d,", i);
	 counter++;
  }

  fclose(out);
  return 0;
}
