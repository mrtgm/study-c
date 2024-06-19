#include <stdio.h>
#include <stdlib.h>

typedef int d_t;

struct vec
{
    d_t *data;
    int capacity;
    int size;
};

struct vec vecNew(int size)
{
    struct vec v;
    v.data = malloc(sizeof(d_t) * size);
    v.capacity = size;
    v.size = size;
    return v;
}

void vecDelete(struct vec *v)
{
    free(v->data);
}

int vecGet(struct vec *v, int i)
{
    return v->data[i];
}

void vecSet(struct vec *v, int i, d_t x)
{
    v->data[i] = x;
}

void vecGrow(struct vec *v)
{
    if (!v->size)
    {
        v->data = malloc(sizeof(d_t));
        v->capacity = 1;
    }
    else
    {
        d_t *data = realloc(v->data, sizeof(d_t) * v->size * 2); // realloc はメモリの再割当を行う
        v->data = data;
        v->capacity = v->size * 2;
    }
}

void vecPush(struct vec *v, d_t x)
{
    if (v->size == v->capacity)
    {
        vecGrow(v);
    }
    v->data[v->size] = x;
    v->size++;
}

void vecPop(struct vec *v, d_t *popped)
{
    if (!v->size)
        return;
    v->size--;
    *popped = v->data[v->size];
}

void vecSize(struct vec *v)
{
    printf("%d\n", v->size);
}

void vecCapacity(struct vec *v)
{
    printf("%d\n", v->capacity);
}

void vecPrint(struct vec *v)
{
    for (int i = 0; i < v->size; i++)
    {
        printf("%d,", v->data[i]);
    }
    printf("\n");
}

int main()
{
    struct vec v = vecNew(0);
    vecPush(&v, 1);
    vecPrint(&v);
    vecCapacity(&v);
    vecPush(&v, 2);
    vecPrint(&v);
    vecCapacity(&v);
    vecPush(&v, 3);
    vecPrint(&v);
    vecCapacity(&v);
    vecPush(&v, 4);
    vecPrint(&v);
    vecCapacity(&v);
    vecPush(&v, 5);
    vecPrint(&v);
    vecCapacity(&v);

    return 0;
}
