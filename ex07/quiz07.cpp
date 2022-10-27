#include <iostream>
#include <map>
#include <string>

int main() {
  // 初期化
  std::map<std::string, std::string> phone_book = {
    std::pair("John", "555-0000"),
    std::pair("Paul", "555-1111"),
    std::pair("Ringo", "555-2222"),
    std::pair("George", "555-3333"),
  };

  // 出力
  for (const auto &[name, phone_number]: phone_book) {
    std::cout << "name:" << name << " phone number:" << phone_number << "\n";
  }
}
