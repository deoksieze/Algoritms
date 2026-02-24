#include <iostream>

int main() {
  int n;
  std::cin >> n;

  for (int i{}; i < n; i++) {
    int h;
    int w;
    std::cin >> h >> w;
    if (w > h) {
      int temp = h;
      h = w;
      w = temp;
    }

    int counter = 0;

    while (h > 0) {
      counter += w - 1;
      if (h > 1) {
        counter += 1;
      }
      h--;
    }
    std::cout << counter << "\n";
  }
}