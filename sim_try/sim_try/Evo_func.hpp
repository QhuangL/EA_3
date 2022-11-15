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
#include "SimulatorBase.hpp"
using namespace std;



class Evo_func{
    public:
    
    void randomGenerate();
    void Crossover();
    void Mutation(double rate);
    void mutateOnce();
    void reConstructFromGene();
    void Out_file(vector<vector<double>> his_fit);
    
    std::vector<double> gene;
    std::vector<double> pap;
    std::vector<double> mom;
    vector<vector<double>> population;

    CubeSimulator* sim = nullptr;
    
    Evo_func(CubeSimulator* tempSim);
    ~Evo_func();
    
    
    int p1;
    int p2;
    
    int types =4;
    int k_u =  20000;
    int k_l = 3000;
    int a_u = 0;
    int a_l = 0;
    int b_u = 2;
    int b_l = 0;
    int c_u= 3.14;
    int c_l = 0;
    int m_u = 1110;
    int m_l = 1100;

};
#endif /* Evo_func_hpp */
