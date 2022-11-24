#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename T>
class Handle {
private:
  T *ptr_;

public:
  Handle() : ptr_(nullptr) {}

  Handle(const Handle &h) {
    ptr_ = new T*(*h.ptr());
  }

  ~Handle() {
    delete ptr_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

  T &operator*() const {
    if (ptr_ != nullptr) {
      return *ptr_;
    }
    throw std::runtime_error("Handle::operator*() : Dereference of unbound Handle");
  }

  T *&ptr() {
    return ptr_;
  }
};

int main() {
  {
    Handle<int> h;
    h.ptr() = new int(42);

    std::cout << *h.ptr() << std::endl;

    assert(*h == 42);
    assert(bool(h) == true);
  }

  {
    Handle<char> h;
    h.ptr() = new char('a');

    std::cout << *h.ptr() << std::endl;

    assert(*h == 'a');
    assert(bool(h) == true);
  }
}
