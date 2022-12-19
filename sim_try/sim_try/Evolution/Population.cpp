#include "Evolution/Population.hpp"

Population::Population(PopulationParam* param){
    this->param = param;
    population.reserve(param->maxPopulationSize);
    fitness.reserve(param->maxPopulationSize);
};

Population::~Population(){
    delete param;
};

std::vector<double>* StringPopulation::randomIndividual(){
    
};