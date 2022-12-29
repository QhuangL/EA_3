#include "Evolution/Selection.hpp"

Selection::Selection(double rate){
    this->rate = rate;
};

Truncation::Truncation(double rate):Selection(rate){
    
};

void Truncation::select(){

};