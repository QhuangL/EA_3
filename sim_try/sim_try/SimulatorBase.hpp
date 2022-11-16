#pragma once
#include "Robot.hpp"
#include "CubeRobot.hpp"

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
    //
    const double dampening = 0.999;
    const double gravity = -9.81;

    const double friction_mu_s = 1; //没用
    const double friction_mu_k = 0.8; //地面摩擦系数
    const double k_vertices_soft = 5000; //默认弹簧进度系数
    const double k_ground = 100000; //地面进度系数
    double omega = 10; //全局频率
    double t = 0;
    int current_step = 0;//现在的步数
    int step; //没用
    virtual void update(); //向前仿真一步
    void output(); //没用
    double e = 0.0; //没用

    
    Simulator(double dt, int step);
    ~Simulator();

    void randomAddRobots(int n_robot, int n_dots);
    void mutate(double rate);
    void crossOver();// 未实现
    void rankSelection();// 未实现
};

class SimNoGravity:public Simulator{
    public:
    void update()override;
    SimNoGravity(double dt, int step);

};

class CubeSimulator{
    public:
    std::vector<CubeRobot*> robots;
    
    double dt= 0.001;
    const double dampening = 0.999;
    const double gravity = -9.81;
    int step = 0;

    const double friction_mu_k = 1; //地面摩擦系数
    const double k_vertices_soft = 5000; //默认弹簧进度系数
    const double k_ground = 100000; //地面进度系数
    double omega = 2; //全局频率
    double t = 0;
    int current_step = 0;//现在的步数
    virtual void update(); //向前仿真一步

    CubeSimulator(double dt, int step);
    ~CubeSimulator();
    
};




