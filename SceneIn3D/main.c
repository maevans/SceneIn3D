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
#define GL_SILENCE_DEPRECATION
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
int axes = 0; // Axes

// Rotation
typedef struct {
    double rotAngle;
    double rotX;
    double rotY;
    double rotZ;
} Rotation;

//=================================TREE=======================================
//----------------------------------------------------------------------------
static void cylinder (double radius, double height, int num,
                      double xPos, double yPos, double zPos, Rotation rot){
    //  Transformation
    glPushMatrix();
    //  Translation Double
    glTranslated(xPos,yPos,zPos); //TranslateD = Double, F = float
    // Rotation Double
    glRotated(rot.rotAngle,rot.rotX,rot.rotY,rot.rotZ); // Tree Branch
    
    // TRUNK
    glBegin(GL_QUADS);
    // Angle in Radians
    for (int i = 0; i < num; i++){
        double angle1 = 2 * pi * i / num; // Num - sides of polygon for base
        double angle2 = 2 * pi * (i+1) / num;
        
        // Z axis
        double z1 = cos(angle1) * radius; // Radius of Cylinder
        double x1 = sin(angle1) * radius; // X Axis
        
        // Y Axis - Height
        double yLow = 0;
        double yHigh = height;
        
        double z2 = cos(angle2) * radius; // Radius of Cylinder
        double x2 = sin(angle2) * radius; // X Axis
        
        // Brown Color
        //glColor3f(0.59,0.29,0.00);
        
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



//===============================DISPLAY======================================
//----------------------------------------------------------------------------
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
    
    //--Tree Rotations--
    Rotation rot = {0, 1, 0, 0}; // Trunk Rotation
    Rotation rot1 = {30, 0, 0, 92}; // Branch 1 Rotation
    Rotation rot2 = {30, 0, 0, 154}; // Branch 2 Rotation
    Rotation rot3 = {30, 0, 0, -88}; // Branch 3 Rotation
    Rotation rot4 = {30, 0, 0, -108}; // Branch 4 Rotation
    
    //---TREE 1---
    
    // Trunk
    glColor3f(0.59,0.35,0.00);
    cylinder(0.3, 2, 250, -0.25, -1.5, 1.2, rot);
   
    // Branch 1
    glColor3f(0.59,0.27,0.00);
    cylinder(0.1, 0.6, 250, -0.4, 0, 1.07, rot1);
    
    // Branch 2
    glColor3f(0.59,0.22,0.00);
    cylinder(0.085, 0.5, 250, -0.38, -0.75, 1.06, rot2);
    
    // Branch 3
    glColor3f(0.59,0.22,0.00);
    cylinder(0.085, 0.3, 250, -0.11, 0.1, 1.03, rot3);
    
    // Branch 4
    glColor3f(0.59,0.27,0.00);
    cylinder(0.1, 0.6, 250, -0.1, -0.65, 1.07, rot4);
    
    
    //---TREE 2---
   
    // Trunk
    glColor3f(0.59,0.35,0.00);
    cylinder(0.08, 1, 250, 0.35, -1.5, 0, rot);
   
    // Branch 1
    glColor3f(0.59,0.27,0.00);
    cylinder(0.05, 0.2, 250, 0.32, -0.8, -0.02, rot1);
    
    // Branch 2
    glColor3f(0.59,0.22,0.00);
    cylinder(0.0425, 0.25, 250, 0.38, -1.08, -0.018, rot2);
    
    // Branch 3
    glColor3f(0.59,0.22,0.00);
    cylinder(0.0425, 0.25, 250, 0.32, -1.1, -0.03, rot3);
    
    // Branch 4
    glColor3f(0.59,0.27,0.00);
    cylinder(0.05, 0.2, 250, 0.38, -0.65, -0.02, rot4);
    
    
    //  Draw axes
    glColor3f(1,1,1);
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
//       glColor3f(1,0,0);//Print("X");
       glRasterPos3d(len,0.0,0.0); // Position
       //Print("X");
//       glColor3f(0,1,0);
       glRasterPos3d(0.0,len,0.0);
       //Print("Y");
//       glColor3f(0,1,0);
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

//===============================WINDOW=======================================
//----------------------------------------------------------------------------
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

//=================================KEYS=======================================
//----------------------------------------------------------------------------
void key(unsigned char ch,int x,int y)
{
    //  ESC to quit
   if (ch == 27)
      exit(0);

    //  Reset
   else if (ch == '0')
      angle = elev = 0;

    //  Toggle Axes
    else if (ch == 'a')
       axes = 1-axes;

    //  Increase
   else if (ch == '[')
   {
       z += 0.5;
   }

    //  Decrease
   else if (ch == ']')
   {
       z -= 0.5;
   }
   //  Redisplay the scene
   glutPostRedisplay();
}
//----------------------------------------------------------------------------
/*
 *  Change Angle UP, DOWN, LEFT, & RIGHT
 */
void arrows(int key,int x,int y)
{

   if (key == GLUT_KEY_DOWN) // Down
      angle += 5;

   else if (key == GLUT_KEY_UP) // Up
      angle -= 5;

   else if (key == GLUT_KEY_LEFT) // Left
      elev += 5;

   else if (key == GLUT_KEY_RIGHT) // Right
      elev -= 5;
    
   //  Redisplay the scene
   glutPostRedisplay();
}

//=================================MAIN=======================================
//----------------------------------------------------------------------------
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
    glutSpecialFunc(arrows);
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
//----------------------------------------------------------------------------
