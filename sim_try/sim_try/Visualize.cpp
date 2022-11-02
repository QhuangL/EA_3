#include "Visualize.hpp"


double rotate_y = 0;
double rotate_x = 0;
float ver[8][3] =
    {
        {-1.0,-1.0,1.0},
        {-1.0,1.0,1.0},
        {1.0,1.0,1.0},
        {1.0,-1.0,1.0},
        {-1.0,-1.0,-1.0},
        {-1.0,1.0,-1.0},
        {1.0,1.0,-1.0},
        {1.0,-1.0,-1.0},
    };
GLfloat color[8][3] =
    {
        {0.6,0.0,1.0},
        {0.0,0.0,1.0},
        {0.0,1.0,1.0},
        {0.0,0.5,1.0},
        {0.0,1.0,1.0},
        {0.0,0.6,1.0},
        {0.0,1.0,1.0},
        {0.0,1.0,1.0},
    };

void Visualizer::init(int argc, char**argv){
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "GLUT" );
    
    //move from display
    glEnable (GL_LINE_SMOOTH);//启用线抗锯齿,边缘会降低其alpha值
    glEnable (GL_BLEND);//启用混合
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*对图像质量和渲染速度之间控制权衡关系*/
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);//没有偏向
    
    //end
    glutDisplayFunc( Visualizer::display );
    glutSpecialFunc( specialKeys );
    glEnable( GL_DEPTH_TEST );
    
};


void Visualizer::specialKeys( int key, int x, int y ){
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
    std::cout<<rotate_x<<std::endl;
};

void Visualizer::quad(int a,int b,int c,int d){
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
};

void Visualizer::colorcube(){
    quad(0,3,6,1); //bottom reverse clockwise
    quad(0,1,4,2); //back
    quad(0,2,5,3); //left
    quad(1,4,7,6); //right
    quad(3,5,7,6); //front
    quad(2,4,7,5); //up
};

void Visualizer::display(){
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(
        40, 40, 40,
        0, 0, 0,
        0, 1, 0
        );

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    Ground::Draw();
    colorcube();
    glutSwapBuffers();
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
