#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  if (!(std::cin >> n)) {
    return 0;
  }
  std::vector<long long> a(n);
  std::vector<long long> b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> b[i];
  }

  // Списки индексов
  std::vector<int> left;
  std::vector<int> right;
  left.reserve(n);
  right.reserve(n);

  for (int i = 0; i < n; ++i) {
    if (a[i] <= b[i]) {
      left.push_back(i);
    } else {
      right.push_back(i);
    }
  }

  // сортируем L по возрастанию a[i]
  std::sort(left.begin(), left.end(), [&](int i, int j) {
    if (a[i] != a[j]) {
      return a[i] < a[j];
    }
    return i < j;
  });

  // сортируем R по убыванию b[i]
  std::sort(right.begin(), right.end(), [&](int i, int j) {
    if (b[i] != b[j]) {
      return b[i] > b[j];
    }
    return i < j;
  });

  // итоговый порядок: L затем R
  std::vector<int> order;
  order.reserve(n);
  for (int idx : left) {
    order.push_back(idx);
  }
  for (int idx : right) {
    order.push_back(idx);
  }

  // симуляция для вычисления makespan
  long long t1 = 0;  // текущее время на машине 1 (первый учитель)
  long long t2 = 0;  // текущее время на машине 2 (второй учитель)
  for (int pos = 0; pos < n; ++pos) {
    int job = order[pos];
    t1 += a[job];
    t2 = t2 < t1 ? t1 : t2;  // машина1 завершает эту работу
    t2 += b[job];
  }

  // Вывод
  std::cout << t2 << "\n";

  // перестановка для первого учителя (1-based индексы)
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << (order[i] + 1);
  }
  std::cout << "\n";

  // перестановка для второго учителя — можно вывести ту же (перестановка
  // совпадает)
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << (order[i] + 1);
  }
  std::cout << "\n";

  return 0;
}
