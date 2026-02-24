#include <iostream>
#include <ostream>
#include <vector>

struct Point3d {
  int x{};
  int y{};
  int z{};
  long long value{};
};

int n{}, m{}, k{};
int a{}, b{}, c{};

inline int Index(int x, int y, int z) { return (((x * m) + y) * k) + z; }

// ----------------------------------------------------
// Свёртка по оси Z
// ----------------------------------------------------
void GoZ(const std::vector<long long>& vec, std::vector<Point3d>& out) {
  for (int x{}; x < n; ++x) {
    for (int y{}; y < m; ++y) {
      std::vector<int> dq(k);
      int head = 0;
      int tail = 0;

      for (int z = k - 1; z >= 0; --z) {
        while (head < tail && dq[head] >= z + c) {
          ++head;
        }

        while (head < tail &&
               vec[Index(x, y, dq[tail - 1])] <= vec[Index(x, y, z)]) {
          --tail;
        }

        dq[tail++] = z;
        int best_z = dq[head];

        if (vec[Index(x, y, z)] < vec[Index(x, y, best_z)]) {
          out[Index(x, y, z)] = {x, y, best_z, vec[Index(x, y, best_z)]};
        } else {
          out[Index(x, y, z)] = {x, y, z, vec[Index(x, y, z)]};
        }
      }
    }
  }
}

// ----------------------------------------------------
// Свёртка по оси Y
// ----------------------------------------------------
void GoY(const std::vector<Point3d>& z_data, std::vector<Point3d>& out) {
  for (int x{}; x < n; ++x) {
    for (int z{}; z < k; ++z) {
      std::vector<int> dq(m);
      int head = 0;
      int tail = 0;

      for (int y = m - 1; y >= 0; --y) {
        while (head < tail && dq[head] >= y + b) {
          ++head;
        }

        while (head < tail && z_data[Index(x, dq[tail - 1], z)].value <=
                                  z_data[Index(x, y, z)].value) {
          --tail;
        }

        dq[tail++] = y;
        int best_y = dq[head];

        if (z_data[Index(x, y, z)].value < z_data[Index(x, best_y, z)].value) {
          out[Index(x, y, z)] = z_data[Index(x, best_y, z)];
        } else {
          out[Index(x, y, z)] = z_data[Index(x, y, z)];
        }
      }
    }
  }
}

// ----------------------------------------------------
// Свёртка по оси X
// ----------------------------------------------------
void GoX(const std::vector<Point3d>& y_data, std::vector<Point3d>& result) {
  for (int y{}; y < m; ++y) {
    for (int z{}; z < k; ++z) {
      std::vector<int> dq(n);
      int head = 0;
      int tail = 0;

      for (int x = n - 1; x >= 0; --x) {
        while (head < tail && dq[head] >= x + a) {
          ++head;
        }

        while (head < tail && y_data[Index(dq[tail - 1], y, z)].value <=
                                  y_data[Index(x, y, z)].value) {
          --tail;
        }

        dq[tail++] = x;
        int best_x = dq[head];

        if (y_data[Index(x, y, z)].value < y_data[Index(best_x, y, z)].value) {
          result[Index(x, y, z)] = y_data[Index(best_x, y, z)];
        } else {
          result[Index(x, y, z)] = y_data[Index(x, y, z)];
        }
      }
    }
  }
}

// ----------------------------------------------------
// Path Compression для быстрых запросов
// ----------------------------------------------------
Point3d Find(std::vector<Point3d>& result, int x, int y, int z) {
  int i = x;
  int j = y;
  int q = z;
  int id = Index(i, j, q);

  while (true) {
    Point3d& cur = result[id];
    if (cur.x == i && cur.y == j && cur.z == q) {
      break;
    }

    i = cur.x;
    j = cur.y;
    q = cur.z;
    id = Index(i, j, q);
  }

  // Path compression
  Point3d final = result[id];
  result[Index(x, y, z)] = final;
  return final;
}

// ----------------------------------------------------
// Основная функция
// ----------------------------------------------------
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> k;
  std::cin >> a >> b >> c;

  std::vector<long long> values(n * m * k);
  for (int x{}; x < n; ++x) {
    for (int y{}; y < m; ++y) {
      for (int z{}; z < k; ++z) {
        std::cin >> values[Index(x, y, z)];
      }
    }
  }

  std::vector<Point3d> z_stage(n * m * k);
  GoZ(values, z_stage);

  std::vector<Point3d> y_stage(n * m * k);
  GoY(z_stage, y_stage);

  std::vector<Point3d> result(n * m * k);
  GoX(y_stage, result);

  int q{};
  std::cin >> q;

  for (int t{}; t < q; ++t) {
    int x{};
    int y{};
    int z{};
    std::cin >> x >> y >> z;
    Point3d res = Find(result, x, y, z);
    std::cout << res.x << " " << res.y << " " << res.z << "\n";
  }
  //   for (int i{}; i < n; i++) {
  //     for (int j{}; j < m; j++) {
  //       for (int q{}; q < k; q++) {
  //         std::cout << "[" << i << " " << j << " " << q << "]=" << "["
  //                   << result[Index(i, j, q)].x << " " << result[Index(i, j,
  //                   q)].y << " "
  //                   << result[Index(i, j, q)].z << "] " << result[Index(i, j,
  //                   q)].value << " ";
  //       }
  //       std::cout << "\n";
  //     }
  //   }

  return 0;
}
