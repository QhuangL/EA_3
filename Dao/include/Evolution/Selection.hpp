#ifndef EVOLUTION_SELECTION_HPP
#define EVOLUTION_SELECTION_HPP

enum SelectionType{TRUNCATION, PROPORTIONAL};




class Selection{
    public:
        Selection(double rate);
        virtual void select()=0;
        double rate;

};

class Truncation: public Selection{
    public:
        Truncation(double rate);
        virtual void select();

};

#endif