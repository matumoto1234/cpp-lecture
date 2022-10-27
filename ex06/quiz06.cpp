#include <iostream>
#include <string>
#include <vector>

struct Tag {
  std::string tag;
  std::string element;

  Tag(): tag(""), element("") {}
  Tag(std::string tag, std::string element): tag(tag), element(element) {}
};

/**
 * @brief 文字列sの半開区間[left,right)の部分連続文字列を取得する
 *
 * @return 文字列sの半開区間[left,right)の部分連続文字列
 */
std::string substr(const std::string &s, std::size_t left, std::size_t right) {
  std::string sub = "";
  for (std::size_t i = left; i < right; i++) {
    sub += s[i];
  }
  return sub;
}

int main() {
  // xmlを定義
  const std::string xml = "<noun>I</noun> <verb>talk</verb> <adverb>about</adverb> <noun>running</noun>";

  // wordsを宣言
  std::vector<Tag> words;
  bool is_element = false;

  for (std::size_t i = 0; i < xml.size(); i++) {
    if (i + 1 < xml.size() and xml[i] == '<' and xml[i+1] == '/') {
      is_element = false;
      const std::size_t end = xml.find_first_of('>', i);
      i = end;
      continue;
    }

    if (xml[i] == '<') {
      const std::size_t end = xml.find_first_of('>', i);
      // clang-format off
      words.push_back(
        Tag(
          /*tag=*/ substr(xml, i+1, end),
          /*element=*/ ""
        )
      );
      // clang-format on
      i = end;
      is_element = true;
      continue;
    }

    if (words.empty() or not is_element) {
      continue;
    }
    words.back().element += xml[i];
  }

  // 出力
  for (const auto &word: words) {
    std::cout << "tag:" << word.tag << " element:" << word.element << "\n";
  }
}