#include <algorithm>
#include <iostream>
#include <list>
#include <string>

// 逆順にソートするためのstd::stringの比較関数
bool compare(const std::string &a, const std::string &b) {
  return a > b;
}

int main() {
  // 入力
  std::string id;
  std::list<std::string> IDs;
  while (std::cin >> id) {
    IDs.push_back(id);
  }

  // compareに従ってソート
  IDs.sort(compare);

  // 出力
  for (auto it = IDs.begin(); it != IDs.end(); it++) {
    std::string id = *it;
    std::cout << id << "\n";
  }
}