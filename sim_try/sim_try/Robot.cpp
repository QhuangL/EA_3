#include "Robot.hpp"

int Robot::getIndex(int i, int j){
    if(i>j){
        return i*(i-1)/2 + j;
    }else if(i==j){
        return -1;
    }else{
        return j*(j-1)/2 + i;
    }
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
    this->pos.push_back(new float[3]());    
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
    this->pos.push_back(new float[3]());
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
    this->pos.push_back(new float[3]());
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
};


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
};

BoxRobot::BoxRobot(double m, double l, double l0, double k, glm::mat4& mat){
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
    this->addSprings(k, l0); // 1-0
    this->addDotsSpringless(m,vec[1][0],vec[1][1],vec[1][2]);
    this->addSprings(k, l0); //2-0
    this->addSprings(0, l0*sqrt2); //2-1
    this->addDotsSpringless(m,vec[2][0],vec[2][1],vec[2][2]);
    this->addSprings(k, l0); //3-0
    this->addSprings(0, l0*sqrt2); //3-1
    this->addSprings(0, l0*sqrt2); //3-2
    this->addDotsSpringless(m,vec[3][0],vec[3][1],vec[3][2]);
    this->addSprings(0, l0*sqrt2); //4-0
    this->addSprings(k, l0); //4-1
    this->addSprings(k, l0); //4-2
    this->addSprings(0, l0*sqrt3); //4-3
    this->addDotsSpringless(m,vec[4][0],vec[4][1],vec[4][2]);
    this->addSprings(0, l0*sqrt2); //5-0
    this->addSprings(0, l0*sqrt3); //5-1
    this->addSprings(k, l0); //5-2
    this->addSprings(k, l0); //5-3
    this->addSprings(0, l0*sqrt2); //5-4
    this->addDotsSpringless(m,vec[5][0],vec[5][1],vec[5][2]);
    this->addSprings(0, l0*sqrt2); //6-0
    this->addSprings(k, l0); //6-1
    this->addSprings(0, l0*sqrt3); //6-2
    this->addSprings(k, l0); //6-3
    this->addSprings(0, l0*sqrt2); //6-4
    this->addSprings(0, l0*sqrt2); //6-5
    this->addDotsSpringless(m,vec[6][0],vec[6][1],vec[6][2]);
    this->addSprings(0, l0*sqrt3); //7-0
    this->addSprings(0, l0*sqrt2); //7-1
    this->addSprings(0, l0*sqrt2); //7-2
    this->addSprings(0, l0*sqrt2); //7-3
    this->addSprings(k, l0); //7-4
    this->addSprings(k, l0); //7-5
    this->addSprings(k, l0); //7-6
    this->addDotsSpringless(m,vec[7][0],vec[7][1],vec[7][2]); 
};


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
};


FullBoxRobot::FullBoxRobot(double m, double l, double l0, double k, glm::mat4& mat){
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
    this->addSprings(k, l0); // 1-0
    this->addDotsSpringless(m,vec[1][0],vec[1][1],vec[1][2]);
    this->addSprings(k, l0); //2-0
    this->addSprings(k, l0*sqrt2); //2-1
    this->addDotsSpringless(m,vec[2][0],vec[2][1],vec[2][2]);
    this->addSprings(k, l0); //3-0
    this->addSprings(k, l0*sqrt2); //3-1
    this->addSprings(k, l0*sqrt2); //3-2
    this->addDotsSpringless(m,vec[3][0],vec[3][1],vec[3][2]);
    this->addSprings(k, l0*sqrt2); //4-0
    this->addSprings(k, l0); //4-1
    this->addSprings(k, l0); //4-2
    this->addSprings(k, l0*sqrt3); //4-3
    this->addDotsSpringless(m,vec[4][0],vec[4][1],vec[4][2]);
    this->addSprings(k, l0*sqrt2); //5-0
    this->addSprings(k, l0*sqrt3); //5-1
    this->addSprings(k, l0); //5-2
    this->addSprings(k, l0); //5-3
    this->addSprings(k, l0*sqrt2); //5-4
    this->addDotsSpringless(m,vec[5][0],vec[5][1],vec[5][2]);
    this->addSprings(k, l0*sqrt2); //6-0
    this->addSprings(k, l0); //6-1
    this->addSprings(k, l0*sqrt3); //6-2
    this->addSprings(k, l0); //6-3
    this->addSprings(k, l0*sqrt2); //6-4
    this->addSprings(k, l0*sqrt2); //6-5
    this->addDotsSpringless(m,vec[6][0],vec[6][1],vec[6][2]);
    this->addSprings(k, l0*sqrt3); //7-0
    this->addSprings(k, l0*sqrt2); //7-1
    this->addSprings(k, l0*sqrt2); //7-2
    this->addSprings(k, l0*sqrt2); //7-3
    this->addSprings(k, l0); //7-4
    this->addSprings(k, l0); //7-5
    this->addSprings(k, l0); //7-6
    this->addDotsSpringless(m,vec[7][0],vec[7][1],vec[7][2]);
};


Tetrahedron::Tetrahedron(double m, double l, double l0, double k, glm::mat4& mat){
    std::vector<glm::vec4> vec;
    double sqrt2 = std::sqrt(2);
    double sqrt3 = std::sqrt(3);
    vec.push_back(glm::vec4(0,0,0,1));
    vec.push_back(glm::vec4(l,0,0,1));
    vec.push_back(glm::vec4(l/2,0 ,sqrt3*l/2,1));
    vec.push_back(glm::vec4(l/2,sqrt2*l/sqrt3,l*sqrt3/6,1));
    for(int i = 0; i< vec.size(); ++i){
        vec[i] = mat*vec[i];
    }
    this->addDotsSpringless(m,vec[0][0],vec[0][1],vec[0][2]);
    this->addDotsSpringless(m,vec[1][0],vec[1][1],vec[1][2]);
    this->addDotsSpringless(m,vec[2][0],vec[2][1],vec[2][2]);
    this->addDotsSpringless(m,vec[3][0],vec[3][1],vec[3][2]);
    for(int i =0; i<6; ++i){
        this->addSprings(k, l0);
    }
};

Robot::~Robot(){
    for(int i = 0; i< this->pos.size(); ++i){
        delete[] pos[i];
    }
}