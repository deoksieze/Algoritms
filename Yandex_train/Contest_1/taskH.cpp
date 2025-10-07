#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Pair {
  int start;
  int number;
  std::string str;
  bool operator<(const Pair& other) const { return start < other.start; }
};

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::string original;
  std::vector<Pair> arr(m);
  std::vector<std::string> str(m);
  std::cin.ignore();
  std::getline(std::cin, original);

  for (int i{0}; i < m; i++) {
    std::getline(std::cin, arr[i].str);
    arr[i].number = i + 1;
  }

  std::sort(arr.begin(), arr.end(),
            [](const Pair& a, const Pair& b) {
              return a.str.length() > b.str.length();
            });

  for (int i{0}; i < m; i++) {
    arr[i].start = original.find(arr[i].str);;
  }

  std::sort(arr.begin(), arr.end());

  for (auto i : arr) {
    std::cout << i.number << " ";
  }
}