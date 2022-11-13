#define GL_SILENCE_DEPRECATION
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

int Robot::pasteRobot(Robot* target){
    if(target->dots.size() != this->dots.size()) {
        return -1;
    }
    target->dots.assign(this->dots.begin(), this->dots.end());
    target->springs.assign(this->springs.begin(), this->springs.end());
    return 0;
};

void Robot::draw(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.6, 1.0);
    for(int i = 0; i< dots.size();++i){
        glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
    }
    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.6, 0.0);
    for(int i= 0; i<dots.size()-1; ++i){
        for(int j=i; j<dots.size(); ++j){
            glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
            glVertex3d(PVA[9*j+0], PVA[9*j+1], PVA[9*j+2]);
        }
    }
    glEnd();
};



void Robot::getCentral(double& x, double& y, double& z){
    x = 0;
    y = 0;
    z = 0;
    for(int i= 0; i< dots.size(); ++i){
        x += PVA[9*i + 0];
        y += PVA[9*i +1];
        z += PVA[9*i +2];
    }
    x = x/dots.size();
    y = y/dots.size();
    z = z/dots.size();
};

void Robot::addSprings(){
    this->springs.push_back(3.0);
    this->springs.push_back(10.0);
    this->springs.push_back(0.0);
    this->springs.push_back(0.0);
};

void Robot::addSprings(double k, double l0){
    this->springs.push_back(k);
    this->springs.push_back(l0);
    this->springs.push_back(0.0);
    this->springs.push_back(0.0);
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

BreathFullBoxRobot::BreathFullBoxRobot(double m, double l, double a, double b, double c, double k, glm::mat4& mat): FullBoxRobot(m,l,a,k,mat){
    for(int i = 0; i< this->springs.size()/4; ++i){
        this->springs[4*i+2] = b;
        this->springs[4*i+3] = c;
    }
};

PedalRobot::PedalRobot(double init_x, double init_y, double init_z){
    double boxheight = 5;
    double legheight = 10;
    double leglength = 3;
    double boxwidth = 10;

    addDotsSpringless(1, 0,0,0);
    addDotsSpringless(1, boxwidth+2*leglength,0,0);
    addDotsSpringless(1, 0,0,boxwidth+2*leglength);
    addDotsSpringless(1, boxwidth+2*leglength,0,boxwidth+2*leglength);
    addDotsSpringless(1, leglength,legheight,leglength);
    addDotsSpringless(1, leglength+boxwidth,legheight,leglength+boxwidth);
    addDotsSpringless(1, leglength,legheight,leglength+boxwidth);
    addDotsSpringless(1, leglength+boxwidth,legheight,leglength);
    addDotsSpringless(1, leglength,legheight+boxheight,leglength);
    addDotsSpringless(1, leglength+boxwidth,legheight+boxheight,leglength);
    addDotsSpringless(1, leglength,legheight+boxheight,leglength+boxwidth);
    addDotsSpringless(1, leglength+boxwidth,legheight+boxheight,leglength+boxwidth);
    
    for(int i = 1; i<dots.size(); ++i){
        for(int j = 0; j<i; ++j){
            double dx = PVA[9*i+0] - PVA[9*j+0];
            double dy = PVA[9*i+1] - PVA[9*j+1];
            double dz = PVA[9*i+2] - PVA[9*j+2];
            double delta = std::sqrt(dx*dx +dy*dy+ dz*dz);
            addSprings(500, delta);
        }
    }
    for(int i = 0; i<dots.size(); ++i){
        PVA[9*i + 0] += init_x;
        PVA[9*i + 1] += init_y;
        PVA[9*i + 2] += init_z;
    }
    for(int i = 0; i<6; ++i){
        springs[4*i +0] = 0;
    }
    getCentral(this->initx, this->inity, this->initz);
    
};

void PedalRobot::draw(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.6, 1.0, 0.0);
    for(int i = 4; i< dots.size();++i){
        glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
    }
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.6, 1.0);
    for(int i = 0; i< 4; ++i){
        glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
    }
    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.6, 0.0);
    for(int i =0; i <4; ++i){
        for(int j = 4; j<dots.size(); ++j){
            glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
            glVertex3d(PVA[9*j+0], PVA[9*j+1], PVA[9*j+2]);
        }
    }
    for(int i= 4; i<dots.size()-1; ++i){
        for(int j=i; j<dots.size(); ++j){
            glVertex3d(PVA[9*i+0], PVA[9*i+1], PVA[9*i+2]);
            glVertex3d(PVA[9*j+0], PVA[9*j+1], PVA[9*j+2]);
        }
    }
    glEnd();

};

Robot::Robot(){
    for(int i = 0; i < 3* types+60; ++i){
        gene.push_back(0.0);
    }
};

void PedalRobot::random(){
    
    for(int i = 0; i< types; ++i){
        gene[3*i+0] = (double)((rand()% (k_u - k_l + 1))+ k_l);
        gene[3*i+1] = (double)((rand()% (b_u - b_l + 1))+ b_l);
        gene[3*i+2] = (double)((rand()% (c_u - c_l + 1))+ c_l);
    };
    for(int i = 3*types; i< 60+ 3*types; ++i){
        gene[i] = rand() % 4;
    };
    for(int i = 0; i<dots.size(); ++i){
        dots[i] = (double)((rand()% (m_u - m_l + 1))+ m_l);
    }
};

void PedalRobot::mutate(double rate){
    double dice ;
    std::cout<<dice<<std::endl;
    for(int i = 0; i< dots.size(); ++i){
        dice = rand()/(double)RAND_MAX;
        if(dice<=rate)dots[i] = (double)((rand()% (m_u - m_l + 1))+ m_l);
        dice = rand()/(double)RAND_MAX;
        if(dice<=rate)springs[4*i+0] = (double)((rand()% (k_u - k_l + 1))+ k_l);
        dice = rand()/(double)RAND_MAX;
        if(dice<=rate)springs[4*i+2] = (double)((rand()% (b_u - b_l + 1))+ b_l);
        dice = rand()/(double)RAND_MAX;
        if(dice<=rate)springs[4*i+3] = (double)((rand()% (c_u - c_l + 1))+ c_l);
    }
};


void PedalRobot::getCentral(double& x, double& y, double& z){
    x = 0;
    y = 0;
    z = 0;
    for(int i= 4; i< dots.size(); ++i){
        x += PVA[9*i + 0];
        y += PVA[9*i +1];
        z += PVA[9*i +2];
    }
    x = x/(dots.size()-4);
    y = y/(dots.size()-4);
    z = z/(dots.size()-4);
};

double Robot::evaluateDis(){
    double dis = 0;
    double x = 0;
    double y = 0;
    double z = 0;
    this->getCentral(x, y, z);
    dis = sqrt((x-this->initx)* (x-this->initx) + (y-this->inity)*(y- this->inity));
    return dis;
};


Robot::~Robot(){
    for(int i = 0; i< this->pos.size(); ++i){
        delete[] pos[i];
    }
};

void Robot::mutateOnce(){
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

void Robot::reConstructFromGene(){
    for(int i = 0; i< springs.size()/4 - 6; ++i){
        int type_index = (int)gene[types*3+ i];
        springs[4*i +0 + 24] = gene[type_index*3 +0];
        springs[4*i +2 + 24] = gene[type_index*3 +1]; 
        springs[4*i +3 + 24] = gene[type_index*3 +2]; 
    }
};
