#include <algorithm>
#include <iostream>
#include <vector>

bool Can(const std::vector<long long>& x, int k, long long len) {
  int used = 1;            // хотя бы один отрезок нужен
  long long start = x[0];  // начало текущего отрезка
  for (long long xi : x) {
    if (xi > start + len) {  // точка вне текущего отрезка
      ++used;
      start = xi;  // начинаем новый отрезок
      if (used > k) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{};
  int k{};
  std::cin >> n >> k;
  std::vector<long long> x(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i];
  }

  std::sort(x.begin(), x.end());

  long long left = 0;
  long long right = x.back() - x.front();  // максимальная возможная длина

  while (left < right) {
    long long mid = (left + right) / 2;
    if (Can(x, k, mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  std::cout << left << "\n";
  return 0;
}
