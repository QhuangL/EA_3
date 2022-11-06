#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>

Simulator* sim;  // bouncing
//SimNoGravity* sim;  //breathing

void timerFunction(int value){
    sim->update();
    sim->output();
    for(int i=0; i<8;i++){
        for(int j=0;j<3;j++){
            ver[i][j] = sim->pos[3*i+j];
//            std::cout<<ver[i][j]<<std::endl;
        }
    }
    glutTimerFunc(1,timerFunction,1);
    glutPostRedisplay();
};


int main(int argc, char **argv){
    int step = 10000;
    double dt = 0.001;  // bouncing
//    double dt = 0.01; //breath
    
    //从以下几种模拟器中选择一个
    sim=new Simulator(dt, step); // 有重力模拟器
    sim->e = 0.5;
//    sim=new SimNoGravity(dt, step); // wu重力模拟器
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.0,20.0,0.0));
    trans = glm::rotate(trans,glm::radians(40.0f), glm::vec3(5.0f, 0.0f, 0.0f));

    sim->robots.push_back(new FullBoxRobot(1, 5, 5, 100, trans));

    Visualizer::init(argc,argv);
    

    glutTimerFunc(100,timerFunction,1);
    glutMainLoop();
    delete sim;
    return 0;
    
}
