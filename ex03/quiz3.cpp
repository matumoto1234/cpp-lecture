#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int num;
  std::vector<int> b;

  // EOFまで読み込んだ値を配列bの末尾に追加
  while (std::cin >> num) {
    b.push_back(num);
  }

  // ソート
  std::sort(b.begin(), b.end());

  // 改行区切りで配列bの値を出力
  for (const auto &val: b) {
    std::cout << val << "\n";
  }
}