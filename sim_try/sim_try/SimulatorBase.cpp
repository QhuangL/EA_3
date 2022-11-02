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
    this->springs.push_back(3.0);
    this->springs.push_back(0.0);
    this->springs.push_back(0.0);
    this->springs.push_back(10.0);
};

void Robot::addSprings(double k, double l0){
    this->springs.push_back(k);
    this->springs.push_back(0.0);
    this->springs.push_back(0.0);
    this->springs.push_back(l0);
};

void Robot::addSprings(double k, double a, double b, double c){
    this->springs.push_back(k);
    this->springs.push_back(a);
    this->springs.push_back(b);
    this->springs.push_back(c);
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

void Robot::addDotsSpringless(double m, double x, double y, double z){
    this->dots.push_back(m);
    this->PVA.push_back(x);
    this->PVA.push_back(y);
    this->PVA.push_back(z);
    for(int i = 0; i< 6; ++i){
        this->PVA.push_back(0.0);
    }
};

Robot* Robot::randomGenerate(int ndots){
    auto robot = new Robot();
    for(int i = 0; i< ndots; ++i)
    robot->addDots(rand()/double(RAND_MAX));
    return robot;
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

BoxRobot::BoxRobot(double m, double l, glm::mat4& mat){
    double sqrt2 = std::sqrt(2);
    double sqrt3 = std::sqrt(3);
    std::vector<glm::vec4> vec;
    vec.push_back(glm::vec4(0,0,0,1));
    vec.push_back(glm::vec4(l,0,0,1));
    vec.push_back(glm::vec4(0,l,0,1));
    vec.push_back(glm::vec4(0,0,l,1));
    vec.push_back(glm::vec4(l,l,0,1));
    vec.push_back(glm::vec4(0,l,l,1));
    vec.push_back(glm::vec4(l,0,l,1));
    vec.push_back(glm::vec4(l,l,l,1));
    for(int i = 0; i< vec.size(); ++i){
        vec[i] = mat*vec[i];
    }
    
    this->addDotsSpringless(m,vec[0][0],vec[0][1],vec[0][2]);
    this->addSprings(10, l); // 1-0
    this->addDotsSpringless(m,vec[1][0],vec[1][1],vec[1][2]);
    this->addSprings(10, l); //2-0
    this->addSprings(0, l*sqrt2); //2-1
    this->addDotsSpringless(m,vec[2][0],vec[2][1],vec[2][2]);
    this->addSprings(10, l); //3-0
    this->addSprings(0, l*sqrt2); //3-1
    this->addSprings(0, l*sqrt2); //3-2
    this->addDotsSpringless(m,vec[3][0],vec[3][1],vec[3][2]);
    this->addSprings(0, l*sqrt2); //4-0
    this->addSprings(10, l); //4-1
    this->addSprings(10, l); //4-2
    this->addSprings(0, l*sqrt3); //4-3
    this->addDotsSpringless(m,vec[4][0],vec[4][1],vec[4][2]);
    this->addSprings(0, l*sqrt2); //5-0
    this->addSprings(0, l*sqrt3); //5-1
    this->addSprings(10, l); //5-2
    this->addSprings(10, l); //5-3
    this->addSprings(0, l*sqrt2); //5-4
    this->addDotsSpringless(m,vec[5][0],vec[5][1],vec[5][2]);
    this->addSprings(0, l*sqrt2); //6-0
    this->addSprings(10, l); //6-1
    this->addSprings(0, l*sqrt3); //6-2
    this->addSprings(10, l); //6-3
    this->addSprings(0, l*sqrt2); //6-4
    this->addSprings(0, l*sqrt2); //6-5
    this->addDotsSpringless(m,vec[6][0],vec[6][1],vec[6][2]);
    this->addSprings(0, l*sqrt3); //7-0
    this->addSprings(0, l*sqrt2); //7-1
    this->addSprings(0, l*sqrt2); //7-2
    this->addSprings(0, l*sqrt2); //7-3
    this->addSprings(10, l); //7-4
    this->addSprings(10, l); //7-5
    this->addSprings(10, l); //7-6
    this->addDotsSpringless(m,vec[7][0],vec[7][1],vec[7][2]); 
}


BoxRobot::BoxRobot(double m, double l, double k, glm::mat4& mat){
    double sqrt2 = std::sqrt(2);
    double sqrt3 = std::sqrt(3);
    std::vector<glm::vec4> vec;
    vec.push_back(glm::vec4(0,0,0,1));
    vec.push_back(glm::vec4(l,0,0,1));
    vec.push_back(glm::vec4(0,l,0,1));
    vec.push_back(glm::vec4(0,0,l,1));
    vec.push_back(glm::vec4(l,l,0,1));
    vec.push_back(glm::vec4(0,l,l,1));
    vec.push_back(glm::vec4(l,0,l,1));
    vec.push_back(glm::vec4(l,l,l,1));
    for(int i = 0; i< vec.size(); ++i){
        vec[i] = mat*vec[i];
    }
    
    this->addDotsSpringless(m,vec[0][0],vec[0][1],vec[0][2]);
    this->addSprings(k, l); // 1-0
    this->addDotsSpringless(m,vec[1][0],vec[1][1],vec[1][2]);
    this->addSprings(k, l); //2-0
    this->addSprings(0, l*sqrt2); //2-1
    this->addDotsSpringless(m,vec[2][0],vec[2][1],vec[2][2]);
    this->addSprings(k, l); //3-0
    this->addSprings(0, l*sqrt2); //3-1
    this->addSprings(0, l*sqrt2); //3-2
    this->addDotsSpringless(m,vec[3][0],vec[3][1],vec[3][2]);
    this->addSprings(0, l*sqrt2); //4-0
    this->addSprings(k, l); //4-1
    this->addSprings(k, l); //4-2
    this->addSprings(0, l*sqrt3); //4-3
    this->addDotsSpringless(m,vec[4][0],vec[4][1],vec[4][2]);
    this->addSprings(0, l*sqrt2); //5-0
    this->addSprings(0, l*sqrt3); //5-1
    this->addSprings(k, l); //5-2
    this->addSprings(k, l); //5-3
    this->addSprings(0, l*sqrt2); //5-4
    this->addDotsSpringless(m,vec[5][0],vec[5][1],vec[5][2]);
    this->addSprings(0, l*sqrt2); //6-0
    this->addSprings(k, l); //6-1
    this->addSprings(0, l*sqrt3); //6-2
    this->addSprings(k, l); //6-3
    this->addSprings(0, l*sqrt2); //6-4
    this->addSprings(0, l*sqrt2); //6-5
    this->addDotsSpringless(m,vec[6][0],vec[6][1],vec[6][2]);
    this->addSprings(0, l*sqrt3); //7-0
    this->addSprings(0, l*sqrt2); //7-1
    this->addSprings(0, l*sqrt2); //7-2
    this->addSprings(0, l*sqrt2); //7-3
    this->addSprings(k, l); //7-4
    this->addSprings(k, l); //7-5
    this->addSprings(k, l); //7-6
    this->addDotsSpringless(m,vec[7][0],vec[7][1],vec[7][2]); 
}

BoxRobot::BoxRobot(double m, double l){
    double sqrt2 = std::sqrt(2);
    double sqrt3 = std::sqrt(3);
    this->addDotsSpringless(m,0,0,0);
    this->addSprings(10, l); // 1-0
    this->addDotsSpringless(m,l,0,0);
    this->addSprings(10, l); //2-0
    this->addSprings(0, l*sqrt2); //2-1
    this->addDotsSpringless(m,0,l,0);
    this->addSprings(10, l); //3-0
    this->addSprings(0, l*sqrt2); //3-1
    this->addSprings(0, l*sqrt2); //3-2
    this->addDotsSpringless(m,0,0,l);
    this->addSprings(0, l*sqrt2); //4-0
    this->addSprings(10, l); //4-1
    this->addSprings(10, l); //4-2
    this->addSprings(0, l*sqrt3); //4-3
    this->addDotsSpringless(m,l,l,0);
    this->addSprings(0, l*sqrt2); //5-0
    this->addSprings(0, l*sqrt3); //5-1
    this->addSprings(10, l); //5-2
    this->addSprings(10, l); //5-3
    this->addSprings(0, l*sqrt2); //5-4
    this->addDotsSpringless(m,0,l,l);
    this->addSprings(0, l*sqrt2); //6-0
    this->addSprings(10, l); //6-1
    this->addSprings(0, l*sqrt3); //6-2
    this->addSprings(10, l); //6-3
    this->addSprings(0, l*sqrt2); //6-4
    this->addSprings(0, l*sqrt2); //6-5
    this->addDotsSpringless(m,l,0,l);
    this->addSprings(0, l*sqrt3); //7-0
    this->addSprings(0, l*sqrt2); //7-1
    this->addSprings(0, l*sqrt2); //7-2
    this->addSprings(0, l*sqrt2); //7-3
    this->addSprings(10, l); //7-4
    this->addSprings(10, l); //7-5
    this->addSprings(10, l); //7-6
    this->addDotsSpringless(m,l,l,l);

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
}

void Simulator::crossOver(){

};

void Simulator::rankSelection(){

};


