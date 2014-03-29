//
//  Components.cpp
//  Assignment1
//
//  Created by Heng Wang on 12-02-04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _Windows_
#include <GL/glut.h>
#else 
#include <GLUT/glut.h>
#endif

#include "Cannon.h"
#include "imageloader.h"

////Makes the image into a texture, and returns the id of the texture
GLuint loadCannonTexture(Image* image) 
{	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE,image->pixels);
	return textureId;
}

Image *metal;
Image *wheel;
Image *gunpeel;
Image *wood;
Image *gun_rust;
Image *smoke;
GLuint _metal;
GLuint _wheel;
GLuint _gunpeel;
GLuint _wood; 
GLuint _gun_rust;
GLuint _smoke;
void Cannon::textureInit()
{
    metal = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/metal.bmp");
    wheel = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/wheel.bmp");
    gunpeel = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/gun.bmp");
    wood = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/box.bmp");
    gun_rust = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/gun_rust.bmp");
    smoke   = loadBMP("/Users/kevinwang264/Documents/Course Materials/COMP6761/COMP6761_Final_Project_6238475/Mac_version/Crazy_Cannon/Crazy_Cannon/Resources/Textures/smoke.bmp");
    
    _metal = loadCannonTexture(metal);
    _wheel = loadCannonTexture(wheel);
    _gunpeel = loadCannonTexture(gunpeel);
    _wood = loadCannonTexture(wood);
    _gun_rust = loadCannonTexture(gun_rust);
    _smoke = loadCannonTexture(smoke);
    
    delete metal;
    delete wheel;
    delete gunpeel;
    delete wood;
    delete gun_rust;
    delete smoke;
}

PARTICLES Particle[ParticleCount];

void Cannon::glCreateParticles (void)
{
    
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		Particle[i].Xpos = 0;
		Particle[i].Ypos = 0;
		Particle[i].Zpos = 0;
		Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%5) + 1) - 1 + 1) * rand()%5) + 1) * 0.003) - (((((((2 - 1 + 1) * rand()%5) + 1) - 1 + 1) * rand()%5) + 1) * 0.003);
		Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%5) + 1) - 1 + 1) * rand()%5) + 1) * 0.003) - (((((((2 - 1 + 1) * rand()%5) + 1) - 1 + 1) * rand()%5) + 1) * 0.003);
		Particle[i].Red = 1;
		Particle[i].Green = 0;
		Particle[i].Blue = 0;
		Particle[i].Scalez =1.5;
		Particle[i].Direction = 0;
		Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%5) ) - 1 + 1) * rand()%5) + 1) * 0.02;
		Particle[i].Deceleration = 0.03;
	}
    
}

void glDrawParticles (void)
{
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, _smoke);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		glPushMatrix();
		glTranslatef(Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
		glRotatef(Particle[i].Direction - 90, 0, 0, 1);
        
		glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);
        
		glDisable (GL_DEPTH_TEST);
		
        //glutSolidSphere(0.15, 10, 10);
        glBegin (GL_QUADS);
		glTexCoord2f(0, 0);glVertex3f (-0.01, -0.01, 0);
		glTexCoord2f(1, 0);glVertex3f (0.01, -0.01, 0);
		glTexCoord2f(1, 1);glVertex3f (0.01, 0.01, 0);
		glTexCoord2f(0, 1);glVertex3f (-0.01, 0.01, 0);
		glEnd();
        
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	}
    glDisable(GL_TEXTURE_2D);
}

void Cannon::glUpdateParticles (void)
{
    glDisable(GL_LIGHTING);
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		glColor3f (Particle[i].Red, Particle[i].Green, Particle[i].Blue);
		Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
		Particle[i].Deceleration = Particle[i].Deceleration + 0.0025;
		Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
		Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;
		Particle[i].Direction = Particle[i].Direction + (((((int)0.5 * rand()%5) + 1) * rand()%5) + 1);
        
		if (Particle[i].Ypos < 0)
		{
			Particle[i].Xpos = 0;
			Particle[i].Ypos = 0;
			Particle[i].Zpos = 0;
			Particle[i].Red = 1;
			Particle[i].Green = 0;
			Particle[i].Blue = 0;
			Particle[i].Direction = 0;
			Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%5)) - 1 + 1) * rand()%5) + 1) * 0.02;
			Particle[i].Deceleration = 0.03;
		}
	}
    glEnable(GL_LIGHTING);
}

GLUquadricObj *qobj=gluNewQuadric();
//Draw spoke
void spoke()
{
        glPushMatrix();
            glTranslatef(0.87, 0.0, 0.0);
            glScalef(1.04, 0.1, 0.2);
            glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
            glRotatef(30, 0, 0, 1);
            glTranslatef(0.87, 0.0, 0.0);
            glScalef(1.04, 0.1, 0.2);
            glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
            glRotatef(60, 0, 0, 1);
            glTranslatef(0.87, 0.0, 0.0);
            glScalef(1.04, 0.1, 0.2);
            glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            glTranslatef(0.87, 0.0, 0.0);
            glScalef(1.04, 0.1, 0.2);
            glutSolidCube(1);
        glPopMatrix();
    
}

//Draw hub
void hub()
{
    glPushMatrix();
        glutSolidTorus(0.05, 0.3, 100, 100); //hub
        glutSolidTorus(0.07, 0.18, 100, 100); //hub
        glutSolidTorus(0.05, 0.3, 100, 100); //hub
        glutSolidTorus(0.07, 0.18, 100, 100); //hub
    glPopMatrix();
    
    //More details
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.15);
        gluCylinder(qobj, 0.2, 0.2, 0.3, 10, 5);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.15);
        gluCylinder(qobj, 0.2, 0.15, 0.2, 10, 5);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.15);
        glRotatef(180, 1.0, 0.0, 0.0);
        gluCylinder(qobj, 0.2, 0.15, 0.2, 10, 5);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.35);
        gluDisk(qobj,0.0, 0.15, 10, 1);
    glPopMatrix();
}

//Draw a single wheel
void singleWheel()
{    
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, _metal);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.1);
        qobj = gluNewQuadric();
        gluCylinder(qobj, 1.6, 1.6, 0.2, 50, 50);
    glPopMatrix();
     
    // glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _wheel);
    
    /*A basic single wheel is composed with two cylinders and two disks.
     Then add the strokes in it.
     */    
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.1);
        gluCylinder(qobj, 1.4, 1.4, 0.2, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.1);
        gluDisk(qobj,1.4, 1.6, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.1);
        gluDisk(qobj,1.4, 1.6, 50, 530);
    glPopMatrix();        

    //spokes
    glPushMatrix();
        spoke();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(90, 0, 0, 1);
        spoke();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(180, 0, 0, 1);
        spoke();
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(270, 0, 0, 1);
        spoke();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//Draw iron_axle
void iron_axle()
{
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _gunpeel);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glPushMatrix();
    {
        //iron_axle tree
        glPushMatrix();
            //GLUquadricObj *qobj;
            //qobj = gluNewQuadric();
            gluCylinder(qobj, 0.15, 0.15, 4.0, 15, 15);
        glPopMatrix();
        
        glPushMatrix();
            glRotatef(180, 1.0, 0.0, 0.0);
            hub();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, 4.0);
            hub();
        glPopMatrix();
        
    }
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

//Draw Ammunition Box
void ammuniBox()
{
   glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _wood);
        // The ammunition Box is composed with for solid cude. Scale them and translate them to the right place.
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.4); //left
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, -0.4); //right
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.4, 0.0); //up
            glRotatef(90, 1.0, 0.0, 0.0);
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, -0.4, 0.0); //down
            glRotatef(90, 1.0, 0.0, 0.0);
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.4, 0.0, 0.0);    //front
            glRotatef(90, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(-0.4, 0.0, 0.0);  //back
            glRotatef(90, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.1);
            glutSolidCube(0.8);
        glPopMatrix();

            
    glBindTexture(GL_TEXTURE_2D, _gunpeel);
        
        glPushMatrix();
            glTranslatef(0.0, 0.48, 0.0);  //pull button
            glutSolidSphere(0.1, 10, 10);
        glPopMatrix();

    glDisable(GL_TEXTURE_2D);
   
}

//Draw LargeWheel
void LargeWheel()
{
    //This is the wheel which will hold the Cannon, it is composed with two single wheels and the iron axle.
        glPushMatrix();
            glTranslatef(0.0, 0.0, 2.0);
            singleWheel();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, -2.0);
            iron_axle();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, -2.0);
            singleWheel();
        glPopMatrix();

}

//Draw SmallWheel
void SmallWheel()
{
    //This is the small wheel. It just scale the large wheel and translate it to a proper position.
    glTranslatef(5.4, -0.6, 0.0);  
    glScalef(0.6, 0.6, 0.6);
    LargeWheel();
}
        
void Carriage()
{
    //It carrys a big ammuni box and the base so that horses could pull the Cannon.
    glPushMatrix();
    {
        glTranslatef(5.4, -0.1, 0.0);
        
        glPushMatrix();
            glTranslatef(0.2, 0.2, 0.0);
            glScalef(1.2, 1.0, 2.3);
            ammuniBox();
        glPopMatrix();
        
        glEnable(GL_TEXTURE_2D);
 
        glBindTexture(GL_TEXTURE_2D, _gunpeel);
        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        glPushMatrix();
            glTranslatef(-0.8, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            gluCylinder(qobj, 0.07, 0.07, 0.3, 10, 10);
        glPopMatrix();
        
        glPushMatrix();        
            glTranslatef(-0.8, 0.0, 0.0);
            glRotatef(90, 0.0, 0.0, 0.0);
            glutSolidSphere(0.07, 10, 10);
        glPopMatrix();
        
        
        
    glBindTexture(GL_TEXTURE_2D, _wood);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        /*ammunition carriage with base*/
        //straight
        
        glPushMatrix();
            glTranslatef(1.0, -0.3, 0.5);
            glScalef(1.5, 0.15, 0.2);
            glutSolidCube(1); 
        glPopMatrix();
        
        //straight
        glPushMatrix();
            glTranslatef(1.0, -0.3, -0.5);
            glScalef(1.5, 0.15, 0.2);
            glutSolidCube(1); 
        glPopMatrix();
        
        //down long
        glPushMatrix();
            glTranslatef(1.5, -0.42, 0.0);
            glScalef(0.2, 0.1, 2.8);
            glutSolidCube(1); 
        glPopMatrix();
        
        //up long
        glPushMatrix();
            glTranslatef(1.5, -0.17, 0.0);
            glScalef(0.2, 0.1, 2.8);
            glutSolidCube(1); 
        glPopMatrix();
        
        //up short
        glPushMatrix();
            glTranslatef(1.0, -0.17, 0.0);
            glScalef(0.2, 0.1, 2.0);
            glutSolidCube(1); 
        glPopMatrix();
        
        //hook.   The eye ring could pull the small wheel.
        glPushMatrix();
            glTranslatef(-0.6, -0.3, 0.0);
            glScalef(0.8, 0.15, 0.4);
            glutSolidCube(1); 
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, -0.3, 0.0);
            glScalef(0.5, 0.4, 2.0);
            glutSolidCube(1);       //bottom, connected with the iron axle
        glPopMatrix();
        
    }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//Draw trail
void trail()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _wheel);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    //The trail is consisted of the main trail, left and right side, ammuni box, trail eye and handle.
    glPushMatrix();
    {
        glRotatef(-8, 0.0, 0.0, 1.0);
        
        glPushMatrix();
        glTranslatef(2.0, 0.6, 0.0);
        glScalef(4.8, 0.3, 1.0);
        glutSolidCube(1);       //main trail
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.4, 0.8, 0.6);
        glScalef(2, 1.0, 0.2);
        glutSolidCube(1);       //right
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.4, 0.8, -0.6);
        glScalef(2, 1.0, 0.2);
        glutSolidCube(1);       //left
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.0, 0.1, 0.0);
        glScalef(0.5, 0.4, 3.3);
        glutSolidCube(1);       //bottom, connected with the iron axle
        glPopMatrix();
        
        glBindTexture(GL_TEXTURE_2D, _gunpeel);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        glPushMatrix();
        glTranslatef(4.55, 0.5, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidTorus(0.06, 0.15, 20, 20); //Trail Eye
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(3.5, 0.8, 0.3);
        glutSolidTorus(0.05, 0.3, 20, 20);  //Trail Handle
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(3.5, 0.8, -0.3);
        glutSolidTorus(0.05, 0.3, 20, 20);  //Trail Handle
        glPopMatrix();
        
    }
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    //Ammunition Box 
    glPushMatrix();
    glTranslatef(0.0, 0.7, 1.2);
    ammuniBox();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.7, -1.2);
    ammuniBox();
    glPopMatrix();
    
    
    
}

//Draw elevating screw
void Cannon::elevatingscrew()
{
    glPushMatrix();
    {
        glTranslatef(2.0, 1.1, 0.0);
        glRotatef(beta*40, 0, 1, 0);
        
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, _gunpeel);
     
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //The elevating screw is consisted of one cylinder and for solid spheres
            glPushMatrix();
                glRotatef(90, 1.0, 0.0, 0.0);
                gluCylinder(qobj, 0.08, 0.08, 0.8, 10, 10);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(0.0, -0.5, 0.18);
                glScalef(0.4, 0.2, 1.0);    
                glutSolidSphere(0.15, 10, 10);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(0.0, -0.5, -0.18);
                glScalef(0.4, 0.2, 1.0);    
                glutSolidSphere(0.15, 10, 10);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(0.2, -0.5, 0.0);
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(0.4, 0.2, 1.0);    
                glutSolidSphere(0.15, 10, 10);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(-0.2, -0.5, 0.0);
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(0.4, 0.2, 1.0);    
                glutSolidSphere(0.15, 10, 10);
            glPopMatrix();
        
        glDisable(GL_TEXTURE_2D);
    
    }
    glPopMatrix();
    
}

//Draw Gun
void Cannon::gun()
{
    
    // The body of the Cannon
    glPushMatrix();
    {
    glRotatef(beta, 0, 0, 1);
    
        glTranslatef(2.0, 1.3, 0.0);    
        glRotatef(-90, 0.0, 1.0, 0.0);
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, 5.0);
            glDrawParticles();
        glPopMatrix();
              
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _gunpeel);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            
        glPushMatrix();
            gluCylinder(qobj, 0.4, 0.25, 5.0, 20, 20);
            gluCylinder(qobj, 0.28, 0.18, 5.0, 20, 20);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, 5.0);
            glutSolidTorus(0.08, 0.2, 20, 20); // top
        glPopMatrix();
        
        // draw Cascable
        glutSolidSphere(0.4, 20, 20);

        //Cascable button
        glPushMatrix();
            glTranslatef(0.0, 0.0, -0.45);
            glutSolidSphere(0.15, 10, 10);
        glPopMatrix();

        //Trunnion(left)
        glPushMatrix();
            glTranslatef(0.3, 0.0, 1.8);
            glRotatef(90, 0.0, 1.0, 0.0);
            gluCylinder(qobj, 0.15, 0.15, 0.5, 20, 20);
        glPopMatrix();
            
        glPushMatrix();
            glTranslatef(0.8, 0.0, 1.8);
            glutSolidSphere(0.15, 10, 10);        
        glPopMatrix();
       
        //Trunnion(right)
        glPushMatrix();
            glTranslatef(-0.3, 0.0, 1.8);
            glRotatef(-90, 0.0, 1.0, 0.0);
            gluCylinder(qobj, 0.15, 0.15, 0.5, 20, 20);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(-0.8, 0.0, 1.8);
            glutSolidSphere(0.15, 10, 10);   
        glPopMatrix();
        
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
        
}

void Cannon::wheelRot(GLfloat rl, GLfloat rs )
{
    rlwheel = rl;
    rswheel = rs;
    
    glPushMatrix();
        glRotatef(-rlwheel,0.0,0.0,1.0);         
        LargeWheel();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(5.4, -0.6, 0.0);  
        glRotatef(-rswheel,0.0,0.0,1.0);
        glTranslatef(-5.4, 0.6, 0.0); 
        SmallWheel();
    glPopMatrix();
}

void Cannon::Gun(Aim new_aim)
{
    aim = new_aim; 
    
    switch (aim) {
        case UP:
            beta -=0.5 ;
            if (beta<=-8)
                beta=-8;
            break;
        
        case DOWN:
            if (beta<=0.1) {
                beta +=0.5;
            }
            else {
                beta=0.1;
            }
            break;
            
        default:
            beta =0;
            break;
    }
    
}

//Draw Cannon
void Cannon::Draw_Cannon()
{
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
        
    GLfloat spotlightpoz[] = {0, 0, 0, 1};
    GLfloat spotlightdirF[]={-1,0,0};
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
       
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 80.0 };    

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glPushMatrix();
        glTranslated(CannonPoz.x, CannonPoz.y, CannonPoz.z);
        glRotatef(turn, 0, 1, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, spotlightpoz);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightdirF);
        wheelRot(rlwheel, rswheel); 
        Carriage();
        trail();
        gun();
        elevatingscrew();
    glPopMatrix();
    
    gluDeleteQuadric (qobj);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void Cannon::MoveForward() 
{
    CannonPoz.x += -CannonSpeed*cos(turn*PI/180);
    CannonPoz.z += CannonSpeed*sin(turn*PI/180);
    rlwheel -=LARGE_WHEEL_SPEED;
    rswheel -=SMALL_WHEEL_SPEED;
    wheelRot(rlwheel, rswheel);
}
void Cannon::MoveBackward() 
{        
    CannonPoz.x -= -CannonSpeed*cos(turn*PI/180);
    CannonPoz.z -= CannonSpeed*sin(turn*PI/180);
    rlwheel +=LARGE_WHEEL_SPEED;
    rswheel +=SMALL_WHEEL_SPEED;
    wheelRot(rlwheel, rswheel);
}
void Cannon::TurnRight() 
{
    turn -= TURN_ANGLE;
}
void Cannon::TurnLeft() 
{
    turn += TURN_ANGLE;
}





//void Bullet::loadBullet()
//{
//    vector<Bullet *> allBullets;
//    
//    for(int i = 0; i < 10; i++)
    
        //allBullets.push_back( new Bullet() );
    
    
    
//    bool ifempty = allBullets.empty();
//    
//    int curr_bullet = 0;
//    
//    curr_bullet++;
//    
//    allBullets[curr_bullet];



