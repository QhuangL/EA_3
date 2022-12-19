
#include "Applications/Draw/Canvas.hpp"

void Visualizer2D::init(int argc, char**argv){
    glutInit( &argc, argv );
    //声明显示模式，窗口大小等
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 1920, 1200 );
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "Canvas" );
    
    //优化显示
    glEnable (GL_LINE_SMOOTH);//启用线抗锯齿,边缘会降低其alpha值
    glEnable (GL_BLEND);//启用混合
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);/*对图像质量和渲染速度之间控制权衡关系*/
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);//没有偏向
    
    //注册显示函数
    glutDisplayFunc(display);
    //注册键盘事件
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(specialKeys );
    glutSpecialUpFunc(releaseKey);
    //注册空闲时函数
    glutIdleFunc(idleFunction);
    //注册形状改变函数
    glutReshapeFunc(reshape);
    
};


void Visualizer2D::releaseKey(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN: 
    
    default:
        break;
    }
}

void Visualizer2D::mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP){
            
        }else{
            
        }
    }
};

void Visualizer2D::processNormalKeys(unsigned char key, int xx, int yy){
    if(key == 27)exit(0);
};



void Visualizer2D::idleFunction(){
    
    glutPostRedisplay();
};

void Visualizer2D::timerFunction(int){
    glutTimerFunc(1, timerFunction,1);
    glutPostRedisplay();
};


void Visualizer2D::specialKeys( int key, int x, int y ){
    if (key == GLUT_KEY_RIGHT)
        std::cout<<"Right"<<std::endl;
    else if (key == GLUT_KEY_LEFT)
        std::cout<<"Left"<<std::endl;
    else if (key == GLUT_KEY_UP)
        std::cout<<"UP"<<std::endl;
    else if (key == GLUT_KEY_DOWN)
        std::cout<<"Down"<<std::endl;
    // glutPostRedisplay();
};


void Visualizer2D::display(){
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    
    glutSwapBuffers();
};

void Visualizer2D::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0, 1.0, 0.0, (GLfloat)h / (GLfloat)w * 1.0, 0.0, 1.0);
	else
		glOrtho(0, (GLfloat)w / (GLfloat)h * 1.0, 0.0, 1.0, 0.0, 1.0);
};