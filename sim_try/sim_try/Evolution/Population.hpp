#ifndef EVOLUTION_POPULATION_HPP
#define EVOLUTION_POPULATION_HPP

#include <vector>
#include <unordered_map>

//假设Gene Length 相同， population Size可以改变
struct PopulationParam{
    int populationSize;
    const int maxPopulationSize;
    const int maxGeneLength;
    std::unordered_map limits;
};

class Population{
    public:
        std::vector<std::vector<double>*> population;
        std::vector<double> fitness;
        PopulationParam* param;

        
        virtual std::vector<double>* randomIndividual()=0;
        virtual void mutate()=0;
        virtual void evaluate()=0;
        virtual ~Population();

};

class StringPopulation: public Population{
    public:
        StringPopulation();
        virtual std::vector<double>* randomIndividual() override;

};

#endif