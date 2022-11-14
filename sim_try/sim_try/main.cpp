#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <cmath>

// srand((unsigned)time(NULL));


Simulator* sim;  // bouncing
//SimNoGravity* sim;  //breathing


int main(int argc, char **argv){
    srand((unsigned)time(NULL));
    int step = 10000;
    double dt = 0.001;  // bouncing
//    double dt = 0.01; //breath
    
    //从以下几种模拟器中选择一个
    sim=new Simulator(dt, step); // 有重力模拟器
    sim->e = 0.5;
//    sim=new SimNoGravity(dt, step); // wu重力模拟器
    

    auto temp = new PedalRobot(0, 0.1, 0);
    temp->random();

    temp->mutate(0.3);
    sim->robots.push_back(temp);

    temp = new PedalRobot(20, 0.1, 0);
    temp->random();
    sim->robots.push_back(temp);

    temp = new PedalRobot(-20, 0.1, 0);
    temp->random();
    sim->robots.push_back(temp);

    // sim->update();
    // //创建100个机器人
    // for(int i = 0; i< 100; ++i){
    //     temp = new PedalRobot(0, 0.1, 0);
    //     temp->random(); //需要新版本
    //     sim->robots.push_back(temp);
    // }
    
    // //跑100个机器人10000步
    // double iter =10000;
    // double rate = 0.3;
    // for(int j = 0; j< iter; ++j){
    //     sim->mutate(); // 需要新版本
    //     sim->crossOver(); // 未实现
    //     for(int i = 0; i< 10000; ++i){
    //         sim->update(rate);
    //     }
    //     sim->rankSelection(); // 未实现

    //     sim->refill(); // 未实现
        
    // }

    // //输出文件
    // // 1. best fitness --- generation --- evaluation
    // // 2. best parameters in last generation k, a, b, c, m
    // // 3. diversity chart --- generation
    // // 4. video
    
    // //需要实现的函数
    // sim->diversity();
    // sim

    




    for(int i =0 ;i< 5; i++){
            temp->random();
            temp->reConstructFromGene();
            sim->robots.push_back(temp);
            temp = new PedalRobot(0, 0.1 , -20*i-20);
    }
    
    
    sim->crossOver();
    for(int i =0; i< temp->gene.size(); ++i){
        std::cout<<sim->pap[i]<<" ";
    }
    std::cout<<std::endl;
    for(int i =0; i< temp->gene.size(); ++i){
        std::cout<<sim->mom[i]<<" ";
    }
    




    Visualizer::sim = sim;
    Visualizer::init(argc,argv);
    

    // glutTimerFunc(100,timerFunction,1);
    glutMainLoop();



    delete Visualizer::sim;
    return 0;
    
}
