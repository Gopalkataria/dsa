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

// function to print a tree in a human readable format
void printTree(Tree tree, int level)
{
    return ; 
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

int findMinPhones(Tree tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    if ((tree->parent != NULL && tree->parent->phone) || (tree->left != NULL && tree->left->phone) || (tree->right != NULL && tree->right->phone))
    {
        return findMinPhones(tree->left) + findMinPhones(tree->right);
    }

    tree->phone = 1;
    int k, m;
    k = findMinPhones(tree->left) + findMinPhones(tree->right) + 1;

    // if (tree->left != NULL)
    // {
    //     tree->left->phone = 1;
    //     m = findMinPhones(tree->left) + findMinPhones(tree->right) + 1;
    //     k = k < m ? k : m;
    //     tree->left->phone = 0;
    // }
    // if (tree->right != NULL)
    // {
    //     tree->right->phone = 1;
    //     m = findMinPhones(tree->left) + findMinPhones(tree->right) + 1;
    //     k = k < m ? k : m;
    //     tree->right->phone = 0;
    // }
    if (tree->right != NULL && tree->left != NULL)
    {
        tree->right->phone = 1;
        tree->left->phone = 1;
        m = findMinPhones(tree->left) + findMinPhones(tree->right) + 2;
        k = k < m ? k : m;
        tree->right->phone = 0;
        tree->left->phone = 0;
    }

    return k;
}

int main()
{

    int n;
    scanf("%d", &n);
    n--;

    Tree tree = createNode(NULL);
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
            currNode->left = createNode(currNode);
            enqueue(&q, currNode->left);
        }
        // printTree(tree, 0);

        // scan right
        scanf("%d", &m);
        if (m)
        {
            currNode->right = createNode(currNode);
            enqueue(&q, currNode->right);
        }
        // printTree(tree, 0);

        n -= 2;
    }

    int ans = findMinPhones(tree);
    printTree(tree, 0);
    printf("%d", ans);
    return 0;
}