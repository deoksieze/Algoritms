#include <iostream>
#include <unordered_map>

int main() {
  constexpr int cMaxN = 100000;
  int n{};
  int k{};
  std::cin >> n >> k;

  std::unordered_map<int, int> map;
  map.reserve(cMaxN);

  int x{};
  for (int i{0}; i < n; i++) {
    std::cin >> x;
    if (!map.contains(x)) {
      map[x] = 1;
    } else {
      map[x] += 1;
    }
  }

  int counter{0};
  for (auto i : map) {
    std::cout << i.first << " ";
    counter++;
    if (counter >= k) {
      break;
    }
  }

  if (counter < k) {
    for (auto i : map) {
      if (i.second > 1) {
        for (int j{1}; (j < i.second && counter < k); j++) {
          std::cout << i.first << " ";
          counter++;
        }
      }

      if (counter >= k) {
        break;
      }
    }
  }
}