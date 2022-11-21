#include <iostream>
#include <string>

class UnderGrad {
  std::string name_;
  double exam_;

public:

  UnderGrad();

  std::string name() const;

  double grade() const;

  std::istream &read(std::istream &is, UnderGrad &ug);
};

class Grad : public UnderGrad {
  double thesis_;

public:

  Grad();

  double grade() const;

  std::istream &read(std::istream &is, Grad &g);
};

int main() {
}