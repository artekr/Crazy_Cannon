//
//  Vector.h
//  Project(0)
//
//  Created by Heng Wang on 12-04-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _Windows_
#include <GL/glut.h>
#else 
#include <GLUT/glut.h>
#endif

#ifndef Project_0__Vector_h
#define Project_0__Vector_h

typedef struct 
{   
    GLfloat x;
    GLfloat y;
    GLfloat z;
}VECTOR;

#endif
