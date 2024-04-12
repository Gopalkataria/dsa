#include <stdio.h>
#include <stdlib.h>

struct stheap
{
    int size;
    int capacity;
    int *data;
};

typedef struct stheap *Heap;

Heap createHeap(int capacity)
{
    Heap h = (Heap)malloc(sizeof(struct stheap));
    h->size = 0;
    h->capacity = capacity;
    h->data = (int *)malloc(capacity * sizeof(int));
    return h;
}

void insert(Heap h, int val)
{
    if (h->size == h->capacity)
    {
        return;
    }
    h->data[h->size] = val;
    h->size++;
    int i = h->size - 1;
    while (i > 0 && h->data[i] < h->data[(i - 1) / 2])
    {
        int temp = h->data[i];
        h->data[i] = h->data[(i - 1) / 2];
        h->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void heapifydown(Heap h, int n, int ind)
{
    int min = ind;
    int l = 2 * ind + 1;
    int r = 2 * ind + 2;
    if (l < n && h->data[l] < h->data[min])
    {
        min = l;
    }
    if (r < n && h->data[r] < h->data[min])
    {
        min = r;
    }
    if (min != ind)
    {
        int temp = h->data[ind];
        h->data[ind] = h->data[min];
        h->data[min] = temp;
        heapifydown(h, n, min);
    }
}

int deleteMin(Heap h)
{
    int res = h->data[0];
    h->data[0] = h->data[h->size - 1];
    int i = 0;
    heapifydown(h, h->size, i);
    h->size--;
    return res;
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

Heap arrtoheap(int *arr, int size)
{
    Heap h = createHeap(size * 2);
    qsort(arr, size, sizeof(int), cmp);

    for (int i = 0; i < size; i++)
    {
        h->data[i] = arr[i];
    }
    h->size = size;
    return h;
}

int *kthSmallestPrimeFraction(int *arr, int arrSize, int k, int *returnSize)
{

    Heap heap = arrtoheap(arr, arrSize);

    for (int i = 0; i < k - 1; i++)
    {
        int numerator = heap->data[0];
        deleteMin(heap);

        for (int j = 1; j < arrSize; j++)
        {
            insert(heap, numerator * arr[j]);
            if (numerator % arr[j] == 0)
                break;
        }
    }

    int *answer = (int *)malloc(2 * sizeof(int));
    answer[0] = heap->data[0];
    answer[1] = heap->data[1];
    *returnSize = 2;
    return answer;
}

int main()
{
    int arr[] = {1, 2, 3, 5, 7, 11};
    int k = 3;
    int returnSize;
    int *result = kthSmallestPrimeFraction(arr, 6, k, &returnSize);

    printf("The %dth smallest fraction is: [%d, %d]\n", k, result[0], result[1]);

    free(result);
    return 0;
}