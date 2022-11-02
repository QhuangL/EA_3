#pragma once
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GLUT/GLUT.h>
#include "ground.hpp"



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Visualizer{
    public:
    static void specialKeys(int key, int x, int y);
    static void quad(int a, int b, int c, int d);
    static void display();
    static void init(int argc, char **argv);
    static void colorcube();
//    static void timerFunction(int value);
    // static double rotate_y = 0;
    // static double rotate_x =0;
    // static float ver[8][3] =
    // {
    //     {-1.0,-1.0,1.0},
    //     {-1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,-1.0,1.0},
    //     {-1.0,-1.0,-1.0},
    //     {-1.0,1.0,-1.0},
    //     {1.0,1.0,-1.0},
    //     {1.0,-1.0,-1.0},
    // };
    // static GLfloat color[8][3] =
    // {
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    //     {1.0,1.0,1.0},
    // };




};



