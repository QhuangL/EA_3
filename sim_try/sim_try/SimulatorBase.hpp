#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Robot{
    public:
    
    std::vector<double> dots;// stride = 1
    std::vector<double> springs;// stride = 4 //k, a*sin(wt + b) + c 
    std::vector<double> PVA;// stride = 9
    void addDots(double m);
    void addDots(double m, double x, double y, double z);
    void addDotsSpringless(double m, double x, double y, double z);
    void addSprings();
    void addSprings(double k, double l0);
    void addSprings(double k, double a, double b, double c);
    static Robot* randomGenerate(int ndots);
    int getIndex(int i, int j);
    double energy;
    double kineticEnergy;
    double potentialEnergy_G;
    double potentialEnergy_Spring;
    
};

class TwoPoints:public Robot{
    public:
    TwoPoints();
};

class BoxRobot:public Robot{
    public:
    BoxRobot(double m, double l);
    BoxRobot(double m, double l, glm::mat4& mat);
    BoxRobot(double m, double l, double k, glm::mat4& mat);
    BoxRobot(double m, double l, double l0, double k, glm::mat4& mat);
    
};

class FullBoxRobot:public Robot{
    public:
    FullBoxRobot(double m, double l, double l0, double k, glm::mat4& mat);
};

class Simulator{
    public:
    std::vector<Robot*> robots;
    double dt= 0.001;
    int t = 0;
    int current_step = 0;
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

class SimNoGravity:public Simulator{
    public:
    void update();
    SimNoGravity(double dt, int step);

};
