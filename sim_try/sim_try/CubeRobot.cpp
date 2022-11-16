#define GL_SILENCE_DEPRECATION
#include "CubeRobot.hpp"

CubeRobot::CubeRobot(double init_x, double init_y, double init_z){
    this->init_x = init_x;
    this->init_y = init_y;
    this->init_z = init_z;
};

void CubeRobot::getCenter(double& x, double& y, double& z){
    double tx = 0;
    double ty = 0;
    double tz = 0;
    double size = dots.size();
    for(int i = 0; i< dots.size(); ++i){
        tx+= PVA[i][0];
        ty+= PVA[i][1];
        tz+= PVA[i][2];
    }
    x = tx / size;
    y = ty / size;
    z = tz / size;
};

void CubeRobot::setStartPos(){
    getCenter(this->start_x, this->start_y, this->start_z);
};

double CubeRobot::getOffset(){
    double x = 0;
    double y = 0;
    double z = 0;
    getCenter(x,y,z);
    return sqrt((x-start_x)*(x-start_x) + (y-start_y)*(y-start_y));
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

void CubeRobot::getgene(std::vector<double> gene){
    for(int i = 0; i< springs.size(); ++i){
        int type_index = (int) gene[types*3+ i];
        springs[i][4] = gene[type_index*3 +0];
        springs[i][6] = gene[type_index*3 +1];
        springs[i][7] = gene[type_index*3 +2];
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
    double l0_Temp = sqrt(dx*dx + dy*dy + dz*dz);
    this->l0.push_back(l0_Temp);

    springs.push_back(new double[8]{(double)i1,(double)p1,(double)i2,(double)p2,(double)k_l,l0_Temp,(double)0,(double)0});
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
    for(int i = 0; i<PVA_init.size(); ++i){
        delete[] PVA_init[i];
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

void CubeRobot::reConstructFromGene(std::vector<double> gene){
    for(int i = 0; i< springs.size(); ++i){
        int type_index = (int)gene[types*3+ i];
        springs[i][4] = gene[type_index*3 +0];
        springs[i][6] = gene[type_index*3 +1];
        springs[i][7] = gene[type_index*3 +2];
        
        springs[i][5] = this->l0[i] - springs[i][6]*sin(springs[i][7]);
    }
};


CrossRobot::CrossRobot(double initx, double inity, double initz):CubeRobot(initx, init_y, initz){
    addBox(2,1,2);
    addBox(2,1,1);
    addBox(2,1,0);
    addBox(3,1,2);
    addBox(4,1,2);
    addBox(1,1,2);
    addBox(0,1,2);
    addBox(2,1,3);
    addBox(2,1,4);
    addBox(2,0,4);
    addBox(4,0,2);
    addBox(0,0,2);
    addBox(2,0,0);
    for(int i = 0; i< PVA.size(); ++i){
        PVA_init.push_back(new double[9]{0,0,0,0,0,0,0,0,0});
        for(int j = 0; j< 9; ++j){
            PVA_init[i][j] =  PVA[i][j];
        }
    }
}
