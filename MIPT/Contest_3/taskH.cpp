#include <deque>
#include <iostream>
#include <vector>

int a{};
int b{};
int c{};
int n{};
int m{};
int k{};

struct Point3d {
  int x{};
  int y{};
  int z{};
  long long value;
};

using Vec3D = std::vector<std::vector<std::vector<int>>>;
using Points3d = std::vector<std::vector<std::vector<Point3d>>>;

void Print(Points3d& ten) {
  int n = ten.size();
  for (int i{}; i < n; i++) {
    int m = ten[i].size();
    for (int j{}; j < m; j++) {
      int k = ten[i][j].size();
      for (int q{}; q < k; q++) {
        std::cout << ten[i][j][k].z << " ";
      }
      std::cout << '\n';
    }
  }
  std::cout << '\n';
}

void GoZ(Vec3D& vec, Points3d& z_shorted) {
  for (int i{}; i < n; i++) {
    z_shorted[i].resize(m);
    for (int j{}; j < m; j++) {
      z_shorted[i][j].resize(k);
      std::deque<int> dq{};
      for (int q{k - 1}; q >= 0; q--) {
        while (!dq.empty() && dq.front() >= q + c) {
          dq.pop_front();
        }

        while (!dq.empty() && vec[i][j][dq.back()] <= vec[i][j][q]) {
          dq.pop_back();
        }

        dq.push_back(q);
        if (vec[i][j][q] < vec[i][j][dq.front()]) {
          z_shorted[i][j][q] = Point3d{i, j, dq.front(), vec[i][j][dq.front()]};
        } else {
          z_shorted[i][j][q] = Point3d{i, j, q, vec[i][j][q]};
        }
      }
    }
  }
}

void GoY(Vec3D& vec, Points3d& y_shorted, Points3d& z_shorted) {
  for (int i{}; i < n; i++) {
    for (int q{}; q < k; q++) {
      std::deque<int> dq;
      for (int j{m - 1}; j >= 0; j--) {
        while (!dq.empty() && dq.front() >= j + b) {
          dq.pop_front();
        }

        while (!dq.empty() &&
               z_shorted[i][dq.back()][q].value <= z_shorted[i][j][q].value) {
          dq.pop_back();
        }

        dq.push_back(j);
        if (vec[i][j][q] < z_shorted[i][dq.front()][q].value) {
          y_shorted[i][j][q] = z_shorted[i][dq.front()][q];
        } else {
          y_shorted[i][j][q] = Point3d{i, j, q, vec[i][j][q]};
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> k;
  std::cin >> a >> b >> c;

  Vec3D vec(n);

  for (int i{}; i < n; i++) {
    vec[i].resize(m);
    for (int j{}; j < m; j++) {
      vec[i][j].resize(k);
      for (int q{}; q < k; q++) {
        std::cin >> vec[i][j][q];
      }
    }
  }

  Points3d z_shorted(n);
  GoZ(vec, z_shorted);

  Points3d y_shorted(
      n, std::vector<std::vector<Point3d>>(m, std::vector<Point3d>(k)));
  GoY(vec, y_shorted, z_shorted);

  Points3d result(
      n, std::vector<std::vector<Point3d>>(m, std::vector<Point3d>(k)));
  for (int j{}; j < m; j++) {
    for (int q{}; q < k; q++) {
      std::deque<int> dq;
      for (int i{n - 1}; i >= 0; i--) {
        while (!dq.empty() && dq.front() >= i + a) {
          dq.pop_front();
        }

        while (!dq.empty() &&
               y_shorted[dq.back()][j][q].value <= y_shorted[i][j][q].value) {
          dq.pop_back();
        }

        dq.push_back(i);
        if (vec[i][j][q] < y_shorted[dq.front()][j][q].value) {
          result[i][j][q] = y_shorted[dq.front()][j][q];
        } else {
          result[i][j][q] = Point3d{i, j, q, vec[i][j][q]};
        }
      }
    }
  }

  //   int r{};
  //   std::cin >> r;
  //   for (int l{}; l < r; l++) {
  //     int i{};
  //     int j{};
  //     int q{};
  //     std::cin >> i >> j >> q;

  //     while (result[i][j][q].x != i || result[i][j][q].y != j ||
  //            result[i][j][q].z != q) {
  //       auto next = result[i][j][q];

  //       i = next.x;
  //       j = next.y;
  //       q = next.z;
  //     }

  //     std::cout << i << " " << j << " " << q << "\n";
  //   }
  for (int i{}; i < n; i++) {
    for (int j{}; j < m; j++) {
      for (int q{}; q < k; q++) {
        std::cout << "[" << i << " " << j << " " << q << "]=" << "["
                  << result[i][j][q].x << " " << result[i][j][q].y << " "
                  << result[i][j][q].z << "] " << result[i][j][q].value << " ";
      }
      std::cout << "\n";
    }
  }
}