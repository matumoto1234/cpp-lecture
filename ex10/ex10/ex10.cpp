#include <algorithm>
#include <fstream>
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

  // 総合点の成績評価
  std::string evaluation() const {
    const double g = grade();
    if (g >= 90.0) {
      return "A";
    }
    if (g >= 80.0) {
      return "B+";
    }
    if (g >= 70.0) {
      return "B";
    }
    if (g >= 60.0) {
      return "C+";
    }
    if (g >= 50.0) {
      return "C";
    }
    return "D";
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

  friend std::istream &operator>>(std::istream &is, Student_info &student) {
    std::string student_id, first_name, last_name;
    int midterm_exam_score, final_exam_score;

    if (not(is >> student_id >> last_name >> first_name >> midterm_exam_score >> final_exam_score)) {
      return is;
    }

    student = Student_info(first_name, last_name, student_id, midterm_exam_score, final_exam_score);

    // 行を読み込み
    std::string line;
    std::getline(is, line);

    // 読み込んだ行をistreamに変換
    std::stringbuf buf(line.c_str());
    std::istream line_is(&buf);

    int assignment_score;
    while (line_is >> assignment_score) {
      student.push_assignment(assignment_score);
    }

    return is;
  }
};

/**
 * @brief EOFまでinput_student()で読み込んで生徒のリストとして返す
 *
 * @param ifs 入力ファイルストリーム
 *
 * @return std::vector<Student> EOFまで読み込んだ際の生徒のリスト
 */
std::vector<Student_info> input_student_list(std::ifstream &ifs) {
  std::vector<Student_info> student_list;
  while (true) {
    Student_info student;
    ifs >> student;

    if (student.is_empty()) {
      break;
    }

    student_list.push_back(student);
  }
  return student_list;
}

/**
 * @brief 生徒のリストを出力するクラス
 */
class StudentListPrinter {
  std::ostream &os_;

  std::size_t max_name_width(const std::vector<Student_info> &student_list) {
    std::size_t max_width = 0;
    for (const auto &student: student_list) {
      max_width = std::max(max_width, student.first_name().size());
      max_width = std::max(max_width, student.last_name().size());
    }
    return max_width;
  }

  std::size_t max_id_width(const std::vector<Student_info> &student_list) {
    std::size_t max_width = 0;
    for (const auto &student: student_list) {
      max_width = std::max(max_width, student.student_id().size());
    }
    return max_width;
  }

public:
  StudentListPrinter(std::ostream &os) : os_(os) {}

  void print(const std::vector<Student_info> &student_list) {
    const std::size_t name_width = max_name_width(student_list);
    const std::size_t id_width = max_id_width(student_list);
    constexpr std::size_t score_width = 5;
    constexpr std::size_t evaluation_width = 5;

    // clang-format off
    // 事前に枠を定義
    const std::string equal_frame = "+" + std::string(name_width, '=') +
                                    "+" + std::string(name_width, '=') +
                                    "+" + std::string(id_width, '=') +
                                    "+" + std::string(score_width , '=') +
                                    "+" + std::string(score_width , '=') +
                                    "+" + std::string(evaluation_width, '=') + "+";

    const std::string hyphen_frame = "+" + std::string(name_width, '-') +
                                    "+" + std::string(name_width, '-') +
                                    "+" + std::string(id_width, '-') +
                                    "+" + std::string(score_width, '-') +
                                    "+" + std::string(score_width, '-') +
                                    "+" + std::string(evaluation_width, '-') + "+";
    // clang-format on

    os_ << equal_frame << "\n";

    for (std::size_t i = 0; i < student_list.size(); i++) {
      const bool is_begin_row = i == 0;
      const bool is_per5rows = i % 5 == 0;
      const bool is_end_row = i + 1 == student_list.size();
      // 初めと最後以外で5行ごとにハイフンの枠を出力
      if ((not is_begin_row) and is_per5rows and (not is_end_row)) {
        os_ << hyphen_frame << i << "\n";
      }

      const Student_info &student = student_list[i];

      // first_nameの枠の文字列
      std::stringstream first_name_stream;
      first_name_stream << std::setfill(' ') << std::setw(name_width) << std::left << student.first_name();

      // last_nameの枠の文字列
      std::stringstream last_name_stream;
      last_name_stream << std::setfill(' ') << std::setw(name_width) << std::left << student.last_name();

      // student_idの枠の文字列
      std::stringstream student_id_stream;
      student_id_stream << std::setfill(' ') << std::setw(id_width) << student.student_id();

      // 演習中央値の枠の文字列
      std::stringstream median_stream;
      median_stream << std::setfill(' ') << std::setw(score_width) << std::right << std::fixed << std::setprecision(1) << student.median();

      // 総合点の枠の文字列
      std::stringstream total_stream;
      total_stream << std::setw(score_width) << std::right << std::fixed << std::setprecision(1) << student.grade();

      // 成績評価の枠の文字列
      std::stringstream evaluation_stream;
      evaluation_stream << std::setfill(' ') << std::setw(evaluation_width) << std::right << student.evaluation();

      if (student.assignment_score_list().empty()) {
        // clang-format off
        // 出力
        os_
            << "|" << last_name_stream.str()
            << "|" << first_name_stream.str()
            << "|" << student_id_stream.str()
            << "|" << std::setfill(' ') << std::left << std::setw(score_width * 3 + /* number of "|"= */2) << " No grade"
            << "|\n";
        // clang-format on
      } else {
        // clang-format off
        // 出力
        os_
            << "|" << last_name_stream.str()
            << "|" << first_name_stream.str()
            << "|" << student_id_stream.str()
            << "|" << median_stream.str()
            << "|" << total_stream.str()
            << "|" << evaluation_stream.str()
            << "|\n";
        // clang-format on
      }
    }

    os_ << equal_frame << "\n";
  }
};

int main(int argc, char *argv[]) {
  // 入力
  std::ifstream in(argv[1]);
  std::vector<Student_info> student_list = input_student_list(in);

  // ソート
  std::sort(student_list.begin(), student_list.end());

  // 出力
  std::ofstream out(argv[2]);
  StudentListPrinter printer(out);
  printer.print(student_list);
}
