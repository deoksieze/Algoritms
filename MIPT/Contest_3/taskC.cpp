#include <iostream>
#include <string>
#include <vector>

template <typename T>
void PrintArr(std::vector<T>& arr) {
  for (auto i : arr) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

int main() {
  int n{};
  std::cin >> n;

  std::vector<std::string> names(n + 1);

  std::vector<int> current_children(n);

  for (int i{1}; i <= n; i++) {
    std::cin >> names[i];
  }

  std::vector<int> left(n + 1);
  std::vector<int> right(n + 1);
  for (int i{1}; i <= n; i++) {
    left[i] = i == 1 ? n : i - 1;
    right[i] = i == n ? 1 : i + 1;
  }

  for (int i{}; i < n - 3; i++) {
    int x;
    std::cin >> x;

    std::cout << names[left[x]] << " " << names[right[x]] << "\n";
    right[left[x]] = right[x];
    left[right[x]] = left[x];
  }
}