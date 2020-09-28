//
//  main.c
//  SceneIn3D
//
//  Created by Mahalia Evans
//

#include "teapot.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//===============================VARIABLES====================================
//----------------------------------------------------------------------------
int angle=0;          //  Azimuth of view angle
int elev=0;          //  Elevation of view angle
int mode=0;        //  Display
double z=0;     // Z variable
double w=1;     // W variable
double pi=3.14159; // Pi
int axes = 1; // Axes

// Rotation
typedef struct {
    double rotAngle;
    double rotX;
    double rotY;
    double rotZ;
} Rotation;


static void cylinder (double radius, double height, int num,
                      double xPos, double yPos, double zPos, Rotation rot){
    //  Transformation
    glPushMatrix();
    //  Translation Double
    glTranslated(xPos,yPos,zPos); //TranslateD = Double, F = float
    
    glRotated(rot.rotAngle,rot.rotX,rot.rotY,rot.rotZ); // Tree Branch
    
    // Tree Trunk
    glBegin(GL_QUADS);
    // Angle in Radians
    for (int i = 0; i < num; i++){
        double angle1 = 2 * pi * i / num; // Num - sides of polygon for base
        double angle2 = 2 * pi * (i+1) / num;
        // Z axis
        double z1 = cos(angle1) * radius; // Radius of Cylinder
        double x1 = sin(angle1) * radius; // X axis
        // Y Axis - Height
        double yLow = 0;
        double yHigh = height;
        
        double z2 = cos(angle2) * radius; // Radius of Cylinder
        double x2 = sin(angle2) * radius; // X axis
        
        // Color
        glColor3f(0,1,0);
        // Quad
        glVertex3f(x1,yLow,z1);
        glVertex3f(x2,yLow,z2);
        glVertex3f(x2,yHigh,z2);
        glVertex3f(x1,yHigh,z1);
        
    }
    //  End
    glEnd();
    //  Undo transformations
    glPopMatrix();
}
//----------------------------------------------------------------------------
//===============================DISPLAY======================================
/*
 * Display the Scene
 */
void display()
{
   //  Clear screen
   glClear(GL_COLOR_BUFFER_BIT);
   //  Make scene visible
   glFlush();

    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //  Undo previous transformations
    glLoadIdentity();
    //  Set view angle
    glRotatef(angle,1,0,0);
    glRotatef(elev,0,1,0);

    Rotation rot = {45, 1, 0 ,0};
    Rotation rot2 = {30, 1, 0 ,0};
    cylinder(0.1, 1, 20, .1, .2, .3, rot);
    cylinder(0.2, .6, 20, -.2, 0, -.3, rot2);
    
    //  White
    glColor3f(1,1,1);
    //  Draw axes
    double len = 4;
    if (axes)
    {
       glBegin(GL_LINES);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(len,0.0,0.0);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(0.0,len,0.0);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(0.0,0.0,len);
       glEnd();
       //  Label axes
       glRasterPos3d(len,0.0,0.0); // Position
       //Print("X");
        //Color Change
       glRasterPos3d(0.0,len,0.0);
       //Print("Y");
       glRasterPos3d(0.0,0.0,len);
       //Print("Z");
    }
    
    //  Draw
    switch (mode)
    {
       //  Draw Sun & Plants
       case 0:
          //sun(0,0,0 , 0.3,0.3,0.3 , 0); // Draw a Sun at this position
          //plantA(1,0,0 , 0.2,0.2,0.2 , 45); // Draw a Plant at this position
          //plantB(0,1,0 , 0.4,0.4,0.2 , 90); // Same Plant at a different position
          break;

       //  Draw Plants & Sun
       case 1:
          //plantA(0,0,0 , 0.4);
          //plantB(1,0,0 , 0.2);
          //sun(0,1,0 , 0.2);
          break;
    }
    //  Render the scene
    glFlush();
    //  Rendered scene make visible
    glutSwapBuffers();
}

//----------------------------------------------------------------------------
//===============================WINDOW=======================================
/*
 *  When window is resized
 */
void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}
//----------------------------------------------------------------------------
//=================================KEYS=======================================
/*
 *  To Exit & Reset Display
 */
void key(unsigned char ch,int x,int y)
{
    //  Exit on ESC
   if (ch == 27)
      exit(0);

    //  Reset view angle
   else if (ch == '0')
      angle = elev = 0;

    //  Switch dimensions
   else if ('1'<=ch && ch<='4')
   {
      mode = ch-'0';
      if (mode==2) z = 0;
      if (mode==4) w = 1;
   }
    //  Toggle axes
    else if (ch == 'a' || ch == 'A')
       axes = 1-axes;

    //  Increase w by 0.1
   else if (ch == '+')
   {
      if (mode==2)
         z += 0.1;
      else
         w += 0.1;
   }

    //  Decrease w by 0.1
   else if (ch == '-')
   {
      if (mode==2)
         z -= 0.1;
      else
         w -= 0.1;
   }
   //  Redisplay the scene
   glutPostRedisplay();
}
//----------------------------------------------------------------------------
/*
 *  Change Angle UP, DOWN, LEFT, & RIGHT
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      angle += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      angle -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      elev += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      elev -= 5;
   //  Angles +/-360 degrees
   angle %= 360;
   elev %= 360;
   //  Redisplay the scene
   glutPostRedisplay();
}
//----------------------------------------------------------------------------
//=================================MAIN=======================================
/*
 * Main Scene In 3D
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Create window
   glutCreateWindow("Scene In 3D");
   //  Register function used to display scene
   glutDisplayFunc(display);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
    //  Tell GLUT to call "special" when an arrow key is pressed
    glutSpecialFunc(special);
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
//----------------------------------------------------------------------------
