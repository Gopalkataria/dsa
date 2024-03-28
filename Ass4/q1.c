#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define lint long long int 

struct ststation
{
    lint depth;
    lint time;
};

typedef struct ststation Station;

struct stminHeap
{
    lint size;
    Station **stations; 
};

typedef struct stminHeap *Heap;

Heap createHeap(lint size)
{
    Heap h = (Heap)malloc(sizeof(struct stminHeap));
    h->stations = (Station **)malloc(size * sizeof(Station *));
    h->size = 0;
    return h;
}

void swap(Station **a, Station **b)
{ 
    Station *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap h, lint i)
{
    lint smallest = i;
    lint left = 2 * i + 1;
    lint right = 2 * i + 2;

    if (left < h->size && h->stations[left]->time < h->stations[smallest]->time)
    {
        smallest = left;
    }

    if (right < h->size && h->stations[right]->time < h->stations[smallest]->time)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&h->stations[i], &h->stations[smallest]);
        heapify(h, smallest);
    }
}

Station *removeMin(Heap h)
{
    if (h->size == 0)
        return NULL;
    Station *min = h->stations[0];
    h->size--;
    h->stations[0] = h->stations[h->size];
    heapify(h, 0);
    return min;
}

void insertStation(Heap h, Station *S)
{
    h->stations[h->size] = S;
    lint i = h->size;
    h->size++;
    while (i > 0 && h->stations[i]->time < h->stations[(i - 1) / 2]->time)
    {
        swap(&h->stations[i], &h->stations[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int cmpdepth(const void *a, const void *b)
{
    const Station *stationA = *(const Station **)a;
    const Station *stationB = *(const Station **)b;
    return stationA->depth - stationB->depth;
}

int main()
{
    int nstations, initoxy, finaldep, refilldepth;

    scanf("%d %d %d %d", &nstations, &initoxy, &finaldep, &refilldepth);

    Station **stations = (Station **)malloc(nstations * sizeof(Station *));
    for (lint i = 0; i < nstations; i++)
    {
        stations[i] = (Station *)malloc(sizeof(Station));
        scanf("%lld", &stations[i]->depth);
    }

    for (lint i = 0; i < nstations; i++)
    {
        scanf("%lld", &stations[i]->time);
    }

    qsort(stations, nstations, sizeof(Station *), cmpdepth);

    // Debug
    // for (lint i = 0; i < nstations; i++)
    // {
    //     printf("%d %d\n", stations[i]->depth, stations[i]->time);
    // }

    Heap h = createHeap(nstations);

    lint currdepth = initoxy;
    lint time = 0;
    lint refills = 0;

    while (currdepth < finaldep)
    {
        // printf("current depth %d  , time %d \n ", currdepth, time);
        while (refills < nstations && stations[refills]->depth <= currdepth)
        {
            insertStation(h, stations[refills]);
            
            refills++;
        }

        if (h->size == 0)
        {
            printf("-1 %lld", currdepth);
            return 0;
        }

        Station *min = removeMin(h);
        time += min->time;
        currdepth += refilldepth;
        
    }

    printf("%lld", time);

    return 0;
}
