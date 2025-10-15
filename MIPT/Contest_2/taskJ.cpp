#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m;
  int n;
  std::cin >> m >> n;

  std::vector<std::pair<long long, int>> sheep(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> sheep[i].first;
    sheep[i].second = i + 1;
  }

  std::vector<std::pair<long long, int>> dogs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> dogs[i].first;
    dogs[i].second = i + 1;
  }

  std::sort(sheep.begin(), sheep.end());

  std::multiset<std::pair<long long, int>> dog_set;
  for (int i = 0; i < n; ++i) {
    dog_set.insert(dogs[i]);
  }

  std::vector<std::tuple<int, int, int>> result;

  for (int i = 0; i < m; ++i) {
    long long val = sheep[i].first;
    int sheep_idx = sheep[i].second;

    // ищем пса с b < a_i
    auto it_low = dog_set.lower_bound({val, 0});
    if (it_low == dog_set.begin()) {
      continue;
    }          // нет пса меньше
    --it_low;  // самый большой пёс с b < a_i
    int dog_low = it_low->second;

    // ищем пса с b > a_i
    auto it_high = dog_set.upper_bound({val, n + 1});
    if (it_high == dog_set.end()) {
      continue;
    }  // нет пса больше
    int dog_high = it_high->second;

    result.emplace_back(sheep_idx, dog_low, dog_high);

    // удаляем использованных псов
    dog_set.erase(it_low);
    dog_set.erase(it_high);
  }

  std::cout << result.size() << "\n";
  for (auto& t : result) {
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << " "
              << std::get<2>(t) << "\n";
  }

  return 0;
}
