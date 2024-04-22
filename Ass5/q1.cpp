#include <bits/stdc++.h>

using namespace std;

void addEdge(vector<vector<int>> &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void dfsConnected(vector<vector<int>> &adj, int u, vector<int> &visited)
{
    visited[u] = 1;
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfsConnected(adj, v, visited);
        }
    }
}

int findConnectedComponents(vector<vector<int>> &adj, vector<int> &connections)
{
    int n = adj.size();
    vector<int> visited(n, 0);
    int components = 0;

    for (int u = 0; u < n; ++u)
    {
        if (!visited[u])
        {
            connections.push_back(u);
            dfsConnected(adj, u, visited);
            components++;
        }
    }
    return components;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> connections;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--; // 0-Based Indexing
        v--;

        addEdge(adj, u, v);
    }

    int result = findConnectedComponents(adj, connections) - 1;
    cout << result << endl;

    for (int i = 0; i < connections.size() - 1; i++)
    {
        cout << connections[i] + 1 << " " << connections[i + 1] + 1 << endl;
    }
}