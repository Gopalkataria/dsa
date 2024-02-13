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
    return; // dbg
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
int count = -1;

int happyNode(Node *N)
{
    if (N == NULL)
    {
        return 1;
    }
    if (N->phone || (N->left != NULL && N->left->phone) || (N->right != NULL && N->right->phone) || (N->parent != NULL && N->parent->phone))
    {
        return 1;
    }
    return 0;
}

int happyTree(Tree tree)
{
    if (tree == NULL)
    {
        return 1;
    }
    return happyTree(tree->left) && happyTree(tree->right) && happyNode(tree);
}

void dbgTree()
{
    if (happyTree(T))
    {
        // printTree(T, 0);
        // printf("----------------\n");
    }
}

int countPhones(Tree tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return countPhones(tree->left) + countPhones(tree->right) + tree->phone;
}

void updates()
{
    if (happyTree(T))
    {
        dbgTree();
        int x = countPhones(T);
        if (x < count || count == -1)
        {
            count = x;
        }
    }
}

int allperms( Node * Q)
{
    if (Q == NULL)
    {
        updates();
        return 0;
    }
    

    Q->phone = 1 ; 
    allperms(Q->next);
    Q->phone = 0 ;
    allperms(Q->next);    

    return count;
}

Queue Gque ; 

int main()
{

    int n;
    scanf("%d", &n);
    n--;

    Tree tree = createNode(NULL);
    T = tree;
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    Gque.front = NULL;
    Gque.rear = NULL;

    enqueue(&q, tree);
    enqueue(&Gque, tree);
    int m = 0;
    scanf("%d", &m);

    while (n)
    {
        Node *node = dequeue(&q);
        int l, r;
        scanf("%d %d", &l, &r);
        if (l)
        {
            node->left = createNode(node);
            enqueue(&q, node->left);
            enqueue(&Gque, node->left);
        }
        if (r)
        {
            node->right = createNode(node);
            enqueue(&q, node->right);
            enqueue(&Gque, node->right);
        }
        n -= 2;
    }

    int ans = allperms(tree);
    printTree(tree, 0);
    printf("%d", ans);
    // print corr ans
    // scanf("%d", &n);
    // printf("\n%d", n);
    return 0;
}