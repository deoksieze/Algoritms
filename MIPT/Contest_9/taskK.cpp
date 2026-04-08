#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

struct AdjEdge {
  int to;
  int len;
};

struct Edge {
  int v;
  int u;
  int len;

  bool operator<(const Edge& other) const { return len < other.len; }
};

struct Node {
  Node* parent;
  int s;
};

Node* Get(Node* x) {
  if (x->parent == x) {
    return x;
  }
  return x->parent = Get(x->parent);
}

bool Same(Node* x, Node* y) { return Get(x) == Get(y); }

void Unite(Node* x, Node* y) {
  Node* u = Get(x);
  Node* v = Get(y);

  if (u == v) {
    return;
  }

  if (u->s < v->s) {
    std::swap(u, v);
  }

  v->parent = u;
  u->s += v->s;
}

std::vector<int> d;
std::vector<int> owner;
std::vector<std::vector<AdjEdge>> g;
std::vector<int> gas_stations;
std::vector<Edge> mst;
int n;
const int cInf = 2009000999;

void FindMst(std::vector<Edge>& edges) {
  std::sort(edges.begin(), edges.end());

  std::vector<Node> nodes(n);
  for (int i = 0; i < n; i++) {
    nodes[i].parent = &nodes[i];
    nodes[i].s = 1;
  }

  for (auto edge : edges) {
    Node* u = &nodes[edge.u];
    Node* v = &nodes[edge.v];
    if (!Same(u, v)) {
      mst.push_back(edge);
      Unite(u, v);
    }
  }
}

void Dijkstra() {
  d.assign(n, cInf);
  owner.assign(n, -1);

  std::set<std::pair<int, int>> q;

  for (int x : gas_stations) {
    d[x] = 0;
    owner[x] = x;
    q.insert({0, x});
  }

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    for (auto e : g[v]) {
      if (d[v] + e.len < d[e.to]) {
        q.erase({d[e.to], e.to});
        d[e.to] = d[v] + e.len;
        owner[e.to] = owner[v];
        q.insert({d[e.to], e.to});
      }
    }
  }
}

std::vector<Edge> BuildCompressedGraph() {
  std::vector<Edge> compressed;

  for (int v = 0; v < n; v++) {
    for (auto e : g[v]) {
      if (v < e.to && owner[v] != owner[e.to]) {
        compressed.push_back({owner[v], owner[e.to], d[v] + e.len + d[e.to]});
      }
    }
  }

  return compressed;
}

const int cLog = 20;
std::vector<std::vector<AdjEdge>> tree;
std::vector<std::vector<int>> up;
std::vector<std::vector<int>> mx;
std::vector<int> depth;
std::vector<int> comp;

void BuildTree() {
  tree.assign(n, {});
  for (auto e : mst) {
    tree[e.v].push_back({e.u, e.len});
    tree[e.u].push_back({e.v, e.len});
  }
}

void PrepareLca() {
  up.assign(cLog, std::vector<int>(n, -1));
  mx.assign(cLog, std::vector<int>(n, 0));
  depth.assign(n, 0);
  comp.assign(n, -1);

  int cc = 0;
  std::queue<int> q;

  for (int root : gas_stations) {
    if (comp[root] != -1) {
      continue;
    }

    comp[root] = cc;
    up[0][root] = -1;
    mx[0][root] = 0;
    depth[root] = 0;
    q.push(root);

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (auto e : tree[v]) {
        if (e.to == up[0][v]) {
          continue;
        }
        if (comp[e.to] != -1) {
          continue;
        }

        comp[e.to] = cc;
        depth[e.to] = depth[v] + 1;
        up[0][e.to] = v;
        mx[0][e.to] = e.len;
        q.push(e.to);
      }
    }

    ++cc;
  }

  for (int j = 1; j < cLog; j++) {
    for (int v = 0; v < n; v++) {
      if (up[j - 1][v] == -1) {
        up[j][v] = -1;
        mx[j][v] = mx[j - 1][v];
      } else {
        up[j][v] = up[j - 1][up[j - 1][v]];
        mx[j][v] = std::max(mx[j - 1][v], mx[j - 1][up[j - 1][v]]);
      }
    }
  }
}

int GetMaxOnPath(int a, int b) {
  if (comp[a] != comp[b]) {
    return cInf;
  }

  int ans = 0;

  if (depth[a] < depth[b]) {
    std::swap(a, b);
  }

  int diff = depth[a] - depth[b];
  for (int j = cLog - 1; j >= 0; j--) {
    if (((diff >> j) & 1) != 0) {
      ans = std::max(ans, mx[j][a]);
      a = up[j][a];
    }
  }

  if (a == b) {
    return ans;
  }

  for (int j = cLog - 1; j >= 0; j--) {
    if (up[j][a] != up[j][b]) {
      ans = std::max(ans, mx[j][a]);
      ans = std::max(ans, mx[j][b]);
      a = up[j][a];
      b = up[j][b];
    }
  }

  ans = std::max(ans, mx[0][a]);
  ans = std::max(ans, mx[0][b]);
  return ans;
}

int main() {
  int k;
  int m;
  std::cin >> n >> k >> m;

  gas_stations.resize(k);
  for (int i = 0; i < k; i++) {
    std::cin >> gas_stations[i];
    --gas_stations[i];
  }

  g.assign(n, {});
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int w;
    std::cin >> u >> v >> w;
    --u;
    --v;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  Dijkstra();
  std::vector<Edge> compressed = BuildCompressedGraph();
  FindMst(compressed);
  BuildTree();
  PrepareLca();

  int q;
  std::cin >> q;
  while ((q) != 0) {
    q--;

    int x;
    int y;
    int c;
    std::cin >> x >> y >> c;
    --x;
    --y;

    int need = GetMaxOnPath(x, y);
    if (need <= c) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}