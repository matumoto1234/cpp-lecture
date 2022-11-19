#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream in(argv[1]);
  std::ofstream out(argv[2]);
  std::vector<std::string> v;
  std::string s;

  // 入力
  while (in >> s) {
    v.push_back(s);
  }

  // ソート
  sort(v.begin(), v.end());

  // 出力
  for(const auto &s : v) {
    out << s << "\n";
  }

  return 0;
}
