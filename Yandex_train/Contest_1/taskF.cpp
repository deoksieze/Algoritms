#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Pair {
  int current{};
};

int main() {
  constexpr int cThou{1000};
  int n{};
  int m{};

  std::cin >> n >> m;
  std::vector<Pair> rows(n);
  std::vector<Pair> columns(m);
  std::vector<std::string> table(n);

  std::cin.ignore();

  for (int i{0}; i < n; i++) {
    std::getline(std::cin, table[i]);
    for (int j{0}; j < m; j++) {
      if (table[i][j] == '+') {
        rows[i].current++;
        columns[j].current++;
      } else if (table[i][j] == '-') {
        rows[i].current--;
        columns[j].current--;
      } else {
        rows[i].current++;
        columns[j].current--;
      }
    }
  }

  int min_val = cThou;
  std::vector<int> min_columns;
  int max_val = -cThou;
  std::vector<int> max_rows;

  for (size_t i = 0; i < columns.size(); i++) {
    if (columns[i].current < min_val) {
      min_val = columns[i].current;
      min_columns.clear();
      min_columns.push_back(i);
    } else if (columns[i].current == min_val) {
      min_columns.push_back(i);
    }
  }

  for (size_t i = 0; i < rows.size(); i++) {
    if (rows[i].current > max_val) {
      max_val = rows[i].current;
      max_rows.clear();
      max_rows.push_back(i);
    } else if (rows[i].current == max_val) {
      max_rows.push_back(i);
    }
  }

  bool answer_done = false;
  for (size_t i{0}; i < max_rows.size(); i++ )
  {
    for (size_t j{0}; j < min_columns.size(); j++)
    {
        if (table[max_rows[i]][min_columns[j]] != '?')
        {
            answer_done = true;
            std::cout << max_val - min_val;
            break;
        }
    }

    if (answer_done)
    {
        break;
    }
  }

  if (!answer_done)
  {
    std::cout << max_val - min_val - 2;
  }
}