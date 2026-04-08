
#include <iostream>
#include <vector>

const long long cInf = -4000000000000000000LL;

void RestorePath(int s, int t, const std::vector<std::vector<int>>& next,
                 const std::vector<std::vector<int>>& edge,
                 std::vector<int>& path) {
  if (next[s][t] == -1 || s == t) {
    return;
  }

  int cur = s;

  while (cur != t) {
    int nxt = next[cur][t];
    path.push_back(edge[cur][nxt]);
    cur = nxt;
  }
}

bool IsInfinite(int s, int t, const std::vector<std::vector<long long>>& dist,
                int n) {
  for (int c = 1; c <= n; ++c) {
    if (dist[s][c] == cInf) {
      continue;
    }
    if (dist[c][t] == cInf) {
      continue;
    }
    if (dist[c][c] > 0) {
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<long long>> dist(n + 1,
                                           std::vector<long long>(n + 1, cInf));
  std::vector<std::vector<int>> next(n + 1, std::vector<int>(n + 1, -1));
  std::vector<std::vector<int>> edge(n + 1, std::vector<int>(n + 1, -1));
  std::vector<int> a(k);

  for (int i{1}; i <= n; i++) {
    dist[i][i] = 0;
    next[i][i] = i;
  }

  for (int i{1}; i <= m; i++) {
    int u;
    int v;
    long long d;

    std::cin >> u >> v >> d;
    if (dist[u][v] < d) {
      dist[u][v] = d;
      next[u][v] = v;
      edge[u][v] = i;
    }
  }

  for (int i{}; i < k; i++) {
    std::cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        if (dist[u][i] == cInf || dist[i][v] == cInf) {
          continue;
        }

        if (dist[u][i] + dist[i][v] > dist[u][v]) {
          dist[u][v] = dist[u][i] + dist[i][v];
          next[u][v] = next[u][i];
        }
      }
    }
  }

  std::vector<int> ans;
  for (int i = 1; i < k; i++) {
    if (IsInfinite(a[i - 1], a[i], dist, n)) {
      std::cout << "infinitely kind\n";
      return 0;
    }
    RestorePath(a[i - 1], a[i], next, edge, ans);
  }

  std::cout << ans.size() << "\n";
  for (auto i : ans) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}