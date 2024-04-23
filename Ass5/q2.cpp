#include <bits/stdc++.h>
using namespace std;

#define lint long long int

void merge(vector<pair<int, int>> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<pair<int, int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].second >= R[j].second)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<pair<int, int>> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

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
    mergeSort(input, 0, k);

    vector<lint> dist(n + 1);
    vector<bool> visited(n + 1);
    priority_queue<pair<lint, lint>, vector<pair<lint, lint>>, greater<pair<lint, lint>>> pq;
    map<lint, lint> fibres;
    lint count = 0;

    dist.assign(n + 1, LLONG_MAX);
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
            if( fibres[a] > b)
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