#include "Evolution/Evolution.hpp"
#include <iostream>

class DrawPopulation: public Population{
    public:
        DrawPopulation(PopulationParam* param);
        ~DrawPopulation();
        void mutate() override;
        void evaluate() override;
        double* newRandomIndividual() override;
};

