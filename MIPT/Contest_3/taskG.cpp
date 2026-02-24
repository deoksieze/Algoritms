#include <climits>
#include <deque>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<long long>>;

void PrintMatrix(Matrix& m) {
  int n = m.size();
  int q = m[0].size();
  for (int i{}; i < n; i++) {
    for (int j{}; j < q; j++) {
      std::cout << m[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int n{};
  int k{};
  std::cin >> n;
  std::cin >> k;

  Matrix mat(n);
  for (int i{}; i < n; i++) {
    mat[i].resize(n);
    for (int j{}; j < n; j++) {
      std::cin >> mat[i][j];
    }
  }

  Matrix row_min(n, std::vector<long long>(n - k + 1));
  for (int i{}; i < n; i++) {
    std::deque<int> dq;

    for (int j = 0; j < n; j++) {
      while (!dq.empty() && dq.front() <= j - k) {
        dq.pop_front();
      }

      while (!dq.empty() && mat[i][dq.back()] >= mat[i][j]) {
        dq.pop_back();
      }

      dq.push_back(j);

      if (j >= k - 1) {
        row_min[i][j - k + 1] = mat[i][dq.front()];
      }
    }
  }

  Matrix result(n - k + 1, std::vector<long long>(n - k + 1));

  for (int j = 0; j < n - k + 1; j++) {  // для каждой колонки
    std::deque<int> dq;
    for (int i = 0; i < n; i++) {
      // удаляем индексы, которые вышли за верхнюю границу окна
      while (!dq.empty() && dq.front() <= i - k) {
        dq.pop_front();
      }

      // удаляем из конца дека элементы больше или равны текущему
      while (!dq.empty() && row_min[dq.back()][j] >= row_min[i][j]) {
        dq.pop_back();
      }
      dq.push_back(i);

      // когда окно достигло размера k, записываем минимум
      if (i >= k - 1) {
        result[i - k + 1][j] = row_min[dq.front()][j];
      }
    }
  }

  PrintMatrix(result);
}