//
//  Map.cpp
//  Project(0)
//
//  Created by Heng Wang on 12-04-08.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <math.h>

#include "Map.h"
#include "imageloader.h"

////Makes the image into a texture, and returns the id of the texture
GLuint loadMapTexture(Image* image) 
{	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

Image *groundland;
Image *skymap;
Image *nightSkymap;
Image *brickwallmap;
Image *winnermap;

GLuint _groundland;
GLuint _skymap;
GLuint _nightSkymap;
GLuint _brickwallmap;
GLuint _winnermap;


void drawGround() 
{
    for (float i=0.0; i<200; i++) 
    {                    
        for (float j=0.0; j<200; j++)
        {
            glColor3f(0.1, 0.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(j-100, -1.6, i-100);
            glTexCoord2f(0, 0); glVertex3f(j-100, -1.6, i-99);
            glTexCoord2f(1, 0); glVertex3f(j-99, -1.6, i-99);
            glTexCoord2f(1, 1); glVertex3f(j-99, -1.6, i-100);
            glEnd();
        }
    }
}

void drawHemisphere(double r, int lats, int longs) 
{
    int i, j;
    int halfLats = lats / 2; 
    for(i = 0; i <= halfLats; i++) 
    {
        double lat0 = PI * (-1 + (double) (i - 1) / lats);
        double z0 = 80*sin(lat0);
        double zr0 = 80*cos(lat0);
        
        double lat1 = PI * (-1 + (double) i / lats);
        double z1 = 80*sin(lat1);
        double zr1 =80*cos(lat1);
        
        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * PI * (double) (j - 1) / longs;
            double x = 2*cos(lng);
            double y = 2*sin(lng);
            
            double s1, s2, t;
            s1 = ((double) i) / halfLats;
            s2 = ((double) i + 1) / halfLats;
            t = ((double) j) / longs;
            
            glTexCoord2d(s1, t);
            glNormal3d(x * zr0, y * zr0, z0);
            glVertex3d(x * zr0, y * zr0, z0);
            
            glTexCoord2d(s2, t);
            glNormal3d(x * zr1, y * zr1, z1);
            glVertex3d(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
    
}

void drawWall()
{
    //front
    glPushMatrix();
        glNormal3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-100, -1.6, 100);
        glTexCoord2f(1, 0); glVertex3f(-100, -1.6, -100);
        glTexCoord2f(1, 1); glVertex3f(-100, 20, -100);
        glTexCoord2f(0, 1); glVertex3f(-100, 20, 100);
        glEnd();
    glPopMatrix();
    
    //back
    glPushMatrix();
        glNormal3f(-1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(100, -1.6, 100);
        glTexCoord2f(1, 0); glVertex3f(100, -1.6, -100);
        glTexCoord2f(1, 1); glVertex3f(100, 20, -100);
        glTexCoord2f(0, 1); glVertex3f(100, 20, 100);
        glEnd();
    glPopMatrix();    
    //left
    glPushMatrix();
        glNormal3f(0.0, 0.0, -1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-100, -1.6, 100);
        glTexCoord2f(1, 0); glVertex3f(100, -1.6, 100);
        glTexCoord2f(1, 1); glVertex3f(100, 20, 100);
        glTexCoord2f(0, 1); glVertex3f(-100, 20, 100);
        glEnd();
    glPopMatrix();
    //right
    glPushMatrix();
        glNormal3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-100, -1.6, -100);
        glTexCoord2f(1, 0); glVertex3f(100, -1.6, -100);
        glTexCoord2f(1, 1); glVertex3f(100, 20, -100);
        glTexCoord2f(0, 1); glVertex3f(-100, 20, -100);
        glEnd();
    glPopMatrix();
}

void drawTarget()
{
   glPushMatrix();
    
    glPushMatrix();
        glTranslatef(-1.5, 2, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(3, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(3, 3, 0);
        glTexCoord2f(0, 1); glVertex3f(0, 3, 0);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glScalef(0.5, 4.0, 0.2);
        glutSolidCube(1);
    glPopMatrix();
    
    glPopMatrix();
    
}

void drawWinBoard()
{
	   glPushMatrix();
	    glTranslatef(0, -2, 0);
        glNormal3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-10, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(10, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(10, 0, -10);
        glTexCoord2f(0, 1); glVertex3f(-10, 0, -10);
        glEnd();
    glPopMatrix();
}

Map::Map()
{    
    skyChange = false;
}

void Map::init()
{
    groundland = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/ground.bmp");
    skymap = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/sky.bmp");
    nightSkymap = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/nightSky.bmp");
    brickwallmap = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/brickwall.bmp");
	winnermap = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/winner.bmp");
    
    _groundland = loadMapTexture(groundland);
    _skymap = loadMapTexture(skymap);
    _nightSkymap = loadMapTexture(nightSkymap);
    _brickwallmap = loadMapTexture(brickwallmap);
	_winnermap = loadMapTexture(winnermap);
    
    delete groundland;
    delete skymap;
    delete nightSkymap;
    delete brickwallmap;
	delete winnermap;
    
    groundList=glGenLists(1);
    glNewList(groundList, GL_COMPILE);
    {
        drawGround();
    }
    glEndList();
    
    skyList=glGenLists(2);
    glNewList(skyList, GL_COMPILE);
    {
        drawHemisphere(1,40,40);    
    }
    glEndList();
    
    wallList=glGenLists(3);
    glNewList(wallList, GL_COMPILE);
    {
        drawWall();    
    }
    glEndList();

	winBoardList=glGenLists(4);
    glNewList(winBoardList, GL_COMPILE);
    {
		drawWinBoard();    
    }
    glEndList();
        
}

void Map::ground()
{
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _groundland);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glCallList(groundList);
    
    glDisable(GL_TEXTURE_2D);
        
}

void Map::sky()
{    
    glEnable(GL_TEXTURE_2D);
    if (skyChange==false) {
        glBindTexture(GL_TEXTURE_2D, _skymap);
    }
	else {
        glBindTexture(GL_TEXTURE_2D, _nightSkymap);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glCallList(skyList);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
}

void Map::wall()
{
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _brickwallmap);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glCallList(wallList);
    
    glDisable(GL_TEXTURE_2D);
}


void Map::win()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _winnermap);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
	glCallList(winBoardList);
    
    glDisable(GL_TEXTURE_2D);
}