#ifndef EVOLUTION_CROSSOVER_HPP
#define EVOLUTION_CROSSOVER_HPP


enum CrossoverType{ONEPOINT, TWOPOINT, SUBTREE};

struct CrossoverParam
{
    /* data */
};


class Crossover{
    public:
        virtual void crossover()=0;
        CrossoverParam param;

};

class Onepoint: public Crossover{

};

class Twopoint: public Crossover{
    public:
        Twopoint();
        virtual void crossover() override;
};

#endif