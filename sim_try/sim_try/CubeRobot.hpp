#define GL_SILENCE_DEPRECATION
#pragma once

#include <vector>
#include <cmath>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>


class CubeRobot{
    public:
    
    double length = 3;// 正方形的初始边长
    int step = 0;
    int xdim = 11;
    int zdim = 11;
    double init_x= 0;
    double init_y = 0;
    double init_z = 0;
    std::vector<double*> PVA;
    std::vector<double> dots;
    std::vector<int*> cubeindex;
    std::vector<double*> PVA_init;

    std::vector<double*> springs;
    std::vector<double> l0;
    void addDot(double x, double y, double z);
    void addBox(int x, int y, int z);
    void addspring(int i1, int i2);
    int getdotpos(int index);
    void getgene(std::vector<double> gene);
    void setStartPos();
    void reConstructFromGene(std::vector<double> gene);
    double start_x,start_y, start_z;
    virtual void getCenter(double& x, double& y, double& z);
    double getOffset();

    CubeRobot(double init_x, double init_y, double init_z);
    ~CubeRobot();
    
    int dotindex(int x, int y, int z);
    void getdotfromindex(int index, int& x, int& y, int& z);

    //grow
    //dir = 0 向前 1 向右 2 向上 3 向下

    //override virtual function
    virtual void draw();
    void random();
    void mutate(double rate);
    
    int types = 4;
    int k_u =  20000;
    int k_l = 3000;
    int a_u = 0;
    int a_l = 0;
    int b_u = 2;
    int b_l = 0;
    int c_u= 3.14;
    int c_l = 0;
    int m_u = 110;
    int m_l = 1;
    double energy; //能量相关
    double kineticEnergy;
    double potentialEnergy_G;
    double potentialEnergy_Spring;
};

class CrossRobot:public CubeRobot{
    public:
    CrossRobot(double initx, double inity, double initz);
};

class rgCube:public CubeRobot{
    public:
    rgCube(double initx, double inity, double initz);
    rgCube(std::vector<std::vector<int>>& robotshape, double initx, double inity, double initz);
    void grow();
};

