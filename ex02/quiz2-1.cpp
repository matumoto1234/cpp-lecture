#include <iostream>
#include <string>
using namespace std;

/**
 * @brief 3の倍数もしくは3が桁に含まれている数ならばtrue、それ以外はfalseを返す
 *
 * @param n 対象の数値
 * @return true 3の倍数もしくは3が桁に含まれている数
 * @return false true出ない場合
 */
bool is_valid(int n) {
  if (n % 3 == 0) {
    return true;
  }

  string s = to_string(n);
  for (auto c: s) {
    if (c == '3') {
      return true;
    }
  }
  return false;
}

int main() {
  for (int i = 1; i <= 100; i++) {
    // 数 i が3の倍数もしくは3が桁に含まれているかどうか
    if (is_valid(i)) {
      cout << i << endl;
    }
  }
}