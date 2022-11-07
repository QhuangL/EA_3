//
//  ground.hpp
//  try_glut
//
//  Created by Qianhuang Li on 11/1/22.
//

#ifndef ground_hpp
#define ground_hpp

#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#pragma once
 
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif

#include <GLFW/glfw3.h>
 
class Ground {
public:
    static void Draw();
};


#endif /* ground_hpp */
