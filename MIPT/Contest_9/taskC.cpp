
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using State = std::tuple<int, int, int>;  // cost vertex time

struct Edge {
  int to;
  int cost;
  int time;
};
int n;
int s;
int m;

using Ll = long long;

const Ll cInf = (Ll)4e18;

std::vector<std::vector<Ll>> dist;
std::vector<std::vector<Edge>> g;
std::vector<std::vector<int>> parent_v;
std::vector<std::vector<int>> parent_t;

void Dijkstra(int start) {
  dist.assign(n + 1, std::vector<Ll>(s + 1, cInf));
  parent_v.assign(n + 1, std::vector<int>(s + 1, -1));
  parent_t.assign(n + 1, std::vector<int>(s + 1, -1));

  dist[start][0] = 0;

  std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
  pq.push({0, start, 0});

  while (!pq.empty()) {
    auto [curCost, v, curTime] = pq.top();
    pq.pop();

    if (curCost != dist[v][curTime]) {
      continue;
    }

    for (auto e : g[v]) {
      int new_time = curTime + e.time;
      Ll new_cost = curCost + e.cost;

      if (new_time <= s && new_cost < dist[e.to][new_time]) {
        dist[e.to][new_time] = new_cost;
        parent_v[e.to][new_time] = v;
        parent_t[e.to][new_time] = curTime;
        pq.push({new_cost, e.to, new_time});
      }
    }
  }
}

int main() {
  std::cin >> n >> m >> s;

  g.resize(n + 1);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    int t;
    std::cin >> u >> v >> c >> t;
    g[u].push_back({v, c, t});
    g[v].push_back({u, c, t});
  }

  Dijkstra(1);

  long long best_cost = cInf;
  int best_time = -1;
  for (int i = 0; i <= s; i++) {
    if (dist[n][i] < best_cost) {
      best_cost = dist[n][i];
      best_time = i;
    }
  }

  if (best_cost == cInf) {
    std::cout << -1 << "\n";
    return 0;
  }

  std::vector<int> route;
  int vertex = n;
  int cur_time = best_time;

  while (vertex != -1) {
    route.push_back(vertex);

    int temp_v = parent_v[vertex][cur_time];
    int temp_t = parent_t[vertex][cur_time];

    vertex = temp_v;
    cur_time = temp_t;
  }

  std::reverse(route.begin(), route.end());

  std::cout << best_cost << "\n";
  std::cout << route.size() << "\n";

  for (auto i : route) {
    std::cout << i << " ";
  }

  std::cout << "\n";
}
