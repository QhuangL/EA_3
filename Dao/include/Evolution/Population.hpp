#ifndef EVOLUTION_POPULATION_HPP
#define EVOLUTION_POPULATION_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <iostream>

//假设Gene Length 相同， population Size可以改变
struct PopulationParam{
    const int InitPopulationSize;
    const int maxPopulationSize;
    const int maxGeneLength;
    std::unordered_map<std::string,double> limits;

};

class Population{
    public:
        
        std::vector<std::vector<double>> genes;
        std::vector<bool> valid;
        std::vector<double> fitness;
        PopulationParam* param;
        double diversity = 0;
        //如果使用valid方式进行selcet，population size将失去意义，并且在cross over中引入新的麻烦；但是显著减少时间空间复杂度
        //如果使用parent

        
        virtual std::vector<double> newRandomIndividual()=0;
        virtual void mutate(double rate)=0;
        virtual void evaluate()=0;

        Population(PopulationParam* param);
        virtual ~Population();

};



#endif