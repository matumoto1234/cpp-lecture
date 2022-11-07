#include <iostream>
#include <string>

struct WordCount {
private:
  std::string Word;
  int Count;

public:
  WordCount() {}
  WordCount(const std::string &s, const int &c): Word(s), Count(c) {}

  std::string word() const {
    return Word;
  }

  int count() const {
    return Count;
  }

  void word(const std::string &s) {
    Word = s;
  }

  void count(const int &c) {
    Count = c;
  }
};

int main() {
  WordCount wc1, wc2("test2", 2);

  wc1.word("test1");
  wc1.count(2);
  std::cout << wc2.word() << " " << wc2.count() << std::endl;
}
