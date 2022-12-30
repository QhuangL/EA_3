#include "Evolution/Crossover.hpp"

Twopoint::Twopoint(Population* pop){
    this->population = pop;
};

void Twopoint::crossover(){
    const auto npop = population->genes.size();
    auto& genes = population->genes;
    auto& mpop = population->param->maxPopulationSize;
    auto& mgene = population->param->maxGeneLength;
    
    std::vector<int> cindex(npop);
    std::iota(cindex.begin()+1, cindex.end(), 1);
    std::random_shuffle(cindex.begin(), cindex.end());
    
    for(int i = 0; i< npop/2; ++i){
        genes.push_back(std::vector<double>(genes[cindex[i]]));
        genes.push_back(std::vector<double>(genes[cindex[i+1]]));
        int p1 = rand()%(mgene - 1);
        int p2 = rand() % (mgene-p1-1) + p1+1;
        
    }
};


