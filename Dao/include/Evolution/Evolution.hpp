#ifndef EVOLUTION_EVOLUTION_HPP
#define EVOLUTION_EVOLUTION_HPP

#include "Evolution/Crossover.hpp"
#include "Evolution/Population.hpp"
#include "Evolution/Selection.hpp"
#include "Evolution/Diversity.hpp"

struct EvolutionParam
{
    CrossoverType crossoverType;
    SelectionType selectionType;
    double selectRate;
    DiversityType diversityType;

};


class Evolution{
    public:
    Selection* selection;
    Crossover* crossover;
    Population* population;
    Diversity* diversity;
    EvolutionParam param;

    Evolution(Population* pop, EvolutionParam& param);
    ~Evolution();

    virtual void init();
    virtual void start();

};

#endif