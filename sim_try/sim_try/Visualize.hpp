#pragma once
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
    static void quad(int a, int b, int c, int d)
    static void display();
    static void init();
    static void colorcube();
    static void timerFunction();




};



