/*
 * @file skelton-ex-08b.cpp
 * @brief Sample solution code of ex-08b in PL04: Programming C++
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
 * @brief an originally implemented copy function acting like std::copy
 * @param[in] b, e InputIterator
 * @param[in] d Output iterator
 * @return OutputIterator of the next iterator
 * @details ;
 */
template <class InputIterator, class OutputIterator>
OutputIterator my_copy(InputIterator b, InputIterator e, OutputIterator d) {
  while (b != e) {
    *d++ = *b++;
  }
  return d;
}

/**
 * @brief main
 * @return int return code
 */
int main() {
  //  Read N = [1, 10^5 ]
  int N;
  std::cin >> N;
  //  Sentence
  std::vector<std::string> sentence_vector;
  std::list<std::string> sentence_list;
  for (int i = 0; i < N; i++) {
    //  Read command
    char c;
    std::cin >> c;
    //  Print word_vector and word_list
    if (c == 'p') {
      for (auto w: sentence_vector) {
        std::cout << w << " ";
      }
      std::cout << std::endl;
      for (auto w: sentence_list) {
        std::cout << w << " ";
      }
      std::cout << std::endl;
    } else if (c == 'b') {
      int M;
      std::cin >> M;
      std::list<std::string> word_vector;
      std::vector<std::string> word_list;
      for (int j = 0; j < M; j++) {
        std::string word;
        std::cin >> word;
        word_vector.push_back(word);
        word_list.push_back(word);
      }
      my_copy(word_vector.begin(), word_vector.end(), std::back_inserter(sentence_list));
      my_copy(word_list.begin(), word_list.end(), std::back_inserter(sentence_vector));
    }
  }

  return (0);
}
