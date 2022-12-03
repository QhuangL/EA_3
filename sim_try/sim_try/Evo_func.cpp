//
//  Evo_func.cpp
//  sim_try
//
//  Created by Qianhuang Li on 11/13/22.
//

#include "Evo_func.hpp"


Evo_func::Evo_func(CubeSimulator* tempSim){
    sim = tempSim;
};

void Evo_func::initGeneFromSim(){
    for (int i=0; i<3*types+ sim->robots[0]->springs.size(); ++i){
        gene.push_back(0);
    };
    return ;
}

void Evo_func::initGeneFromSimPos(int types){
    for(int i = 0; i<6* types; ++i){
        gene.push_back(0);
    }
};

Evo_func::~Evo_func(){
    
};

void Evo_func::randomGenerate(){
    for(int i = 0; i< types; ++i){
        gene[3*i+0] = rand()/double(RAND_MAX)* (k_u - k_l)+ k_l ;
        gene[3*i+1] = rand()/double(RAND_MAX)* (b_u - b_l)+ b_l ;
        gene[3*i+2] = rand()/double(RAND_MAX)* (c_u - c_l)+ c_l ;
    };
    for(int i = 3 * types; i< 3*types+sim->robots[0]->springs.size(); ++i){
        gene[i] = rand() % 4;
    };
    population.push_back(gene);//?
    // std::cout<< sim->robots[0]->springs.size()<<std::endl;
};

// 随机产生位置编码的基因
void Evo_func::randomGeneratePos(int types, double x_u, double x_l, double y_u, double y_l, double z_u, double z_l){
    //产生每个类型的 弹簧参数 k b c，并储存再基因的前types*3个位置中
    for(int i = 0; i< types; ++i){
        gene[3*i+0] = rand()/double(RAND_MAX)* (k_u - k_l)+ k_l ;
        gene[3*i+1] = rand()/double(RAND_MAX)* (b_u - b_l)+ b_l ;
        gene[3*i+2] = rand()/double(RAND_MAX)* (c_u - c_l)+ c_l ;
    };
    // 产生每个类型的中心位置 cx, cy, cz并存储到基因的types*3之后
    for(int i = 0; i<types; ++i){
        gene[3*types+ 3*i +0] = rand()/double(RAND_MAX)* (x_u - x_l)+ x_l;
        gene[3*types+ 3*i +1] = rand()/double(RAND_MAX)* (y_u - y_l)+ y_l;
        gene[3*types+ 3*i +2] = rand()/double(RAND_MAX)* (z_u - z_l)+ z_l;
    };
    population.push_back(gene);
};

// 随机
void Evo_func::Crossover(){
    double temp;
    int n_gene = gene.size();
    int n_pop = population.size();
    for (int i = 0; i<n_pop-1; i+=2){
        int p1 = rand() % (n_gene-1);
        int p2 = rand() % (n_gene-p1-1) + p1+1;
        pap.assign(population[i].begin(),population[i].end());
        mom.assign(population[i+1].begin(),population[i+1].end());
        for(int i=p1; i<p2+1; ++i){
            temp = pap[i];
            pap[i] = mom[i];
            mom[i] = temp;
        };
        population.push_back(pap);
        population.push_back(mom);
    };
};

void Evo_func::Mutation(double rate){
    for(int i = population.size()/2; i <population.size(); ++i){
        double dice = rand()/double(RAND_MAX);
        if(dice < rate){
            gene = population[i];
            mutateOnce();
        }
    }
};

// 直接对population中的gene进行变异， pos专用
void Evo_func::mutatePos(double rate){
    double dice = 0;
    for(int i = population.size()/2; i< population.size(); ++i){
        dice = rand()/double(RAND_MAX);
        if(dice<rate){
            int pos = (rand()% (this->gene.size() + 1));
            int pospos = pos%3;
            if(pos < types *3){
                if(pospos == 0){
                    this->gene[pos] = rand()/double(RAND_MAX)* (k_u - k_l)+ k_l ;
                }else if(pospos == 1){
                    this->gene[pos] = rand()/double(RAND_MAX)* (b_u - b_l)+ b_l ;
                }else{
                    this->gene[pos] = rand()/double(RAND_MAX)* (c_u - c_l)+ c_l ;
                }
            }else{
                if(pospos == 0){
                    this->gene[pos] = rand()/double(RAND_MAX)* (x_u - x_l)+ x_l ;
                }else if(pospos == 1){
                    this->gene[pos] = rand()/double(RAND_MAX)* (y_u - y_l)+ y_l ;
                }else{
                    this->gene[pos] = rand()/double(RAND_MAX)* (z_u - z_l)+ z_l ;
                }
            }
        }
    }
}


void Evo_func::mutateOnce(){
    int pos = (rand()% (this->gene.size() + 1));
    if(pos < types *3){
        int pospos = pos%3;
        if(pospos == 0){
            this->gene[pos] = rand()/double(RAND_MAX)* (k_u - k_l)+ k_l ;
        }else if(pospos == 1){
            this->gene[pos] = rand()/double(RAND_MAX)* (b_u - b_l)+ b_l ;
        }else{
            this->gene[pos] = rand()/double(RAND_MAX)* (c_u - c_l)+ c_l ;
        }
    }else{
        this->gene[pos] = (double)((rand()% ((types)*9)+ 1)/10);
    }
};


void Evo_func::Out_file(vector<vector<double>> his_fit){
    string EA_method = "cross_";
    string filename = "lc_" + EA_method + "1" + ".csv";
    ofstream outFile;
    outFile.open(filename, ios::out|ios::trunc);

    for (auto iter : his_fit)
    {
        for(auto idx : iter){
            outFile << idx << ",";
        }
        outFile << endl;
        
    }
    cout << "File saved!" << endl;
};

void Evo_func::Out_fil2(vector<vector<double>> best_list){
    string EA_method = "cross_";
    string filename = "bestG_" + EA_method + "1" + ".csv";
    ofstream outFile2;
    outFile2.open(filename, ios::out|ios::trunc );

    for (auto iter : best_list)
    {
        for(auto idx : iter){
            outFile2 << idx << ",";
        }
        outFile2 << endl;
    }
    cout << "File saved!" << endl;
};

void Evo_func::Out_file3(vector<int*> robot_shape){
    ofstream outFile3;
    string filename = "RobotShape.csv";
    outFile3.open(filename, ios::out|ios::trunc);
    for(auto iter: robot_shape){
        for(int i = 0; i< 8; ++i){
            outFile3 << iter[i] << ",";
        }
        outFile3 << endl;
    }
    cout<<"robot shape saved!"<<std::endl;
};



