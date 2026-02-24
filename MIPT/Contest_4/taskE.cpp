#include <cstddef>
#include <iostream>
#include <vector>

class Fenwick {
 public:
  int len{};
  std::vector<int> data;

  Fenwick(int n) {
    len = n;
    data.resize(n);
  }

  static int G(int i) { return i | (i + 1); }

  static int F(int i) { return i & (i + 1); }

  void Add(int ind, int val) {
    for (int i = ind; i < len; i = G(i)) {
      data[i] += val;
    }
  }

  long long Sum(int ind) {
    long long ans = 0;
    for (int i = ind; i >= 0; i = F(i) - 1) {
      ans += data[i];
    }

    return ans;
  }

  

};


int main()
{
  std::vector<int> inv{};

  int i{};
  while (std::cin >> i) {
    inv.push_back(i);
  }

  /*Какие шаги можно применить?
  1. Из массива инверсий найти перестановку
  2. Из перестановки найти обратную перестановку
  3. Из обратной перестановки найти её массив инверсий*/
}