// nQueensProblem.cpp : Defines the entry point for the console application.
//
#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include "Population.h"

int main() {
		
	size_t n = 10;
	size_t pop = n * 25;
        Population* p = new Population(pop, n);

        p->print(std::cout);
		int no;
		std::cin >> no;


        return 0;

}

#endif //POPULATION_H
