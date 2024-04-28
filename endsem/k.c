#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct ListNode
{
    int dest;
    struct ListNode *next;
};

// Structure to represent the adjacency list of a vertex
struct AdjList
{
    struct ListNode *head;
};

// Structure to represent the graph
struct Graph
{
    int V;
    struct AdjList *array;
};

// Function to create a new adjacency list node
struct ListNode *newListNode(int dest)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest)
{
    struct ListNode *newNode = newListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Function to perform depth-first search on the graph
void DFS(struct Graph *graph, int v, bool visited[], int component[])
{
    visited[v] = true;
    component[v] = 1; // Mark vertex as part of current component
    struct ListNode *temp = graph->array[v].head;

    while (temp != NULL)
    {
        int adj = temp->dest;
        if (!visited[adj])
            DFS(graph, adj, visited, component);
        temp = temp->next;
    }
}

// Function to perform DFS in reverse graph to find SCC
void reverseDFS(struct Graph *graph, int v, bool visited[], int component[])
{
    visited[v] = true;
    struct ListNode *temp = graph->array[v].head;

    while (temp != NULL)
    {
        int adj = temp->dest;
        if (!visited[adj])
            reverseDFS(graph, adj, visited, component);
        temp = temp->next;
    }
}

// Function to print all strongly connected components
void printSCCs(struct Graph *graph)
{
    int V = graph->V;
    bool *visited = (bool *)malloc(V * sizeof(bool));
    int *component = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; ++i)
    {
        visited[i] = false;
        component[i] = 0; // Initialize all vertices as not visited and not part of any component
    }

    // First DFS to fill stack with vertices in increasing order of finish time
    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
            DFS(graph, i, visited, component);
    }

    // Reinitialize visited array for the second DFS
    for (int i = 0; i < V; ++i)
        visited[i] = false;

    // Reverse the graph
    struct Graph *reverseGraph = createGraph(V);
    for (int v = 0; v < V; v++)
    {
        struct ListNode *temp = graph->array[v].head;
        while (temp != NULL)
        {
            addEdge(reverseGraph, temp->dest, v);
            temp = temp->next;
        }
    }

    // Second DFS to find strongly connected components
    printf("Strongly Connected Components:\n");
    for (int i = V - 1; i >= 0; --i)
    {
        int v = component[i];
        if (!visited[v])
        {
            reverseDFS(reverseGraph, v, visited, component);
            printf("Component: ");
            for (int j = 0; j < V; ++j)
            {
                if (component[j] == v)
                    printf("%d ", j);
            }
            printf("\n");
        }
    }
}

int main()
{
    int V = 5; // Number of vertices
    struct Graph *graph = createGraph(V);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printSCCs(graph); // Print all strongly connected components
    return 0;
}


