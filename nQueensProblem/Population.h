//Not tested

#include <iostream>
#include <stdlib.h>

/*
 * Class defines Population for the algorithm;
 * template parameter N sets n in n-Queens Problem
 */
class Population {

/*
 * Indiviual of the Population
 * m_iFitnness - Integer that represents the viability to use in Mutation/Crossover
 * m_rgQueenPositions - Integer Array with positions of Queens
 */
struct ChessBoard {

	/*
	* Constructor - Randomizes position of queens
	*/
	ChessBoard::ChessBoard(size_t board)
	{
		boardSize = board;
		m_rgQueenPositions = new int[boardSize];
		m_iFitness = 0;
		for (size_t i = 0; i < boardSize; i++) {
			m_rgQueenPositions[i] = rand() % boardSize;
		}
	}

	ChessBoard::~ChessBoard()
	{
		delete m_rgQueenPositions;
	}
        int m_iFitness;
		size_t boardSize;
		int *m_rgQueenPositions;



        /*
         * Function to set the fitness var
         */
        void fnCheckFitness() {
                std::cout << m_iFitness << std::endl;
                m_iFitness -= fnCheckRow() + fnCheckDiag();
                std::cout << m_iFitness << std::endl;
        }

        int fnCheckRow();
        int fnCheckDiag(); // TODO: combine with fnCheckRow; OR use Threads?

};

/*
 * Dynamic array that holds the Indiviuals (TODO: use vector instead?)
 */
ChessBoard **m_cbBestInd;
const static size_t m_cMaxPopulation = 500;
size_t boardSize;
size_t m_cPopulationCount;
ChessBoard **m_rgcbPopulation;

public:
Population(size_t, size_t);
~Population();
void fnRateFitness();
void fnGetBestInd();
void fnMutatePop();
void fnCrossoverPop();
virtual std::ostream& print(std::ostream& o) const;

};


 
Population ::~Population() {
        for(size_t i = 0; i < m_cPopulationCount; i++) {
                delete m_rgcbPopulation[i];
        }
        delete [] m_rgcbPopulation;
        delete m_cbBestInd;
}

/*
 * Constructor - Fills member Array with n (TODO: 50?!)
 */
Population ::Population(size_t ucInitialPopSize, size_t boardsize) {
        m_rgcbPopulation = new ChessBoard *[ucInitialPopSize]; //array initialize with ucInitialPopSize
        m_cPopulationCount = 0;
		boardSize = boardsize;
        std::cout << m_cPopulationCount << std::endl;
        for(size_t i = 0; i < ucInitialPopSize; i++) {
                m_rgcbPopulation[i] = new ChessBoard(boardSize);
                std::cout << m_rgcbPopulation[i]->m_iFitness << std::endl;
                //m_cPopulationCount++;
        }
        m_cPopulationCount = ucInitialPopSize;

        std::cout << ucInitialPopSize << std::endl;
}

/*
 * Rates Fitness for Individuals in Population
 */
void Population ::fnRateFitness() {

    std::cout << m_cPopulationCount << std::endl;

        for(size_t i = 0; i < m_cPopulationCount; i++) {
            std::cout << m_rgcbPopulation[i]->m_iFitness << std::endl;
            std::cout << i << std::endl;
                m_rgcbPopulation[i]->fnCheckFitness();
        }

}

/*
 * Checks if a queen is the only one in a vertical/horizontal row
 * counter to modify fitness var in Individuals
 */
int Population ::ChessBoard::fnCheckRow() {
        int i_cFitCountRow = 0;

        for(size_t i = 0; i < boardSize; i++) {
                for(size_t j = i+1; j < boardSize-i; j++) {
                        if(m_rgQueenPositions[i] == m_rgQueenPositions[j]) {
                                i_cFitCountRow++;
                        }
                }
        }

        return i_cFitCountRow;
}

/*
 * Checks if a queen is the only one in a diagonal row
 * counter to modify fitness var in Individuals
 */
int Population ::ChessBoard::fnCheckDiag() {
        int i_cFitCountDiag = 0;

        for(size_t i = 0; i < boardSize; i++) {
                for(size_t j = i+1; j < boardSize-i; j++) {
                        if(m_rgQueenPositions[j] == m_rgQueenPositions[i]+j || m_rgQueenPositions[j] == m_rgQueenPositions[i]-j) {
                                i_cFitCountDiag++;
                        }
                }
        }

        return i_cFitCountDiag;
}

 
void Population ::fnGetBestInd() {
    
}

 
void Population ::fnMutatePop() {

}

 
void Population ::fnCrossoverPop() {

}

std::ostream& Population ::print(std::ostream& o) const {
        o << "Population, N = " << boardSize << ", popCount = " << m_cPopulationCount <<  '\n';
        for(size_t i = 0; i < m_cPopulationCount; i++) {
                o << '\n';
                o << "Individual " << i << ", fitness = " << m_rgcbPopulation[i]->m_iFitness << '\n';
                o << "QueensPos: [";
                for(size_t j = 0; j < boardSize; j++) {
                        o << m_rgcbPopulation[i]->m_rgQueenPositions[j] << ' ';
                } o << ']' << '\n';
        }

        return o;
}
