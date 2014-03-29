//
//  Variables.h
//  Assignment1
//
//  Created by Heng Wang on 12-02-19.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _Windows_
#include <GL/glut.h>
#else 
#include <GLUT/glut.h>
#endif

#ifndef VARIANLES_H
#define VARIANLES_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <time.h>


#define WIDTH  800
#define HEIGHT 600

#define ON 1
#define OFF 0
#define PI 3.14159265

int width =WIDTH;              //window width
int height=HEIGHT;              //window height

GLfloat lookX = 0.0f;		// Look-at Point
GLfloat lookY = 0.0f;		// Look-at Point
GLfloat lookZ = -1.0f;		// Look-at Point

GLfloat cameraX = 0.0f;	// Rotate screen on x axis 
GLfloat cameraY = 0.0f;	// Rotate screen on y axis
GLfloat cameraZ = 0.0f;	// Rotate screen on z axis

GLfloat xpoz = 0.0f;      //x position.
GLfloat ypoz = 0.0f;      //y position.
GLfloat zpoz = 0.0f;      //z position.


GLfloat ylwheel = 0.0f;      //y position.
GLfloat yswheel = 0.0f;      //y position.
GLfloat rl = 0.0f;      //z position.
GLfloat rs = 0.0f;      //z position.

static float eyex = 0.0f;   // Camera x
static float eyey = 10.0f;   // Camera y
static float eyez = 35.0f;   // Camera z

static float angle = 50.0f; //Perspective angle

int WireFrame = 1;			// Flag for wire frame mode

enum {
    PERSPECTIVE,  ORTHO, FIRST, THIRD
} mode = PERSPECTIVE;       //swicth between different view

// Ligting data
GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0};
GLfloat diffuse[] = {0.4, 0.4, 0.5, 1.0};  /* Red diffuse light. */
GLfloat diractionpoz[] = {0.0, 3.0, 0.0, 0.0};
//cannon spot light
//GLfloat spotlightpoz[] = {0, 0, 0, 1};
//GLfloat spotlightdirF[]={1,0,0};
GLfloat spotlightdirN[]={1,-0.5,0}; 

GLfloat targetRot=0; //rotate the target


bool camera = ON;
bool light0 = ON, light1 = ON, spotlight = OFF; //control the light
bool fog = OFF;
bool spotlightChange = OFF;

GLuint _textureId; //define texture ID

#endif
