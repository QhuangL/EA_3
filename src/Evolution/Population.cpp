#include "Evolution/Population.hpp"

Population::Population(PopulationParam* param){
    this->param = param;
    population.reserve(param->maxPopulationSize);
    fitness.reserve(param->maxPopulationSize);
};

Population::~Population(){
    delete param;
    param = NULL;
    for(int i = 0; i < population.size(); ++i){
        delete[] population[i];
        population[i] = NULL;
    }
};
