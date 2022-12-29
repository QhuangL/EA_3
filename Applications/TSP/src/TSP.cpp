#include "TSP.hpp"



double* TSP::newRandomIndividual(){
    double* p = new double[param->maxGeneLength];
    for(int i = 0; i< param->maxGeneLength; ++i){
        p[i] = std::rand()/(param->limits["upper"] - param->limits["lower"]) + param->limits["lower"];
    };
    return p;
};

void TSP::mutate(double rate){
    for(int i = 0; i < param->populationSize; ++i){
        for(int j = 0; j < param->maxGeneLength; ++j){
            
        }
    }
};

void TSP::evaluate(){

};

TSP::~TSP(){

};

TSP::TSP(PopulationParam* param):Population(param){

};