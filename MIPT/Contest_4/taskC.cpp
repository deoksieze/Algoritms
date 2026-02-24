#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

struct Nodes {
  int l_border{};
  int r_border{};
  long long plus_sum{};
  long long minus_sum{};
};

void TreeBuild(std::vector<Nodes>& t, std::vector<int>& a) {
  size_t n{a.size()};
  for (size_t i{}; i < n; i++) {
    t[n + i].plus_sum = a[i];
    t[n + i].minus_sum = -a[i];
    t[n + i].l_border = i + 1;
    t[n + i].r_border = i + 1;
  }

  for (int i{static_cast<int>(n - 1)}; i > 0; i--) {
    t[i].l_border = t[2 * i].l_border;
    t[i].r_border = t[(2 * i) + 1].r_border;

    bool has_grand_children{(t[i].r_border - t[i].l_border) >= 2};
    if (!has_grand_children) {
      t[i].plus_sum = t[2 * i].plus_sum + t[(2 * i) + 1].minus_sum;
    } else {
      t[i].plus_sum = t[2 * i].plus_sum + t[(2 * i) + 1].plus_sum;
    }

    t[i].minus_sum = -t[i].plus_sum;
  }
}

long long Get(std::vector<Nodes>& t, int n, int l, int r) {
  long long res{};
  int lb = l;  // запоминаем левую границу
  l += n;
  r += n;
  while (l <= r) {
    if (l % 2 == 1) {
      if ((t[l].l_border - lb) % 2 == 0) {
        res += t[l].plus_sum;
      } else {
        res += t[l].minus_sum;
      }
      l++;
    }
    if (r % 2 == 0) {
      if ((t[r].l_border - lb) % 2 == 0) {
        res += t[r].plus_sum;
      } else {
        res += t[r].minus_sum;
      }

      r--;
    }
    l /= 2;
    r /= 2;
  }
  return res;
}

void Update(std::vector<Nodes>& t, int n, int pos, int val) {
  pos += n;
  t[pos].plus_sum = val;
  t[pos].minus_sum = -val;

  for (pos /= 2; pos >= 1; pos /= 2) {
    bool has_grand_children{(t[pos].r_border - t[pos].l_border) >= 2};
    if (!has_grand_children) {
      t[pos].plus_sum = t[2 * pos].plus_sum + t[(2 * pos) + 1].minus_sum;
    } else {
      t[pos].plus_sum = t[2 * pos].plus_sum + t[(2 * pos) + 1].plus_sum;
    }

    t[pos].minus_sum = -t[pos].plus_sum;
  }
}

int main() {
  int n{};
  std::cin >> n;
  int len{2};
  while (len < n) {
    len *= 2;
  }

  std::vector<int> a(len);
  for (int i{}; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<Nodes> t(2 * len);

  TreeBuild(t, a);

  int q{};
  std::cin >> q;

  for (int i{}; i < q; i++) {
    int oper{};
    int s1{};
    int s2{};
    std::cin >> oper >> s1 >> s2;

    if (oper == 0) {
      Update(t, len - 1, s1, s2);
    } else {
      std::cout << Get(t, len - 1, s1, s2) << '\n';
    }
  }
}
