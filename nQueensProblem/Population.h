#include <iostream>
#include <stdlib.h>

template <int N>
class Population {

  template <int N>
  struct ChessBoard {
    int m_iFitness;
    int m_rgQueenPositions[N-1];

    ChessBoard(): m_iFitness(0) {
      for(size_t i = 0; i < N; i++) {
        m_rgQueenPositions[i] = std::rand() % N;
      }
    };

    void fnCheckFitness() {
      for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N-i; j++) {
          if(m_rgQueenPositions[i] == m_rgQueenPositions[j]) {
            m_iFitness--;
          }
        }
      }
    }
  };

  ChessBoard **m_rgcbPopulation;

public:
Population<N>::Population() {
  for(size_t i = 0; i < 50; i++) {
    m_rgcbPopulation[i] = new ChessBoard;
  }
}

};
