//Not tested

#include <iostream>
#include <stdlib.h>
#include <ctime>

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
	ChessBoard(size_t board)
	{
		m_boardSize = board;
		m_rgQueenPositions = new int[m_boardSize];
		m_iFitness = 0;
		for (size_t i = 0; i < m_boardSize; i++) {
			m_rgQueenPositions[i] = rand() % m_boardSize;
		}
	}

	~ChessBoard()
	{
		delete m_rgQueenPositions;
	}
        int m_iFitness;
		size_t m_boardSize;
		int *m_rgQueenPositions;



        /*
         * Function to set the fitness var
         */
        void fnCheckFitness() {
			m_iFitness = fnCheck();
        }

        int fnCheck();

};

/*
 * Dynamic array that holds the Indiviuals (TODO: use vector instead?)
 */
ChessBoard **m_cbBestInd;
const static size_t m_cMaxPopulation = 500;
size_t m_boardSize;
size_t m_cPopulationCount;
size_t m_bestPop;
ChessBoard **m_rgcbPopulation;

public:
Population(size_t, size_t);
~Population();
void fnRateFitness();
void fnMutatePop();
void fnCrossoverPop();
void fnInitCycle();
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
		m_boardSize = boardsize;

        std::cout << m_cPopulationCount << std::endl;
        for(size_t i = 0; i < ucInitialPopSize; i++) {
                m_rgcbPopulation[i] = new ChessBoard(m_boardSize);
               // std::cout << m_rgcbPopulation[i]->m_iFitness << std::endl;
                //m_cPopulationCount++;
        }
        m_cPopulationCount = ucInitialPopSize;
		m_bestPop = m_cPopulationCount/6;
		fnRateFitness();
		fnInitCycle();
}

/*
 * Rates Fitness for Individuals in Population
 */
void Population ::fnRateFitness() {


        for(size_t i = 0; i < m_cPopulationCount; i++) {
            m_rgcbPopulation[i]->fnCheckFitness();
        }
		int min;
		size_t nextmin;
		for (size_t i = 0; i < m_cPopulationCount; i++)
		{
			min = m_rgcbPopulation[i]->m_iFitness;
			nextmin = 0;
			for (size_t j = i+1; j < m_cPopulationCount; j++)
			{
				if (min > m_rgcbPopulation[j]->m_iFitness)
				{
					nextmin = j;
					min = m_rgcbPopulation[j]->m_iFitness;
				}
			}
			if (nextmin != 0)
			{
				ChessBoard* temp = m_rgcbPopulation[i];
				m_rgcbPopulation[i] = m_rgcbPopulation[nextmin];
				m_rgcbPopulation[nextmin] = temp;
			}
		}

}

/*
 * Checks if a queen is the only one in a vertical/horizontal row
 * counter to modify fitness var in Individuals
 */
int Population ::ChessBoard::fnCheck() {
        int i_cFitCount = 0;

        for(size_t i = 0; i < m_boardSize; i++) {
			int pos = m_rgQueenPositions[i];
			int counter = 1;
                for(size_t j = i+1; j < m_boardSize; j++) {
					int testPos = m_rgQueenPositions[j];
                        if(pos == testPos) {
                                i_cFitCount++;
                        }
						if (pos == testPos + counter)
						{
							i_cFitCount++;
						}

						if (pos == testPos - counter)
						{
							i_cFitCount++;
						}
						counter++;
                }
        }

        return i_cFitCount;
}


 


 
void Population ::fnMutatePop() {


	for (size_t i = m_bestPop; i < m_cPopulationCount; i++)
	{
		int randDec = rand() % 2;
		if (randDec == 0)
		{
			size_t randGen = rand() % m_boardSize;
			m_rgcbPopulation[i]->m_rgQueenPositions[randGen] = rand() % m_boardSize;
		}
	}
}

 
void Population ::fnCrossoverPop() {


	for (size_t i = 0; i < m_cPopulationCount - m_bestPop; i++)
	{
		int dec = 1;
		if (i < m_bestPop);
		else if (i < m_cPopulationCount / 4)
			dec = rand() % 2;
		else if (i < m_cPopulationCount / 2)
		{
			dec = rand() % 3;
		}
		else if (i < m_cPopulationCount / 1.5)
		{
			dec = rand() % 5;
		}
		else
		{
			dec = 0;
		}
			if (dec == 1)
			{
				size_t rand1 = rand() % (m_cPopulationCount/2);
				size_t rand2 = rand() % m_boardSize;
				/*if (rand2 > m_boardSize / 2)
				{
					for (size_t j = m_boardSize; j > rand2; j--)
					{
						size_t temp = m_rgcbPopulation[i]->m_rgQueenPositions[j];
						m_rgcbPopulation[i]->m_rgQueenPositions[j] = m_rgcbPopulation[rand1]->m_rgQueenPositions[j];
						m_rgcbPopulation[rand1]->m_rgQueenPositions[j] = temp;
					}

				}
				else
				{
					for (size_t j = rand2; j < m_boardSize / 2; j++)
					{
						size_t temp = m_rgcbPopulation[i]->m_rgQueenPositions[j];
						m_rgcbPopulation[i]->m_rgQueenPositions[j] = m_rgcbPopulation[rand1]->m_rgQueenPositions[j];
						m_rgcbPopulation[rand1]->m_rgQueenPositions[j] = temp;
					}
				}*/
				size_t rand3 = rand() % m_boardSize;
				size_t temp = m_rgcbPopulation[i]->m_rgQueenPositions[rand3];
				m_rgcbPopulation[i]->m_rgQueenPositions[rand3] = m_rgcbPopulation[rand1]->m_rgQueenPositions[rand3];
				m_rgcbPopulation[rand1]->m_rgQueenPositions[rand3] = temp;
			}
	}
}

void Population::fnInitCycle()
{
	srand(time(NULL));
	int counter = 1;
	while (m_rgcbPopulation[0]->m_iFitness > 0)
	{

		fnCrossoverPop();
		fnMutatePop();
		fnRateFitness();
		counter++;
		if (counter % 1000 == 0)
		{
			std::cout << m_rgcbPopulation[0]->m_iFitness<<std::endl;
		}
	}
	std::cout << "cycle: " << counter<<std::endl;
}

std::ostream& Population ::print(std::ostream& o) const {
        o << "Population, N = " << m_boardSize << ", popCount = " << m_cPopulationCount <<  '\n';
        for(size_t i = 0; i < 2; i++) {
                o << '\n';
                o << "Individual " << i << ", fitness = " << m_rgcbPopulation[i]->m_iFitness << '\n';
                o << "QueensPos: [";
                for(size_t j = 0; j < m_boardSize; j++) {
                        o << m_rgcbPopulation[i]->m_rgQueenPositions[j] << ' ';
                } o << ']' << '\n';
        }
		for (size_t i = 0; i < m_boardSize; i++)
		{
			
			for (size_t j = 0; j < m_boardSize; j++)
			{
				if (m_rgcbPopulation[0]->m_rgQueenPositions[i] == j)
					o << 1<<" ";
				else
					o << 0<<" ";
			}
			o<< std::endl;
		}

        return o;
}
