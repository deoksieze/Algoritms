#include <iostream>
#include <list>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 generator(rd());
const float cLoad = 0.75;
const int cBigPi = 1000000007;
const int cM = 16;

struct Node {
  int val;
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

  int Hash(int x) const {
    int64_t res = ((int64_t)a_ * x + b_) % p_;
    if (res < 0) {
      res += p_;
    }
    return (int)(res % m_);
  }

  bool Find(int x) {
    int hashed = Hash(x);
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

    int old_m = m_;
    std::vector<std::list<Node>> old_arr = std::move(arr_);

    m_ *= 2;
    arr_.clear();
    arr_.resize(m_);

    std::uniform_int_distribution<int> distribution(1, p_ - 1);
    a_ = distribution(generator);
    b_ = distribution(generator);

    for (int i = 0; i < old_m; ++i) {
      for (Node node : old_arr[i]) {
        int hashed = Hash(node.val);
        arr_[hashed].push_back(node);
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
    int hashed = Hash(x);

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

  void Erase(int x) {
    int hashed = Hash(x);

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

  bool Contains(int x) { return Find(x); }

  int GetSize() const { return size_; }
  float GetLoadFactor() const { return load_factor_; }
  ~HashMap() { arr_.clear(); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  HashMap hash_map = HashMap();
  int n{};
  std::cin >> n;
  for (int i{}; i < n; i++) {
    int x{};
    std::cin >> x;
    hash_map.Insert(x);
  }

  int m{};
  std::cin >> m;
  std::vector<int> answer{};
  for (int i{}; i < m; i++) {
    int y{};
    std::cin >> y;
    if (hash_map.Contains(y)) {
      answer.push_back(y);
      hash_map.Erase(y);
    }
  }

  std::cout << answer.size() << "\n";
  for (auto i : answer) {
    std::cout << i << " ";
  }
}