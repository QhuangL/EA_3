#ifndef EVOLUTION_POPULATION_HPP
#define EVOLUTION_POPULATION_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>

//假设Gene Length 相同， population Size可以改变
struct PopulationParam{
    int populationSize;
    const int maxPopulationSize;
    const int maxGeneLength;
    std::unordered_map<std::string,double> limits;

};

class Population{
    public:
        
        std::vector<std::vector<double>*> population;
        std::vector<double> fitness;
        PopulationParam* param;

        
        virtual double* newRandomIndividual()=0;
        virtual void mutate()=0;
        virtual void evaluate()=0;

        Population(PopulationParam* param);
        virtual ~Population();

};



#endif