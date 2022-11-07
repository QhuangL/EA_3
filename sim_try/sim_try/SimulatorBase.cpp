#include "SimulatorBase.hpp"


Simulator::Simulator(double dt, int step){
    this->dt = dt;
    this->step = step;
};

Simulator::~Simulator(){
    for(int i = 0; i<this->robots.size(); ++i){
        delete this->robots[i];
    }
};


void Simulator::update(){
    this->current_step +=1;
    for(int i =0 ; i< this->robots.size(); ++i){
        auto robot = this->robots[i];
        for(int j = 0; j<robot->dots.size(); ++j){
            robot->PVA[9*j+6] = 0;
            robot->PVA[9*j+7] = 0;
            robot->PVA[9*j+8] = 0;
        }
        robot->energy = 0;
        robot->potentialEnergy_G = 0;
        robot->kineticEnergy = 0;
        robot->potentialEnergy_Spring =0;
        for(int j = 0; j<robot->dots.size()-1; ++j){
            for(int k = j+1; k<robot->dots.size(); ++k){
                //interact
                int index = robot->getIndex(j, k);
                double dx = robot->PVA[9*j+0] - robot->PVA[9*k+0];
                double dy = robot->PVA[9*j+1] - robot->PVA[9*k+1];
                double dz = robot->PVA[9*j+2] - robot->PVA[9*k+2];
                double length= std::sqrt(dx*dx + dy*dy + dz*dz);
                double ex = dx/length;
                double ey = dy/length;
                double ez = dz/length;
                double l0 = robot->springs[index*4+1]* sin(robot->springs[index*4+2]) + robot->springs[index*4+3];
                double fint = robot->springs[index*4+0]*(length - l0);
                robot->potentialEnergy_Spring += 0.5*robot->springs[index*4+0]*(length-l0)*(length-l0);
                robot->PVA[9*j+6] -= ex * fint/robot->dots[j];
                robot->PVA[9*j+7] -= ey * fint/robot->dots[j];
                robot->PVA[9*j+8] -= ez * fint/robot->dots[j];
                robot->PVA[9*k+6] += ex * fint/robot->dots[k];
                robot->PVA[9*k+7] += ey * fint/robot->dots[k];
                robot->PVA[9*k+8] += ez * fint/robot->dots[k];

            }
        }
        //calculate energy
        for(int i =0; i<robot->dots.size();++i){
            double vi_vi = robot->PVA[9*i+3]*robot->PVA[9*i+3]+ robot->PVA[9*i+4]*robot->PVA[9*i+4]+ robot->PVA[9*i+5]*robot->PVA[9*i+5];
            robot->kineticEnergy += 0.5*robot->dots[i]* vi_vi ;
            robot->potentialEnergy_G+= robot->dots[i]* 9.8 * robot->PVA[9*i+1];
        }
        robot->energy = robot->kineticEnergy + robot->potentialEnergy_G + robot->potentialEnergy_Spring;
        
        //gravity
        for(int i = 0; i<robot->dots.size(); ++i){
            robot->PVA[9*i+7] -= 9.8;
        }
        
        for(int j = 0; j<robot->dots.size(); ++j){
            //integrate
            robot->PVA[9*j+3] += robot->PVA[9*j+6]*dt;
            robot->PVA[9*j+4] += robot->PVA[9*j+7]*dt;
            robot->PVA[9*j+5] += robot->PVA[9*j+8]*dt;
            robot->PVA[9*j+0] += robot->PVA[9*j+3]*dt;
            robot->PVA[9*j+1] += robot->PVA[9*j+4]*dt;
            robot->PVA[9*j+2] += robot->PVA[9*j+5]*dt;
            
        }
        // bounce from the floor
        for(int i = 0; i<robot->dots.size(); ++i){
            if(robot->PVA[9*i+1]< 0 ){
                robot->PVA[9*i+1] = -robot->PVA[9*i+1] ;
                robot->PVA[9*i+4] = - this->e * robot->PVA[9*i+4] ;
            }
        }
    }
    
    return;
}


void Simulator::output(){
    for(int r = 0; r < this->robots.size(); ++r){
        auto& robot = this->robots[r];
        for(int i =0; i<robot->dots.size();++i){
            robot->pos[i][0] = robot->PVA[9*i+0];
            robot->pos[i][1] = robot->PVA[9*i+1];
            robot->pos[i][2] = robot->PVA[9*i+2];
        }
    }
};


void Simulator::randomAddRobots(int n_robot, int n_dots){
    for(int i = 0; i< n_robot; ++i)
    this->robots.push_back(Robot::randomGenerate(n_dots));
};

void Simulator::mutate(double rate){
    // for(int i = 0; i< n_robot; ++i){

    // }
};

SimNoGravity::SimNoGravity(double dt, int step):Simulator(dt, step){

};

void SimNoGravity::update(){
    this->current_step+=1;
    for(int i =0 ; i< this->robots.size(); ++i){
        auto robot = this->robots[i];
        for(int j = 0; j<robot->dots.size(); ++j){
            robot->PVA[9*j+6] = 0;
            robot->PVA[9*j+7] = 0;
            robot->PVA[9*j+8] = 0;
        }
        robot->energy = 0;
        robot->potentialEnergy_G = 0;
        robot->kineticEnergy = 0;
        robot->potentialEnergy_Spring =0;

        for(int j = 0; j<robot->dots.size()-1; ++j){
            for(int k = j+1; k<robot->dots.size(); ++k){
                //interact
                int index = robot->getIndex(j, k);
                double dx = robot->PVA[9*j+0] - robot->PVA[9*k+0];
                double dy = robot->PVA[9*j+1] - robot->PVA[9*k+1];
                double dz = robot->PVA[9*j+2] - robot->PVA[9*k+2];
                double length= std::sqrt(dx*dx + dy*dy + dz*dz);
                double ex = dx/length;
                double ey = dy/length;
                double ez = dz/length;
                double l0 = robot->springs[index*4+1]* sin(robot->springs[index*4+2]) + robot->springs[index*4+3];
                double fint = robot->springs[index*4+0]*(length - l0);
                robot->potentialEnergy_Spring += 0.5*robot->springs[index*4+0]*(length-l0)*(length-l0);
                robot->PVA[9*j+6] -= ex * fint/robot->dots[j];
                robot->PVA[9*j+7] -= ey * fint/robot->dots[j];
                robot->PVA[9*j+8] -= ez * fint/robot->dots[j];
                robot->PVA[9*k+6] += ex * fint/robot->dots[k];
                robot->PVA[9*k+7] += ey * fint/robot->dots[k];
                robot->PVA[9*k+8] += ez * fint/robot->dots[k];

            }
        }
        //calculate energy
        for(int i =0; i<robot->dots.size();++i){
            double vi_vi = robot->PVA[9*i+3]*robot->PVA[9*i+3]+ robot->PVA[9*i+4]*robot->PVA[9*i+4]+ robot->PVA[9*i+5]*robot->PVA[9*i+5];
            robot->kineticEnergy += 0.5*robot->dots[i]* vi_vi ;
        }
        robot->energy = robot->kineticEnergy  + robot->potentialEnergy_Spring;
        
        
        for(int j = 0; j<robot->dots.size(); ++j){
            //integrate
            robot->PVA[9*j+3] += robot->PVA[9*j+6]*dt;
            robot->PVA[9*j+4] += robot->PVA[9*j+7]*dt;
            robot->PVA[9*j+5] += robot->PVA[9*j+8]*dt;
            robot->PVA[9*j+0] += robot->PVA[9*j+3]*dt;
            robot->PVA[9*j+1] += robot->PVA[9*j+4]*dt;
            robot->PVA[9*j+2] += robot->PVA[9*j+5]*dt;
            
        }
    }
    
    return;
};

void Simulator::crossOver(){

};

void Simulator::rankSelection(){

};


