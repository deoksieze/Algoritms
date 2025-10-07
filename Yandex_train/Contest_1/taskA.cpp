#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  constexpr int cMaxWeight = 1000;
  int n{};
  std::cin >> n;

  int min_vaisya{cMaxWeight};
  int max_maria{-1};

  int sum_vaisya{};
  int sum_maria{};

  int x{};
  for (int i{0}; i < n; i++) {
    std::cin >> x;
    if (i % 2 == 0) {
      sum_vaisya += x;
      min_vaisya = std::min(min_vaisya, x);
    } else {
      sum_maria += x;
      max_maria = std::max(max_maria, x);
    }
    // std::cout << sum_vaisya << " " << min_vaisya << " " << sum_maria << " "
    // << max_maria << "\n";
  }

  if (max_maria > min_vaisya) {
    std::cout << (sum_vaisya - min_vaisya + max_maria) -
                     (sum_maria - max_maria + min_vaisya)
              << std::endl;
  } else {
    std::cout << sum_vaisya - sum_maria;
  }
}