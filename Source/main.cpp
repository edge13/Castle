// **********************************
// File: main.c++
// Submitted as part of Project 4 for EECS 672
// May 9, 2007
// By Joel Angelone, KUID 1311419
// **********************************

#include <GL/glut.h>
#include <stdlib.h>
#include "geometry.h"

// Keep track of the current viewing parameters
double xmin = -60.0;
double xmax = 60.0;
double ymin = -40.0;
double ymax = 80.0;
double zmin = -1600;
double zmax = 1600.0;

// Accumulated rotation matrix
double	rot[16] = { 1.0, 0.0, 0.0, 0.0 ,
					0.0, 1.0, 0.0, 0.0 ,
					0.0, 0.0, 1.0, 0.0 ,
					0.0, 0.0, 0.0, 1.0 };

// Mouse buttons currently being used
bool left_button = false;
bool middle_button = false;

// The most recent x/y coordinate of the mouse
int screen_x, screen_y;

// The width and height of the window (initially 800x600)
int width = 800, height = 600;

// The z coordinate of the eye
double eye_z = 180.0;

// Flags set by the menu callback
bool OrthoMode = false;
bool DayTime = true;

// Instance of the geometry class (does all the model rendering)
Geometry geom;

// Sets the modelview matrix
// This function is called every time the display callback is invoked
// It first multiplies the modelview matrix by the current rotation matrix,
// then applies the gluLookAt transformation
void EstablishModelviewMatrix()
{
	// Start with the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply the rotation matrix (shift the model to the center of the
	// eye coordinate system first)
	glTranslated(0.0, -10.0, -eye_z);
	glMultMatrixd(rot);
	glTranslated(0.0, 10.0, eye_z);

	gluLookAt(0.0, 10.0, eye_z,
		  0.0, 20.0, 0.0,
		  0.0, 1.0, 0.0);
}

// Sets the project matrix
// This matrix is different depending on which mode is currently
// active -- Orthogonal or Perspective. This is toggled via the
// menu attached to the right mouse.
// This function is also responsible for maintaining the aspect ratio
// of the window.
void EstablishProjectionMatrix(double viewportAR)
{
	// These will hold the newly calculated values corresponding to
	// the correct aspect ratio
	double new_xmin = xmin;
	double new_xmax = xmax;
	double new_ymin = ymin;
	double new_ymax = ymax;

	// Compute the "desired" aspect ratio
	double windowAR   = (ymax - ymin) / (xmax - xmin);

	// The screen is too tall
	if (viewportAR > windowAR)
	{
		double dy = viewportAR*(xmax - xmin) - (ymax - ymin);

		new_ymax += dy/2;
		new_ymin -= dy/2;
	}
	
	// The screen is too wide
	else
	{
		double dx = (ymax - ymin)/viewportAR - (xmax - xmin);

		new_xmax += dx/2;
		new_xmin -= dx/2;
	}

	// Make the appropriate call based on the current projection mode
	if (OrthoMode)
		glOrtho(new_xmin, new_xmax, new_ymin, new_ymax, zmin, zmax);
	else
		gluPerspective(60.0, 1/viewportAR, 5, 800);
}

// This function sets the lighting in the scene
// The lighting is different depending on whether the user has day or night
// lighting enabled (this is set using the menu).
void Lights()
{
	// Sunlight
	if (DayTime)
	{
		// Sunlight is a directional light (a vector that hits every
		// vertex in the scene) so w is set to 0 here
		GLfloat position[] = {50.0, 100.0, 50.0, 0.0};
		GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat ambient[] = {0.2, 0.1, 0.2, 1.0};

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	}

	// Night lighting
	// Consists of two torches and a glowing window
	else
	{
		// Torch 1
		// These lights are point lights so w is 1
		GLfloat position[] = {5.0, 25.0, -25.0, 1.0};
		GLfloat direction[] = {0.0, -0.2, 1.0, 1.0};
		GLfloat diffuse[] = {1.0, 1.0, 0.0, 1.0};
		GLfloat specular[] = {1.0, 0.8, 0.0, 1.0};
		GLfloat ambient[] = {0.3, 0.1, 0.0, 1.0};

		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90);

		// Torch 2
		position[0] = 35.0;
		glLightfv(GL_LIGHT2, GL_POSITION, position);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.005);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);

		//Window
		position[0] = 20.0;
		position[1] = 95.0;
		position[2] = -40.0;

		specular[0] = specular[1] = 0.7;
		diffuse[0] = diffuse[1] = 0.8;
		ambient[0] = ambient[1] = 0.4;
		direction[1] = 0.0;

		glLightfv(GL_LIGHT2, GL_POSITION, position);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
	}
}

// The reshape callback is invoked whenever the window is resized by the user,
// and also whenever the user switches projection modes.
void ReshapeCB(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Store the width and height of the window as globals
	width = w;
	height = h;

	EstablishProjectionMatrix(double(height) / double(width));
}

// The MouseFunc callback happens whenever a mouse button is pressed
// It has two functionalities in this program - the first is to allow
// the user to rotate the scene using the left mouse button, the second
// is to allow the user to zoom using the middle mouse button
void MouseFuncCB(int button, int state, int x, int y)
{
	// Rotate if the left button is depressed
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		// The current screen x/y becomes the new x/y of the mouse
		screen_x = x;
		screen_y = y;
		// Keep track of the current action
		middle_button = false;
		left_button = true;
	}

	else
	{
		// Don't want to rotate if the left mouse isn't down
		left_button = false;
	}

	// Zooming
	if (state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON)
	{
		screen_x = x;
		screen_y = y;
		middle_button = true;
		left_button = false;
	}

	else
	{
		middle_button = false;
	}
}

// Mouse motion occurs whenever the user moves the mouse
void MouseMotionCB(int new_x, int new_y)
{
	// If the current action is zoom
	if (middle_button)
	{
		// Zoom distance is set to 2/3 of the pixel offset of the mouse
		int dy = (new_y - screen_y) * 2/3;

		// New window limits
		xmin -= dy;
		xmax += dy;
		ymin -= dy;
		ymax += dy;

		// Keep track of the screen x/y
		screen_x = new_x;
		screen_y = new_y;

		// Move the "eye" in relation to the scene
		eye_z += dy*2;

		// Stop zooming at a reasonable distance
		if (xmax < 6)
		{
			xmin = -6;
			xmax = 6;
			ymin = -4;
			ymax = 8;
		}

		if (eye_z < 30)
			eye_z = 30;

		// Call the reshape callback manually
		ReshapeCB(width, height);
		glutPostRedisplay();
	}

	// If the current action is rotating
	else if (left_button)
	{
		// Mouse offset determines how much to rotate
		int dx = (new_x - screen_x);
		int dy = (new_y - screen_y);

		// Keep track of the current x/y of the mouse
		screen_x = new_x;
		screen_y = new_y;

		double scale = 360.0 / 500.0;

		double rot_y = scale * dx;
		double rot_x = scale * dy;

		// Rotate the scene
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(rot_x, 1.0, 0.0, 0.0);
		glRotated(rot_y, 0.0, 1.0, 0.0);
		glMultMatrixd(rot);
		// Grab the current modelview matrix and stuff it into our global matrix
		glGetDoublev(GL_MODELVIEW_MATRIX, rot);

		glutPostRedisplay();
	}
}

// The menu callback allows for -- switching between day and night lighting,
// switching between projection modes, and exiting the program
void MenuCB(int value)
{
	// Toggle Lighting
	if (value == 1)
	{
		// Enable daytime lighting
		if (DayTime)
		{
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			DayTime = false;
		}
		
		// Enable night lighting
		else
		{
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			DayTime = true;
		}
			
		glutPostRedisplay();
	}

	// Toggle Projection
	else if (value == 2)
	{
		if (OrthoMode)
			OrthoMode = false;
		else
			OrthoMode = true;

		// Need to manually call the reshape callback
		ReshapeCB(width, height);
		glutPostRedisplay();
	}

	// Exit
	else if (value == 3)
	{
		exit(0);
	}
}

// Display callback renders the scene
void DisplayCB()
{
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);

	EstablishModelviewMatrix();

	Lights();

	geom.Ground();
	geom.Castle();
	geom.Moat();
	geom.Forest();

	// Use the mirror function do draw the forest on the
	// opposite side of the castle
	glPushMatrix();
	geom.Mirror(35.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	geom.Forest();
	glPopMatrix();

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	geom.Torches();
	//geom.Clouds();

	glFlush();
	glutSwapBuffers();
}

void TimerCB(int value)
{
	// Update Display
	if (value == 0)
	{
		geom.UpdateParticles();
		glutPostRedisplay();
		glutTimerFunc(50, TimerCB, 0);
	}

	// Spawn a particle
	else if (value == 1)
	{
		geom.SpawnParticle();
		glutTimerFunc(5, TimerCB, 1);
	}
}

// The only keyboard event used in this program is the ESC key,
// which exits the program
void KeyboardCB(unsigned char key, int x, int y)
{
	// ESC quits the program
	if (key == 27)
		exit(0);
}

// Initializes the window, rendering context, and various
// opengl attributes
void InitOpenGL()
{
	// Creates the window
	glutInitWindowSize(width, height);
	glutInitWindowPosition(250, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("3D Castle - by Joel Angelone");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Register callbacks
	glutDisplayFunc(DisplayCB);
	glutKeyboardFunc(KeyboardCB);
	glutReshapeFunc(ReshapeCB);
	glutMouseFunc(MouseFuncCB);
	glutMotionFunc(MouseMotionCB);

	// Creates the menu
	glutCreateMenu(MenuCB);
	glutAddMenuEntry("Toggle Lighting", 1);
	glutAddMenuEntry("Toggle Projection Mode", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// "Sky" looking clear color
	glClearColor(0.3, 0.3, 0.5, 1.0);
	
	// Start out in daytime mode, so light0 is enabled
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	geom.LoadTextures();
}

// Main function
// Initializes opengl and gives control to the glut loop
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	InitOpenGL();

	glutTimerFunc(30, TimerCB, 0);
	glutTimerFunc(30, TimerCB, 1);

	glutMainLoop();

	return 0;
}
