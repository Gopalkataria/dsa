#pragma once
void findping(std::vector<long long> &dist, std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<std::pair<long long, long long>>> &pq, std::vector<bool> &visited, std::vector<std::vector<std::pair<long long, long long>>> &graph);
