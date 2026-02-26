#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

struct TaksM {
  int index;
  const TaksM* prev;
  TaksM(int idx, const TaksM* p) : index(idx), prev(p) {}
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> num(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> num[i];
  }

  std::vector<std::unique_ptr<TaksM>> nodes;

  nodes.push_back(std::make_unique<TaksM>(0, nullptr));
  nodes.push_back(std::make_unique<TaksM>(0, nullptr));

  const TaksM* up_node = nodes[0].get();
  const TaksM* down_node = nodes[1].get();
  int up_len = 1;
  int down_len = 1;

  for (int i = 1; i < n; ++i) {
    if (num[i] > num[i - 1]) {
      up_len = down_len + 1;
      nodes.push_back(std::make_unique<TaksM>(i, down_node));
      up_node = nodes.back().get();
    }
    if (num[i] < num[i - 1]) {
      down_len = up_len + 1;
      nodes.push_back(std::make_unique<TaksM>(i, up_node));
      down_node = nodes.back().get();
    }
  }

  const TaksM* best_node = (down_len >= up_len) ? down_node : up_node;
  int best_len = std::max(down_len, up_len);

  std::vector<int> indices;
  for (const TaksM* node = best_node; node != nullptr; node = node->prev) {
    indices.push_back(node->index);
  }
  std::reverse(indices.begin(), indices.end());

  std::cout << best_len << "\n";
  for (int idx : indices) {
    std::cout << num[idx] << " ";
  }
  std::cout << "\n";

  return 0;
}