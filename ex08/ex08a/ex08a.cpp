/*
 * @file skelton-ex-08a.cpp
 * @brief Skelton code of ex-08a in PL04: Programming C++
 * @author Keitaro Naruse
 * @date 2022-11-02
 * @copyright MIT License
 */
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

/**
 * @brief an originally implemented search function acting like std::search
 * @param[in] b, e, b2, e2
 * @return ForwardIterator an iterator of searched position
 * @details ;
 */
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 my_search(ForwardIterator1 b, ForwardIterator1 e, ForwardIterator2 b2, ForwardIterator2 e2) {
  for (; b != e; std::advance(b, 1)) {
    ForwardIterator1 itr1 = b;
    ForwardIterator2 itr2 = b2;
    while (true) {
      if (itr2 == e2) {
        return b;
      }

      if (itr1 == e) {
        return e;
      }

      if (*itr1 != *itr2) {
        break;
      }

      std::advance(itr1, 1);
      std::advance(itr2, 1);
    }
  }
  return b;
}

/**
 * @brief main
 * @return int return code
 * @details Do not change the codes in main
 */
int main() {
  //  Read N = [1, 10^5 ]
  int N;
  std::cin >> N;

  //  Read Si and store in vector and list
  std::vector<std::string> word_vector;
  std::list<std::string> word_list;
  for (int i = 0; i < N; i++) {
    std::string word;
    std::cin >> word;
    word_vector.push_back(word);
    word_list.push_back(word);
  }
  //  Read M = [1, 10^4 ]
  int M;
  std::cin >> M;
  //  Read queries
  for (int j = 1; j <= M; j++) {
    int K;
    std::cin >> K;
    std::vector<std::string> query_vector;
    std::list<std::string> query_list;
    for (int k = 0; k < K; k++) {
      std::string query;
      std::cin >> query;
      query_vector.push_back(query);
      query_list.push_back(query);
    }
    const int Q = 4;
    for (int q = 0; q < 4; q++) {
      bool is_found = true;
      if (q == 0) {
        //  Case 0, word: vector, query: vector
        if (my_search(word_vector.begin(), word_vector.end(), query_vector.begin(), query_vector.end()) == word_vector.end()) {
          is_found = false;
        }
      } else if (q == 1) {
        //  Case 1, word: vector, query: list
        if (my_search(word_vector.begin(), word_vector.end(), query_list.begin(), query_list.end()) == word_vector.end()) {
          is_found = false;
        }
      } else if (q == 2) {
        //  Case 2, word: list, query: vector
        if (my_search(word_list.begin(), word_list.end(), query_vector.begin(), query_vector.end()) == word_list.end()) {
          is_found = false;
        }
      } else if (q == 3) {
        //  Case 3, word: list, query: list
        if (my_search(word_list.begin(), word_list.end(), query_list.begin(), query_list.end()) == word_list.end()) {
          is_found = false;
        }
      }
      if (is_found) {
        std::cout << "Yes ";
      } else {
        std::cout << "No ";
      }
    }
    std::cout << std::endl;
  }

  return (0);
}
