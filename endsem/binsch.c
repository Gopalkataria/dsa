#include <stdio.h>

int binsearch(int *arr, int size, int key)
{
    // assuming we return any valid index
    // if there are repeated entries
    int x = -1;
    for (int b = size / 2; b > 0; b /= 2)
        while (x + b < size && arr[x + b] <= key)
            x += b;
    if (arr[x] == key)
        return x;
    return -1;
}

struct node
{
    struct node *left;
    struct node *right;
    int val;
};

struct queue
{
    struct node **arr;
    int maxsize;
    int size;
};
struct queue *createqueue()
{
    struct queue *N = (struct queue *)malloc(sizeof(struct queue));
    N->arr = (struct node **)malloc(10000 * sizeof(struct node *));
    N->size = 0;
    return N;
}

void enqu(struct queue *Q, struct node *N)
{
    Q->size++;
    if (Q->size == Q->maxsize)
        return;
    Q->arr[Q->size - 1] = N;
}

struct node *deque(struct queue *Q)
{
    if (Q->size == 0)
    {
        return NULL;
    }
    return Q->arr[--Q->size];
}

void printleaves(struct node *head)
{
    if (head == NULL)
        return;
    if (head->left == NULL && head->right == NULL)
        printf("%d ", head->val);
    printleaves(head->left);
    printleaves(head->right);
}

void printleavesnonrec(struct node *head)
{

    struct queue *q = createqueue();
    if (head != NULL)
    {
        enqu(q, head);
    }
    else
    {
        return;
    }
    while (q->size > 0)
    {
        struct node *m = deque(q);
        if (m->left != NULL)
            enqu(q, m->left);
        if (m->right != NULL)
            enqu(q, m->right);

        if (m->left == NULL && m->right == NULL)
        {
            printf("%d ");
        }
    }
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};

    printf("%d %d\n", 5, binsearch(arr, 10, 5));
    printf("%d %d\n", 100, binsearch(arr, 10, 100));
    printf("%d %d\n", -1, binsearch(arr, 10, -1));
    for (int i = 0; i <= 10; i++)
    {

        printf("%d %d\n", i, binsearch(arr, 10, i));
    }

    return 0;
}
