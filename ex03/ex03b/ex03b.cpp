#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  int T;
  std::cin >> T;

  // 配列を0で初期化
  std::vector<int> data(T, 0);

  for (int _ = 0; _ < T; _++) {
    char c;
    std::cin >> c;

    if (c == 'a') {
      int i, x;
      std::cin >> i >> x;

      // 添字iに対する値を代入
      data[i] = x;
      continue;
    }
    if (c == 'd') {
      int i;
      std::cin >> i;

      // 添字iに対する値を削除(削除後の値は0とする)
      data.erase(data.begin() + i);
      continue;
    }
    if (c == 'p') {
      int i;
      std::cin >> i;

      // 添字iに対する値を出力
      std::cout << data[i] << "\n";
    }
  }
}