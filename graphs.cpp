#include <bits/stdc++.h>
using namespace std;


void DFS(int v, vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[v] = true;
    for (int u : adj[v])
    {
        if (!visited[u])
        {
            DFS(u, adj, visited);
        }
    }
}


int countDisconnectedComponents(int V, vector<vector<int>> &adj)
{
    int count = 0;
    vector<bool> visited(V, false);
    for (int v = 0; v < V; ++v)
    {
        if (!visited[v])
        {
            DFS(v, adj, visited);
            count++;
        }
    }
    return count;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);

    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    int disconnectedComponents = countDisconnectedComponents(V, adj);
    cout << "N : " << disconnectedComponents << endl;

    return 0;
}