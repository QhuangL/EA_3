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
        {0.6,0.0,1.0},
        {0.0,1.0,1.0},
        {0.0,0.6,1.0},
        {0.6,0.0,1.0},
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

