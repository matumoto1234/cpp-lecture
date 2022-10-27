#include "hoge.h"

A::A() {}

A::A(int value): value_(value) {}

A *A::create() const {
  return &A();
}

A *A::clone() const {
  
}
