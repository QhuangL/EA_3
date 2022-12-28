#ifndef EVOLUTION_EVOLUTION_HPP
#define EVOLUTION_EVOLUTION_HPP

#include "Evolution/Crossover.hpp"
#include "Evolution/Population.hpp"
#include "Evolution/Selection.hpp"

struct EvolutionParam
{
    CrossoverType crossoverType;
    SelectionType selectionType;
};


class Evolution{
    public:
    Selection* selection;
    Crossover* crossover;
    Population* population;
    EvolutionParam param;

    Evolution(Population* pop, EvolutionParam& param);
    ~Evolution();

    virtual void init();
    virtual void start();

};

#endif