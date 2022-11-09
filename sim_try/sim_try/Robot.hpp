#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif

class Robot{
    public:
    
    std::vector<double> dots;// stride = 1
    std::vector<double> springs;// stride = 4 //k, a*sin(wt + b) + c 
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
    double energy;
    double kineticEnergy;
    double potentialEnergy_G;
    double potentialEnergy_Spring;

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
    void draw();

};