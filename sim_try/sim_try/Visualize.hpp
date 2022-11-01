#pragma once
#define GLFW_INCLUDE_NONE
//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"




// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
class Visualizer{
    public:
    Visualizer();
    ~Visualizer();
    int initWindow();
    int initShader();
    void input(float* vertices, int sizeofV, unsigned int* indices, int sizeofI);
    //循环内函数
    void inloop1();
    void inloop2();
    void ground();


    unsigned int VBO, VAO, EBO, VAO1;
    GLFWwindow* window =NULL;
    Shader* corShader;

    

};
    

