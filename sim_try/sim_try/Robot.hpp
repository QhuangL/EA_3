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

class Robot{
    public:
    
    std::vector<double> dots;// stride = 1
    std::vector<double> springs;// stride = 4 //k, a*sin(wt + b) + c
    
//    std::vector<double> bone;
//    std::vector<double> muscle;
//    std::vector<double> tissue;
//    std::vector<double> blood;
    int types = 4;
    std::vector<double> gene;
    
    std::vector<double> PVA;// stride = 9
    std::vector<float*> pos;

    void addDots(double m);
    void addDots(double m, double x, double y, double z);
    void addDotsSpringless(double m, double x, double y, double z);
    void addSprings();
    void addSprings(double k, double l0);
    void addSprings(double k, double a, double b, double c);
    static Robot* randomGenerate(int ndots);
    int getIndex(int i, int j);
    double evaluateDis();
    double initx, inity, initz;
    double energy;
    double kineticEnergy;
    double potentialEnergy_G;
    double potentialEnergy_Spring;

    //virtual function 
    virtual void draw();
    virtual void getCentral(double& x, double& y, double& z);
    virtual int pasteRobot(Robot* target);
    // virtual void mutate(double rate);
    // virtual void random();

    ~Robot();
    
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

class BreathFullBoxRobot: public FullBoxRobot{
    public:
    BreathFullBoxRobot(double m, double l, double a, double b, double c, double k, glm::mat4& mat);
};

class Tetrahedron:public Robot{
    public:
    Tetrahedron(double m, double l, double l0, double k, glm::mat4& mat);
};

class PedalRobot:public Robot{
    public:
    PedalRobot(double init_x, double init_y, double init_z);

    double ver[12];

    //override virtual function
    void getCentral(double& x, double& y, double& z)override;
    void draw() override;
    void random();
    void mutate(double rate);


    int k_u =  800;
    int k_l = 500;
    int a_u = 0;
    int a_l = 0;
    int b_u = 3;
    int b_l = 0;
    int c_u= 3.14;
    int c_l = 0;
    int m_u = 1;
    int m_l = 10;
    


};
