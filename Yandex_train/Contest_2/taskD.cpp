#include <iostream>
#include <string>
#include <unordered_set>

int main() {
  std::unordered_set<std::string> dict;
  std::string typing{};
  std::getline(std::cin, typing);
  int size = typing.size();
  int n{};
  std::cin >> n;

  std::cin.ignore();

  std::string current{};
  current.reserve(size);
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, current);
    dict.insert(current);
  }

  current.clear();
  std::string answer;
  for (int i = 0; i < size; i++) {
    current += typing[i];
    if (dict.find(current) != dict.end()) {
      answer += current;
      answer += " ";
      current.clear();
    }
  }

  std::cout << answer;
}