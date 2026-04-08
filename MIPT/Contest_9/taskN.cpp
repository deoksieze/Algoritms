

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

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

std::vector<Edge> mst;
int n;
int m;

void FindMst(std::vector<Edge>& g) {
  std::sort(g.begin(), g.end());

  std::vector<Node> nodes(n + 1);
  for (int i = 1; i <= n; i++) {
    nodes[i].parent = &nodes[i];
    nodes[i].s = 1;
  }

  for (auto edge : g) {
    Node* u = &nodes[edge.u];
    Node* v = &nodes[edge.v];
    if (!Same(u, v)) {
      mst.push_back(edge);
      Unite(u, v);
    }
  }
}

int main() {
  std::cin >> n >> m;

  std::vector<Edge> g;
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    g.push_back({u, v, c});
  }

  FindMst(g);

  long long sum = 0;
  for (auto edge : mst) {
    sum += edge.len;
  }

  std::cout << sum << "\n";
}