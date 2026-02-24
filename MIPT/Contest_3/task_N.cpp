#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n{};
    int64_t q{};
    std::cin >> n >> q;

    std::set<std::pair<int64_t, int64_t>> free_by_size;
    std::set<std::pair<int64_t, int64_t>> free_by_start;
    std::vector<std::pair<int64_t, int64_t>> allocated(q + 1, {-1, -1});

    free_by_start.insert({1, n});
    free_by_size.insert({-n, 1});

    for (int64_t i = 1; i <= q; ++i) {
        int64_t k;
        std::cin >> k;

        if (k > 0) {
            auto it = free_by_size.lower_bound({-k, 0});
            if (it == free_by_size.end()) {
                std::cout << -1 << '\n';
                continue;
            }

            int64_t size = -it->first;
            int64_t start = it->second;
            int64_t end = start + size - 1;

            free_by_size.erase(it);
            free_by_start.erase({start, end});

            allocated[i] = {start, k};
            std::cout << start << '\n';

            if (size > k) {
                int64_t new_start = start + k;
                int64_t new_size = size - k;
                free_by_start.insert({new_start, end});
                free_by_size.insert({-new_size, new_start});
            }
        } else {
            int64_t idx = -k;
            if (idx >= i || allocated[idx].first == -1) {
                continue;
            }

            int64_t start = allocated[idx].first;
            int64_t size = allocated[idx].second;
            int64_t end = start + size - 1;

            auto it = free_by_start.lower_bound({start, end});
            if (it != free_by_start.begin()) {
                auto prev = std::prev(it);
                if (prev->second == start - 1) {
                    start = prev->first;
                    free_by_size.erase({-(prev->second - prev->first + 1), prev->first});
                    free_by_start.erase(prev);
                }
            }

            it = free_by_start.lower_bound({start, end});
            if (it != free_by_start.end() && it->first == end + 1) {
                end = it->second;
                free_by_size.erase({-(it->second - it->first + 1), it->first});
                free_by_start.erase(it);
            }

            free_by_start.insert({start, end});
            free_by_size.insert({-(end - start + 1), start});

            allocated[idx] = {-1, -1};
        }
    }

    return 0;
}