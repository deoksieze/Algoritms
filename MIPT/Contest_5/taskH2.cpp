#include <iostream>
#include <stack>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> x(n + 1);
  std::vector<int> y(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> x[i] >> y[i];
  }

  std::vector<int> parent(n + 1, 0);
  std::vector<int> left(n + 1, 0);
  std::vector<int> right(n + 1, 0);

  std::stack<int> st;

  for (int i = 1; i <= n; ++i) {
    int last = 0;
    while (!st.empty() && y[st.top()] > y[i]) {
      last = st.top();
      st.pop();
    }

    if (!st.empty()) {
      parent[i] = st.top();
      right[st.top()] = i;
    }

    if (last != 0) {
      parent[last] = i;
      left[i] = last;
    }

    st.push(i);
  }

  std::cout << "YES\n";
  for (int i = 1; i <= n; ++i) {
    std::cout << parent[i] << " " << left[i] << " " << right[i] << "\n";
  }

  return 0;
}
