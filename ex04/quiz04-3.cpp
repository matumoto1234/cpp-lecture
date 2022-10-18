#include <algorithm>
#include <iostream>
#include <vector>

std::istream &read(std::istream &is, std::vector<double> &v) {
  double val;

  // EOFまで入力
  while (is >> val) {
    v.push_back(val);
  }
  return is;
}

double median(std::vector<double> v) {
  // 空の場合
  if (v.empty()) {
    return -1.0;
  }

  std::sort(v.rbegin(), v.rend());

  // 要素数が偶数個の場合
  if (v.size() % 2 == 0) {
    return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0;
  }

  // 要素数が奇数個の場合
  return v[v.size() / 2];
}

int main() {
  // 入力
  std::vector<double> v;
  read(std::cin, v);

  // 中央値を取得
  double med = median(v);

  // 実数列と中央値を出力
  std::cout << "v:";
  for (std::size_t i = 0; i < v.size(); i++) {
    bool is_end = i == v.size() - 1;
    std::cout << v[i] << (is_end ? "\n" : " ");
  }

  std::cout << "median:" << med << "\n";
}
