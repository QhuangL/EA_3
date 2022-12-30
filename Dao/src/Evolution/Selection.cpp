#include "Evolution/Selection.hpp"

Selection::Selection(double rate, Population* pop){
    this->rate = rate;
    this->population = pop;
};

Truncation::Truncation(double rate, Population* pop):Selection(rate, pop){
    
};

void Truncation::select(){
    
    auto& fit = population->fitness;
    auto& genes = population->genes;
    auto& valid = population->valid;
    
    auto n = genes.size();
    if(fit.size()!=genes.size())return;//test
    auto rank = argsort(fit);
    for(int i = n*rate; i < n; ++i){
        valid[rank[i]] = false;
    }
};