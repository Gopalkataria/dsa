#include <bits/stdc++.h>

using namespace std;
#define lint long long int

void dfs(lint i, vector<vector<lint>> graph, vector<bool> &visited)
{
    visited[i] = true;
    for (auto j : graph[i])
    {
        if (!visited[j])
            dfs(j, graph, visited);
    }
}

int main()
{

    lint n, m;
    char inp;
    cin >> n >> m;
    lint A, B; 

    bool inps[n * m + 1];

    vector<vector<lint>> graph(n * m + 1);

    for (lint i = 0; i < n; i++)
    {
        for (lint j = 0; j < m; j++)
        {
            cin >> inp;
            if (inp == '.')
                inps[i * m + j] = true;
            else
                inps[i * m + j] = false;
            if (inp == 'A')
            {
                A = i * m + j;
                continue;
            }
            if (inp == 'B')
            {
                B = i * m + j;
                continue;
            }

            if ((i > 0) && inps[(i - 1) * m + j])
            {
                graph[i * m + j].push_back((i - 1) * m + j);
                graph[(i - 1) * m + j].push_back(i * m + j);
            }
            if ((j > 0) && inps[i * m + j - 1])
            {
                graph[i * m + j].push_back(i * m + j - 1);
                graph[i * m + j - 1].push_back(i * m + j);
            }
        }
    }

    vector<bool> visited(n * m + 1, false);
    lint count = 0;
    for (lint i = 0; i < n * m; i++)
    {
        if (!visited[i] && inps[i])
        {
            dfs(i, graph, visited);
            count++;
        }
    }

    cout << count << endl;
}