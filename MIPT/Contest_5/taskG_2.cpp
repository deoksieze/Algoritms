#include <algorithm>
#include <iostream>
#include <vector>

struct QValues {
  int value;
  int tl;
  int tr;
  int l;
  int r;
  int x;
  int y;
};

struct UValues {
  int value;
  int tl;
  int tr;
  int position;
  int old_v;
  int new_v;
};

class SegementTree {
 public:
  int q;
  std::vector<std::vector<int>> tree;

  explicit SegementTree(const std::vector<int>& arr) {
    q = arr.size();
    tree.resize(4 * q);
    Build(1, 0, q - 1, arr);
  }

  void Update(const UValues& p) {
    int v = p.value;
    int tl = p.tl;
    int tr = p.tr;
    int pos = p.position;
    int old_val = p.old_v;
    int new_val = p.new_v;

    auto it = std::lower_bound(tree[v].begin(), tree[v].end(), old_val);
    tree[v].erase(it);

    auto it2 = std::lower_bound(tree[v].begin(), tree[v].end(), new_val);
    tree[v].insert(it2, new_val);

    if (tl == tr) {
      return;
    }

    int tm = (tl + tr) / 2;

    if (pos <= tm) {
      UValues np{};
      np.value = v * 2;
      np.tl = tl;
      np.tr = tm;
      np.position = pos;
      np.old_v = old_val;
      np.new_v = new_val;
      Update(np);
    } else {
      UValues np{};
      np.value = v * 2 + 1;
      np.tl = tm + 1;
      np.tr = tr;
      np.position = pos;
      np.old_v = old_val;
      np.new_v = new_val;
      Update(np);
    }
  }

  void Build(int v, int tl, int tr, const std::vector<int>& a) {
    if (tl == tr) {
      tree[v] = {a[tl]};
      return;
    }

    int tm = (tl + tr) / 2;
    Build(v * 2, tl, tm, a);
    Build((v * 2) + 1, tm + 1, tr, a);

    tree[v].reserve(tree[v * 2].size() + tree[(v * 2) + 1].size());
    std::merge(tree[v * 2].begin(), tree[v * 2].end(),
               tree[(v * 2) + 1].begin(), tree[(v * 2) + 1].end(),
               std::back_inserter(tree[v]));
  }

  int Query(const QValues& p) const {
    int v = p.value;
    int tl = p.tl;
    int tr = p.tr;
    int l = p.l;
    int r = p.r;
    int x = p.x;
    int y = p.y;

    if (l > r) {
      return 0;
    }

    if (l == tl && r == tr) {
      auto it1 = std::lower_bound(tree[v].begin(), tree[v].end(), x);
      auto it2 = std::upper_bound(tree[v].begin(), tree[v].end(), y);
      return static_cast<int>(it2 - it1);
    }

    int tm = (tl + tr) / 2;

    QValues left{};
    left.value = v * 2;
    left.tl = tl;
    left.tr = tm;
    left.l = l;
    left.r = std::min(r, tm);
    left.x = x;
    left.y = y;

    QValues right{};
    right.value = v * 2 + 1;
    right.tl = tm + 1;
    right.tr = tr;
    right.l = std::max(l, tm + 1);
    right.r = r;
    right.x = x;
    right.y = y;

    return Query(left) + Query(right);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int q;
  std::cin >> n >> q;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  SegementTree st(a);

  for (int i{}; i < q; i++) {
    std::string operation;
    std::cin >> operation;

    if (operation == "SET") {
      int i;
      int x;
      std::cin >> i >> x;
      i--;

      UValues p;
      p.value = 1;
      p.tl = 0;
      p.tr = n - 1;
      p.position = i;
      p.old_v = a[i];
      p.new_v = x;

      st.Update(p);
      a[i] = x;

    } else {
      int l;
      int r;
      int x;
      int y;
      std::cin >> l >> r >> x >> y;
      l--;
      r--;

      QValues p;
      p.value = 1;
      p.tl = 0;
      p.tr = n - 1;
      p.l = l;
      p.r = r;
      p.x = x;
      p.y = y;

      int ans = st.Query(p);
      std::cout << ans << "\n";
    }
  }

  return 0;
}