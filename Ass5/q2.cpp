#include <bits/stdc++.h>
using namespace std;

#define lint long long int

int main()
{

    lint n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<lint, lint>>> graph(n + 1);
    lint a, b, l;
    while (m--)
    {
        cin >> a >> b >> l;
        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
    }

    vector<pair<int, int>> input;
    while (k--)
    {
        cin >> a >> b;
        input.push_back({a, b});
    }

    sort(input.begin(), input.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.second > b.second; });
    k = input.size() - 1;

    vector<lint> dist(n + 1);
    vector<bool> visited(n + 1);
    priority_queue<pair<lint, lint>, vector<pair<lint, lint>>, greater<pair<lint, lint>>> pq;
    map<lint, lint> fibres;
    lint count = 0;

djikstra:
    dist.assign(n + 1, LLONG_MAX);
    visited.assign(n + 1, false);
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty())
    {
        lint u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;
        else
            visited[u] = true;

        for (auto neighbor : graph[u])
        {
            lint v = neighbor.first, weight = neighbor.second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (lint i = 1; i < n+1; i++)
    {
        cout << i << "-" << dist[i] << "\n";
    }
    

justif:
    if (k >= 0)
    {
        tie(a, b) = input[k--];
        cout << a << " " << b << endl;
        if (fibres.find(a) == fibres.end())
        {
            l = dist[a];
            if (l <= b)
            {
                count++;
                goto justif;
                // cout << a << " " << b << " " << l << endl;
            }
            else
            {
                fibres[a] = b;
                graph[a].push_back({1, b});
                graph[1].push_back({a, b});
                goto djikstra;
            }
        }
        else
        {
            // cout << a << " " << b << " " << l << endl;
            count++;
            if( fibres[a] > b)
            {
                fibres[a] = b;
                graph[a].push_back({1, b});
                graph[1].push_back({a, b});
                goto djikstra;
            }
            else
            {
                goto justif;
            }
        }
    }

    cout << count << endl;

    return 0;
}