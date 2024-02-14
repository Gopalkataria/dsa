#include <stdio.h>
#include <stdlib.h>

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

    if (N->phone \
    || (N->left != NULL && N->left->phone) \
    || (N->right != NULL && N->right->phone) \
    || (N->parent != NULL && N->parent->phone))
        return 1;

    return 0;
}
int countPhones(Tree tree)
{
    if (tree == NULL)
        return 0;
    return countPhones(tree->left) + countPhones(tree->right) \
    + tree->phone;
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

    enqueue(&q, tree);
    int m = 0;
    scanf("%d", &m);

    while (1)
    {
        Node *node = dequeue(&q);
        int l, r;
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

    if (N == 0)
    {
        printf("0");
    }
    else if (N <= 3)
    {
        printf("1");
    }
    else
    {

        processLeaves(tree);
        int ans = countPhones(tree);

        printf("%d", ans);
    }

    return 0;
}
