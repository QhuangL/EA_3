#pragma once
#include "Robot.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Simulator{
    public:
    std::vector<Robot*> robots;
    double dt= 0.001;
    int t = 0;
    int current_step = 0;
    int step;
    void update();
    void output();
    double e = 0.0;
    
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

