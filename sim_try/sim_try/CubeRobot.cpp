#include "CubeRobot.hpp"

CubeRobot::CubeRobot(double init_x, double init_y, double init_z){
    this->init_x = init_x;
    this->init_y = init_y;
    this->init_z = init_z;
};

int CubeRobot::dotindex(int x, int y, int z){
    return x + z*xdim + y*xdim*zdim;
};

void CubeRobot::getdotindex(int index, int& x, int& y, int& z){
    y = index/(xdim*zdim);
    z = (index%(xdim*zdim))/xdim;
    x = (index%(xdim*zdim))%xdim;
};

void CubeRobot::addBox(int x, int y, int z){
    int d0 = dotindex(x, y, z+1);
    int d1 = dotindex(x+1, y, z+1);
    int d2 = dotindex(x, y, z);
    int d3 = dotindex(x+1, y, z);
    int d4 = dotindex(x, y+1, z+1);
    int d5 = dotindex(x+1, y+1, z+1);
    int d6 = dotindex(x, y+1, z);
    int d7 = dotindex(x+1, y+1, z);
    for(int i = 0; i< cubeindex.size(); ++i){
        if(d0==cubeindex[i][0])return;
    }
    int n_box = cubeindex.size();
    cubeindex.push_back(new int[8]{d0,d1,d2,d3,d4,d5,d6,d7});
    
    for(int i = 0; i<7; ++i){
        for(int j = i+1; j<8; ++j){
            addspring(cubeindex[n_box][i], cubeindex[n_box][j]);
        }
    }

    
};

void CubeRobot::addspring(int i1, int i2){
    for(int i = 0; i< springs.size(); ++i){
        int s1 = (int)springs[i][0];
        int s2 = (int)springs[i][2];
        if((i1==s1&&i2==s2)||(i1==s2&&i2==s1)){
            return;
        }
    }
    int p1,p2;
    p1 = getdotpos(i1);
    p2 = getdotpos(i2);
    double dx = PVA[p1][0] - PVA[p2][0];
    double dy = PVA[p1][1] - PVA[p2][1];
    double dz = PVA[p1][2] - PVA[p2][2];
    double l0 = sqrt(dx*dx + dy*dy + dz*dz);

    springs.push_back(new double[8]{(double)i1,(double)p1,(double)i2,(double)p2,(double)k_l,l0,(double)0,(double)0});
};

int CubeRobot::getdotpos(int index){
    for(int i = 0; i< springs.size(); i++){
        int s1 = (int)springs[i][0];
        int s2 = (int)springs[i][2];
        if(s1 == index)return (int)springs[i][1];
        if(s2 == index)return (int)springs[i][3];
    }
    int x,y,z;
    getdotindex(index, x, y, z);
    PVA.push_back(new double[9]{
        init_x+ x*length, init_y+y*length, init_z+z*length,
        0,0,0,
        0,0,0
    });
    dots.push_back(m_l);
    return PVA.size()-1;
};


CubeRobot::~CubeRobot(){
    for(int i = 0; i < springs.size(); ++i){
        delete[] springs[i];
    }
    for(int i = 0; i< PVA.size(); ++i){
        delete[] PVA[i];
    }
    for(int i = 0; i<cubeindex.size(); ++i){
        delete[] cubeindex[i];
    }
};

void CubeRobot::draw(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.6, 1.0);
    for(int i = 0; i< dots.size();++i){
        glVertex3d(PVA[i][0], PVA[i][1], PVA[i][2]);
    }
    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.6, 0.0);
    for(int i = 0; i <springs.size(); ++i){
        int p1 = (int)springs[i][1];
        int p2 = (int)springs[i][3];
        glVertex3d(PVA[p1][0], PVA[p1][1], PVA[p1][2]);
        glVertex3d(PVA[p2][0], PVA[p2][1], PVA[p2][2]);
    }
    glEnd();


};


