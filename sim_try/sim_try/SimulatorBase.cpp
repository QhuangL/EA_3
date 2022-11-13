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
    this->t += this->dt;
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
                double l0 = robot->springs[index*4+1]+  sin(this->omega*this->t + robot->springs[index*4+3]) * robot->springs[index*4+2];
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
        for(int j =0; j<robot->dots.size();++j){
            double vi_vi = robot->PVA[9*j+3]*robot->PVA[9*j+3]+ robot->PVA[9*j+4]*robot->PVA[9*j+4]+ robot->PVA[9*j+5]*robot->PVA[9*j+5];
            robot->kineticEnergy += 0.5*robot->dots[j]* vi_vi ;
            robot->potentialEnergy_G+= robot->dots[j]* 9.8 * robot->PVA[9*j+1];
        }
        robot->energy = robot->kineticEnergy + robot->potentialEnergy_G + robot->potentialEnergy_Spring;
        
        //gravity
        for(int j = 0; j<robot->dots.size(); ++j){
            robot->PVA[9*j+7] += gravity;
        }

        // react with the ground
        for(int j = 0; j< robot->dots.size(); ++j){
            if(robot->PVA[9*j+1] <= 0){
                if(robot->PVA[9*j+7] < 0){
                    // normal force * mu
                    double friction = -this->k_ground* robot->PVA[9*j+1] * friction_mu_k;
                    
                    // horizental force
                    double fh = std::sqrt(robot->PVA[9*j+6]* robot->PVA[9*j+6] + robot->PVA[9*j+8]* robot->PVA[9*j+8]);
                    double vh = std::sqrt(robot->PVA[9*j+3]*robot->PVA[9*j+3] + robot->PVA[9*j+5]*robot->PVA[9*j+5]);
                    
                    if(vh > 0.1){
                        robot->PVA[9*j+6] -= robot->PVA[9*j+3]/vh * friction;
                        robot->PVA[9*j+8] -= robot->PVA[9*j+5]/vh * friction;
                    }else if(vh <= 0.1){
                        if(fh < friction){
                            robot->PVA[9*j+6] = 0;
                            robot->PVA[9*j+8] = 0;
                        }else{
                            robot->PVA[9*j+6] -= robot->PVA[9*j+6]/fh * friction;
                            robot->PVA[9*j+8] -= robot->PVA[9*j+8]/fh * friction;
                        }
                    }
                }

                robot->PVA[9*j+7] -= k_ground* robot->PVA[9*j+1];
            }
        }
        
        for(int j = 0; j<robot->dots.size(); ++j){
            //integrate
            robot->PVA[9*j+3] += robot->PVA[9*j+6]*this->dt;
            robot->PVA[9*j+4] += robot->PVA[9*j+7]*this->dt;
            robot->PVA[9*j+5] += robot->PVA[9*j+8]*this->dt;
            //dampening
            robot->PVA[9*j+3] *= dampening;
            robot->PVA[9*j+4] *= dampening;
            robot->PVA[9*j+5] *= dampening;
            robot->PVA[9*j+0] += robot->PVA[9*j+3]*this->dt;
            robot->PVA[9*j+1] += robot->PVA[9*j+4]*this->dt;
            robot->PVA[9*j+2] += robot->PVA[9*j+5]*this->dt;
            
        }

    }
    for(int i =0 ;i< this->robots.size(); ++i){
        std::cout<<robots[i]->evaluateDis()<<" ";
    }
    std::cout<<std::endl;
    
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

//这个crossOver必须要求机器人形状相同！！
void Simulator::crossOver(){
    int n_robot = robots.size();
    

};

void Simulator::rankSelection(){
    for(int i = 0; i< robots.size(); ++i){
        
    }
};


