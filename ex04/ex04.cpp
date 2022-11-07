#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

struct Student {
  std::string first_name;
  std::string last_name;
  std::string student_id;
  int midterm_exam_score_;
  int final_exam_score;
  std::vector<int> assignment_score_list;

  Student(): first_name(""), last_name(""), student_id(""), midterm_exam_score_(0), final_exam_score(0), assignment_score_list() {}

  constexpr static std::size_t max_name_size = 16;
  constexpr static std::size_t max_student_id_size = 9;

  // 演習点の総和
  double sum_assignment_score() const {
    return std::accumulate(assignment_score_list.begin(), assignment_score_list.end(), 0.0);
  }

  // 演習点の平均値
  double average_assignment_score() const {
    if (assignment_score_list.empty()) {
      return 0.0;
    }
    return sum_assignment_score() / double(assignment_score_list.size());
  }

  // 演習点の中央値
  double median_assignment_score() const {
    if (assignment_score_list.empty()) {
      return 0.0;
    }

    auto score_list = assignment_score_list;
    std::sort(score_list.begin(), score_list.end());

    // 要素数が偶数個の場合
    if (score_list.size() % 2 == 0) {
      return (score_list[score_list.size() / 2 - 1] + score_list[score_list.size() / 2]) / 2.0;
    }

    // 要素数が奇数個の場合
    return score_list[score_list.size() / 2];
  }

  // 総合点の計算
  double total_score() const {
    constexpr double midterm_exam_ratio = 20.0;
    constexpr int midterm_exam_perfect_score = 100;
    double midterm_exam = midterm_exam_ratio * midterm_exam_score_ / double(midterm_exam_perfect_score);

    constexpr double final_exam_ratio = 40.0;
    constexpr int final_exam_perfect_score = 100;
    double final_exam = final_exam_ratio * final_exam_score / double(final_exam_perfect_score);

    constexpr double median_assignment_score_ratio = 40.0;
    constexpr int median_assignment_score_perfect_score = 100;
    double median_assignment = median_assignment_score_ratio * median_assignment_score() / double(median_assignment_score_perfect_score);

    return midterm_exam + final_exam + median_assignment;
  }

  // 生徒の情報が空かどうか
  bool is_empty() const {
    return student_id == "";
  }
};

/**
 * @brief 生徒の情報を標準入力から受け取って返す
 *
 * @return Student EOFだった場合は空の生徒、そうでない場合は標準入力から読み込んだ生徒を返す
 */
Student input_student() {
  Student s;
  auto &&istream = (std::cin >> s.student_id >> s.first_name >> s.last_name >> s.midterm_exam_score_ >> s.final_exam_score);
  if (istream.eof()) {
    return Student();
  }

  int assignment_score;
  while (true) {
    std::cin >> assignment_score;

    bool is_input_end = assignment_score == -1;
    if (is_input_end) {
      break;
    }

    s.assignment_score_list.push_back(assignment_score);
  }

  return s;
}

/**
 * @brief EOFまでinput_student()で読み込んで生徒のリストとして返す
 *
 * @return std::vector<Student> EOFまで読み込んだ際の生徒のリスト
 */
std::vector<Student> input_student_list() {
  std::vector<Student> student_list;
  while (true) {
    Student student = input_student();
    if (student.is_empty()) {
      break;
    }

    student_list.push_back(student);
  }
  return student_list;
}

int main() {
  const std::vector<Student> student_list = input_student_list();

  // 出力の際の点の枠幅
  constexpr int score_frame_width = 8;

  // clang-format off
  // 事前に枠を定義
  const std::string equal_frame = "+" + std::string(Student::max_name_size, '=') +
                                  "+" + std::string(Student::max_name_size, '=') +
                                  "+" + std::string(Student::max_student_id_size, '=') +
                                  "+" + std::string(score_frame_width, '=') +
                                  "+" + std::string(score_frame_width, '=') +
                                  "+" + std::string(score_frame_width, '=') +
                                  "+" + std::string(score_frame_width, '=') + "+";
  const std::string hyphen_frame = "+" + std::string(Student::max_name_size, '-') +
                                   "+" + std::string(Student::max_name_size, '-') +
                                   "+" + std::string(Student::max_student_id_size, '-') +
                                   "+" + std::string(score_frame_width, '-') +
                                   "+" + std::string(score_frame_width, '-') +
                                   "+" + std::string(score_frame_width, '-') +
                                   "+" + std::string(score_frame_width, '-') + "+";
  // clang-format on

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
      std::cout << hyphen_frame << i << "\n";
    }

    // first_nameの枠の文字列
    std::stringstream first_name_stream;
    first_name_stream << std::setfill(' ') << std::setw(Student::max_name_size) << std::left << student.first_name;

    // last_nameの枠の文字列
    std::stringstream last_name_stream;
    last_name_stream << std::setfill(' ') << std::setw(Student::max_name_size) << std::left << student.last_name;

    // student_idの枠の文字列
    std::stringstream student_id_stream;
    student_id_stream << std::setfill(' ') << std::setw(Student::max_student_id_size) << std::left << student.student_id;

    // 演習合計点の枠の文字列
    std::stringstream sum_stream;
    sum_stream << std::setfill(' ') << std::setw(score_frame_width) << std::right << std::fixed << std::setprecision(1) << student.sum_assignment_score();

    // 演習平均点の枠の文字列
    std::stringstream average_stream;
    average_stream << std::setfill(' ') << std::setw(score_frame_width) << std::right << std::fixed << std::setprecision(1) << student.average_assignment_score();

    // 演習中央値の枠の文字列
    std::stringstream median_stream;
    median_stream << std::setfill(' ') << std::setw(score_frame_width) << std::right << std::fixed << std::setprecision(1) << student.median_assignment_score();

    // 総合点の枠の文字列
    std::stringstream total_stream;
    total_stream << std::setfill(' ') << std::setw(score_frame_width) << std::right << std::fixed << std::setprecision(1) << student.total_score();

    // clang-format off
    // 出力
    std::cout << "|" << first_name_stream.str()
              << "|" << last_name_stream.str()
              << "|" << student_id_stream.str()
              << "|" << sum_stream.str()
              << "|" << average_stream.str()
              << "|" << median_stream.str()
              << "|" << total_stream.str()
              << "|\n";
    // clang-format on
  }

  // 最後の行を出力
  std::cout << equal_frame << "\n";
}