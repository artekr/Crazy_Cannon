//
//  Map.h
//  Project(0)
//
//  Created by Heng Wang on 12-04-08.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Project_0__Map_h
#define Project_0__Map_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <windows.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else 
#include <gl/glut.h>
#endif

#define PI 3.14159265



class Map {
    
public:
    bool skyChange; 
    Map();
    void init();
    void ground();
    void sky();
    void wall();
	void win();

private:
    GLuint textureId;
    GLuint groundList;
    GLuint skyList;
    GLuint wallList;
	GLuint winBoardList;
};


#endif

