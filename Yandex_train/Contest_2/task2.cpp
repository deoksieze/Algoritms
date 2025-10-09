#include <iostream>
#include <string>
#include <vector>

struct Pair {
  int left;
  int right;
};

int main() {
  std::string str;
  std::getline(std::cin, str);
  int n = str.size();

  std::vector<Pair> arr(n + 1);
  arr[0].left = 0;
  arr[0].right = 1;

  for (int i{1}; i < n + 1; i++) {
    char lake = str[i - 1];

    if (lake == 'B') {
      arr[i].right = arr[i - 1].right + 1;
      arr[i].left = arr[i - 1].left + 1;
    } else if (lake == 'L') {
      arr[i].right = arr[i - 1].right;
      arr[i].left = arr[i - 1].left < arr[i].right ? arr[i - 1].left + 1
                                                   : arr[i - 1].right + 1;
    } else {
      arr[i].left = arr[i - 1].left;
      arr[i].right = arr[i - 1].right < arr[i].left ? arr[i - 1].right + 1
                                                   : arr[i - 1].left + 1;
    }
  }

//   for (auto i : arr)
//   {
//     std::cout << "( " << i.left << ";" << i.right << ") ";
//   }
  std::cout << arr[n].right;
}