#include "Evolution/Population.hpp"

Population::Population(PopulationParam* param){
    this->param = param;
    genes.reserve(param->maxPopulationSize);
    fitness.reserve(param->maxPopulationSize);
};

Population::~Population(){
    delete param;
    param = NULL;
    for(int i = 0; i < genes.size(); ++i){
        delete[] genes[i];
        genes[i] = NULL;
    }
};
