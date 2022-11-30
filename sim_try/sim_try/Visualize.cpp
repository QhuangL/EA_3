#include "Visualize.hpp"

   float Visualizer:: deltaAngle = 0.0f;
   int Visualizer:: xOrigin = -1;
    // 相机相关
   float  Visualizer:: angle =0.0f;
   float  Visualizer:: pos_x=0.0f;
   float  Visualizer:: pos_z = 0.0f;
   double  Visualizer:: rotate_z = 0;
   double  Visualizer:: rotate_x = 0;
   float Visualizer::deltaMove = 0;

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
    glutInitWindowPosition(50, 50);

    glutCreateWindow( "GLUT" );
    
    //move from display
    glEnable (GL_LINE_SMOOTH);//启用线抗锯齿,边缘会降低其alpha值
    glEnable (GL_BLEND);//启用混合
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*对图像质量和渲染速度之间控制权衡关系*/
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);//没有偏向
    
    //end
    glutDisplayFunc( Visualizer::display );

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc( specialKeys );
    glutSpecialUpFunc(releaseKey);
    
    glEnable( GL_DEPTH_TEST );
    // glutTimerFunc(1,timerFunction,1);
    glutIdleFunc(idleFunction);

    glGetFloatv(GL_POINT_SIZE_RANGE, point_sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &point_step);
    cur_point_size = point_sizes[0];

    // std::cout<<point_sizes[0]<<"  "<<(float)point_step<<"  "<<point_sizes[1]<<std::endl;

    glGetFloatv(GL_LINE_WIDTH_RANGE, line_widths);
    cur_line_width = line_widths[0];
    
};

void Visualizer::releaseKey(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN: deltaMove = 0; break;
    
    default:
        break;
    }
}

void Visualizer::mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP){
            angle += deltaAngle;
            xOrigin = -1;
        }else{
            xOrigin = x;
        }
    }
};

void Visualizer::processNormalKeys(unsigned char key, int xx, int yy){
    if(key == 27)exit(0);
};

void Visualizer::mouseMove(int x, int y){
    if(xOrigin >=0){
        deltaAngle = (x - xOrigin)* 0.001f;
        rotate_x = sin(angle + deltaAngle);
        rotate_z = -cos(angle + deltaAngle);
    }
};

void Visualizer::idleFunction(){
    cubesim->update();
    glutPostRedisplay();
};

void Visualizer::timerFunction(int){
    cubesim->update();
    glutTimerFunc(1, timerFunction,1);
    glutPostRedisplay();
};


void Visualizer::specialKeys( int key, int x, int y ){
    if (key == GLUT_KEY_RIGHT)
        rotate_z += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_z -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
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
        60+pos_x, 40, 40 + pos_z,
        pos_x+rotate_x, 0, pos_z+rotate_z,
        0, 1, 0
        );

    Ground::Draw();
    // for(int i = 0; i < sim->robots.size()-1; ++i){
    //     drawBoxRobot(i);
    // }
    for(int i=0; i< cubesim->robots.size(); ++i){
        cubesim->robots[i]->draw();
    }
    

    glutSwapBuffers();
};

Simulator* Visualizer::sim = nullptr;
CubeSimulator* Visualizer::cubesim = nullptr;

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
};




