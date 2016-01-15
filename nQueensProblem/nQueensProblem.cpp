// nQueensProblem.cpp : Defines the entry point for the console application.
//
#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include "Population.h"

int main() {
	int dec = 1;
	
	while (dec == 1)
	{
		size_t n = 8;
		std::cout << "1  -  8-queens problem" << std::endl;
		std::cout << "2  -  Variable n-queens problem" << std::endl;
		int dec1;
		std::cin >> dec1;
		if (dec1 != 1 && dec1 != 2)
		{
			dec1 = 1;
			std::cout << "Invalid value!  Initiating 8-queens problem.";
		}
		else if (dec1 == 2)
		{
			std::cout << "Enter value n." << std::endl;
			std::cin >> n;
		}


		size_t pop =  200;
		Population* p = new Population(pop, n);

		p->print(std::cout);
		std::cout << std::endl << std::endl << "1  -  Reset" << std::endl << "2  -  Exit"<<std::endl;
		int dec2;
		std::cin >> dec2;
		if (dec2 == 2)
		{
			dec= 0;
		}
		else
		{
			std::cout << std::endl << std::endl<<std::endl;
		}
	}
	


        return 0;

}

#endif //POPULATION_H
