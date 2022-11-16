#define GL_SILENCE_DEPRECATION
#include "SimulatorBase.hpp"
#include <iomanip>
#include <fstream>
#include <algorithm>    // std::reverse
#include "Visualize.hpp"
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <cmath>
#include "Evo_func.hpp"
#include "Robot.hpp"
#include <random>
#include "CubeRobot.hpp"

// srand((unsigned)time(NULL));
std::mt19937 g;

Simulator* sim;  // bouncing
//SimNoGravity* sim;  //breathing
int iter_num = 10;
int pop_size = 10;
double mutation_pro = 0.1;
vector<double> gene;
vector<double> fit_list;
vector<int> o_fit;
vector<double> one_fitlist;
vector<vector<double>> his_fit; //output
vector<double> best_gene;
double select_pro = 0.8;
vector<vector<double>> good_pop;


vector<int> argsort(vector<double> &fit){
    
    vector<int> o_fit(fit.size());
        iota(o_fit.begin(), o_fit.end(), 0);

        stable_sort(o_fit.begin(), o_fit.end(),
            [&fit](int i1, int i2) {return fit[i1] < fit[i2];});
    
    return o_fit;
}


int main(int argc, char **argv){
    double dt = 0.001;
    int step = 10000;
    
    
    CubeSimulator* sim = new CubeSimulator(dt, step);
    
    sim->robots.push_back(new CubeRobot(0,0.5,0));
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


    Evo_func* evo = new Evo_func(sim);

    for(int i = 0; i< pop_size; ++i){
        evo ->randomGenerate();
    };
    sim ->robots[0] -> reConstructFromGene(evo->population[0]);
    Visualizer* vis = new Visualizer();
    vis->cubesim = sim;
    vis->init(argc, argv);
    glutMainLoop();
    return 0;
    





   

    evo ->population.clear();
    fit_list.clear();
    his_fit.clear();


    // random parents
    for(int i = 0; i< pop_size; ++i){
        evo ->randomGenerate();
    };
    // std::cout<<evo->population[0][0]<<" "<<evo->population[1][0];
    double n_pop = evo->population.size();
    //iter for numbers
    for(int i =0 ;i< iter_num; i++){
        //crossover
        evo->Crossover();
        //mutation
        evo->Mutation(mutation_pro);
        
        //reconstruct
        fit_list.clear();
        for(int j = 0; j< pop_size; ++j){
            gene = evo->population[j];
            sim ->robots[0] -> reConstructFromGene(gene);
            sim ->robots[0] ->setStartPos();
            for (int k = 0; k<10000; ++k){
                sim->update();
            };
            fit_list.push_back(sim ->robots[0] ->getOffset());

        };

        //rank select
        o_fit = argsort(fit_list);
        std::reverse(o_fit.begin(),o_fit.end());
        one_fitlist.clear();
        for (auto temp: o_fit){
            one_fitlist.push_back(fit_list[temp]);
        };
        his_fit.push_back(one_fitlist);
        best_gene = evo ->population[o_fit[0]];

        good_pop.clear();
        std::vector<double> good;
        for(int k = 0; k<n_pop*select_pro; ++k){
            good = evo ->population[o_fit[k]];
            good_pop.push_back(good);
        }
        evo ->population.assign(good_pop.begin(),good_pop.end());
        //refill
        for(int k=0; k<n_pop*(1-select_pro); ++k){
            evo ->randomGenerate();
        }
        
        shuffle(evo ->population.begin(), evo ->population.end(), g);  

    }
    
    evo ->Out_file(his_fit);
    




    
    // // glutTimerFunc(100,timerFunction,1);


    // sim->robots.push_back(new CubeRobot(0,10.1,0));
    // sim->robots[0]->addBox(2,1,2);
    // sim->robots[0]->addBox(2,1,1);
    // sim->robots[0]->addBox(2,1,0);
    // sim->robots[0]->addBox(3,1,2);
    // sim->robots[0]->addBox(4,1,2);
    // sim->robots[0]->addBox(1,1,2);
    // sim->robots[0]->addBox(0,1,2);
    // sim->robots[0]->addBox(2,1,3);
    // sim->robots[0]->addBox(2,1,4);
    // sim->robots[0]->addBox(2,0,4);
    // sim->robots[0]->addBox(4,0,2);
    // sim->robots[0]->addBox(0,0,2);
    // sim->robots[0]->addBox(2,0,0);

    // Visualizer* vis = new Visualizer();
    // vis->cubesim = sim;
    // vis->init(argc, argv);
    // glutMainLoop();

    // delete vis;
    delete sim;
    delete evo;

    
    
    return 0;
}
