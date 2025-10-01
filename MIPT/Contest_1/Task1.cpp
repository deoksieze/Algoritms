#include <iostream>
#include <vector>

// Думаю, что было излишне писать эту структуры и операторы перегружать, но я
// хотел попробовать
struct Section {
  int left;
  int right;

  friend bool operator<(const Section& s1, const Section& s2) {
    return (s1.left < s2.left) ||
           ((s1.left == s2.left) && (s1.right <= s2.right));
  }
  friend bool operator>(const Section& s1, const Section& s2) {
    return operator<(s2, s1);
  }
};

using Pairs = std::vector<Section>;
Pairs Merge(Pairs arr1, Pairs arr2) {
  Pairs back(arr1.size() + arr2.size());

  size_t i1{};
  size_t i2{};
  size_t index{};

  while (i1 < arr1.size() && i2 < arr2.size()) {
    if (arr1[i1] < arr2[i2]) {
      back[index] = arr1[i1];
      i1++;
    } else {
      back[index] = arr2[i2];
      i2++;
    }
    index++;
  }
  if (i1 == arr1.size()) {
    for (size_t i = i2; i < arr2.size(); i++) {
      back[index] = arr2[i];
      index++;
    }
  } else {
    for (size_t i = i1; i < arr1.size(); i++) {
      back[index] = arr1[i];
      index++;
    }
  }

  return back;
}

Pairs MergeSort(Pairs arr) {
  if (arr.size() <= 1) {
    return arr;
  }

  if (arr.size() == 2) {
    if (arr[0].left > arr[1].left) {
      return Pairs{arr[1], arr[0]};
    }
    return arr;
  }

  auto mid = arr.begin() + arr.size() / 2;
  return Merge(MergeSort(Pairs(arr.begin(), mid)),
               MergeSort(Pairs(mid, arr.end())));
}

int main() {
  size_t n{};
  std::cin >> n;
  Pairs arr(n);
  for (size_t i = 0; i < n; i++) {
    int l{};
    int r{};
    std::cin >> l >> r;
    arr[i] = {l, r};
  }

  auto sorted = MergeSort(arr);

  Pairs answer(n);
  size_t ind{0};

  Section sec{sorted[0].left, sorted[0].right};
  for (auto i : sorted) {
    if (sec.right < i.left) {
      answer[ind].left = sec.left;
      answer[ind].right = sec.right;
      sec.left = i.left;
      sec.right = i.right;
      ind++;
    } else {
      sec.right = sec.right > i.right ? sec.right : i.right;
    }
  }

  answer[ind].left = sec.left;
  answer[ind].right = sec.right;
  ind++;

  std::cout << ind << "\n";
  for (size_t i = 0; i < ind; i++) {
    std::cout << answer[i].left << " " << answer[i].right << "\n";
  }
}