/*
 Course: COMP 6761
 Name: Heng Wang
 ID:   6238475
 Lab:  NI
*/
/*
 This is code is developed on MAC OX system.
*/
#include "Cannon.h"
#include "Variables.h"
#include "Bullet.h"
#include "Map.h"
#include "Target.h"
#include "fmod.h"
#include "fmod_errors.h"

#ifdef WIN32
	#include <windows.h>
	// automatically link to fmod library
	#pragma comment(lib,"Resources\\\Library\\Sound(Lib)\\lib\\fmod.lib")
#else
	#include "wincompat.h"
#endif

Cannon cannon1;
vector<Bullet> allBullets;
Map map; 
Target target;
/// this is a pointer to the mp3 stream we will be reading from the disk.
FSOUND_STREAM* sound = NULL;

void init(void)
{
    /*Set the light, just help to modify the cannon model.
     */
    glClearColor(1, 1, 1, 0.0); 
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_QUAD_STRIP);
    glEnable(GL_LIGHTING);
    
    // Enable material properties for lighting
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    //glEnable(GL_BLEND); //Enable alpha blending
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

    //directional light
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT1, GL_POSITION, diractionpoz);
   
	map.init();
	target.init();
	cannon1.textureInit();
    //cannon1.glCreateParticles();

	// initialise fmod, 44000 Hz, 64 channels
	if( FSOUND_Init(44000,64,0) == FALSE )
	cerr << "[ERROR] Could not initialise fmod\n";
}

void text(char* string)
{
    char* p;
    for (p = string; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
}


void display(void)
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
    
    //light control
    if(light0 == OFF) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
    if(light1 == ON) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
    if(spotlight == ON) {
        glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glEnable(GL_LIGHT4);glEnable(GL_LIGHT5);glEnable(GL_LIGHT6);
        glEnable(GL_LIGHT7);}
    else {
        glDisable(GL_LIGHT2);glDisable(GL_LIGHT3);glDisable(GL_LIGHT4);glDisable(GL_LIGHT5);glDisable(GL_LIGHT6);
        glDisable(GL_LIGHT7);
    }
    if (fog == ON) glEnable(GL_FOG);
    else glDisable(GL_FOG);

    
    GLfloat fogColor[] = {0.3f, 0.3f, 0.3f, 1};		//Sets the color for the fog
	glFogfv(GL_FOG_COLOR, fogColor);				//Modes for the fog are linear, exp and exp2
	glFogi(GL_FOG_MODE, GL_LINEAR);				// Linear interpolation between start and end values
	glFogi(GL_FOG_MODE, GL_EXP);				   //  y = 1 - e-0.05x ; x is distance from camera
	glFogi(GL_FOG_MODE, GL_EXP2);					// y = 1 - e-(0.05x)^2 ; x is distance from camera
	glFogf(GL_FOG_DENSITY, 0.013f);
    
    
    //camera control
    if (camera == true)
    {
        gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(cameraX, 1, 0, 0);
        glRotatef(cameraY, 0, 1, 0);
    }
    else {
        //gluLookAt (-cos(cannon1.turn*PI/180)+12, cannon1.CannonPoz.y+3, sin(cannon1.turn*PI/180), cannon1.CannonPoz.x, cannon1.CannonPoz.y, cannon1.CannonPoz.z, 0.0, 1.0, 0.0);
    gluLookAt(cannon1.CannonPoz.x+12, 3, cannon1.CannonPoz.z, cannon1.CannonPoz.x, cannon1.CannonPoz.y, cannon1.CannonPoz.z, 0, 1, 0);
    }
    
        //display cannon
        if (spotlightChange==false) {
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,50.0);    	// set cutoff angle
            glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,4.0);   	// set focusing strength
        }
        else {
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightdirN);
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,40.0);    	// set cutoff angle
            glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,15.0);   	// set focusing strength
        }    
    for (int i = 0; i < allBullets.size(); ++i)
	{
		allBullets.at(i).Draw_Bullet();
        target.collision(allBullets.at(i).BulletPoz);
    }
    cannon1.Draw_Cannon();
    target.Draw_Target();
	
    if( target.Response()==WIN )
	{	
		
		glLoadIdentity();
		angle=60;
		glViewport(0, 0, width, height);
		gluLookAt (0, 5, 6.5, 0.0, 5.0, 1.0, 0.0, 1.0, 0.0);
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			map.win();
		glPopMatrix();
	}  
   
    glDisable(GL_COLOR_MATERIAL);
    
    map.ground(); 
    map.sky();
    map.wall();
	sound = FSOUND_Stream_Open( "Resources\\Sound\\progressive.mid" , FSOUND_2D , 0 , 0 );
	if (music==ON)
	{
	
	FSOUND_Stream_Play(0,sound);
	}
	else
	{
		FSOUND_Stream_Stop( sound );
	}

    glutSwapBuffers();
}


void idle()
{
        for (int i = 0; i < allBullets.size(); i++)
        {
            allBullets.at(i).shoot();
			//cannon1.glUpdateParticles();
		}
    glutPostRedisplay();   
}


void screen_reshape(int w, int h)
{
    //Use this function to switch between perspective view and orthographic view
    width = w;
    height = h;
    int wh = width / height;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (mode == PERSPECTIVE) 
    {
        gluPerspective(angle, (GLfloat)wh*2, 1.0, 500.0);
    }
    else if ( mode == ORTHO)
    {
        glOrtho(-30, 30, -20, 20, 1.0, 500.0);
    }        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void default_reshape(int w, int h)
{
    width = w;
    height = h;
    int wh = width / height;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, (GLfloat)wh*2, 5.0, 1000.0);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
                  
        //Wire frame or Shaded Model
        case 'w':
        case 'W':  
            WireFrame = 1-WireFrame;
            if (WireFrame)
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);     // Solid
            else 
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);     // Wireframes
            break;    
            
        //Camera forward
        case 'f':              
            //glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            eyez -= 1.5f;                      
            gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
            break;
            
        //Camera backward
        case 'b':
            glLoadIdentity();
            eyez += 1.5f;                      
            gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
            break;
            
        //Zoom in
        case 'z':    
            angle -=2.0;
            default_reshape(width, height);            
            break;
            
        //Zoom out
        case 'Z':
            angle +=2.0;
            default_reshape(width, height);
            break;
        
        //Perspective View
        case 'p':
        case 'P':
            mode = PERSPECTIVE;
            screen_reshape(width, height);
            break;
        
        //Orthographic View
        case 'o':
        case 'O':
            mode = ORTHO;
            screen_reshape(width, height);
            break;
            
        //fog control
        case '0':
            fog = !fog;
            break;
            
        //Light control
        case '1': 
            light0 = !light0; //Cannnon spot light
            light1 = !light1;  //sun light
            spotlight = !spotlight; //Target spot light
            map.skyChange = !map.skyChange; //Change to night sky
            break;
            
        //camera control
        case '2':
            camera = !camera;
            break;
        
        case '3':
            spotlightChange = !spotlightChange;
            break;
            
        //animation control
        case ' ':
            allBullets.push_back(Bullet(cannon1.CannonPoz,cannon1.turn,cannon1.beta));
			// attempt to open the mp3 file as a stream
			sound = FSOUND_Stream_Open( "Resources\\Sound\\fire.wav" , FSOUND_2D , 0 , 0 );
			FSOUND_Stream_Play(0,sound);
            break;
             
        //Gun control
        case '[':
            cannon1.Gun(UP);
            break;
        
        //Gun control
        case ']':
            cannon1.Gun(DOWN);
            break;

        case '/':
			glutFullScreen();
			break;

		case 'm':
			music = !music;
			break;
            
        case 'i':
            cameraX += 5.0f;
            break;
            
        case 'k':
            cameraX -= 5.0f;
            break;
        
        case 'j':
            cameraY -= 10.0f;
            break;
            
        case 'l':
            cameraY += 10.0f;            
            break;
            
        //Clear viewing parameter
        case 'c':
        case 'C':
            cameraX = 0.0f;
            cameraY = 0.0f;
            cameraZ = 0.0f;
            eyex = 0.0f;
            eyey = 10.0f;
            eyez = 35.0f;
            angle = 50.0f;
            default_reshape(width, height);
            break;
        
        //Exit from the program, by pressing "Esc" key.
        case 27:
            exit(0);
            break;

    }
    glutPostRedisplay();
   
}



// Camera Motion (called on special key pressed)
void specialkeyboard(int key, int x, int y)
{
    switch(key)
    {
          
        case GLUT_KEY_UP :                  // Camera up 
            cannon1.MoveForward();
            break;
            
        case GLUT_KEY_DOWN :                // Camera down 
            cannon1.MoveBackward();
            break;
    
        case GLUT_KEY_LEFT :                // Camera left
            cannon1.TurnLeft();
            break;
            
        case GLUT_KEY_RIGHT :               // Camera right
            cannon1.TurnRight();
            break;
        
        //Exit from the program, by pressing Esc key.
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Crazy Cannon");
    init();    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(idle);    
    glutReshapeFunc(default_reshape);

    glutMainLoop();
    return 0;
}
