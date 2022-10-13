#include <algorithm>
#include <iostream>
#include <vector>

namespace data_structure_library {
  using namespace std;
}

/**
 * @brief 累積和を計算する構造体
 *
 * set(k, x): 位置kに値xを代入
 * add(k, x): 位置kに値xを加算
 * get(k): 位置kの値を取得
 * build(): 現在の配列をもとに累積和配列を構築
 * query(): 半開区間[l, r)の累積和をΘ(1)で計算
 */
namespace data_structure_library {
  template <typename T>
  struct CumulativeSum {
    vector<T> data;
    CumulativeSum(int n): data(n + 1, 0) {}
    CumulativeSum(int n, T x): data(n + 1, x) {}

    void set(int k, T x) {
      data[k + 1] = x;
    }

    void add(int k, T x) {
      data[k + 1] = x;
    }

    T get(int k) {
      return data[k + 1];
    }

    void build() {
      for (int i = 0; i < static_cast<int>(data.size()) - 1; i++) {
        data[i + 1] += data[i];
      }
    }

    // [l,r)
    T query(int l, int r) {
      return data[r] - data[l];
    }
  };
} // namespace data_structure_library

// 型エイリアス
using ll = long long;

int main() {
  // Nの入力
  int N;
  std::cin >> N;

  // 値Xの配列を入力
  std::vector<int> Xs(N);
  for (auto &X: Xs) {
    std::cin >> X;
  }

  // 累積和配列を計算
  data_structure_library::CumulativeSum<ll> cumulative_sum(N);
  for (int i = 0; i < N; i++) {
    cumulative_sum.set(i, ll(Xs[i]));
  }

  // 累積和配列をビルド
  cumulative_sum.build();

  // Tの入力
  int T;
  std::cin >> T;

  // クエリに対して結果を出力
  for (int _ = 0; _ < T; _++) {
    int L, R;
    std::cin >> L >> R;

    std::cout << cumulative_sum.query(L, R) << "\n";
  }
}