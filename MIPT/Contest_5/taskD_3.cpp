#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int height;
  int widht;
  std::cin >> n >> height >> widht;

  std::vector<std::pair<int, std::pair<int, int>>> events;

  for (int i = 0; i < n; i++) {
    int x;
    int l;
    int r;
    std::cin >> x >> l >> r;
    events.push_back({l, {x, 1}});
    events.push_back({(r + 1), {x, -1}});
  }

  std::sort(events.begin(), events.end());

  std::vector<int> answer((height + 1), widht);

  int event_idx = 0;
  std::multiset<int> active_x;
  std::map<int, int> gap_count;

  active_x.insert(0);
  active_x.insert(widht);
  gap_count[widht] = 1;

  for (int track = 0; track <= height; track++) {
    while ((event_idx < static_cast<int>(events.size())) &&
           (events[event_idx].first == track)) {
      int x = events[event_idx].second.first;
      int delta = events[event_idx].second.second;

      if (delta == 1) {
        auto it = active_x.lower_bound(x);
        int right = *it;
        it--;
        int left = *it;

        int old_gap = (right - left);
        gap_count[old_gap]--;
        if (gap_count[old_gap] == 0) {
          gap_count.erase(old_gap);
        }

        int left_gap = (x - left);
        int right_gap = (right - x);

        gap_count[left_gap]++;
        gap_count[right_gap]++;

        active_x.insert(x);
      } else {
        auto it = active_x.find(x);
        auto it_right = it;
        it_right++;
        auto it_left = it;
        it_left--;

        int left = *it_left;
        int right = *it_right;

        int left_gap = (x - left);
        int right_gap = (right - x);

        gap_count[left_gap]--;
        if (gap_count[left_gap] == 0) {
          gap_count.erase(left_gap);
        }

        gap_count[right_gap]--;
        if (gap_count[right_gap] == 0) {
          gap_count.erase(right_gap);
        }

        int new_gap = (right - left);
        gap_count[new_gap]++;

        active_x.erase(it);
      }

      event_idx++;
    }

    answer[track] = gap_count.rbegin()->first;
  }

  for (int track = 0; track <= height; track++) {
    std::cout << answer[track] << "\n";
  }

  return 0;
}