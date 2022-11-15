//
//  Evo_func.cpp
//  sim_try
//
//  Created by Qianhuang Li on 11/13/22.
//

#include "Evo_func.hpp"

Evo_func::Evo_func(){
    for (int i=0; i<72; ++i){
        gene.push_back(0);
    };
    
}

void Evo_func::randomGenerate(){
    for(int i = 0; i< types; ++i){
        gene[3*i+0] = (double) ((rand()% (k_u - k_l + 1))+ k_l) ;
        gene[3*i+1] = (double) ((rand()% ((b_u - b_l + 1)*10))+ b_l) /10;
        gene[3*i+2] = (double) ((rand()% ((c_u - c_l + 1)*10))+ c_l)/10;
    };
    for(int i = 3 * types; i< 60+ 3*types; ++i){
        gene[i] = rand() % 4;
    };
    population.push_back(gene);
};


void Evo_func::Crossover(){
    double temp;
    int n_gene = gene.size();
    for (int i = 0; i<population.size()-1; i+=2){
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
    std::cout<< pos<<std::endl;
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


void Evo_func::Out_file(){
    string EA_method = "cube";
    string filename = "lc_" + EA_method + "1" + ".csv";
    ofstream outFile;
    outFile.open(filename, ios::out);

    for (auto iter : fitness_list)
    {
        outFile << iter << endl;
    }
    cout << "File saved!" << endl;
}
