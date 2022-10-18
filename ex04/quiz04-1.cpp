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

int main() {
  std::vector<double> v;
  read(std::cin, v);
  for (const auto &V: v) {
    std::cout << V << "\n";
  }
}