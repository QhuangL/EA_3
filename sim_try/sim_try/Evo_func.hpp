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
    // 通用方法和成员
    void Crossover(); // 
    Evo_func(CubeSimulator* tempSim);
    ~Evo_func();
    std::vector<double> gene;
    std::vector<double> pap;
    std::vector<double> mom;
    vector<vector<double>> population;
    CubeSimulator* sim = nullptr;
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

    // 骨骼肌肉法的专用函数
    void randomGenerate();
    void Mutation(double rate);
    void mutateOnce();
    void initGeneFromSim();
    int types = 4;
    


    // 输出文件
    void Out_file(vector<vector<double>> his_fit, int index); //
    void Out_fil2(vector<vector<double>> best_list, int index); //输出
    void Out_file3(vector<int*> robot_shape, int index); //输出机器人形状
    

    // 半径-圆心法的编码方式专用方法和对象
    void randomGeneratePos(int types, double x_u, double x_l, double y_u, double y_l, double z_u, double z_l);
    void initGeneFromSimPos(int types);
    void mutatePos(double mutateRate);
    double x_u = 10;
    double x_l = 0;
    double y_u = 8;
    double y_l = 0;
    double z_u = 10;
    double z_l = 0;

};


// class Evolution{
//     public:

//     virtual void randomAdd() = 0;//在population中加入一个随机生成的基因
//     virtual void mutate(double rate) = 0;//对population进行mutate
//     virtual void crossOver() = 0;//
//     virtual void selection() = 0;//
//     // virtual void 

//     vector<vector<double>> population;



//     //内存管理相关
//     int populationMax;

//     //可动态变化
//     int populationSize;
//     int geneLength;
    
// };


// class MOP:public Evolution{
//     public:

//     MOP(int populationMax, int types);
//     ~MOP();

//     void randomAdd() override;
//     void mutate(double rate) override;
//     void crossOver() override;
//     void selection() override;

//     int types;
//     vector<double> gene;

// };
#endif /* Evo_func_hpp */
