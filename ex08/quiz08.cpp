#include <iostream>
#include <iterator>
#include <list>
#include <string>

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

int main() {
  // 入力
  std::string word;
  std::list<std::string> words;
  while (std::cin >> word) {
    words.push_back(word);
  }

  bool is_inserted = false;
  // 奇数個の要素数なら番兵を末尾に挿入
  if (words.size() % 2 == 1) {
    std::string back = words.back();
    words.push_back(back);
    is_inserted = true;
  }

  for (auto itr = words.begin(); itr != words.end(); std::advance(itr, 2)) {
    swap(*itr, *std::next(itr));
  }

  // 奇数個の要素数なら番兵を削除
  if (is_inserted) {
    words.pop_back();
  }

  // 出力
  for (auto word: words) {
    std::cout << word << "\n";
  }
}
