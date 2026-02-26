#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> num(n);

  for (int i{}; i < n; i++) {
    std::cin >> num[i];
  }

  std::vector<int> up(n, 1);    //< - последний знак
  std::vector<int> down(n, 1);  //>
  std::vector<std::vector<int>> parent(n, std::vector<int>(2, -1));

  for (int i{}; i < n; i++) {
    for (int j{}; j < i; j++) {
      if (num[j] < num[i] && down[j] + 1 > up[i]) {
        up[i] = down[j] + 1;
        parent[i][0] = j;
      }

      if (num[j] > num[i] && down[i] < up[j] + 1) {
        down[i] = up[j] + 1;
        parent[i][1] = j;
      }
    }
  }

  int type = -1;
  int ind = -1;
  int len = 0;
  for (int i{}; i < n; i++) {
    if (up[i] > len) {
      len = up[i];
      type = 0;
      ind = i;
    }

    if (down[i] > len) {
      len = down[i];
      type = 1;
      ind = i;
    }
  }

  std::cout << (type == 1 ? down[ind] : up[ind]) << "\n";

  std::vector<int> answer;

  while (ind != -1) {
    answer.push_back(num[ind]);
    int next = parent[ind][type];
    type = 1 - type;
    ind = next;
  }

  std::reverse(answer.begin(), answer.end());

  for (int x : answer) {
    std::cout << x << " ";
  }
}