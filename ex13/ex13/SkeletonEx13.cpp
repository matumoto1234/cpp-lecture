/*
 * @file SkeltonEx13.cpp
 * @brief Skelton of Ex-13 ofin PL04: Programming C++
 * @author Keitaro Naruse
 * @date 2022-11-17
 * @copyright MIT License
*/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace utility {

  double median(const std::vector<double> &value_list) {
    if (value_list.empty()) {
      return 0.0;
    }

    auto sorted = value_list;
    std::sort(sorted.begin(), sorted.end());

    // 要素数が偶数個の場合
    if (sorted.size() % 2 == 0) {
      return (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
    }

    // 要素数が奇数個の場合
    return sorted[sorted.size() / 2];
  }

  double grade(double midterm, double final, const std::vector<double> &homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * median(homework);
  }

  std::istream &read_homework(std::istream &is, std::vector<double> &homework) {
    std::string line;
    std::getline(is, line);

    std::stringbuf buf(line.c_str());
    std::istream line_is(&buf);

    double value;
    while (line_is >> value) {
      homework.push_back(value);
    }

    return is;
  }
} // namespace utility


/*
    Core class
        Provide core functions for student information
*/
class Core {
  friend class Student_info;

  std::string n;

public:
  Core() : midterm(0), final(0), n("") {}

  Core(std::istream &is) {
    read(is);
  };

  std::string name() const {
    return n;
  }

  virtual double grade() const {
    return utility::grade(midterm, final, homework);
  }

  virtual std::istream &read(std::istream &is) {
    read_common(is);
    utility::read_homework(is, homework);
    return is;
  }

protected:
  std::istream &read_common(std::istream &is) {
    is >> n >> midterm >> final;
    return is;
  }

  virtual Core *clone() const {
    return new Core(*this);
  }

  double midterm, final;
  std::vector<double> homework;
};

/*
    Grad class
        Provide a class for a graduate student
*/
class Grad: public Core {
  double thesis;

public:
  Grad() : thesis(0) {}
  Grad(std::istream &is) {
    read(is);
  }

  double grade() const {
    return std::min(Core::grade(), thesis);
  }

  std::istream &read(std::istream &is) {
    read_common(is);
    is >> thesis;
    utility::read_homework(is, homework);
    return is;
  }

protected:
  virtual Grad *clone() const {
    return new Grad(*this);
  }
};

/*
    Student_info class
        Provide a handle class
*/
class Student_info {
private:
  Core *cp;

public:
  Student_info() : cp(0) {}
  Student_info(std::istream &is) : cp(0) {
    read(is);
  }


  Student_info(const Student_info &student): cp(nullptr) {
    if (student.cp) {
      cp = student.cp->clone();
    }
  }

  ~Student_info() {
    delete cp;
  }
  std::istream &read(std::istream &is) {
    delete cp;

    char ch;
    is >> ch;

    if (ch == 'u') {
      cp = new Core(is);
    } else {
      cp = new Grad(is);
    }

    return is;
  }

  std::string name() const {
    if (cp) {
      return cp->name();
    }
    throw std::runtime_error("uninitialized");
  }

  bool valid() const {
    if (cp) {
      return not cp->homework.empty();
    }
    return false;
  }

  double grade() const {
    if (cp) {
      return cp->grade();
    }
    throw std::runtime_error("uninitialized");
  }

  static bool compare(const Student_info &s1, const Student_info &s2) {
    return s1.name() < s2.name();
  }

  Student_info &operator=(const Student_info &student) {
    if (&student != this) {
      delete cp;
      if (student.cp) {
        cp = student.cp->clone();
      } else {
        cp = nullptr;
      }
    }
    return *this;
  }
};

/*
    main()
*/
int main(int argc, char *argv[]) {
  std::vector<Student_info> students;
  Student_info record;
  std::string::size_type maxlen = 0;

  while (record.read(std::cin)) {
    maxlen = std::max(maxlen, record.name().size());
    students.push_back(record);
  }

  std::sort(students.begin(), students.end(), Student_info::compare);

  for (std::vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
    std::cout << students[i].name() << std::string(maxlen + 1 - students[i].name().size(), ' ');
    if (students[i].valid()) {
      double final_grade = students[i].grade();
      std::streamsize prec = std::cout.precision();
      std::cout << std::setprecision(3) << final_grade << std::setprecision(prec);
    } else {
      std::cout << "Caanot evaluate";
    }
    std::cout << std::endl;
  }

  return 0;
}
