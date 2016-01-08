// nQueensProblem.cpp : Defines the entry point for the console application.
//
#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include "Population.h"

int main() {

        Population* p = new Population(30, 8);
        /*const char helpStr[] =
           "This is a Helperstr\n"
           "It is here to help.\n";
         */
        std::cout << "alls gucci1" << std::endl;
        p->fnRateFitness();
        std::cout << "alls gucci2" << std::endl;
        p->print(std::cout);
        std::cout << "alls gucci3" << std::endl;
		int no;
		std::cin >> no;


        return 0;

}

#endif //POPULATION_H
