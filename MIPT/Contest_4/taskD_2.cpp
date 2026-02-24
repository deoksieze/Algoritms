#include <iostream>
#include <vector>
using LL = long long;

// t: массив дерева размера 2*len (len — степень двойки)
// листья находятся в t[len..2*len-1]
void Build(std::vector<int>& t, int len) {
  for (int i = len - 1; i >= 1; --i) {
    t[i] = std::max(t[2 * i], t[(2 * i) + 1]);
  }
}

void Update(std::vector<int>& t, int len, int pos0, int val) {
  // pos0 — 0-based индекс в исходном массиве
  int pos = pos0 + len;
  t[pos] = val;
  pos >>= 1;
  while (pos >= 1) {
    t[pos] = std::max(t[2 * pos], t[(2 * pos) + 1]);
    pos >>= 1;
  }
}

// Найти первый индекс j >= l (0-based), такой что a[j] >= x.
// Возвращает 0-based индекс или -1 если нет.
int FindFirstGe(std::vector<int>& t, int len, int l, int x) {
  int pos = l + len;
  // если в левом краю (листе) уже достаточно, просто опустимся вниз из него
  if (t[pos] >= x) {
    // опускаемся до листа
    while (pos < len) {
      if (t[2 * pos] >= x) {
        pos = 2 * pos;
      } else {
        pos = (2 * pos) + 1;
      }
    }
    return pos - len;
  }
  // иначе поднимаемся вверх, и при переходе с правого ребёнка на родителя
  // проверяем правого брата (pos%2==0 -> мы были левым; надо проверить pos+1)
  while (pos > 1) {
    if ((pos & 1) == 0) {  // pos — левый сын
      if (t[pos + 1] >= x) {
        pos = pos + 1;
        // спускаемся вниз из этого узла
        while (pos < len) {
          if (t[2 * pos] >= x) {
            pos = 2 * pos;
          } else {
            pos = (2 * pos) + 1;
          }
        }
        return pos - len;
      }
    }
    pos >>= 1;
  }
  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int q;
  if (!(std::cin >> n >> q)) {
    return 0;
  }
  // вычислим len — ближайшая степень двойки >= n
  int len = 1;
  while (len < n) {
    len <<= 1;
  }

  std::vector<int> t(2 * len, 0);
  for (int i = 0; i < n; ++i) {
    int v;
    std::cin >> v;
    t[len + i] = v;
  }
  // остальные листья (len + n .. 2*len-1) уже 0 (или -INF, если нужны)
  Build(t, len);

  for (int qi = 0; qi < q; ++qi) {
    int type;
    int ind;
    int x;
    std::cin >> type >> ind >> x;
    // входной индекс ind — 1-based, приведём к 0-based:
    int pos0 = ind - 1;
    if (type == 0) {
      // присвоить a[ind] = x
      if (pos0 >= 0 && pos0 < n) {
        Update(t, len, pos0, x);
      }
    } else {
      int ans = FindFirstGe(t, len, pos0, x);
      if (ans == -1) {
        std::cout << -1 << '\n';
      } else {
        std::cout << (ans + 1) << '\n';
      }  // выводим 1-based
    }
  }
  return 0;
}
