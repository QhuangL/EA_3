#ifndef EVOLUTION_POPULATION_HPP
#define EVOLUTION_POPULATION_HPP

#include <vector>

//假设Gene Length 相同， population Size可以改变
struct PopulationParam{
    int populationSize;
    int maxPopulationSize;
    int maxGeneLength;


};

class Population{
    public:
        PopulationParam param;
        std::vector<std::vector<double>*> population;
        
        std::vector<double> fitness;
        virtual std::vector<double>* randomIndividual()=0;
        virtual void mutate()=0;



};

#endif