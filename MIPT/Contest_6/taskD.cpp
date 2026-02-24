#include <cstring>
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
  std::vector<std::list<std::string>> arr_;
  int m_;
  int p_;
  int a_;
  int b_;
  int size_;
  float load_factor_;

  int HashStr(const std::string& st) const {
    long long hash = 0;
    for (char c : st) {
      hash = (hash * a_ + c) % p_;
    }
    return (int)((a_ * hash + b_) % p_ % m_);
  }

  //   int Hash(int x) const {
  //     int64_t res = ((int64_t)a_ * x + b_) % p_;
  //     if (res < 0) {
  //       res += p_;
  //     }
  //     return (int)(res % m_);
  //   }

  bool Find(const std::string& x) {
    int hashed = HashStr(x);
    for (const std::string& val : arr_[hashed]) {
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
    std::vector<std::list<std::string>> old_arr = std::move(arr_);

    m_ *= 2;
    arr_.clear();
    arr_.resize(m_);

    std::uniform_int_distribution<int> distribution(1, p_ - 1);
    a_ = distribution(generator);
    b_ = distribution(generator);

    for (int i = 0; i < old_m; ++i) {
      for (std::string val : old_arr[i]) {
        int hashed = HashStr(val);
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

  void Insert(std::string x) {
    if (Find(x)) {
      return;
    }
    int hashed = HashStr(x);
    arr_[hashed].push_back(x);
    size_++;
    UpdateTable();
  }

  void Erase(std::string x) {
    if (!Find(x)) {
      return;
    }
    int hashed = HashStr(x);
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

  bool Contains(std::string x) { return Find(x); }

  int GetSize() const { return size_; }
  float GetLoadFactor() const { return load_factor_; }
  ~HashMap() { arr_.clear(); }

  static std::string Canon(const std::string& s) {
    const int cAlphabet = 26;
    int mp[cAlphabet];
    memset(mp, -1, sizeof(mp));

    std::string res;
    int nxt = 0;

    for (char c : s) {
      int id = c - 'a';
      if (mp[id] == -1) {
        mp[id] = nxt++;
      }
      res.push_back(char('a' + mp[id]));
    }
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  HashMap hm;

  for (int i{}; i < q; i++) {
    char type;
    std::string t;
    std::cin >> type >> t;

    std::string key = HashMap::Canon(t);

    if (type == '+') {
      hm.Insert(key);
    } else {
      std::cout << (hm.Contains(key) ? "YES\n" : "NO\n");
    }
  }
}