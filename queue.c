#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int n;
    struct Node *next;
} Node;

typedef struct queue
{
    Node *head;
    Node *tail;
    int len;
} queue;

void enqueue( queue * q , int n {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->n = n;
    newnode->next = NULL;

    if (q->tail == NULL)
    {
        q->tail = newnode;
        q->head = newnode;
    }
    else
    {
        q->tail->next = newnode;
        q->tail = newnode;
    }
    q->len ++ ; 

}

int dequeue 


int main() {

}