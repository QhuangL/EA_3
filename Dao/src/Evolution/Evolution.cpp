#include "Evolution/Evolution.hpp"

Evolution::Evolution(Population* pop, EvolutionParam& param){
    
    switch (param.crossoverType)
    {
    case CrossoverType::TWOPOINT:
        crossover = dynamic_cast<Crossover*>(new Twopoint());
        break;
    
    default:
        break;
    }

    switch (param.selectionType)
    {
    case SelectionType::TRUNCATION:
        selection = dynamic_cast<Selection*>(new Truncation(param.selectRate));
        break;
    
    default:
        break;
    }

    switch (param.diversityType)
    {
    case DIS:
        diversity = dynamic_cast<Diversity*>(new Distance());
        break;
    case NONE:
        break;
    
    default:
        break;
    }
    
    population = pop;
};

Evolution::~Evolution(){
    delete selection;
    delete crossover;
};

void Evolution::init(){

};

void Evolution::start(){

};