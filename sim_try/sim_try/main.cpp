#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <cmath>
#include "Evo_func.hpp"
#include "Robot.hpp"
#include "CubeRobot.hpp"

// srand((unsigned)time(NULL));


Simulator* sim;  // bouncing
//SimNoGravity* sim;  //breathing
int iter_num = 100;
int pop_size = 10;
double mutation_pro = 0.1;
vector<double> gene;

int main(int argc, char **argv){
    double dt = 0.001;
    int step = 10000;
    double dt = 0.001;  // bouncing
    

//    double dt = 0.01; //breath
    
    //从以下几种模拟器中选择一个
    sim=new Simulator(dt, step); // 有重力模拟器
    sim->e = 0.5;
    Evo_func* evo = new Evo_func();
    Robot* robo = new Robot();
    
//    sim=new SimNoGravity(dt, step); // wu重力模拟器
    

//    auto temp = new PedalRobot(0, 0.1, 0);
//    temp->random();
//
//    temp->mutate(0.3);
//    sim->robots.push_back(temp);
//
//    temp = new PedalRobot(20, 0.1, 0);
//    temp->random();
//    sim->robots.push_back(temp);
//
//    temp = new PedalRobot(-20, 0.1, 0);
//    temp->random();
//    sim->robots.push_back(temp);

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

    
    // random parents
    for(int i = 0; i< pop_size; ++i){
        evo ->randomGenerate();
    };
    //iter for numbers
    for(int i =0 ;i< iter_num; i++){
        //crossover
        evo->Crossover();
        //mutation
        evo->Mutation(mutation_pro);
        
        //reconstruct
        for(int i = 0; i< pop_size; ++i){
            gene = evo->population[i];
            robo -> reConstructFromGene(gene);
        };
            
    }
    




    Visualizer::sim = sim;
    Visualizer::init(argc,argv);
    

    // glutTimerFunc(100,timerFunction,1);
    CubeSimulator* sim = new CubeSimulator(dt, step);


    sim->robots.push_back(new CubeRobot(0,10.1,0));
    sim->robots[0]->addBox(2,1,2);
    sim->robots[0]->addBox(2,1,1);
    sim->robots[0]->addBox(2,1,0);
    sim->robots[0]->addBox(3,1,2);
    sim->robots[0]->addBox(4,1,2);
    sim->robots[0]->addBox(1,1,2);
    sim->robots[0]->addBox(0,1,2);
    sim->robots[0]->addBox(2,1,3);
    sim->robots[0]->addBox(2,1,4);
    sim->robots[0]->addBox(2,0,4);
    sim->robots[0]->addBox(4,0,2);
    sim->robots[0]->addBox(0,0,2);
    sim->robots[0]->addBox(2,0,0);

    Visualizer* vis = new Visualizer();
    vis->cubesim = sim;
    vis->init(argc, argv);
    glutMainLoop();

    delete vis;

    
    
    return 0;
}
