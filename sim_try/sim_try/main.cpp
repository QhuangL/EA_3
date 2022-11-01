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

int main(){
    int step = 10000;
    double dt = 0.001;
    
    //从以下几种模拟器中选择一个
    // SimNoGravity sim(dt, step);// 没有重力的模拟器
    Simulator sim(dt, step); // 有重力模拟器

    sim.robots.push_back(new BoxRobot(1, 10));
    

    Visualizer vis = Visualizer();
    vis.initWindow();
    vis.initShader();
    float vertices[] = {
    // positions         // colors
    0.0f, 0.0f, 0.0f,  0.2f, 0.5f, 1.0f,  // bottom right
    0.5f, 0.0f, 0.0f,  0.2f, 0.5f, 1.0f,  // bottom left
    0.0f, 0.5f, 0.0f,  0.2f, 0.5f, 1.0f,   // top
    0.5f, 0.5f, 0.0f,  0.2f, 0.5f, 1.0f,   //
    
    0.0f, 0.0f, 0.5f,  0.2f, 0.5f, 1.0f,  // front
    0.5f, 0.0f, 0.5f,  0.2f, 0.5f, 1.0f,  // bottom left
    0.0f, 0.5f, 0.5f,  0.2f, 0.5f, 1.0f,   // top
    0.5f, 0.5f, 0.5f,  0.2f, 0.5f, 1.0f   //
    
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 4,  // back
            0, 2, 4,   //
            3, 5, 7,   // front
            3, 6, 7,
            0, 2, 4,  // left
            0, 3, 5,  //
            1, 4, 7,  //right
            1, 6, 7,  //
            2, 4, 7,  //up
            2, 5, 7,
            0, 1, 6,  //bottom
            0, 3, 6
        };

    // std::ofstream E;

    // E.open("E2.txt", std::ios::trunc);


    std::cout<<sizeof(vertices)<<std::endl;
    while(!glfwWindowShouldClose(vis.window)&& sim.current_step!=step){
        sim.update();
        sim.output();
        
        
        vis.inloop1();
        vis.input(sim.pos, 24*4,indices,sizeof(indices));

      // E<<sim.robots[0]->potentialEnergy_G<<","
        // E<<sim.robots[0]->potentialEnergy_Spring<<","
        // <<sim.robots[0]->kineticEnergy<<","
        // <<sim.robots[0]->energy<<std::endl;  

        std::cout<<sim.pos[1]<<" "<<sim.robots[0]->energy<<std::endl;
        vis.inloop2();
    }


    // E.close();
    return 0;
    
}
