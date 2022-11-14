#include "CubeRobot.hpp"

CubeRobot::CubeRobot(double init_x, double init_y, double init_z){
    for(int i = 0; i < 8; ++i){
        dots.push_back(m_l);
    }
    box.push_back(new int[8]{0,1,2,3,4,5,6,7});
    springs.push_back(new double[4*28]);
    
};

CubeRobot::~CubeRobot(){
    for(int i = 0; i< box.size(); ++i){
        delete[] box[i];
    }
    for(int i = ; i < springs.size(); ++i){
        delete[] springs[i];
    }
};



void CubeRobot::draw(){
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
}