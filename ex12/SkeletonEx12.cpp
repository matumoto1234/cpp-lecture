/*
 * @file SkeltonEx12.cpp
 * @brief Skelton of Ex-12 ofin PL04: Programming C++
 * @author Keitaro Naruse
 * @date 2022-11-17
 * @copyright MIT License
 * */
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <memory>

//  Put class Vec here
//  You can import the source file in ex11
template <class T>
class Vec {
public:
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  Vec() {
    create();
  };
  explicit Vec(size_type n, const T &val = T()) {
    create(n, val);
  };
  Vec(const Vec &v) {
    create(v.begin(), v.end());
  };
  Vec<T> &operator=(const Vec &rhs);
  ~Vec() {
    uncreate();
  };
  T &operator[](size_type i) {
    return data[i];
  };
  const T &operator[](size_type i) const {
    return data[i];
  };
  void push_back(const T &val) {
    if (avail == limit) {
      grow();
    }
    unchecked_append(val);
  }
  void clear() {
    uncreate();
  }
  size_type size() const {
    return avail - data;
  };
  iterator begin() {
    return data;
  };
  const_iterator begin() const {
    return data;
  };
  iterator end() {
    return avail;
  };
  const_iterator end() const {
    return avail;
  };

private:
  iterator data;
  iterator avail;
  iterator limit;
  std::allocator<T> alloc;
  void create();
  void create(size_type, const T &);
  void create(const_iterator, const_iterator);
  void uncreate();
  void grow();
  void unchecked_append(const T &);
};

/*
    Vec<T>::operator=
        Assignment operator
*/
template <class T>
Vec<T> &Vec<T>::operator=(const Vec &rhs) {
  if (&rhs != this) { // 自己代入でなければ
    uncreate();
    create(rhs.begin(), rhs.end());
  }
  return *this;
}

/*
    Vec<T>::create()
        Initialize function (default)
*/
template <class T>
void Vec<T>::create() {
  data = avail = limit = 0;
}

/*
    Vec<T>::create()
        Initialize function with size and value
*/
template <class T>
void Vec<T>::create(size_type n, const T &val) {
  data = alloc.allocate(n);
  limit = avail = data + n;
  std::uninitialized_fill(data, limit, val);
}

/*
    Vec<T>::create()
        Initialize function with iterators
*/
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
  data = alloc.allocate(j - i);
  limit = avail = std::uninitialized_copy(i, j, data);
}

/*
    Vec<T>::uncreate()
        Finalize function
*/
template <class T>
void Vec<T>::uncreate() {
  if (data) {
    iterator it = avail;
    while (it != data) {
      alloc.destroy(--it);
    }
    alloc.deallocate(data, limit - data);
  }
  data = limit = avail = 0;
}

/*
    Vec<T>::grow()
        Increase data size
*/
template <class T>
void Vec<T>::grow() {
  size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1)); // メモリの確保と既存の内容のコピー
  iterator new_data = alloc.allocate(new_size);
  iterator new_avail = std::uninitialized_copy(data, avail, new_data);
  uncreate();
  data = new_data;
  avail = new_avail;
  limit = data + new_size;
}

/*
    Vec<T>::unchecked_append()
        Append data
*/
template <class T>
void Vec<T>::unchecked_append(const T &val) {
  alloc.construct(avail++, val);
}

class Str {
public:
  friend std::istream &operator>>(std::istream &, Str &);
  typedef Vec<char>::size_type size_type;
  Str(){};
  Str(size_type n, char c) : data(n, c){};
  Str(const char *cp) {
    std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
  }
  template <class In>
  Str(In b, In e) {
    std::copy(b, e, std::back_inserter(data));
  }
  char &operator[](size_type i) {
    return data[i];
  };
  const char &operator[](size_type i) const {
    return data[i];
  }
  size_type size() const {
    return data.size();
  }
  Str &operator+=(const Str &s) {
    std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
    return *this;
  }
  bool operator==(const Str &s) const {
    return strcmp(data.begin(), s.data.begin()) == 0;
  }
  bool operator!=(const Str &s) const {
    return strcmp(data.begin(), s.data.begin()) != 0;
  }
  char *begin() {
    return data.begin();
  }
  char *end() {
    return data.end();
  }

private:
  Vec<char> data;
};
std::ostream &operator<<(std::ostream &, const Str &);

std::ostream &operator<<(std::ostream &os, const Str &s) {
  for (Str::size_type i = 0; i != s.size(); ++i)
    os << s[i];

  return os;
}

std::istream &operator>>(std::istream &is, Str &s) {
  s.data.clear();
  char c;
  while (is.get(c) && isspace(c))
    ;
  if (is) {
    do
      s.data.push_back(c);
    while (is.get(c) && !isspace(c));
    if (is)
      is.unget();
  }
  return is;
}

Str operator+(const Str &s, const Str &t) {
  Str r = s;
  r += t;
  return r;
}

int main(int argc, char *argv[]) {
  Str s1;
  Str s2(8, 'a');
  Str s3("Hello! How are you?");
  Str s4(s3.begin(), s3.end());

  std::cout << "s1:[" << s1 << "]" << std::endl;
  std::cout << "s2:[" << s2 << "]" << std::endl;
  std::cout << "s3:[" << s3 << "]" << std::endl;
  std::cout << "s4:[" << s4 << "]" << std::endl;
  if (s3 == s4) {
    std::cout << "#1: s3 is same as s4" << std::endl;
  } else {
    std::cout << "#1: s3 is different from s4" << std::endl;
  }
  s4[0] = 'h';
  std::cout << "s4:[" << s4 << "]" << std::endl;
  if (s3 == s4) {
    std::cout << "#2: s3 is same as s4" << std::endl;
  } else {
    std::cout << "#1: s3 is different from s4" << std::endl;
  }
  std::cout << "Finished" << std::endl;

  return 0;
}
