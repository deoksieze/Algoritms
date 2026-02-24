#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Event {
  int y;
  int x;
  int type;
  bool operator<(Event const& other) const {
    if (y != other.y) {
      return y < other.y;
    }
    return type < other.type;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int h;
  int w;
  std::cin >> n >> h >> w;

  std::vector<Event> events;
  events.reserve(2 * n);

  for (int i = 0; i < n; i++) {
    int x;
    int l;
    int r;
    std::cin >> x >> l >> r;
    events.push_back({l, x, 0});
    events.push_back({r + 1, x, 1});
  }

  sort(events.begin(), events.end());

  std::set<int> xs;
  xs.insert(0);
  xs.insert(w);

  std::multiset<int> gaps;
  gaps.insert(w - 0);

  auto add_x = [&](int x) {
    auto it = xs.lower_bound(x);
    int right = *it;
    int left = *prev(it);

    gaps.erase(gaps.find(right - left));
    gaps.insert(x - left);
    gaps.insert(right - x);
    xs.insert(x);
  };

  auto remove_x = [&](int x) {
    auto it = xs.find(x);
    int right = *next(it);
    int left = *prev(it);

    gaps.erase(gaps.find(x - left));
    gaps.erase(gaps.find(right - x));
    gaps.insert(right - left);
    xs.erase(it);
  };

  int eidx = 0;
  int m = events.size();

  for (int i = 0; i <= h; i++) {
    while (eidx < m && events[eidx].y <= i) {
      if (events[eidx].type == 0) {
        add_x(events[eidx].x);
      } else {
        remove_x(events[eidx].x);
      }
      eidx++;
    }

    int ans = *gaps.rbegin();
    std::cout << ans << '\n';
  }

  return 0;
}
