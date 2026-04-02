#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<int> ans;
std::vector<bool> visited;
std::vector<int> parent;
std::vector<int> parent_edge;
std::vector<int> order;
std::vector<int> b;
int n;
int m;

bool BFS(int start) {
  std::queue<int> q;
  q.push(start);
  visited[start] = true;
  parent[start] = 0;
  parent_edge[start] = -1;
  order.clear();
  order.push_back(start);
  int sum_b = b[start];

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto [v, id] : adj[u]) {
      if (!visited[v]) {
        visited[v] = true;
        parent[v] = u;
        parent_edge[v] = id;
        q.push(v);
        order.push_back(v);
        sum_b ^= b[v];
      } else {
        if (v != parent[u] && ans[id] == -1) {
          ans[id] = 0;
        }
      }
    }
  }

  if (sum_b % 2 != 0) {
    return false;
  }

  for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
    int v = order[i];
    if (parent[v] == 0) {
      continue;
    }
    int cur = 0;
    for (auto [to, id] : adj[v]) {
      if (ans[id] != -1) {
        cur ^= ans[id];
      }
    }
    ans[parent_edge[v]] = b[v] ^ cur;
  }

  return true;
}

int main() {
  int t;
  std::cin >> t;
  while (t != 0) {
    std::cin >> n >> m;

    adj.assign(n + 1, {});
    ans.assign(m, -1);
    visited.assign(n + 1, false);
    parent.assign(n + 1, 0);
    parent_edge.assign(n + 1, -1);
    b.assign(n + 1, 0);

    for (int i = 0; i < m; ++i) {
      int u;
      int v;
      std::cin >> u >> v;
      adj[u].emplace_back(v, i);
      adj[v].emplace_back(u, i);
    }

    std::string s;
    std::cin >> s;
    for (int i = 1; i <= n; ++i) {
      b[i] = s[i - 1] - '0';
    }

    bool impossible = false;
    for (int start = 1; start <= n; ++start) {
      if (!visited[start]) {
        if (!BFS(start)) {
          impossible = true;
          break;
        }
      }
    }

    if (impossible) {
      std::cout << "-1\n";
    } else {
      for (int x : ans) {
        std::cout << x;
      }
      std::cout << '\n';
    }

    t--;
  }

  return 0;
}