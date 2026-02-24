#include <climits>
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

struct Mins {
  int index{};
  long long val{};
};
using SparseTable = std::vector<std::vector<Mins>>;

Mins GetMin(SparseTable& spr, int left, int right) {
  right++;
  int t = std::floor(std::log2(right - left));
  return spr[t][left].val < spr[t][right - (1 << t)].val
             ? spr[t][left]
             : spr[t][right - (1 << t)];
}

int main() {
  int n{};
  int q{};
  std::cin >> n >> q;
  std::vector<long long> arr(n);
  for (int i{}; i < n; i++) {
    std::cin >> arr[i];
  }

  int k = std::floor(std::log2(n)) + 1;
  SparseTable spr(k);
  for (int i{}; i < k; i++) {
    spr[i].resize(2 * n);
    for (int j{}; j < n; j++) {
      if (i == 0) {
        spr[i][j] = {j, arr[j]};
      } else {
        int right_begin =
            j + std::pow(2, i - 1) < n - 1 ? j + std::pow(2, i - 1) : n - 1;
        if (spr[i - 1][j].val < spr[i - 1][right_begin].val) {
          spr[i][j] = spr[i - 1][j];
        } else {
          spr[i][j] = spr[i - 1][right_begin];
        }
      }
    }
  }

  // for (int i{}; i < k; i++) {
  //   for (int j{}; j < n; j++) {
  //     std::cout << spr[i][j].val << " ";
  //   }
  //   std::cout << "\n";
  // }

  for (int i{}; i < q; i++) {
    int left{};
    int right{};
    std::cin >> left >> right;
    left--;
    right--;

    int min_ind{GetMin(spr, left, right).index};
    // std::cout << "min_index:" << min_ind << " left: " << left << " right: "
    // << right  << std::endl;

    long long min_1{};
    if (left == min_ind - 1) {
      min_1 = arr[left];
    } else if (left > min_ind - 1) {
      min_1 = LLONG_MAX;
    } else {
      min_1 = GetMin(spr, left, min_ind - 1).val;
    }

    long long min_2{};
    if (right == min_ind + 1) {
      min_2 = arr[right];
    } else if (right < min_ind + 1) {
      min_2 = LLONG_MAX;
    } else {
      min_2 = GetMin(spr, min_ind + 1, right).val;
    }
    int min = min_1 < min_2 ? min_1 : min_2;
    // std::cout << min << " " << min_1 << " " << min_2 << "\n";
    std::cout << min << "\n";
  }
}