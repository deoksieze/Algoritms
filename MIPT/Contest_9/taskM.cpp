
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Request {
  bool is_cut;
  int u;
  int v;
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

int main() {
  int n;
  int m;
  int q;
  std::cin >> n >> m >> q;

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    std::cin >> u >> v;
  }

  std::vector<Request> req(q);
  for (int i = 0; i < q; i++) {
    std::string type;
    int u;
    int v;
    std::cin >> type >> u >> v;
    req[i] = {type == "cut", u, v};
  }

  std::reverse(req.begin(), req.end());

  std::vector<Node> nodes(n + 1);
  for (int i = 1; i <= n; i++) {
    nodes[i] = {&nodes[i], 1};
  }

  std::vector<std::string> ans;
  for (auto r : req) {
    Node* u = &nodes[r.u];
    Node* v = &nodes[r.v];
    if (r.is_cut) {
      Unite(u, v);
    } else {
      ans.push_back(Same(u, v) ? "YES" : "NO");
    }
  }

  std::reverse(ans.begin(), ans.end());

  for (auto s : ans) {
    std::cout << s << "\n";
  }
}