#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // 入出力高速化
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // 定義
  std::vector<std::string> str_list;

  // 入力
  std::string c;
  while (std::cin >> c) {
    if (c == "a") {
      std::string s;
      std::cin >> s;

      // sを末尾に追加
      str_list.push_back(s);
      continue;
    }

    if (c == "d") {
      std::string s;
      std::cin >> s;

      auto removed_end_itr = std::remove(str_list.begin(), str_list.end(), s);

      // std::removeでは要素数が変更しないので、[removed_end_itr, str_list.end())を削除
      str_list.erase(removed_end_itr, str_list.end());
      continue;
    }

    if (c == "i") {
      std::string s, r;
      std::cin >> s >> r;

      // new_str_listにinsertしていく
      decltype(str_list) new_str_list;

      for (const auto &str: str_list) {
        if (str == s) {
          new_str_list.push_back(r);
        }
        new_str_list.push_back(str);
      }

      str_list = new_str_list;
      continue;
    }

    if (c == "r") {
      std::string s, r;
      std::cin >> s >> r;

      // 置換
      std::replace(str_list.begin(), str_list.end(), s, r);
      continue;
    }

    if (c == "p") {
      // 出力
      for (const auto &s: str_list) {
        std::cout << s << " ";
      }
      std::cout << "\n";
      continue;
    }
  }
}