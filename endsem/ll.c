#include <stdio.h>
#include <stdlib.h>

typedef struct Person
{
    char name[100];
    int age;
} Person;

typedef struct Node
{
    Person data;
    struct Node *next;
} Node;

typedef Node *LinkedList;

LinkedList mergell(LinkedList A, LinkedList B)
{
    LinkedList H, C;
    if (A == NULL || B == NULL)
    {
        return ((A == NULL) ? B : A);
    }
    if (A->data.age > B->data.age)
    {
        H = C = B;
        B = B->next;
    }
    else
    {
        H = C = A;
        A = A->next;
    }
    while (A != NULL && B != NULL)
    {
        if (A->data.age <= B->data.age)
        {
            C->next = A;
            A = A->next;
        }
        else
        {
            C->next = B;
            B = B->next;
        }
        C = C->next;
    }
    if (A != NULL)
    {
        C->next = A;
    }
    else if (B != NULL)
    {
        C->next = B;
    }
    return H;
}

LinkedList Mergesortll(LinkedList L)
{
    LinkedList q[100];
    int front = 0, back = -1, size = 0;
    LinkedList temp = L;
    while (temp != NULL)
    {
        q[++back] = temp;
        temp = temp->next;
        q[back]->next = NULL ; 
        size++;
    }
    while (size > 1)
    {
        LinkedList A = q[front++];
        LinkedList B = q[front++];
        LinkedList merged = mergell(A, B);
        q[++back] = merged;
        size--;
    }
    return q[front];
}

int sizeofLinkedList(LinkedList l)
{
    int count = 0;
    while (l != NULL)
    {
        count++;
        l = l->next;
    }
}
LinkedList concatlinkedlist(LinkedList l1, LinkedList l2)
{
    if (l1 == NULL)
    {
        return l2;
    }
    if (l2 == NULL)
    {
        return l1;
    }
    LinkedList l = (LinkedList)malloc(sizeof(Node));
    l->data = l1->data;
    l->next = concatlinkedlist(l1->next, l2);
    if (l->next == NULL)
    {
        l->next = (LinkedList)malloc(sizeof(Node));
        l->next->data = l2->data;
        l->next->next = NULL;
    }
    return l;
}
LinkedList insertAtPosLinkedList(LinkedList l, int pos, Person p)
{
    if (pos < 0 || pos > sizeofLinkedList(l))
        return l;
    LinkedList newnode = (LinkedList)malloc(sizeof(Node));
    newnode->data = p;
    newnode->next = NULL;
    if (pos == 0)
    {
        newnode->next = l;
        return newnode;
    }
    if (pos == 1)
    {
        newnode->next = l->next;
        l->next = newnode;
        return l;
    }
    l->next = insertAtPosLinkedList(l->next, pos - 1, p);
    return l;
}

LinkedList insertoLinkedList(LinkedList l, Person p)
{
    LinkedList newnode = (LinkedList)malloc(sizeof(Node));
    newnode->data = p;
    newnode->next = NULL;
    if (l == NULL)
    {
        return newnode;
    }
    LinkedList temp = l;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    return l;
}

LinkedList reverselinkedlist(LinkedList l)
{
    LinkedList prev = NULL, cur = l, next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

void free_linked_list(LinkedList l)
{
    if (l == NULL)
    {
        return;
    }
    free_linked_list(l->next);
    free(l);
}

LinkedList rever_in_place(LinkedList l)
{
    if (l == NULL || l->next == NULL)
    {
        return l;
    }
    LinkedList rest = rever_in_place(l->next);
    l->next->next = l;
    l->next = NULL;
    return rest;
}

int main()
{

    // Construct a linked list with random dummy values
    LinkedList list = NULL;
    int numNodes = 15; // Number of nodes in the linked list

    // Generate random dummy values and insert them into the linked list
    for (int i = 0; i < numNodes; i++)
    {
        Person p;
        sprintf(p.name, "Person %d", i);
        p.age = rand() % 100; // Random age between 0 and 99

        list = insertoLinkedList(list, p);
    }

    // Print the linked list
    LinkedList temp = list;
    // while (temp != NULL)
    // {
    //     printf("Name: %s, Age: %d\n", temp->data.name, temp->data.age);
    //     temp = temp->next;
    // }
    list = Mergesortll(list);
    temp = list;
    while (temp != NULL)
    {
        printf("Name: %s, Age: %d\n", temp->data.name, temp->data.age);
        temp = temp->next;
    }

    return 0;
}