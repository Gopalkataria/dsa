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

void printTree(Tree T, int n)
{
    if (T == NULL)
    {
        return;
    }
    printf(" %d %d\n", n, T->phone);
    printTree(T->left, n + 1);
    printTree(T->right, n + 1);
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

Node *createNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->phone = -1;
    return node;
}

int main()
{

    int n;
    scanf("%d", &n);
    n--;

    Tree tree = createNode();
    Queue q;
    q.front = NULL;
    q.rear = NULL;

    enqueue(&q, tree);
    int m = 0;
    scanf("%d", &m);

    while (n)
    {

        Node *currNode = dequeue(&q);
        // scan left
        scanf("%d", &m);
        if (m)
        {
            currNode->left = createNode();
            currNode->left->phone = n - 1;
            enqueue(&q, currNode->left);
        }
        // printTree(tree, 0);

        // scan right
        scanf("%d", &m);
        if (m)
        {
            currNode->right = createNode();
            enqueue(&q, currNode->right);
            currNode->right->phone = -1 * (n - 2);
        }
        // printTree(tree, 0);

        n -= 2;
    }

    printTree(tree, 0);

    printf("\nmeow\n");
    return 0;
}