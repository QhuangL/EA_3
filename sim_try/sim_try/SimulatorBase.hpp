#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

class Robot{
    public:
    
    std::vector<double> dots;// stride = 1
    std::vector<double> springs;// stride = 4 //k, a*sin(wt + b) + c 
    std::vector<double> PVA;// stride = 9
    void addDots(double m);
    void addDots(double m, double x, double y, double z);
    void addSprings();
    static Robot* randomGenerate(int ndots);
    int getIndex(int i, int j);
    double energy;
    
};

class TwoPoints:public Robot{
    public:
    TwoPoints();
};

class BoxRobot:public Robot{
    public:
    BoxRobot();
};

class Simulator{
    public:
    std::vector<Robot*> robots;
    double dt= 0.001;
    int t = 0;
    int step;
    void update();
    float* pos;
    void output();
    
    Simulator(double dt, int step);
    ~Simulator();

    void randomAddRobots(int n_robot, int n_dots);
    void mutate(double rate);
    void crossOver();
    void rankSelection();

    

};


