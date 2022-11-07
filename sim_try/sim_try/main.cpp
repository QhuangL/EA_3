#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>

Simulator* sim;  // bouncing
//SimNoGravity* sim;  //breathing


int main(int argc, char **argv){
    int step = 10000;
    double dt = 0.001;  // bouncing
//    double dt = 0.01; //breath
    
    //从以下几种模拟器中选择一个
    sim=new Simulator(dt, step); // 有重力模拟器
    sim->e = 0.5;
//    sim=new SimNoGravity(dt, step); // wu重力模拟器

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.0,30.0,0.0));
    trans = glm::rotate(trans,glm::radians(40.0f), glm::vec3(5.0f, 0.0f, 0.0f));
    sim->robots.push_back(new FullBoxRobot(1, 5, 5, 500, trans));

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::translate(trans2, glm::vec3(10.0,10.0,0.0));
    trans2 = glm::rotate(trans2,glm::radians(0.0f), glm::vec3(5.0f, 0.0f, 0.0f));
    sim->robots.push_back(new FullBoxRobot(1, 5, 5, 100, trans2));

    glm::mat4 trans3 = glm::mat4(1.0f);
    trans3 = glm::translate(trans3, glm::vec3(0.0,10.0,10.0));
    trans3 = glm::rotate(trans3,glm::radians(70.0f), glm::vec3(0.0f, 0.0f, 5.0f));
    sim->robots.push_back(new BreathFullBoxRobot(1, 5, 5, 0.5, 0, 100, trans3));

    Visualizer::sim = sim;
    Visualizer::init(argc,argv);
    

    // glutTimerFunc(100,timerFunction,1);
    glutMainLoop();
    delete Visualizer::sim;
    return 0;
    
}
