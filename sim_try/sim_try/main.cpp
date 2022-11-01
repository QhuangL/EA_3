//
//  main.cpp
//  sim_try
//
//  Created by Qianhuang Li on 10/30/22.
//
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include <glad/glad.h>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>


int main(int argc, char **argv){
    int step = 10000;
    double dt = 0.001;
    
    //从以下几种模拟器中选择一个
    // SimNoGravity sim(dt, step);// 没有重力的模拟器
    Simulator sim(dt, step); // 有重力模拟器
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.0,0.0,0.0));
    trans = glm::rotate(trans,glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    sim.robots.push_back(new BoxRobot(1, 10, trans));
    Visualizer::init(argc,argv);
    glutMainLoop();

    



    // std::ofstream E;

    // E.open("E2.txt", std::ios::trunc);
    
    
    


    // while(!glfwWindowShouldClose(vis.window)&& sim.current_step!=step){
    //     sim.update();
    //     sim.output();
        
        
        

    //   // E<<sim.robots[0]->potentialEnergy_G<<","
    //     // E<<sim.robots[0]->potentialEnergy_Spring<<","
    //     // <<sim.robots[0]->kineticEnergy<<","
    //     // <<sim.robots[0]->energy<<std::endl;  

    //     // std::cout<<sim.pos[1]<<" "<<sim.robots[0]->energy<<std::endl;
        
    // }


    // E.close();
    return 0;
    
}
