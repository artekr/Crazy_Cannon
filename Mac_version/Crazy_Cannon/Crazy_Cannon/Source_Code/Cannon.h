//
//  Cannon.h
//  Assignment1
//
//  Created by Heng Wang on 12-02-18.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifdef _Windows_
#include <GL/glut.h>
#else 
#include <GLUT/glut.h>
#endif

#ifndef CANNON_H
#define CANNON_H

#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <time.h>

#include "Vector.h"
#define PI 3.14159265
#define CANNON_SPEED 0.5
#define TURN_ANGLE 5
#define LARGE_WHEEL_SPEED 12
#define SMALL_WHEEL_SPEED 14

using namespace std;

//GLfloat beta1;
enum Aim {KEEP, UP, DOWN};

/*****Create a Cannon class*******************************/
class Cannon 
{

public:
    VECTOR CannonPoz;  //position of cannon
    //Bullet bullet;
    GLfloat CannonSpeed;
    GLfloat turn;
    GLfloat beta;
    Cannon() {
        turn = 0;
        CannonSpeed = CANNON_SPEED;
    }
    void gun();
    void elevatingscrew();
    void Draw_Cannon();
    void Gun(Aim);
    void wheelRot(GLfloat, GLfloat);
    void textureInit();
    void glCreateParticles();
    void glUpdateParticles();
    void MoveForward(); 
    void MoveBackward();
    void TurnRight();
    void TurnLeft();    
    
private:
    GLfloat rlwheel;
    GLfloat rswheel;
   
    Aim aim;
};




const int ParticleCount = 100;

typedef struct
{
	double Xpos;
	double Ypos;
	double Zpos;
	double Xmov;
	double Zmov;
	double Red;
	double Green;
	double Blue;
	double Direction;
	double Acceleration;
	double Deceleration;
	double Scalez;
	bool Visible;
}PARTICLES;



#endif
