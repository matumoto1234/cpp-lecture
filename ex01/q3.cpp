#include <iostream>
#include <string>

int main() {
  std::string family_name, first_name;

  // input the name.
  std::cout << "Please input the family name and first name separated by space\n";
  std::cin >> family_name >> first_name;

  // output the name.
  std::cout << first_name << " " << family_name << "\n";
}

