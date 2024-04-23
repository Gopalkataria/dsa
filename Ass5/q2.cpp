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

    
    k = input.size() - 1;
    for (lint curr_size = 1; curr_size <= k; curr_size *= 2)
    {
        for (lint left_start = 0; left_start < k; left_start += 2 * curr_size)
        {
            lint mid = min(left_start + curr_size - 1, k);
            lint right_end = min(left_start + 2 * curr_size - 1, k);
            lint n1 = mid - left_start + 1;
            lint n2 = right_end - mid;
            vector<pair<lint, lint>> L(n1), R(n2);
            for (lint i = 0; i < n1; i++)
                L[i] = input[left_start + i];
            for (lint j = 0; j < n2; j++)
                R[j] = input[mid + 1 + j];
            lint i = 0, j = 0, idx = left_start;
            while (i < n1 && j < n2)
            {
                if (L[i].second >= R[j].second)
                    input[idx++] = L[i++];
                else
                    input[idx++] = R[j++];
            }
            while (i < n1)
                input[idx++] = L[i++];
            while (j < n2)
                input[idx++] = R[j++];
        }
    }

    
    vector<lint> dist(n + 1, LLONG_MAX);
    vector<bool> visited(n + 1);
    priority_queue<pair<lint, lint>, vector<pair<lint, lint>>, greater<pair<lint, lint>>> pq;
    map<lint, lint> fibres;
    lint count = 0;

    dist[1] = 0;
    pq.push({0, 1});

djikstra:
    visited.assign(n + 1, false);
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

justif:
    if (k >= 0)
    {
        tie(a, b) = input[k--];
        if (fibres.find(a) == fibres.end())
        {
            l = dist[a];
            if (l <= b)
            {
                count++;
                goto justif;
            }
            else
            {
                fibres[a] = b;
                pq.push({b, a});
                dist[a] = b;
                goto djikstra;
            }
        }
        else
        {
            count++;
            if (fibres[a] > b)
            {
                fibres[a] = b;
                pq.push({b, a});
                dist[a] = b;
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
