//
//  Evo_func.cpp
//  sim_try
//
//  Created by Qianhuang Li on 11/13/22.
//

#include "Evo_func.hpp"


Evo_func::Evo_func(CubeSimulator* tempSim){
    sim = tempSim;
    for (int i=0; i<3*types+ sim->robots[0]->springs.size(); ++i){
        gene.push_back(0);
    };
};

Evo_func::~Evo_func(){
    // for(int i = 0; i< population.size(); ++i){
    //     delete population[i];
    // }
};

void Evo_func::randomGenerate(){
    for(int i = 0; i< types; ++i){
        gene[3*i+0] = (double) ((rand()% (k_u - k_l + 1))+ k_l) ;
        gene[3*i+1] = (double) ((rand()% ((b_u - b_l + 1)*10))+ b_l) /100;
        gene[3*i+2] = (double) ((rand()% ((c_u - c_l + 1)*10))+ c_l)/100;
    };
    for(int i = 3 * types; i< 3*types+sim->robots[0]->springs.size(); ++i){
        gene[i] = rand() % 4;
    };
    population.push_back(gene);//?
    // std::cout<< sim->robots[0]->springs.size()<<std::endl;
};


void Evo_func::Crossover(){
    double temp;
    int n_gene = gene.size();
    int n_pop = population.size();
    for (int i = 0; i<n_pop-1; i+=2){
        p1 = rand() % (n_gene-1);
        p2 = rand() % (n_gene-p1-1) + p1+1;
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


void Evo_func::mutateOnce(){
    int pos = (rand()% (this->gene.size() + 1));
    if(pos < types *3){
        int pospos = pos%3;
        if(pospos == 0){
            this->gene[pos] = (double)((rand()% (k_u - k_l + 1))+ k_l);
        }else if(pospos == 1){
            this->gene[pos] = (double) ((rand()% ((b_u - b_l + 1)*10))+ b_l) /10;
        }else{
            this->gene[pos] = (double) ((rand()% ((c_u - c_l + 1)*10))+ c_l)/10;
        }
    }else{
        this->gene[pos] = (double)((rand()% ((types)*9)+ 1)/10);
    }
};


void Evo_func::Out_file(vector<vector<double>> his_fit){
    string EA_method = "cross_";
    string filename = "lc_" + EA_method + "1" + ".csv";
    ofstream outFile;
    outFile.open(filename, ios::out);

    for (auto iter : his_fit)
    {
        for(auto idx : iter){
            outFile << idx << ",";
        }
        outFile << endl;
        
    }
    cout << "File saved!" << endl;
}
