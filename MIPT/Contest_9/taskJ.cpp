#include <algorithm>
#include <cstddef>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

const int cMil = 1000000;
const int cInf = 2009000999;

struct Edge {
  int to;
  int len;
};

std::vector<int> dist;
std::vector<std::vector<Edge>> g;
std::vector<std::vector<int>> teleports;
std::unordered_map<int, int> compressed_coords;
std::vector<int> d;
int total_vertex;

void Dijkstra(int s) {
  d.assign(total_vertex + 1, cInf);
  d[s] = 0;

  std::set<std::pair<int, int>> q;
  q.insert({0, s});

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    if (d[v] == cInf) {
      break;
    }

    for (auto e : g[v]) {
      if (d[v] + e.len < d[e.to]) {
        q.erase({d[e.to], e.to});
        d[e.to] = d[v] + e.len;
        q.insert({d[e.to], e.to});
      }
    }
  }
}

int main() {
  int n;
  int up_cost;
  int down_cost;
  int in_cost;
  int out_cost;
  int k;
  std::cin >> n >> up_cost >> down_cost >> in_cost >> out_cost >> k;

  teleports.assign(k, std::vector<int>());

  std::vector<int> important_vertex{1, n};

  for (int group = 0; group < k; ++group) {
    int t;
    std::cin >> t;
    teleports[group].reserve(t);

    for (int j = 0; j < t; ++j) {
      int floor;
      std::cin >> floor;
      teleports[group].push_back(floor);
      important_vertex.push_back(floor);
    }
  }

  std::sort(important_vertex.begin(), important_vertex.end());
  important_vertex.erase(
      std::unique(important_vertex.begin(), important_vertex.end()),
      important_vertex.end());

  total_vertex = important_vertex.size() + teleports.size();
  g.resize(total_vertex + 1);

  for (size_t index = 0; index < important_vertex.size(); ++index) {
    compressed_coords[important_vertex[index]] = static_cast<int>(index) + 1;
  }

  int floor_vertex_count = static_cast<int>(important_vertex.size());
  for (int group = 0; group < k; ++group) {
    compressed_coords[cMil + 1 + group] = floor_vertex_count + group + 1;
  }

  for (size_t index = 1; index < important_vertex.size(); ++index) {
    int prev_floor = important_vertex[index - 1];
    int cur_floor = important_vertex[index];
    int prev_id = compressed_coords[prev_floor];
    int cur_id = compressed_coords[cur_floor];
    int floors_diff = cur_floor - prev_floor;

    g[prev_id].push_back({cur_id, floors_diff * up_cost});
    g[cur_id].push_back({prev_id, floors_diff * down_cost});
  }

  for (int group = 0; group < k; ++group) {
    int teleport_id = compressed_coords[cMil + 1 + group];

    for (int floor : teleports[group]) {
      int floor_id = compressed_coords[floor];
      g[floor_id].push_back({teleport_id, in_cost});
      g[teleport_id].push_back({floor_id, out_cost});
    }
  }

  Dijkstra(compressed_coords[1]);

  std::cout << d[compressed_coords[n]] << "\n";
  return 0;
}