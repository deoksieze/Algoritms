#include <iostream>
#include <vector>

int main() {
  int n{};
  std::cin >> n;
  n += 4;
  std::vector<int> arr(n);
  arr[0] = 0;
  arr[1] = 0;
  arr[2] = 0;

  for (int i = 3; i < n; i++) {
    if (i == 3) {
      arr[i] = 1;
      continue;
    }
    arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3];
  }

  std::cout << arr[n-1];
}