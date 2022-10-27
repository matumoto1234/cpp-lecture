struct A {
  int value_;

  A();
  A(int value);
  A(const A &other);

  A *create() const;
  A *clone() const;
};
