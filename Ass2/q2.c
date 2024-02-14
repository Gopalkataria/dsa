#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    int phone;
    struct Node *left;
    struct Node *right;
    struct Node *next;
    struct Node *parent;
} Node;

typedef Node *Tree;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

int N;

void enqueue(Queue *q, Node *node)
{
    if (q->front == NULL)
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
}

// function to print a tree in a human readable format
void printTree(Tree tree, int level)
{
    // return; // dbg
    if (tree == NULL)
    {
        return;
    }

    printTree(tree->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("%d\n", tree->phone);
    printTree(tree->left, level + 1);
}

Node *dequeue(Queue *q)
{

    if (q->front == q->rear)
    {
        Node *r = q->front;
        q->front = NULL;
        q->rear = NULL;
        return r;
    }

    Node *r = q->front;
    q->front = q->front->next;
    return r;
}

Node *createNode(Node *parent)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->phone = 0;
    return node;
}

Tree T;

int happyNode(Node *N)
{
    if (N == NULL)
        return 1;

    if (N->phone || (N->left != NULL && N->left->phone) || (N->right != NULL && N->right->phone) || (N->parent != NULL && N->parent->phone))
        return 1;

    return 0;
}
int countPhones(Tree tree)
{
    if (tree == NULL)
        return 0;
    return countPhones(tree->left) + countPhones(tree->right) + tree->phone;
}

void processLeaves(Tree tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL || tree->right != NULL)
    {
        processLeaves(tree->left);
        processLeaves(tree->right);
    }
    else
    {
        if (tree->parent != NULL)
        {
            tree->parent->phone = 1;
        }
    }
    if (happyNode(tree))
    {
        return;
    }
    else
    {
        if (tree->parent != NULL)
            tree->parent->phone = 1;
        else
            tree->phone = 1;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    N = n;
    n--;
    Tree tree = createNode(NULL);
    T = tree;
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    int l, r;

    enqueue(&q, tree);
    int m = 0;
    scanf("%d", &m);

    while (1)
    {
        Node *node = dequeue(&q);
        n--;
        scanf("%d", &l);
        if (l)
        {
            node->left = createNode(node);
            enqueue(&q, node->left);
        }
        if (n == 0)
            break;
        n--;
        scanf("%d", &r);
        if (r)
        {
            node->right = createNode(node);
            enqueue(&q, node->right);
        }
        if (n == 0)
            break;
    }

    scanf("%d %d", &l, &r);

    int ans;
    if (N == 0)
    {
        printf("0");
        ans = 0;
    }
    else if (N <= 3)
    {
        ans = 1;
        printf("1");
    }
    else
    {

        processLeaves(tree);
        ans = countPhones(tree);

        printf("%d", ans);
    }

    if (ans == 0)
    {
        printf("\n0");
    }

    // ans = 100000;
    int primes[ans];
    primes[0] = 2;
    int i = 1;
    int j = 3;
    while (i < ans)
    {
        int ispm = 1;

        if (j > 3)
        {
            if ((j % 2 == 0) || (j % 3 == 0))
            {
                ispm = 0;
            }
            else
            {
                for (int k = 5; k < sqrt(j) + 1; k += 6)
                    if ((j % k == 0) || (j % (k + 2) == 0))
                    {
                        ispm = 0;
                        break;
                    }
            }
        }
        if (ispm)
        {
            primes[i] = j;
            i++;
        }
        j += 2;
    }
    // for (int i = 0; i < ans; i++)
    // {
    //     printf(" %d", primes[i]);
    // }

    int count = 0;

    for (i = 0; i < ans - 1; i++)
    {
        for (int j = i + 1; j < ans; j++)
        {
            count += ((primes[i] ^ primes[j]) > r) || ((primes[i] ^ primes[j]) < l);
        }
    }

    printf("\n%d", count);

    return 0;
}
