//
//  Evo_func.cpp
//  sim_try
//
//  Created by Qianhuang Li on 11/13/22.
//

#include "Evo_func.hpp"

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
    };
};
void Evo_func::Mutation(double rate){
    
    
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
void Evo_func::reConstructFromGene(){
    for(int i = 0; i< springs.size()/4 - 6; ++i){
        int type_index = (int)gene[types*3+ i];
        springs[4*i +0 + 24] = gene[type_index*3 +0];
        springs[4*i +2 + 24] = gene[type_index*3 +1];
        springs[4*i +3 + 24] = gene[type_index*3 +2];
    }
};
