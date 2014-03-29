//
//  Bullet.cpp
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

#include "Bullet.h"
#include "imageloader.h"

GLuint loadBulletTexture(Image* image) 
{	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

Image *bulletTex;
GLuint _bulletTex;

Bullet::Bullet(VECTOR aBulletPoz,GLfloat arotAngle,GLfloat aupAngle)
{
    bulletTex = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/gun.bmp");
    _bulletTex = loadBulletTexture(bulletTex);
    delete bulletTex;
    
    speed = SPEED;
    BulletPoz = aBulletPoz;
    rotAngle = arotAngle;
    upAngle = aupAngle;
    
}

void Bullet::Draw_Bullet()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _bulletTex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glPushMatrix();
        glTranslatef(BulletPoz.x, BulletPoz.y+1.3, BulletPoz.z);
        glutSolidSphere(BULLET_RADIUS, 10, 10);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

void Bullet::shoot()
{
    BulletPoz.x +=-cos(rotAngle*PI/180)*speed;
    BulletPoz.y +=-sin(upAngle*PI/180)*speed;
    BulletPoz.z +=sin(rotAngle*PI/180)*speed;
} 
