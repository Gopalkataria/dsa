#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Quack;

void initializeQuack(Quack *quack)
{
    quack->front = quack->rear = NULL;
}

void pushFront(Quack *quack, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = quack->front;

    if (quack->front == NULL)
    {
        quack->front = quack->rear = newNode;
    }
    else
    {
        quack->front->prev = newNode;
        quack->front = newNode;
    }
}

void pushRear(Quack *quack, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = quack->rear;

    if (quack->rear == NULL)
    {
        quack->front = quack->rear = newNode;
    }
    else
    {
        quack->rear->next = newNode;
        quack->rear = newNode;
    }
}

int popFront(Quack *quack)
{
    if (quack->front == NULL)
    {
        printf("Quack is empty\n");
        return -1;
    }

    Node *frontNode = quack->front;
    int data = frontNode->data;

    quack->front = frontNode->next;
    if (quack->front == NULL)
    {
        quack->rear = NULL;
    }
    else
    {
        quack->front->prev = NULL;
    }

    free(frontNode);
    return data;
}

int popRear(Quack *quack)
{
    if (quack->rear == NULL)
    {
        printf("Quack is empty\n");
        return -1;
    }

    Node *rearNode = quack->rear;
    int data = rearNode->data;

    quack->rear = rearNode->prev;
    if (quack->rear == NULL)
    {
        quack->front = NULL;
    }
    else
    {
        quack->rear->next = NULL;
    }

    free(rearNode);
    return data;
}

void printQuack(Quack *quack)
{
    Node *current = quack->front;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    Quack quack;
    initializeQuack(&quack);

    pushFront(&quack, 1);
    pushRear(&quack, 2);
    pushFront(&quack, 3);
    pushRear(&quack , 69 ) ; 
    printf("Quack: ");
    printQuack(&quack);

    printf("Pop from front: %d\n", popFront(&quack));

    printf("Quack after popping from front: ");
    printQuack(&quack);

    printf("Pop from rear: %d\n", popRear(&quack));

    printf("Quack after popping from rear: ");
    printQuack(&quack);

    return 0;
}
