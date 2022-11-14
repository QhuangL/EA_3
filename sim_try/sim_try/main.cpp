#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <cmath>
#include "CubeRobot.hpp"

// srand((unsigned)time(NULL));



int main(int argc, char **argv){
    double dt = 0.001;
    int step = 10000;
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
