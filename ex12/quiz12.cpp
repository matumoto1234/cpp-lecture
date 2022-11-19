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

class Str	{

public:
  typedef Vec<char>::size_type size_type;
  Str();//  デフォルトコンストラクタ

  Str(const std::size_t &n, const char &c);//  n個のcという文字（キャラクター）から文字列で初期化するコンストラクタ

  Str(const char *cp);//  cpというポインタが表す文字列で初期化するコンストラクタ

  template <typename Iterator>
  Str(Iterator b, Iterator e);//  テンプレート機能を用いてbからeで指定される範囲の文字列で初期化するコンストラクタ

  char &operator[](std::size_t index);//  添え字[]のオペレータ

  size_type size() const;//  文字列のサイズを返すsize()関数

  Str &operator+=(const Str &rhs);//  文字列の連結を行う+=オペレータ
  bool operator==(const Str &rhs) const;//  文字列が同一かの判定を行う==オペレータ
  bool operator!=(const Str &rhs) const;//  文字列が異なるかの判定を行う!=オペレータ

  friend std::istream &operator>>(std::istream &is, Str &rhs);//  入力ストリームから文字列を読み取りStrに保存するオペレータ>>

private:
  Vec<char> data;
};
