#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define lint long long int

typedef struct node
{
    lint data;
    struct node *next;
} node;

typedef struct graphnode
{
    node *connections;
    node *lastconnection;
    lint nconnections;
} graphnode;

graphnode *graph;
bool *visited;

void dfs(int i)
{
    visited[i] = true;
    for (node *a = graph[i].connections; a != NULL; a = a->next)
        if (!visited[a->data])
            dfs(a->data);
}

void addtographnode(graphnode *gn, lint n)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = n;
    newnode->next = NULL;
    if (gn->lastconnection == NULL)
        gn->connections = newnode;
    else
        gn->lastconnection->next = newnode;
    gn->lastconnection = newnode;
    gn->nconnections++;
}

void connect(lint a, lint b)
{
    addtographnode(graph + a, b);
    addtographnode(graph + b, a);
}

int main()
{
    lint n, q, a, b;
    scanf("%lld %lld", &n, &q);
    graph = (graphnode *)calloc(n + 1, sizeof(graphnode));

    while (q--)
    {
        scanf("%lld %lld", &a, &b);
        connect(a, b);
    }

    visited = (bool *)calloc(n + 1, sizeof(bool));
    lint count = 0 ;
    lint sentinent[n + 1];
    for (int i = 1; i <= n; i++)
        if (!visited[i])
        {
            sentinent[count++] = i;
            dfs(i);
        }

    printf("%lld\n", count - 1);

    for (lint i = 0; i < count - 1; i++)
        printf("%lld %lld\n", sentinent[i], sentinent[i + 1]);

    return 0;
}