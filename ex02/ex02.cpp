#include <iostream>
#include <string>
#include <vector>

/**
 * @brief 生徒に関する情報を保持しておくクラス
 */
class Student {
  std::string first_name_;
  std::string last_name_;
  std::string student_id_;

public:
  Student() = default;
  Student(std::string first_name, std::string last_name, std::string student_id): first_name_(first_name), last_name_(last_name), student_id_(student_id) {}

  constexpr static std::size_t max_name_size = 12;
  constexpr static std::size_t max_student_id_size = 8;

  std::string first_name() const {
    return first_name_;
  }

  std::string last_name() const {
    return last_name_;
  }

  std::string student_id() const {
    return student_id_;
  }
};

/**
 * @brief 学籍番号、ファーストネーム、ラストネームをEOFまで読み込む
 *
 * @return std::vector<Student> 読み取った生徒のリストを返す
 */
std::vector<Student> input_student_list() {
  std::vector<Student> student_list;
  std::string student_id, first_name, last_name;

  while (std::cin >> student_id >> first_name >> last_name) {
    student_list.push_back(Student(first_name, last_name, student_id));
  }

  return student_list;
}

int main() {
  // 入力
  std::vector<Student> student_list = input_student_list();

  // 事前に枠を定義
  const std::string equal_frame = "+=" + std::string(Student::max_name_size, '=') + "=+=" + std::string(Student::max_name_size, '=') + "=+=" + std::string(Student::max_student_id_size, '=') + "=+";
  const std::string hyphen_frame = "+-" + std::string(Student::max_name_size, '-') + "-+-" + std::string(Student::max_name_size, '-') + "-+-" + std::string(Student::max_student_id_size, '-') + "-+";

  // 初めの行の枠
  std::cout << equal_frame << "\n";

  // 途中の行を出力
  for (std::size_t i = 0; i < student_list.size(); i++) {
    const Student student = student_list[i];

    const bool is_begin_row = i == 0;
    const bool is_per5rows = i % 5 == 0;
    const bool is_end_row = i + 1 == student_list.size();
    // 初めと最後以外で5行ごとにハイフンの枠を出力
    if ((not is_begin_row) and is_per5rows and (not is_end_row)) {
      std::cout << hyphen_frame << "\n";
    }

    std::cout << "| " << student.last_name() << std::string(Student::max_name_size - student.last_name().size(), ' ')
              << " | " << student.first_name() << std::string(Student::max_name_size - student.first_name().size(), ' ')
              << " | " << student.student_id() << std::string(Student::max_student_id_size - student.student_id().size(), ' ')
              << " |\n";
  }

  // 最後の行を出力
  std::cout << equal_frame << "\n";
}