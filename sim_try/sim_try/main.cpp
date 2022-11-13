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

    auto temp = new PedalRobot(0,0.1,0);
    temp->random();
    // for(int i =0; i< temp->gene.size(); ++i){
    //     std::cout<<temp->gene[i]<<" ";
    // }
    // std::cout<<std::endl;

    
    sim->robots.push_back(temp);
    sim->mutate(1.3);
    // for(int i =0; i< temp->gene.size(); ++i){
    //     std::cout<<temp->gene[i]<<" ";
    // }
    // std::cout<<std::endl;
    temp->reConstructFromGene();

    temp = new PedalRobot(0, 0.1, 20);
    temp->random();
    temp->reConstructFromGene();
    sim->robots.push_back(temp);

    for(int i =0; i< temp->gene.size(); ++i){
        std::cout<<sim->robots[0]->gene[i]<<" ";
    }
    std::cout<<std::endl;
    for(int i =0; i< temp->gene.size(); ++i){
        std::cout<<sim->robots[1]->gene[i]<<" ";
    }
    std::cout<<std::endl;
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
