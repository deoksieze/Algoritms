#include <iostream>
#include <vector>

int main() {
  long long n{};
  std::cin >> n;

  std::vector<long long> arr(n);
  for (long long i{}; i < n; i++) {
    std::cin >> arr[i];
  }

  std::vector<long long> stack;
  stack.push_back(-1);
  long long max = 0;

  for (long long i{}; i <= n; i++) {
    long long curr_h = (i == n ? 0 : arr[i]);
    while (stack.back() != -1 && curr_h < arr[stack.back()]) {
      long long top = stack.back();
      stack.pop_back();

      long long height = arr[top];
      long long width = i - stack.back() - 1;

      long long square = height * width;
      //   std::cout << width << "*" << height << "=" << square << "\n";
      max = max > square ? max : square;
    }

    stack.push_back(i);
  }

  std::cout << max << std::endl;
}