//
//  Vector.h
//  Project(0)
//
//  Created by Heng Wang on 12-04-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Project_0__Vector_h
#define Project_0__Vector_h

#ifdef _APPLE_
#include <GLUT/glut.h>
#else 
#include <gl/glut.h>
#endif

typedef struct 
{   
    GLfloat x;
    GLfloat y;
    GLfloat z;
}VECTOR;

#endif
