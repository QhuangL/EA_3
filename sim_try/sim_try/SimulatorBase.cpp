#include "SimulatorBase.hpp"

int Robot::getIndex(int i, int j){
    if(i>j){
        return i*(i-1)/2 + j;
    }else if(i==j){
        return -1;
    }else{
        return j*(j-1)/2 + i;
    }
};



Simulator::Simulator(double dt, int step){
    this->dt = dt;
    this->step = step;
    this->pos = new float[3*8];
};

Simulator::~Simulator(){
    for(int i = 0; i<this->robots.size(); ++i){
        delete this->robots[i];
    }
    delete this->pos;
};


void Robot::addSprings(){
    this->springs.push_back(10.0);
    this->springs.push_back(0.0);
    this->springs.push_back(0.0);
    this->springs.push_back(16.0);
};

void Robot::addDots(double m){
    this->dots.push_back(m);
    for(int i = 0; i < 3; ++i){
        this->PVA.push_back(10* rand()/double(RAND_MAX));
    }
    for(int i = 0; i< 6; ++i){
        this->PVA.push_back(0.0);
    }
    for(int i  =0; i< this->dots.size()-1; ++i){
        addSprings();
    }
    return;
};

void Robot::addDots(double m, double x, double y, double z){
    this->dots.push_back(m);
    this->PVA.push_back(x);
    this->PVA.push_back(y);
    this->PVA.push_back(z);
    for(int i = 0; i< 6; ++i){
        this->PVA.push_back(0.0);
    }
    for(int i  =0; i< this->dots.size()-1; ++i){
        addSprings();
    }
    return;
};

Robot* Robot::randomGenerate(int ndots){
    auto robot = new Robot();
    for(int i = 0; i< ndots; ++i)
    robot->addDots(rand()/double(RAND_MAX));
    return robot;
};


void Simulator::update(){
    for(int i =0 ; i< this->robots.size(); ++i){
        auto robot = this->robots[i];
        for(int j = 0; j<robot->dots.size(); ++j){
            robot->PVA[9*j+6] = 0;
            robot->PVA[9*j+7] = 0;
            robot->PVA[9*j+8] = 0;
        }
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
                
                robot->PVA[9*j+6] -= ex * fint/robot->dots[j];
                robot->PVA[9*j+7] -= ey * fint/robot->dots[j];
                robot->PVA[9*j+8] -= ez * fint/robot->dots[j];
                robot->PVA[9*k+6] += ex * fint/robot->dots[k];
                robot->PVA[9*k+7] += ey * fint/robot->dots[k];
                robot->PVA[9*k+8] += ez * fint/robot->dots[k];

            }
        }
        
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
        for(int i = 0; i<robot->dots.size(); ++i){
            if(robot->PVA[9*i+1]< 0 ){
                robot->PVA[9*i+1] = -robot->PVA[9*i+1] ;
                robot->PVA[9*i+4] = -robot->PVA[9*i+4] ;
            }
        }
    }
    // if hit ground
    
    return;
}

BoxRobot::BoxRobot(){
    this->addDots(1,0,0,0);
    this->addDots(1,5,0,0);
    this->addDots(1,0,5,0);
    this->addDots(1,0,0,5);
    this->addDots(1,5,5,0);
    this->addDots(1,0,5,5);
    this->addDots(1,5,0,5);
    this->addDots(1,5,5,5);
};

TwoPoints::TwoPoints(){
    this->addDots(1,0,0,0);
    this->addDots(1,1,0,0);
}

void Simulator::output(){
    auto& robot = this->robots[0];
    for(int i =0; i<this->robots[0]->dots.size();++i){
        this->pos[3*i] = robot->PVA[9*i+0];
        this->pos[3*i+1] = robot->PVA[9*i+1];
        this->pos[3*i+2] = robot->PVA[9*i+2];
        
    }
}

void Simulator::randomAddRobots(int n_robot, int n_dots){
    for(int i = 0; i< n_robot; ++i)
    this->robots.push_back(Robot::randomGenerate(n_dots));
};

void Simulator::mutate(double rate){
    // for(int i = 0; i< n_robot; ++i){

    // }
};

void Simulator::crossOver(){

};

void Simulator::rankSelection(){

};


