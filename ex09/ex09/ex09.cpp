#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

class Student_info {
  std::string first_name_;
  std::string last_name_;
  std::string student_id_;
  int midterm_exam_score_;
  int final_exam_score_;
  std::vector<int> assignment_score_list_;

public:
  // デフォルトコンストラクタ
  Student_info() : first_name_(""), last_name_(""), student_id_(""), midterm_exam_score_(0), final_exam_score_(0), assignment_score_list_() {}

  // 入力ストリームからデータを読み込んでそれを渡すスタイルのコンストラクタ
  Student_info(std::string first_name, std::string last_name, std::string student_id, int midterm_exam_score, int final_exam_score) :
    first_name_(first_name), last_name_(last_name), student_id_(student_id), midterm_exam_score_(midterm_exam_score), final_exam_score_(final_exam_score) {}

  std::string first_name() const {
    return first_name_;
  }

  std::string last_name() const {
    return last_name_;
  }

  std::string student_id() const {
    return student_id_;
  }

  int midterm_exam_score() const {
    return midterm_exam_score_;
  }

  int final_exam_score() const {
    return final_exam_score_;
  }

  std::vector<int> assignment_score_list() const {
    return assignment_score_list_;
  }

  // 演習点の総和
  double sum_assignment_score() const {
    return std::accumulate(assignment_score_list_.begin(), assignment_score_list_.end(), 0.0);
  }

  // 演習点の平均値
  double average_assignment_score() const {
    if (assignment_score_list_.empty()) {
      return 0.0;
    }
    return sum_assignment_score() / double(assignment_score_list_.size());
  }

  // 演習点の中央値
  double median() const {
    if (assignment_score_list_.empty()) {
      return 0.0;
    }

    auto score_list = assignment_score_list_;
    std::sort(score_list.begin(), score_list.end());

    // 要素数が偶数個の場合
    if (score_list.size() % 2 == 0) {
      return (score_list[score_list.size() / 2 - 1] + score_list[score_list.size() / 2]) / 2.0;
    }

    // 要素数が奇数個の場合
    return score_list[score_list.size() / 2];
  }

  // 総合点の計算
  double grade() const {
    constexpr double midterm_exam_ratio = 20.0;
    constexpr int midterm_exam_perfect_score = 100;
    double midterm_exam = midterm_exam_ratio * midterm_exam_score_ / double(midterm_exam_perfect_score);

    constexpr double final_exam_ratio = 40.0;
    constexpr int final_exam_perfect_score = 100;
    double final_exam = final_exam_ratio * final_exam_score_ / double(final_exam_perfect_score);

    constexpr double median_assignment_score_ratio = 40.0;
    constexpr int median_assignment_score_perfect_score = 100;
    double median_assignment = median_assignment_score_ratio * median() / double(median_assignment_score_perfect_score);

    return midterm_exam + final_exam + median_assignment;
  }

  // 演習の点数を追加する
  void push_assignment(int assignment_score) {
    assignment_score_list_.push_back(assignment_score);
  }

  // 生徒の情報が空かどうか
  bool is_empty() const {
    return student_id_ == "";
  }

  // < を定義
  bool operator<(const Student_info &rhs) const {
    if (last_name_ != rhs.last_name_) {
      return last_name_ < rhs.last_name_;
    }
    return first_name_ < rhs.first_name_;
  }

  // 出力の際の幅
  constexpr static std::size_t name_width = 11;
  constexpr static std::size_t id_width = 7;
  constexpr static std::size_t score_width = 5;

  friend std::ostream &operator<<(std::ostream &os, const Student_info &student) {
    // first_nameの枠の文字列
    std::stringstream first_name_stream;
    first_name_stream << "  " << std::setfill(' ') << std::setw(name_width) << std::left << student.first_name() << " ";

    // last_nameの枠の文字列
    std::stringstream last_name_stream;
    last_name_stream <<  "  " << std::setfill(' ') << std::setw(name_width) << std::left << student.last_name() << " ";

    // student_idの枠の文字列
    std::stringstream student_id_stream;
    student_id_stream << "  " << student.student_id() << "  ";

    // 演習中央値の枠の文字列
    std::stringstream median_stream;
    median_stream << " " << std::setfill(' ') << std::setw(score_width) << std::right << std::fixed << std::setprecision(1) << student.median() << " ";

    // 総合点の枠の文字列
    std::stringstream total_stream;
    total_stream << " " << std::setfill(' ') << std::setw(score_width) << std::right << std::fixed << std::setprecision(1) << student.grade() << " ";

    if (student.assignment_score_list().empty()) {
      // clang-format off
      // 出力
      os  << "|" << first_name_stream.str()
          << "|" << last_name_stream.str()
          << "|" << student_id_stream.str()
          << "|" << std::left << std::setw(15) << " no exercises"
          << "|";
      // clang-format on
    } else {
      // clang-format off
      // 出力
      os  << "|" << first_name_stream.str()
          << "|" << last_name_stream.str()
          << "|" << student_id_stream.str()
          << "|" << median_stream.str()
          << "|" << total_stream.str()
          << "|";
      // clang-format on
    }

    return os;
  }
};

/**
 * @brief 生徒の情報を標準入力から受け取って返す
 *
 * @return Student EOFだった場合は空の生徒、そうでない場合は標準入力から読み込んだ生徒を返す
 */
Student_info input_student() {
  std::string student_id, first_name, last_name;
  int midterm_exam_score, final_exam_score;

  if (not (std::cin >> student_id >> last_name >> first_name >> midterm_exam_score >> final_exam_score)) {
    return Student_info();
  }

  Student_info s(first_name, last_name, student_id, midterm_exam_score, final_exam_score);

  // 行を読み込み
  std::string line;
  std::getline(std::cin, line);

  // 読み込んだ行をistreamに変換
  std::stringbuf buf(line.c_str());
  std::istream is(&buf);

  int assignment_score;
  while(is >> assignment_score) {
    s.push_assignment(assignment_score);
  }

  return s;
}

/**
 * @brief EOFまでinput_student()で読み込んで生徒のリストとして返す
 *
 * @return std::vector<Student> EOFまで読み込んだ際の生徒のリスト
 */
std::vector<Student_info> input_student_list() {
  std::vector<Student_info> student_list;
  while (true) {
    Student_info student = input_student();
    if (student.is_empty()) {
      break;
    }

    student_list.push_back(student);
  }
  return student_list;
}

int main() {
  std::vector<Student_info> student_list = input_student_list();

  // ソート
  std::sort(student_list.begin(), student_list.end());

  // clang-format off
  // 事前に枠を定義
  const std::string equal_frame = "+" + std::string(Student_info::name_width + 3, '=') +
                                  "+" + std::string(Student_info::name_width + 3, '=') +
                                  "+" + std::string(Student_info::id_width + 4, '=') +
                                  "+" + std::string(Student_info::score_width + 2 , '=') +
                                  "+" + std::string(Student_info::score_width + 2, '=') + "+";

  const std::string hyphen_frame = "+" + std::string(Student_info::name_width + 3, '-') +
                                  "+" + std::string(Student_info::name_width + 3, '-') +
                                  "+" + std::string(Student_info::id_width + 4, '-') +
                                  "+" + std::string(Student_info::score_width + 2, '-') +
                                  "+" + std::string(Student_info::score_width + 2, '-') + "+";
  // clang-format on

  // 初めの行の枠
  std::cout << equal_frame << "\n";

  // 途中の行を出力
  for (std::size_t i = 0; i < student_list.size(); i++) {
    const Student_info student = student_list[i];

    const bool is_begin_row = i == 0;
    const bool is_per5rows = i % 5 == 0;
    const bool is_end_row = i + 1 == student_list.size();
    // 初めと最後以外で5行ごとにハイフンの枠を出力
    if ((not is_begin_row) and is_per5rows and (not is_end_row)) {
      std::cout << hyphen_frame << i << "\n";
    }

    // 出力
    std::cout << student << "\n";
  }

  // 最後の行を出力
  std::cout << equal_frame << "\n";
}
