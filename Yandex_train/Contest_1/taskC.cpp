#include <iostream>
#include <string>
#include <vector>
int main() {
  constexpr int cAlphabetLen = 26;
  std::string password;
  std::vector<long long> arr(cAlphabetLen);
  std::getline(std::cin, password);

  for (auto i : password) {
    arr[i - 'a']++;
  }

  long long n = password.size();
  long long answer = n * (n - 1) / 2;
  // std::cout << answer << "\n";

  for (auto i : arr) {
    answer -= i * (i-1)/2;
    // if (C(i, 2) != 0) {
    //   std::cout << answer << "\n";
    // }
  }

  std::cout << answer + 1;
}