#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure to represent the graph
typedef struct
{
    int vertices;                          // Number of vertices
    int edges[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix
} Graph;

// Function to initialize the graph
void initGraph(Graph *graph, int vertices)
{
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->edges[i][j] = 0; // Initialize all edges to 0
        }
    }
}

// Function to add an edge between two vertices
void addEdge(Graph *graph, int vertex1, int vertex2)
{
    // Since it's an undirected graph, set both edges
    graph->edges[vertex1][vertex2] = 1;
    graph->edges[vertex2][vertex1] = 1;
}

// Function to remove an edge between two vertices
void removeEdge(Graph *graph, int vertex1, int vertex2)
{
    // Since it's an undirected graph, remove both edges
    graph->edges[vertex1][vertex2] = 0;
    graph->edges[vertex2][vertex1] = 0;
}

// Function to check if there's an edge between two vertices
bool hasEdge(Graph *graph, int vertex1, int vertex2)
{
    return graph->edges[vertex1][vertex2] == 1;
}

// Function to print the adjacency matrix
void printGraph(Graph *graph)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
        {
            printf("%d ", graph->edges[i][j]);
        }
        printf("\n");
    }
}

#include <stdbool.h>

// Helper function for DFS
bool DFS(Graph *graph, int currentVertex, int endVertex, bool visited[])
{
    // Mark current vertex as visited
    visited[currentVertex] = true;

    // If current vertex is the end vertex, return true
    if (currentVertex == endVertex)
        return true;

    // Traverse all adjacent vertices of current vertex
    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->edges[currentVertex][i] == 1 && !visited[i])
        {
            // Recursively check if there's a path from this adjacent vertex to endVertex
            if (DFS(graph, i, endVertex, visited))
                return true;
        }
    }

    // If no path is found, return false
    return false;
}

// Function to check if a path exists between two vertices using DFS
bool pathExists(Graph *graph, int startVertex, int endVertex)
{
    // Create an array to keep track of visited vertices
    bool visited[MAX_VERTICES] = {false};

    // Call DFS helper function to find if path exists
    return DFS(graph, startVertex, endVertex, visited);
}

int main()
{
    Graph graph;
    int vertices, edges;
    int vertex1, vertex2;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++)
    {
        printf("Enter edge %d (format: vertex1 vertex2): ", i + 1);
        scanf("%d %d", &vertex1, &vertex2);
        addEdge(&graph, vertex1, vertex2);
    }

    printGraph(&graph);

    return 0;
}


