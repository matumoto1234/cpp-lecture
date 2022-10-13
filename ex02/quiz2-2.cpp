#include <iostream>
#include <string>
using namespace std;

int main() {
  int count = 0;
  string s;

  // EOFまで読み込む
  while (cin >> s) {
    // 文字列数をインクリメント
    count++;
  }
  cout << count << endl;
}