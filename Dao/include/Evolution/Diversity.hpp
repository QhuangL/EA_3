#ifndef EVOLUTION_DIVERSITY_HPP
#define EVOLUTION_DIVERSITY_HPP

enum DiversityType{DIS, NONE};

class Diversity{
    public:
        virtual double calculate()=0;
};

class Distance:public Diversity{
    public:
        virtual double calculate();
};

#endif