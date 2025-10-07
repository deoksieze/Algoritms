#include <iostream>
#include <string>
#include <vector>

struct Three {
  int cross;
  int dots;
  int oes;
};

bool Right(int i, int j, std::vector<std::string>& table) {
  Three ans{};
  for (int k{0}; k < 5; k++) {
    if (table[i][j + k] == 'X') {
      ans.cross++;
    } else if (table[i][j + k] == 'O') {
      ans.oes++;
    } else {
      ans.dots++;
    }
  }

    return ans.cross == 5 || ans.oes == 5;
}

bool Down(int i, int j, std::vector<std::string>& table) {
  Three ans{};
  for (int k{0}; k < 5; k++) {
    if (table[i + k][j] == 'X') {
      ans.cross++;
    } else if (table[i + k][j] == 'O') {
      ans.oes++;
    } else {
      ans.dots++;
    }
  }

    return ans.cross == 5 || ans.oes == 5;
}

bool LeftDownDiag(int i, int j, std::vector<std::string>& table) {
  Three ans{};
  for (int k{0}; k < 5; k++) {
    if (table[i + k][j - k] == 'X') {
      ans.cross++;
    } else if (table[i + k][j - k] == 'O') {
      ans.oes++;
    } else {
      ans.dots++;
    }
  }

    return ans.cross == 5 || ans.oes == 5;
}

bool RightDownDiag(int i, int j, std::vector<std::string>& table) {
  Three ans{};
  for (int k{0}; k < 5; k++) {
    if (table[i + k][j + k] == 'X') {
      ans.cross++;
    } else if (table[i + k][j + k] == 'O') {
      ans.oes++;
    } else {
      ans.dots++;
    }
  }

    return ans.cross == 5 || ans.oes == 5;
}

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<std::string> table(n);
  std::cin.ignore();

  for (int i{0}; i < n; i++) {
    std::getline(std::cin, table[i]);
  }

  bool is_possible = false;

  for (int i{}; i < n; i++) {
    for (int j{}; j < m; j++) {
      if (m - j >= 5 && Right(i, j, table)) {
        is_possible = true;
        break;
      }
      if (n - i >= 5 && Down(i, j, table)) {
        is_possible = true;
        break;
      }
      if (j >= 4 && n - i >= 5 && LeftDownDiag(i, j, table)) {
        is_possible = true;
        break;
      }
      if (m - j >= 5 && n - i >= 5 && RightDownDiag(i, j, table)) {
        is_possible = true;
        break;
      }
    }
    if (is_possible) {
      break;
    };
  }

  if (is_possible) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }
}
