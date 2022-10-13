#include <iostream>
#include <string>

/**
 * @brief first name, middle name, last nameを受け取って整形したメッセージを返す
 *
 * @param first_name
 * @param middle_name
 * @param last_name
 * @return std::string 整形されたメッセージ
 */
std::string formatted_message(std::string first_name, std::string middle_name, std::string last_name) {
  const std::string greeting = "* Hello, " + first_name + " " + middle_name + " " + last_name + "! *";

  const std::size_t width = greeting.size();

  return
    std::string(width, '*') + "\n" +
    "*" + std::string(width - 2, ' ') + "*" + "\n" +
    greeting + "\n" +
    "*" + std::string(width - 2, ' ') + "*" + "\n" +
    std::string(width, '*');
}

int main() {
  std::string first_name, middle_name, last_name;

  // 入力
  std::cout << "Please input your first name\n";
  std::cin >> first_name;

  std::cout << "Please input your middle name\n";
  std::cin >> middle_name;

  std::cout << "Please input your last name\n";
  std::cin >> last_name;

  const std::string message = formatted_message(first_name, middle_name, last_name);

  // 出力
  std::cout << message << "\n";

  /**
   * 仮にfirst_name, middle_name, last_nameがすべて "-" が入力された際の出力結果
   * *****************
   * *               *
   * * Hello, - - -! *
   * *               *
   * *****************
   */

  /**
   * 仮にfirst_name, middle_name, last_nameがすべて "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" が入力された際の出力結果
   * ********************************************************************************************************************************
   * *                                                                                                                              *
   * * Hello, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa! *
   * *                                                                                                                              *
   * ********************************************************************************************************************************
   */

  return 0;
}
