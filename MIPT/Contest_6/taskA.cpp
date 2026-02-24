#include <iostream>
#include <list>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 generator(rd());
const float cLoad = 0.75;
const int cBigPi = 1000000007;
const int cM = 16;

class HashMap {
  std::vector<std::list<int>> arr_;
  int m_;
  int p_;
  int a_;
  int b_;
  int size_;
  float load_factor_;

  int Hash(int x) const {
    int64_t res = ((int64_t)a_ * x + b_) % p_;
    if (res < 0) {
      res += p_;
    }
    return (int)(res % m_);
  }

  bool Find(int x) {
    int hashed = Hash(x);
    for (int val : arr_[hashed]) {
      if (val == x) {
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

    int old_m = m_;
    std::vector<std::list<int>> old_arr = std::move(arr_);

    m_ *= 2;
    arr_.clear();
    arr_.resize(m_);

    std::uniform_int_distribution<int> distribution(1, p_ - 1);
    a_ = distribution(generator);
    b_ = distribution(generator);

    for (int i = 0; i < old_m; ++i) {
      for (int val : old_arr[i]) {
        int hashed = Hash(val);
        arr_[hashed].push_back(val);
      }
    }

    UpdateLoadFactor();
  }

 public:
  HashMap(int p = cBigPi, int m = cM)
      : m_(m), p_(p), size_(0), load_factor_(0) {
    arr_.resize(m_);
    std::uniform_int_distribution<int> distribution(1, p_);
    a_ = distribution(generator);
    b_ = distribution(generator);
  }

  void Insert(int x) {
    if (Find(x)) {
      return;
    }
    int hashed = Hash(x);
    arr_[hashed].push_back(x);
    size_++;
    UpdateTable();
  }

  void Erase(int x) {
    if (!Find(x)) {
      return;
    }
    int hashed = Hash(x);
    for (auto it = arr_[hashed].begin(); it != arr_[hashed].end();) {
      if (*it == x) {
        it = arr_[hashed].erase(it);
      } else {
        ++it;
      }
    }
    size_--;
    UpdateTable();
  }

  bool Contains(int x) { return Find(x); }

  int GetSize() const { return size_; }
  float GetLoadFactor() const { return load_factor_; }
  ~HashMap() { arr_.clear(); }
};

int main() {
  HashMap hm = HashMap();
  int q{};
  std::cin >> q;

  for (int i{}; i < q; i++) {
    char op{};
    int x{};
    std::cin >> op >> x;
    if (op == '+') {
      hm.Insert(x);
    } else if (op == '-') {
      hm.Erase(x);
    } else {
      if (hm.Contains(x)) {
        std::cout << "YES";
      } else {
        std::cout << "NO";
      }
      std::cout << "\n";
    }
  }
}