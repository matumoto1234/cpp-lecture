#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

// 削除すべき文字を削除する関数
std::string remove_char(std::string s) {
  std::string should_remove_char_list = ".,'\"()";

  std::string formatted = "";

  for (const auto &c: s) {
    const bool should_remove = should_remove_char_list.find(c) != std::string::npos;
    if (should_remove) {
      continue;
    }
    formatted += c;
  }

  return formatted;
}

int main() {
  std::map<std::string, int> list;
  std::string s;

  while (std::cin >> s) {
    std::string word = remove_char(s);

    // 小文字に変換
    if (not word.empty()) {
      std::transform(word.begin(), word.end(), word.begin(), tolower);
    }

    // カウント
    list[word]++;
  }

  // 出力
  for (const auto &[word, count]: list) {
    std::cout << std::left << std::setw(18) << std::setfill(' ') << word << count << "\n";
  }
}
