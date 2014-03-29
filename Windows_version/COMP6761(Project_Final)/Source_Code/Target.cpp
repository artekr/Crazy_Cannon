//
//  Target.cpp
//  Project(0)
//
//  Created by Heng Wang on 12-04-12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Target.h"
#include "imageloader.h"
#include "fmod.h"
#include "fmod_errors.h"

#ifdef WIN32
	#include <windows.h>
	// automatically link to fmod library
	#pragma comment(lib,"Resources\\Library\\Sound(Lib)\\lib\\fmod.lib")
#else
	#include "wincompat.h"
#endif
FSOUND_STREAM* hitTarget = NULL;

////Makes the image into a texture, and returns the id of the texture
GLuint loadTargetTexture(Image* image) 
{	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}
Image *targetTex;
GLuint _targetTex;


Target::Target()
{
    srand(time(NULL)); 
    targetPoz1.x = rand()%180-90;
    targetPoz1.z = rand()%180-90;
    
    targetPoz2.x = rand()%180-90;
    targetPoz2.z = rand()%180-90;
    
    targetPoz3.x = rand()%180-90;
    targetPoz3.z = rand()%180-90;
    
    targetPoz4.x = rand()%180-90;
    targetPoz4.z = rand()%180-90;
    
    targetPoz5.x = rand()%180-90;
    targetPoz5.z = rand()%180-90;
    
    targetPoz6.x = rand()%180-90;
    targetPoz6.z = rand()%180-90;

   	flag1 =0;
    flag2 =0;
    flag3 =0;
    flag4 =0;
    flag5 =0;
    flag6 =0;
}

void Target::init()
{
    targetTex = loadBMP("Resources\\Textures\\target.bmp");
    _targetTex = loadTargetTexture(targetTex);
    delete targetTex;
}

void Target::Draw_Target()
{
    targetList=glGenLists(4);
    glNewList(targetList, GL_COMPILE);
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
    glEndList();
    
}


int Target::collision(VECTOR aBulletPoz)
{
    BulletPoz = aBulletPoz;
    
    d1 = sqrt(((BulletPoz.x - targetPoz1.x) * (BulletPoz.x - targetPoz1.x)) + ((BulletPoz.y - targetPoz1.y) * (BulletPoz.y - targetPoz1.y)) + ((BulletPoz.z - targetPoz1.z) * (BulletPoz.z - targetPoz1.z)));
    
    d2 = sqrt(((BulletPoz.x - targetPoz2.x) * (BulletPoz.x - targetPoz2.x)) + ((BulletPoz.y - targetPoz2.y) * (BulletPoz.y - targetPoz2.y)) + ((BulletPoz.z - targetPoz2.z) * (BulletPoz.z - targetPoz2.z)));
    
    d3 = sqrt(((BulletPoz.x - targetPoz3.x) * (BulletPoz.x - targetPoz3.x)) + ((BulletPoz.y - targetPoz3.y) * (BulletPoz.y - targetPoz3.y)) + ((BulletPoz.z - targetPoz3.z) * (BulletPoz.z - targetPoz3.z)));
    
    d4 = sqrt(((BulletPoz.x - targetPoz4.x) * (BulletPoz.x - targetPoz4.x)) + ((BulletPoz.y - targetPoz4.y) * (BulletPoz.y - targetPoz4.y)) + ((BulletPoz.z - targetPoz4.z) * (BulletPoz.z - targetPoz4.z)));
    
    d5 = sqrt(((BulletPoz.x - targetPoz5.x) * (BulletPoz.x - targetPoz5.x)) + ((BulletPoz.y - targetPoz5.y) * (BulletPoz.y - targetPoz5.y)) + ((BulletPoz.z - targetPoz5.z) * (BulletPoz.z - targetPoz5.z)));
    
    d6 = sqrt(((BulletPoz.x - targetPoz6.x) * (BulletPoz.x - targetPoz6.x)) + ((BulletPoz.y - targetPoz6.y) * (BulletPoz.y - targetPoz6.y)) + ((BulletPoz.z - targetPoz6.z) * (BulletPoz.z - targetPoz6.z)));

    if (d1<=TARGET_RADIUS+BULLET_RADIUS)
        return 1;
	if (d2<=TARGET_RADIUS+BULLET_RADIUS)
        return 2;
	if (d3<=TARGET_RADIUS+BULLET_RADIUS)
        return 3;
	if (d4<=TARGET_RADIUS+BULLET_RADIUS)
        return 4;
	if (d5<=TARGET_RADIUS+BULLET_RADIUS)
        return 5;
	if (d6<=TARGET_RADIUS+BULLET_RADIUS)
        return 6;
}


Status Target::Response()
{    
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _targetTex);
    
    //camera spot light
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat uplightpoz[] = {0, 20, 0, 1};
    GLfloat uplightdir[]={0, -1, 0};
    
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50);
    
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 50);
    
    glLightfv(GL_LIGHT4, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 50);
    
    glLightfv(GL_LIGHT5, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 50);
    
    glLightfv(GL_LIGHT6, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 50);
    
    glLightfv(GL_LIGHT7, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, uplightdir);
    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 60);
    glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 50);
    

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glPushMatrix();
    glTranslatef(targetPoz1.x, 0, targetPoz1.z);
    glLightfv(GL_LIGHT2, GL_POSITION,uplightpoz);
    if (flag1 == 1)
    {
        glDisable(GL_LIGHT2);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
	else if (collision(BulletPoz)==1) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag1 = 1;
    }
    glCallList(targetList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(targetPoz2.x, 0, targetPoz2.z);
    glLightfv(GL_LIGHT3, GL_POSITION,uplightpoz);
    if (flag2 == 1)
    {
        glDisable(GL_LIGHT3);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
    else if (collision(BulletPoz)==2) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag2 = 1;
    }
    glCallList(targetList);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(targetPoz3.x, 0, targetPoz3.z);
    glLightfv(GL_LIGHT4, GL_POSITION,uplightpoz);
    if (flag3 == 1)
    {
        glDisable(GL_LIGHT4);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
    else if (collision(BulletPoz)==3) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag3 = 1;
    }
    glCallList(targetList);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(targetPoz4.x, 0, targetPoz4.z);
    glLightfv(GL_LIGHT5, GL_POSITION,uplightpoz);
    if (flag4 == 1)
    {
        glDisable(GL_LIGHT5);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
    else if (collision(BulletPoz)==4) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag4 = 1;
    }
    glCallList(targetList);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(targetPoz5.x, 0, targetPoz5.z);
    glLightfv(GL_LIGHT6, GL_POSITION,uplightpoz);
    if (flag5 == 1)
    {
        glDisable(GL_LIGHT6);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
    else if (collision(BulletPoz)==5) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag5 = 1;
    }
    glCallList(targetList);    
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(targetPoz6.x, 0, targetPoz6.z);
    glLightfv(GL_LIGHT7, GL_POSITION,uplightpoz);
    if (flag6 == 1)
    {
        glDisable(GL_LIGHT7);
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
    }
    else if (collision(BulletPoz)==6) 
    {
        glTranslatef(0, -1.6, 0);
        glRotatef(90, 1, 0, 0);
		//if hit the target, play clap sound
		hitTarget = FSOUND_Stream_Open( "Resources\\Sound\\hitTarget.wav" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0,hitTarget);
        flag6 = 1;
    }
    glCallList(targetList);    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);

	if (flag1==1&&flag2==1&&flag3==1&&flag4==1&&flag5==1&&flag6==1)
	{
		return WIN;
	}
    
}


