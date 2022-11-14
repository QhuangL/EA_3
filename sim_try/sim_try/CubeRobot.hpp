#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>


class CubeRobot{
    public:
    double length = 5;
    std::vector<double> PVA;
    std::vector<double> dots;
    std::vector<int*> box;
    std::vector<double*> springs;


    CubeRobot(double init_x, double init_y, double init_z);
    ~CubeRobot();

    //grow
    grow(int dir, int box_index);


    //override virtual function
    virtual void draw();
    void random();
    void mutate(double rate);

    int k_u =  20000;
    int k_l = 3000;
    int a_u = 0;
    int a_l = 0;
    int b_u = 2;
    int b_l = 0;
    int c_u= 3.14;
    int c_l = 0;
    int m_u = 1110;
    int m_l = 1100;


};
