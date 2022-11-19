#include <iostream>
#include <vector>

template <class T> class Vec {
public:
  typedef T* iterator;  //  イテレータの型定義
  typedef const T* const_iterator;
  typedef std::size_t size_type;  //  サイズの型定義
  typedef T value_type; //  値の型定義

  Vec(); //  デフォルトコンストラクタ
  Vec(const Vec &vec); //  コピーコンストラクタ
  ~Vec(); //  デストラクタ
  Vec &operator=(const Vec &rhs); //  代入演算子
  size_type size() const; //  size()関数
  value_type &operator[](std::size_t index); //  []演算子
  const value_type &operator[](std::size_t index) const; //  const []演算子
  iterator begin(); // 先頭のイテレータを返す関数
  const_iterator begin() const; //読取専用の先頭イテレータを返す関数
  iterator end(); //終端イテレータを返す関数
  const_iterator end() const;   //読取専用の終端イテレータを返す関数

private:
  iterator  data;
  iterator  limit;
};

int main() {
}
