#pragma once
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif
#include "ground.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SimulatorBase.hpp"

extern GLfloat color[8][3];



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Visualizer{
    public:
    static void init(int argc, char **argv);
    
    //注册函数
    static void specialKeys(int key, int x, int y);
    static void display();
    static void timerFunction(int value);

    //绘制函数
    // static void colorcube();
    // static void quad(int a, int b, int c, int d);
    static void drawRobot();
    static void drawBoxRobot(int i );
    static void drawQuadfromPVA(int i, int a, int b, int c, int d);

    //
    static Simulator* sim;
    static CubeSimulator* cubesim;

    static GLfloat point_sizes[2];
    static GLfloat point_step;
    static GLfloat cur_point_size;
    static GLfloat line_widths[2];
    static GLfloat cur_line_width;

    
    
};



