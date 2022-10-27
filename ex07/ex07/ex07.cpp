#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  /**
   * 以下のような構造を作る
   * "hoge": {1,2,2,3,5}
   * "word": {2,30,42}
   * "aiueo": {2,10,10,10,20}
   */
  map<string, vector<int>> word_to_row_number_list;

  // n行入力
  for (int row = 0; row < n; row++) {
    // 1行分入力
    string s;
    getline(cin, s);

    // 入力ストリームに変換
    stringbuf str_buf(s.c_str());
    istream is(&str_buf);

    // 空白区切りでwordを入力し、wordに対して行番号を追加する
    string word;
    while (is >> word) {
      word_to_row_number_list[word].push_back(row);
    }
  }

  int m;
  cin >> m;

  // m行入力して行番号を出力する
  for (int i = 0; i < m; i++) {
    string word;
    cin >> word;

    // wordが存在するなら行番号のリストを出力
    bool exists = word_to_row_number_list.find(word) != word_to_row_number_list.end();
    if (exists) {
      const auto &row_number_list = word_to_row_number_list[word];
      for (const auto &row_number: row_number_list) {
        cout << row_number << " ";
      }
      cout << "\n";
    } else {
      cout << -1 << "\n";
    }
  }
}