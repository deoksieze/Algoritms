#include <iostream>
#include <list>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 generator(rd());
const float cLoad = 0.75;
const int cBigPi = 1000000007;
const int cM = 16;

struct Point {
  long long x;
  long long y;

  long long DistanceTo(const Point& p) const {
    return ((x - p.x) * (x - p.x)) + ((y - p.y) * (y - p.y));
  }
};

struct Node {
  long long val;
  int quant;
};

class HashMap {
  std::vector<std::list<Node>> arr_;
  int m_;
  int p_;
  int a_;
  int b_;
  int size_;
  float load_factor_;

  long long Hash(long long x) const {
    int64_t res = ((int64_t)a_ * x + b_) % p_;
    if (res < 0) {
      res += p_;
    }
    return (long long)(res % m_);
  }

  bool Find(long long x) {
    long long hashed = Hash(x);
    for (Node node : arr_[hashed]) {
      if (node.val == x) {
        return true;
      }
    }
    return false;
  }

  void UpdateLoadFactor() { load_factor_ = (float)size_ / (float)m_; }

  void UpdateTable() {
    UpdateLoadFactor();
    if (load_factor_ <= cLoad) {
      return;
    }

    long long old_m = m_;
    std::vector<std::list<Node>> old_arr = std::move(arr_);

    m_ *= 2;
    arr_.clear();
    arr_.resize(m_);

    std::uniform_int_distribution<int> distribution(1, p_ - 1);
    a_ = distribution(generator);
    b_ = distribution(generator);

    for (int i = 0; i < old_m; ++i) {
      for (Node node : old_arr[i]) {
        long long hashed = Hash(node.val);
        arr_[hashed].push_back(node);
      }
    }

    UpdateLoadFactor();
  }

 public:
  HashMap(long long p = cBigPi, long long m = cM)
      : m_(m), p_(p), size_(0), load_factor_(0) {
    arr_.resize(m_);
    std::uniform_int_distribution<long long> distribution(1, p_);
    a_ = distribution(generator);
    b_ = distribution(generator);
  }

  void Insert(long long x) {
    long long hashed = Hash(x);

    for (Node& node : arr_[hashed]) {
      if (node.val == x) {
        node.quant++;
        UpdateTable();
        return;
      }
    }

    Node node{x, 1};
    arr_[hashed].push_back(node);
    size_++;
    UpdateTable();
  }

  void Erase(long long x) {
    long long hashed = Hash(x);

    for (auto it = arr_[hashed].begin(); it != arr_[hashed].end(); ++it) {
      if (it->val == x) {
        it->quant--;

        if (it->quant == 0) {
          size_--;
          arr_[hashed].erase(it);
        }

        UpdateTable();
        return;
      }
    }
  }

  bool Contains(long long x) { return Find(x); }

  int GetSize() const { return size_; }
  float GetLoadFactor() const { return load_factor_; }

  long long CountTriangles() {
    long long counter = 0;
    for (auto list : arr_) {
      for (Node node : list) {
        counter += (node.quant * (node.quant - 1)) / 2;
      }
    }

    return counter;
  }
  ~HashMap() { arr_.clear(); }
};

int main() {
  int n{};
  int t{};
  std::cin >> n >> t;

  if (t == 2) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::vector<Point> arr(n);
  long long counter = 0;

  for (int i{}; i < n; i++) {
    std::cin >> arr[i].x >> arr[i].y;
  }

  for (int i{}; i < n; i++) {
    Point point = arr[i];
    HashMap hm = HashMap();

    for (int j = 0; j < n; j++) {
      if (j == i) {
        continue;
      }
      hm.Insert(point.DistanceTo(arr[j]));
    }

    counter += hm.CountTriangles();
    // std::cout << "For point: (" << point.x << ", " << point.y << ") " <<
    // counter
    //           << "\n";
  }

  std::cout << counter << "\n";
}