#include "Applications/Draw/Canvas.hpp"

DrawPopulation::DrawPopulation(PopulationParam* param):Population(param){
    std::cout<<param->maxGeneLength<<std::endl;
};

double* DrawPopulation::newRandomIndividual(){
    auto temp = new double[param->maxGeneLength];
    temp[0] = (rand()/RAND_MAX)*(param->limits["a_h"] - param->limits["a_l"]) + param->limits["a_l"];
    return temp;
};

void DrawPopulation::mutate(){

};

void DrawPopulation::evaluate(){

};

DrawPopulation::~DrawPopulation(){

};