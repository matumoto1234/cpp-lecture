#include <algorithm>
#include <iostream>
#include <vector>

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
  {
    std::vector<double> v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    std::cout << median(v) << "\n";
  }
  {
    std::vector<double> v = { 1.0, 2.0, 3.0, 4.0 };

    std::cout << median(v) << "\n";
  }
}
