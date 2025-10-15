#include <iostream>
#include <string>
#include <vector>

char ReturnPair(char scob) {
  switch (scob) {
    case ')':
      return '(';
    case ']':
      return '[';
    case '}':
      return '{';
    default:
      return '\0';
  }
}

void PrintArr(std::vector<char>& i) {
  for (auto j : i) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}

int main() {
  std::string str;
  std::getline(std::cin, str);
  std::vector<char> stack;
  bool flag = true;

  for (auto i : str) {
    if (i == '(' || i == '[' || i == '{') {
      stack.push_back(i);
    } else {
      if (stack.empty() || stack.back() != ReturnPair(i)) {
        flag = false;
        break;
      }
      stack.pop_back();
    }
  }

  if (!stack.empty() && flag) {
    flag = false;
  }

  if (flag) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}