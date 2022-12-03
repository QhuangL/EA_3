//
//  Evo_func.hpp
//  sim_try
//
//  Created by Qianhuang Li on 11/13/22.
//

#ifndef Evo_func_hpp
#define Evo_func_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <sstream>     
#include "SimulatorBase.hpp"

using namespace std;


class Evo_func{
    public:
    
    void randomGenerate();
    
    void randomGeneratePosGene(int types, double x_u, double x_l, double y_u, double y_l, double z_u, double z_l);


    void Crossover();
    void Mutation(double rate);
    void mutateOnce();
    void Out_file(vector<vector<double>> his_fit); //
    void Out_fil2(vector<vector<double>> best_list); //输出
    void Out_file3(vector<int*> robot_shape); //输出机器人形状
    
    std::vector<double> gene;
    std::vector<double> pap;
    std::vector<double> mom;
    vector<vector<double>> population;

    CubeSimulator* sim = nullptr;
    
    Evo_func(CubeSimulator* tempSim);
    void initGeneFromSim();
    void initGeneFromSimPos();
    ~Evo_func();
    
    
    int p1;
    int p2;
    
    int types =4;
    double k_u =  4000;
    double k_l = 3000;
    double a_u = 0;
    double a_l = 0;
    double b_u = 1.0;
    double b_l = -0.8;
    double c_u= 1.7;
    double c_l = 0;
    double m_u = 10;
    double m_l = 1;

};
#endif /* Evo_func_hpp */
