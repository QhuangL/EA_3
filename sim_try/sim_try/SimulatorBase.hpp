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
    std::vector<double> pap;
    std::vector<double> mom;
    int p1;
    int p2;
    
    double dt= 0.001;
    const double dampening = 0.997;
    const double gravity = -9.81;
    const double friction_mu_k = 0.8;
    const double k_vertices_soft = 5000;
    const double k_ground = 100000;
    double omega = 10;
    double t = 0;
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

