#include <iostream>
#include <string>
#include <vector>

bool IsDigit(char ch) { return '0' <= ch && ch <= '9'; }

int ConvertCharToInt(char ch) { return static_cast<int>(ch - '0'); }

int MakeOperation(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    default:
      return 0;
  }
}

template <typename T>
void PrintArr(std::vector<T>& i) {
  for (auto j : i) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}

int main() {
  std::string str;
  std::getline(std::cin, str);
  int size = str.size();

  std::vector<int> stack{};
  for (int i{0}; i < size; i += 2) {
    char sym = str[i];
    if (IsDigit(sym)) {
      stack.push_back(ConvertCharToInt(sym));
    } else {
      int ans =
          MakeOperation(stack[stack.size() - 2], stack[stack.size() - 1], sym);
      stack.resize(stack.size() - 2);
      stack.push_back(ans);
    }
  }

  std::cout << stack.back();
}