
#include <Evolution/Population.hpp>
#include "Applications/Draw/Canvas.hpp"
int main(int argc, char **argv){

    std::unordered_map<std::string, double> popLimits = {
        {"a_l", 0},
        {"a_h", 10}
    };
    
    PopulationParam popParam = {
        .populationSize = 10,
        .maxPopulationSize = 100,
        .maxGeneLength = 20,
        .limits = popLimits
    };

    auto population = new DrawPopulation(&popParam);
    delete population;


    return 0;
};
