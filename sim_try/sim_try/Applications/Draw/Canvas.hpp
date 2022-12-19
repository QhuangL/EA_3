#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#ifndef APPLICATIONS_DRAW_CANVAS
#define APPLICATIONS_DRAW_CANVAS


#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Visualizer2D{
    public:
    static void init(int argc, char **argv);
    
    //注册函数
    static void specialKeys(int key, int x, int y);
    static void mouseButton(int buttom, int state, int x, int y);
    static void display();
    static void timerFunction(int value);
    static void idleFunction();
    static void processNormalKeys(unsigned char key, int xx, int yy);
    static void releaseKey(int key, int x, int y);
    static void reshape(int w, int h);
};




#endif