#ifndef EVOLUTION_CROSSOVER_HPP
#define EVOLUTION_CROSSOVER_HPP
#include "Evolution/Population.hpp"
#include <numeric>
#include <algorithm>

enum CrossoverType{ONEPOINT, TWOPOINT, SUBTREE};

struct CrossoverParam
{
    /* data */
};


class Crossover{
    public:
        virtual void crossover()=0;
        Population* population;
        CrossoverParam param;

};

class Onepoint: public Crossover{

};

class Twopoint: public Crossover{
    public:
        Twopoint(Population* pop);
        virtual void crossover() override;
};

#endif