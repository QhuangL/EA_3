#ifndef EVOLUTION_DIVERSITY_HPP
#define EVOLUTION_DIVERSITY_HPP
#include "Evolution/Population.hpp"

enum DiversityType{DIS, NONE};

class Diversity{
    public:
        virtual double calculate()=0;
        Population* population;
};

class Distance:public Diversity{
    public:
        virtual double calculate();
};

#endif