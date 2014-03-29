//
//  Bullet.h
//  Project(0)
//
//  Created by Heng Wang on 12-04-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Project_0__Bullet_h
#define Project_0__Bullet_h

#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Vector.h"

#ifdef _APPLE_
#include <GLUT/glut.h>
#else 
#include <gl/glut.h>
#endif

#define PI 3.14159265
#define SPEED 10
#define BULLET_RADIUS 0.25

using namespace std;

/*****Create a Bullet class*******************************/
class Bullet
{
public:
    VECTOR BulletPoz;
    Bullet(VECTOR,GLfloat,GLfloat);
    void Draw_Bullet();
    void shoot();

private:
    GLfloat upAngle;
    GLfloat rotAngle;
    GLfloat speed;
};



#endif
