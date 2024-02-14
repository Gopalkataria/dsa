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

Queue Gque;
int N;
int DBG;

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
int countPhones(Tree tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return countPhones(tree->left) + countPhones(tree->right) + tree->phone;
}

typedef struct hc
{
    int h;
    int c;
} hc;

hc *happyAndCountPhones(Tree tree)
{
    hc *ans = (hc *)malloc(sizeof(hc));

    if (tree == NULL)
    {
        ans->h = 1;
        ans->c = 0;
        return ans;
    }
    hc *lh = happyAndCountPhones(tree->left);
    hc *rh = happyAndCountPhones(tree->right);

    ans->c = lh->c + rh->c + tree->phone;
    ans->h = lh->h && rh->h && happyNode(tree);
    free(lh);
    free(rh);

    return ans;
}

void dbgTree(int H)
{
    if (DBG)
    {
        return;
    }

    printTree(T, 0);
    if (H)
    {
        printf("--------H-----\n");
    }
    else
    {

        printf("----------------\n");
    }
}

void updates()
{
    hc *ans = happyAndCountPhones(T);
    if (ans->h)
    {
        int x = ans->c;
        if (x < count || count == -1)
        {
            dbgTree(1);
            count = x;
        }
    }
    else
    {
        dbgTree(0);
    }
    free(ans);
}

int allperms(Node *Q, int lim)
{

    if (Q == NULL)
    {
        updates();
        return 0;
    }

    if ((Q->left != NULL || Q->right != NULL) && lim > 0)
    {

        Q->phone = 1;
        allperms(Q->next, lim - 1);
        Q->phone = 0;
        allperms(Q->next, lim);
    }
    else
    {
        allperms(Q->next, lim);
    }

    return count;
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
            tree->phone = 1 ; 
    }
}

int findMinPhones(Tree tree)
{
    int m, n, p, k;
    if (tree == NULL)
    {
        return 0;
    }

    processLeaves(tree);
    return countPhones(tree);

    return k;
}

int main()
{

    // int tests ;
    // scanf("%d", &tests) ;

    // while (tests--)
    // {

    int n;
    scanf("%d", &n);
    N = n;
    n--;
    count = -1;
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
            enqueue(&Gque, node->left);
        }
        if (n == 0)
            break;
        n--;
        scanf("%d", &r);
        if (r)
        {
            node->right = createNode(node);
            enqueue(&q, node->right);
            enqueue(&Gque, node->right);
        }
        if (n == 0)
            break;
    }

    int ans = 0, ans2 = 0;
    DBG = 1;
    dbgTree(0);
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
        ans2 = findMinPhones(tree);
        printf("%d", ans2);
    }

    // scanf("%d", &n);

    // printf("ans : %d  ;", ans2 ) ;
    // printf("findmin : %d \n %s \n  ", ans2 , ans2 == n ? "pass" : "fail");
    // printf("all perms : %d : %s ; ", ans , ans == n ? "pass" : "fail");
    // printf("equal ? :  %s \n %s \n",  ans2 == ans ? "pass" : "fail" , (ans2 == ans && ans == n ) ? "PASS" : "FAIL");
    // }
    return 0;
}