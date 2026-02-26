#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using Ll = long long;
static const Ll cMod = 1e9 + 7;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);

  std::unordered_map<int, std::list<int>> pos;

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    pos[a[i]].push_back(i);
  }
  std::vector<Ll> dp(n + 1, 0);
  dp[0] = 1;

  std::unordered_map<int, int> last_seen_pos;
  last_seen_pos.reserve(pos.size() * 2);

  for (int i = 1; i <= n; ++i) {
    int x = a[i - 1];

    int cur_pos = pos[x].front();
    pos[x].pop_front();

    Ll val = (2 * dp[i - 1]) % cMod;

    auto it = last_seen_pos.find(x);
    if (it != last_seen_pos.end()) {
      int prev_pos = it->second;
      val = (val - dp[prev_pos] + cMod) % cMod;
    }

    dp[i] = val;

    last_seen_pos[x] = cur_pos;
  }

  Ll ans = (dp[n] - 1 + cMod) % cMod;
  std::cout << ans << "\n";
}
