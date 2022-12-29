#ifndef APPLICATIONS_TSP
#define APPLICATIONS_TSP
#include "Evolution/Population.hpp"

class TSP:public Population{
    public:
        virtual double* newRandomIndividual() override;
        virtual void mutate(double rate) override;
        virtual void evaluate() override;
        TSP(PopulationParam* param);
        virtual ~TSP() override;
};


#endif