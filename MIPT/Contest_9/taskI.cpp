#include <algorithm>
#include <array>
#include <iostream>
#include <string>

static const int cN = 4;
static const int cSize = 16;
static const int cInf = 1e9;
static const int cFound = -1;
static const int cDeskSize = 15;
static const int cGameSize = 16;

int direction_row[4] = {-1, 1, 0, 0};
int drection_column[4] = {0, 0, -1, 1};
char out_char[4] = {'D', 'U', 'R', 'L'};

std::array<int, cSize> board;
int dist_table[cGameSize][cGameSize];
std::string cur_path;
std::string answer;

int Opposite(int mv) {
  return mv ^ 1;  // 0<->1, 2<->3
}

int ManhattanAll() {
  int h = 0;
  for (int pos = 0; pos < cSize; ++pos) {
    int tile = board[pos];
    if (tile != 0) {
      h += dist_table[tile][pos];
    }
  }
  return h;
}

int Dfs(int zero_pos, int g, int h, int bound, int prev_move) {
  int f = g + h;
  if (f > bound) {
    return f;
  }

  if (h == 0) {
    answer = cur_path;
    return cFound;
  }

  int zero_row = zero_pos / cN;
  int zero_column = zero_pos % cN;
  int min_next_bound = cInf;

  for (int mv = 0; mv < 4; ++mv) {
    if (prev_move != -1 && mv == Opposite(prev_move)) {
      continue;
    }

    int new_row = zero_row + direction_row[mv];
    int new_column = zero_column + drection_column[mv];
    if (new_row < 0 || new_row >= cN || new_column < 0 || new_column >= cN) {
      continue;
    }

    int next_pos = new_row * cN + new_column;
    int tile = board[next_pos];

    int new_h = h - dist_table[tile][next_pos] + dist_table[tile][zero_pos];

    std::swap(board[zero_pos], board[next_pos]);
    cur_path.push_back(out_char[mv]);

    int t = Dfs(next_pos, g + 1, new_h, bound, mv);
    if (t == cFound) {
      return cFound;
    }
    if (t < min_next_bound) {
      min_next_bound = t;
    }

    cur_path.pop_back();
    std::swap(board[zero_pos], board[next_pos]);
  }

  return min_next_bound;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int zero_pos = -1;
  for (int i = 0; i < cSize; ++i) {
    std::cin >> board[i];
    if (board[i] == 0) {
      zero_pos = i;
    }
  }

  for (int tile = 1; tile <= cDeskSize; ++tile) {
    int goal_pos = tile - 1;
    int gr = goal_pos / cN;
    int gc = goal_pos % cN;
    for (int pos = 0; pos < cSize; ++pos) {
      int r = pos / cN;
      int c = pos % cN;
      dist_table[tile][pos] = abs(r - gr) + abs(c - gc);
    }
  }

  int h = ManhattanAll();
  int bound = h;

  while (true) {
    int t = Dfs(zero_pos, 0, h, bound, -1);
    if (t == cFound) {
      break;
    }
    bound = t;
  }

  std::cout << answer.size() << '\n';
  std::cout << answer << '\n';

  return 0;
}