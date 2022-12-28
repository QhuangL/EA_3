#ifndef EVOLUTION_SELECTION_HPP
#define EVOLUTION_SELECTION_HPP

enum SelectionType{TRUNCATION, PROPORTIONAL};

struct SelectionParam
{
    /* data */
};


class Selection{
    public:
        virtual void select()=0;
        SelectionParam param;

};

class Truncation: public Selection{
    public:
        virtual void select();

};

#endif