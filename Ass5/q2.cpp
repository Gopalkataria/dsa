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


    vector<lint> dist(n + 1, INT64_MAX);
    vector<bool> visited(n + 1, false);
    priority_queue<pair<lint, lint>, vector<pair<lint, lint>>, greater<pair<lint, lint>>> pq;

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


    lint count = 0;
    map<lint, lint> fibres;
    while (k--)
    {
        cin >> a >> b;
        if (fibres.find(a) == fibres.end())
        {
            l = dist[a];
            if (l <= b)
            {
                count++;
                fibres[a] = l;
            }
            else
                fibres[a] = b;
        }
        else
        {
            fibres[a] = min(fibres[a], b);
            count++;
        }
    }

    cout << count << endl;

    return 0;
}