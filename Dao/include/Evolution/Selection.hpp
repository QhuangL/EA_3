#ifndef EVOLUTION_SELECTION_HPP
#define EVOLUTION_SELECTION_HPP

#include "Evolution/Population.hpp"

enum SelectionType{TRUNCATION, PROPORTIONAL};




class Selection{
    public:
        Selection(double rate);
        Population* population;

        virtual void select()=0;
        double rate;

};

class Truncation: public Selection{
    public:
        Truncation(double rate);
        virtual void select();

};

#endif