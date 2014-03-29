//
//  Target.h
//  Project(0)
//
//  Created by Heng Wang on 12-04-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Project_0__Target_h
#define Project_0__Target_h

#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <time.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else 
#include <gl/glut.h>
#endif

#include "Bullet.h"

#define TARGET_RADIUS 3

enum Status {WIN=1,LOSE};

class Target
{
public:
    Target();
    void Draw_Target();
    int collision(VECTOR);
	Status Response();
    void init();
  
	Status gamestatus;
    int p1radius;
    int p2radius;
    int flag1;
    int flag2;
    int flag3;
    int flag4;
    int flag5;
    int flag6;

private:
    GLuint targetList;
    VECTOR BulletPoz;
    
    VECTOR targetPoz1;
    VECTOR targetPoz2;
    VECTOR targetPoz3;
    VECTOR targetPoz4;
    VECTOR targetPoz5;
    VECTOR targetPoz6;
    
    GLfloat d1; //distance between two objects
    GLfloat d2; //distance between two objects
    GLfloat d3; //distance between two objects
    GLfloat d4; //distance between two objects
    GLfloat d5; //distance between two objects
    GLfloat d6; //distance between two objects

};

#endif
