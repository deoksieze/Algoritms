#include <iostream>
constexpr long long cTen = 10;
constexpr long long cTwenty = 20;

// unsigned long long LongSolution(unsigned long long n, unsigned long long k) {
//   for (unsigned long long i{0}; i < k; i++) {
//     n += n % cTen;
//   }
//   return n;
// }

int main() {
  unsigned long long n{};
  unsigned long long k{};

  unsigned long long answer{};
  std::cin >> n >> k;
//   unsigned long long right_answer{LongSolution(n, k)};

  if (k == 0) {
    answer = n;
  } else if (n % cTen == 5) {
    answer = n + 5;
  } else if (n % cTen == 0) {
    answer = n;
  } else {
    if (n % 2 != 0) {
      n += n % cTen;
      k -= 1;
    }

    answer = cTwenty * (k / 4);
    for (unsigned long long i{0}; i < k % 4; i++) {
      n += n % cTen;
    }
    answer += n;
  }
//   std::cout << right_answer << "\n";
  std::cout << answer << std::endl;
}