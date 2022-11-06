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

extern float ver[8][3];
extern GLfloat color[8][3];



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

};



