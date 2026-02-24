
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Common {
  long long len = 0;
  std::vector<int> a_ind;
  std::vector<int> b_ind;

  Common() = default;
  Common(const Common&) = default;
  Common& operator=(const Common&) = default;
  ~Common() = default;

  bool operator<(const Common& c) const { return len < c.len; }
};

int main() {
  std::string a;
  std::string b;
  std::cin >> a;
  std::cin >> b;

  std::vector<std::vector<Common>> dp(a.length() + 1,
                                      std::vector<Common>(b.length() + 1));

  for (size_t i = 0; i <= a.length(); ++i) {
    for (size_t j = 0; j <= b.length(); ++j) {
      if (i == 0 || j == 0) {
        dp[i][j].len = 0;
        continue;
      }

      dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

      if (a[i - 1] == b[j - 1] && dp[i][j].len < dp[i - 1][j - 1].len + 1) {
        dp[i][j] = dp[i - 1][j - 1];
        dp[i][j].len++;
        dp[i][j].a_ind.push_back(i);
        dp[i][j].b_ind.push_back(j);
      }
    }
  }

  Common* x = &dp[a.length()][b.length()];

  std::cout << x->len << "\n";

  for (auto i : x->a_ind) {
    std::cout << i << " ";
  }
  std::cout << "\n";

  for (auto i : x->b_ind) {
    std::cout << i << " ";
  }
}