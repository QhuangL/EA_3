#include "Visualize.hpp"


double rotate_y = 0;
double rotate_x = 0;

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
    glutTimerFunc(1,timerFunction,1);

    glGetFloatv(GL_POINT_SIZE_RANGE, point_sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &point_step);
    cur_point_size = point_sizes[0];

    std::cout<<point_sizes[0]<<"  "<<(float)point_step<<"  "<<point_sizes[1]<<std::endl;

    glGetFloatv(GL_LINE_WIDTH_RANGE, line_widths);
    cur_line_width = line_widths[0];
    
};

void Visualizer::timerFunction(int){
    sim->update();
    sim->output();
    glutTimerFunc(1, timerFunction,1);
    glutPostRedisplay();
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
    for(int i = 0; i < sim->robots.size()-1; ++i){
        drawBoxRobot(i);
    }
    // PedalRobot* temp = static_cast<PedalRobot*>(sim->robots[3]);
    // temp->draw();
    sim->robots[3]->draw();
    
    // colorcube();

    glutSwapBuffers();
};

Simulator* Visualizer::sim = nullptr;

    GLfloat Visualizer::point_sizes[2]{0.0, 0.0};
    GLfloat Visualizer::point_step = 0.0;
    GLfloat Visualizer::cur_point_size= 0.0;
    GLfloat Visualizer::line_widths[2]{0.0, 0.0};
    GLfloat Visualizer::cur_line_width=0.0;


void Visualizer::drawBoxRobot(int i){
    drawQuadfromPVA(i,0,3,6,1); //bottom reverse clockwise
    drawQuadfromPVA(i,0,1,4,2); //back
    drawQuadfromPVA(i,0,2,5,3); //left
    drawQuadfromPVA(i,1,4,7,6); //right
    drawQuadfromPVA(i,3,5,7,6); //front
    drawQuadfromPVA(i,2,4,7,5); //up
};

void Visualizer::drawQuadfromPVA(int i, int a,int b,int c,int d){
    glBegin(GL_QUADS);
    auto& ver = sim->robots[i]->pos;
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
}

