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
#include "utils.hpp"
using namespace std;

std::mt19937 g;

// Simulator* sim;  // bouncing
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
vector<vector<double>> best_gene_list;
double select_pro = 0.8;
vector<vector<double>> good_pop;


void train(){
    double dt = 0.001;
    int step = 10000;
    srand((unsigned)time(NULL));
    CubeSimulator* sim = new CubeSimulator(dt, step);
    Evo_func* evo = new Evo_func(sim);


    // 随便生长一个Cube
    sim->robots.push_back(new rgCube(0, 0.1, 0));
    for(int i = 0; i< 19; ++i){
        static_cast<rgCube*>(sim->robots[0])->grow();
        if(sim->robots[0]->cubeindex.size() != i+2){
            --i;
        }
    }
    cout<<sim->robots[0]->cubeindex.size();
    evo->initGeneFromSim();
    
    evo ->population.clear();
    fit_list.clear();
    his_fit.clear();
    best_gene_list.clear();


    // random parents
    for(int i = 0; i< pop_size; ++i){
        evo ->randomGenerate();
    };

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
            for(int i = 0; i< sim->robots[0]->PVA.size(); ++i){
                for(int j = 0; j< 9; ++j){
                    sim->robots[0]->PVA[i][j] =  sim->robots[0]->PVA_init[i][j];
                }
            }
            sim->current_step =0;
            sim->t =0;
            
            sim ->robots[0] ->setStartPos();
            for (int k = 0; k<10000; ++k){
                sim->update();
            };
            fit_list.push_back(sim ->robots[0] ->getOffset());
            // std:: cout<<fit_list[0]<<std::endl;

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
        best_gene_list.push_back(best_gene);
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
    evo ->Out_fil2(best_gene_list);
    evo->Out_file3(evo->sim->robots[0]->cubeindex);


    delete sim;
    delete evo;
    return;
};

void multiObjectTrain(){
     double dt = 0.001;
    int step = 10000;
    srand((unsigned)time(NULL));
    CubeSimulator* sim = new CubeSimulator(dt, step);
    Evo_func* evo = new Evo_func(sim);


    // 随便生长一个Cube
    sim->robots.push_back(new rgCube(0, 0.1, 0));
    for(int i = 0; i< 19; ++i){
        static_cast<rgCube*>(sim->robots[0])->grow();
        if(sim->robots[0]->cubeindex.size() != i+2){
            --i;
        }
    }
    cout<<sim->robots[0]->cubeindex.size();
    evo->initGeneFromSim();
    
    evo ->population.clear();
    fit_list.clear();
    his_fit.clear();
    best_gene_list.clear();
    // dirBias


    // random parents
    for(int i = 0; i< pop_size; ++i){
        evo ->randomGenerate();
    };

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
            for(int i = 0; i< sim->robots[0]->PVA.size(); ++i){
                for(int j = 0; j< 9; ++j){
                    sim->robots[0]->PVA[i][j] =  sim->robots[0]->PVA_init[i][j];
                }
            }
            sim->current_step =0;
            sim->t =0;
            
            sim ->robots[0] ->setStartPos();
            for (int k = 0; k<10000; ++k){
                sim->update();
            };
            fit_list.push_back(sim ->robots[0] ->getOffset());
            // std:: cout<<fit_list[0]<<std::endl;

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
        best_gene_list.push_back(best_gene);
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
    evo ->Out_fil2(best_gene_list);
    evo->Out_file3(evo->sim->robots[0]->cubeindex);


    delete sim;
    delete evo;
    return;
};

void visualizeFromFiles(int argc, char **argv){
    double dt = 0.001;
    int step = 10000;
    srand((unsigned)time(NULL));

    CubeSimulator* sim = new CubeSimulator(dt, step);

    Evo_func* evo = new Evo_func(sim);
    
    Visualizer* vis = new Visualizer();
    vis->cubesim = sim;
    vis->init(argc, argv);

    // 从文件中读取形状
    vector<vector<int>> robotshape;
    readRobotShape(robotshape, "RobotShape6.csv");
   // std::cout<<robotshape[0][0]<<std::endl;
    sim->robots.push_back(new rgCube(robotshape, 0.0, 0.1, 0.0));
    // 从文件中读取基因并加载到机器人中
    sim->robots[0]->reConstructFromGene(readGene("bestG_cross_6.csv", 0));
    

    // readRobotShape(robotshape, "RobotShape2.csv");
    // sim->robots.push_back(new rgCube(robotshape, 0.0, 0.1, -15.0));
    // sim->robots[1]->reConstructFromGene(readGene("bestG_cross_2.csv", 0));

    // readRobotShape(robotshape, "RobotShape8.csv");
    // sim->robots.push_back(new rgCube(robotshape, 0.0, 0.1, 15.0));
    // sim->robots[2]->reConstructFromGene(readGene("bestG_cross_8.csv", 0));
    
        
    glutMainLoop();


    delete sim;
    delete evo;
    delete vis;
    return;
};

void visualTest(int argc, char ** argv){
    double dt = 0.001;
    int step = 10000;
    srand((unsigned)time(NULL));

    CubeSimulator* sim = new CubeSimulator(dt, step);

    Evo_func* evo = new Evo_func(sim);
    
    Visualizer* vis = new Visualizer();
    vis->cubesim = sim;
    vis->init(argc, argv);

     // 随便生长一个Cube
    sim->robots.push_back(new rgCube(0, 5.1, 0));
    for(int i = 0; i< 6; ++i){
        static_cast<rgCube*>(sim->robots[0])->grow();
        if(sim->robots[0]->cubeindex.size() != i+2){
            --i;
        }
    }
    cout<<sim->robots[0]->cubeindex.size();
    evo->initGeneFromSim();
    evo->randomGenerate();
    sim->robots[0]->reConstructFromGene(evo->population[0]);

    glutMainLoop();


    delete sim;
    delete evo;
    delete vis;
    return;
};



int main(int argc, char **argv){

    visualizeFromFiles(argc, argv);

    // train
    // train();
    
    // // visual test
    // visualTest(argc, argv);

    return 0;
}
