// **********************************
// File: geometry.c++
// Submitted as part of Project 4 for EECS 672
// May 9, 2007
// By Joel Angelone, KUID 1311419
// **********************************

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include "geometry.h"
using namespace std;

// Constructor for the geometry class
Geometry::Geometry()
{
	// GLU quadratics for rendering cylinders and disks
	cylinder = gluNewQuadric();
	disk = gluNewQuadric();

	// Define normals at every vertex
	gluQuadricNormals(cylinder, GLU_FLAT);
	gluQuadricNormals(disk, GLU_FLAT);

	gluQuadricTexture(cylinder, GL_TRUE);

	for (int i = 0; i < 1000; i++)
		particles[i].alive = false;

	num_particles = 0;

}

// Destructor for the geometry class
Geometry::~Geometry()
{
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(disk);
}

// Load and initialize the textures for the scene
void Geometry::LoadTextures()
{
	int width, height, channels;
	unsigned char *grassImage;
	unsigned char *stoneImage;
	unsigned char *waterImage;
	unsigned char *woodImage;
	unsigned char *brickImage;
	unsigned char *stoneLargeImage;

	// Load grass texture
	if(loadBMPData("Textures/grass.bmp", &grassImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/grass.bmp" << endl;

	else
	{
		glGenTextures(1, &grass);
		glBindTexture(GL_TEXTURE_2D, grass);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassImage);

		delete grassImage;
	}

	// Load stone texture
	if(loadBMPData("Textures/stone.bmp", &stoneImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/stone.bmp" << endl;

	else
	{
		glGenTextures(1, &stone);
		glBindTexture(GL_TEXTURE_2D, stone);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, stoneImage);

		delete stoneImage;
	}

	// Load water texture
	if(loadBMPData("Textures/water.bmp", &waterImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/water.bmp" << endl;

	else
	{
		glGenTextures(1, &water);
		glBindTexture(GL_TEXTURE_2D, water);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, waterImage);

		delete waterImage;
	}

	// Load wood texture
	if(loadBMPData("Textures/wood.bmp", &woodImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/wood.bmp" << endl;

	else
	{
		glGenTextures(1, &wood);
		glBindTexture(GL_TEXTURE_2D, wood);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodImage);

		delete woodImage;
	}

	// Load brick texture
	if(loadBMPData("Textures/brick.bmp", &brickImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/brick.bmp" << endl;

	else
	{
		glGenTextures(1, &brick);
		glBindTexture(GL_TEXTURE_2D, brick);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, brickImage);

		delete brickImage;
	}

	// Load stone large texture
	if(loadBMPData("Textures/stone_large.bmp", &stoneLargeImage, width, height, channels) != LOAD_TEXTUREBMP_SUCCESS)
		cout << "Error loading texture: Textures/stone_large.bmp" << endl;

	else
	{
		glGenTextures(1, &stone_large);
		glBindTexture(GL_TEXTURE_2D, stone_large);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, stoneLargeImage);

		delete stoneLargeImage;
	}
}

// Mirror takes a point and a normal vector defining a plane and builds the 4x4
// matrix that represents the affine transformation mirroring points across this plane
void Geometry::Mirror(double x, double y, double z, double nx, double ny, double nz)
{
	double matrix[16];
	double result[9];
	double m3x3[9];
	double identity[9] = { 1, 0, 0,
			       0, 1, 0,
			       0, 0, 1 };
	double bx = x;
	double by = y;
	double bz = z;

	// Start by defining the 3x3 matrix m = I - 2(n-hat tensor n-hat)

	// n-hat tensor n-hat
	Tensor(nx, ny, nz, nx, ny, nz, result);

	// multiplies the result by 2
	Multiply(result, 2);

	// Subtract from the 3x3 identity matrix - this gives m3x3
	Subtract(identity, result, m3x3);

	// Now find the vector t = B - MB
	Multiply(m3x3, bx, by, bz);

	Subtract(x, y, z, bx, by, bz);
	
	// Build the 4x4
	matrix[0] = m3x3[0];
	matrix[1] = m3x3[1];
	matrix[2] = m3x3[2];
	matrix[4] = m3x3[3];
	matrix[5] = m3x3[4];
	matrix[6] = m3x3[5];
	matrix[8] = m3x3[6];
	matrix[9] = m3x3[7];
	matrix[10] = m3x3[8];

	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;

	matrix[3] = 0;
	matrix[7] = 0;
	matrix[11] = 0;
	matrix[15] = 1;
	
	// Tell OpenGl to multiply the current modelview matrix by this new mirror matrix
	glMultMatrixd(matrix);
}

// Compute the tensor product of two vectors - the result is a 3x3 matrix
void Geometry::Tensor(double x1, double y1, double z1, double x2, double y2, double z2, double m[9])
{
	m[0] = x1*x2;
	m[1] = y1*x2;
	m[2] = z1*x2;
	m[3] = x1*y2;
	m[4] = y1*y2;
	m[5] = z1*y2;
	m[6] = x1*z2;
	m[7] = y1*z2;
	m[8] = z1*z2;
}

// Subtracts two matrices - the result is a new 3x3 matrix
void Geometry::Subtract(double m1[9], double m2[9], double result[9])
{
	for (int i = 0; i < 9; i++)
	{
		result[i] = m1[i] - m2[i];
	}
}

// Subtracts two vectors, the first vector contains the result
void Geometry::Subtract(double &x1, double &y1, double &z1, double x2, double y2, double z2)
{
	x1 -= x2;
	y1 -= y2;
	z1 -= z2;
}

// Multiplies a matrix times a vector - the result is stored in the vector
void Geometry::Multiply(double m[9], double &x, double &y, double &z)
{
	x = x*m[0] + x*m[3] + x*m[6];
	y = y*m[1] + y*m[4] + y*m[7];
	z = z*m[2] + z*m[5] + z*m[8];
}

// Multiplies a matrix times a scalar - the result is stored in the matrix
void Geometry::Multiply(double m[9], int scalar)
{
	for (int i = 0; i < 9; i++)
	{
		m[i] = scalar*m[i];
	}
}

// Sets the current material properties for rendering objects
void Geometry::SetMaterial(int type)
{
	if (type == STONE)
	{
		GLfloat amb[] = {0.1, 0.1, 0.1, 1.0 };
		GLfloat diff[] = {0.7, 0.7, 0.8, 1.0};
		GLfloat spec[] = { 0.5, 0.6, 0.8, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 60.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == BRICK)
	{
		GLfloat amb[] = {0.3, 0.1, 0.1, 1.0 };
		GLfloat diff[] = {0.4, 0.1, 0.1, 1.0};
		GLfloat spec[] = { 0.8, 0.1, 0.1, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 80.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == METAL)
	{
		GLfloat amb[] = {0.1, 0.1, 0.1, 1.0 };
		GLfloat diff[] = {0.1, 0.1, 0.2, 1.0};
		GLfloat spec[] = { 0.0, 0.0, 0.0, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 20.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == WOOD)
	{
		GLfloat amb[] = {0.2, 0.2, 0.1, 1.0 };
		GLfloat diff[] = {0.7, 0.4, 0.0, 1.0};
		GLfloat spec[] = { 0.1, 0.1, 0.1, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 10.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == GRASS)
	{
		GLfloat amb[] = {0.1, 0.1, 0.1, 1.0 };
		GLfloat diff[] = {0.2, 0.6, 0.1, 1.0};
		GLfloat spec[] = { 0.3, 0.6, 0.4, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 40.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == WATER)
	{
		GLfloat amb[] = {0.1, 0.1, 0.8, 1.0 };
		GLfloat diff[] = {0.5, 0.6, 0.8, 1.0};
		GLfloat spec[] = { 0.4, 0.2, 0.7, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.3, 1.0 };
		GLfloat shine = 20.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == FOREST)
	{
		GLfloat amb[] = {0.1, 0.1, 0.1, 1.0 };
		GLfloat diff[] = {0.1, 0.5, 0.0, 1.0};
		GLfloat spec[] = { 0.1, 0.3, 0.1, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 40.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == FLAME)
	{
		GLfloat amb[] = {1.0, 1.0, 0.0, 1.0 };
		GLfloat diff[] = {0.8, 0.7, 0.0, 1.0};
		GLfloat spec[] = { 1.0, 1.0, 0.0, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 100.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == WINDOW)
	{
		GLfloat amb[] = {1.0, 1.0, 0.0, 1.0 };
		GLfloat diff[] = {0.8, 0.8, 0.0, 1.0};
		GLfloat spec[] = { 1.0, 1.0, 0.0, 1.0};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat shine = 100.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}

	else if (type == CLOUD)
	{
		GLfloat amb[] = {1.0, 1.0, 1.0, 0.4 };
		GLfloat diff[] = {1.0, 1.0, 1.0, 0.4};
		GLfloat spec[] = { 1.0, 1.0, 1.0, 0.4};
		GLfloat emis[] = { 0.0, 0.0, 0.0, 0.0 };
		GLfloat shine = 10.0;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	}
}

// Renders the ground for the scene
// In order to achieve the desired effects using attenuation of point lights,
// the ground is actually a series of small polygons (since the lighting model
// is only evaluated at vertices)
void Geometry::Ground()
{
	glPushMatrix();

	SetMaterial(GRASS);
	glNormal3d(0.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (double x = -300.0; x < 300.0; x += 20.0)
	{
		for (double z = -300.0; z < 300.0; z += 20.0)
		{
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3d(x, 0.0, z);
				glTexCoord2f(1.0, 0.0);
				glVertex3d(x + 20.0, 0.0, z);
				glTexCoord2f(1.0, 1.0);
				glVertex3d(x + 20.0, 0.0, z + 20.0);
				glTexCoord2f(0.0, 1.0);
				glVertex3d(x, 0.0, z + 20.0);
			glEnd();
		}
	}

	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

// Spawns a new flame particle
void Geometry::SpawnParticle()
{
	// Max number of particles on screen is 5000
	if (num_particles < 5000)
	{
		// Set the default values for a particle
		particles[num_particles].alive = true;
		particles[num_particles].lifespan = 100;

		float px = rand() % 100;
		float pz = rand() % 100;

		particles[num_particles].x = px / 100 - .5;
		particles[num_particles].y = 0.0;
		particles[num_particles].z = pz / 100 - .5;

		particles[num_particles].r = 0.7;
		particles[num_particles].g = 0.7;
		particles[num_particles].b = 0.05;
		particles[num_particles].a = 0.9;

		float x = rand() % 100;
		float z = rand() % 100;

		particles[num_particles].xbias = x / 3000 - .016;
		particles[num_particles].zbias = z / 3000 - .016;

		num_particles++;
		return;
	}

	// If we've reached the max number of particles, try to find an empty slot
	for (int i = 0; i < num_particles; i++)
	{
		if (particles[i].alive == false)
		{
			particles[i].alive = true;
			particles[i].lifespan = 1000;

			float px = rand() % 100;
			float pz = rand() % 100;

			particles[i].x = px / 100 - .5;
			particles[i].y = 0.0;
			particles[i].z = pz / 100 - .5;

			particles[i].r = 0.7;
			particles[i].g = 0.7;
			particles[i].b = 0.05;
			particles[i].a = 0.9;

			float x = rand() % 100;
			float z = rand() % 100;

			particles[num_particles].xbias = x / 3000 - .016;
			particles[num_particles].zbias = z / 3000 - .016;

			return;
		}
	}
}

// Draws a single torch
void Geometry::Torch()
{
	glPushMatrix();

	SetMaterial(WOOD);

	glTranslated(0.0, 4.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);

	gluCylinder(cylinder, 1.0, 1.0, 4.0, 12, 12);

	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 4.0, 0.0);

	SetMaterial(FLAME);

	// Draw every flame particle based on its properties
	for (int i = 0; i < num_particles; i++)
	{
		if (particles[i].alive == false)
			continue;

		GLfloat emis[] = { particles[i].r, particles[i].g, particles[i].b, particles[i].a };
		GLfloat diff[] = { 0.5, 0.0, 0.0, particles[i].a };
		GLfloat spec[] = { 0.0, 0.0, 0.0, particles[i].a };
		GLfloat amb[] = { 0.1, 0.0, 0.0, particles[i].a };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);

		glPushMatrix();
		glTranslated(particles[i].x, particles[i].y, particles[i].z);
		glutSolidCube(0.3);
		glPopMatrix();
	}

	glPopMatrix();
}

// Updates the fire particles
void Geometry::UpdateParticles()
{
	// Loop through all the fire particles
	for (int i = 0; i < num_particles; i++)
	{
		// If the particle isn't alive, don't update it
		if (particles[i].alive == false)
			continue;

		// If the particle's lifespan is over, kill it
		if (particles[i].lifespan < 1)
		{
			particles[i].alive = false;
			continue;
		}

		// Update particle attributes
		particles[i].lifespan--;

		float rand1 = rand() % 100;
		float rand2 = rand() % 100;
		float rand3 = rand() % 100;

		particles[i].x += particles[i].xbias + (rand1 / 1000.0) - .05;
		particles[i].y += rand2 / 350.0;
		particles[i].z += particles[i].zbias + (rand3 / 1000.0) - .05;

		float rdif = rand() % 100;
		float gdif = rand() % 100;
		float bdif = rand() % 100;
		
		particles[i].r += (rdif / 1000.0) - .01;
		particles[i].g -= (gdif / 3000.0);
		particles[i].b -= (bdif / 8000.0);

		// Particles become less and less visible as they project out from the torch
		particles[i].a -= .01;
	}
}

// Draws the torches
void Geometry::Torches()
{
	glPushMatrix();
	glTranslated(5, 12, -20);
	Torch();
	glTranslated(30, 0, 0);
	Torch();
	glPopMatrix();
}

// Draws a series of trees
void Geometry::Forest()
{
	glPushMatrix();
	
	glTranslated(-120.0, 0.0, 65.0);
	Tree(0.0);
	glTranslated(-10.0, 0.0, -15.0);
	Tree(45.0);
	glTranslated(-10.0, 0.0, -45.0);
	Tree(90.0);
	glTranslated(30.0, 0.0, -45.0);
	Tree(20.0);
	glTranslated(5.0, 0.0, -25.0);
	Tree(100.0);
	glTranslated(-20.0, 0.0, -30.0);
	Tree(110.0);
	glTranslated(-40.0, 0.0, -10.0);
	Tree(0.0);
	glTranslated(20.0, 0.0, 30.0);
	Tree(110.0);
	glTranslated(100.0, 0.0, 190.0);
	Tree(50.0);
	glTranslated(30.0, 0.0, -15.0);
	Tree(75.0);
	glTranslated(110.0, 0.0, 5.0);
	Tree(10.0);

	glPopMatrix();
}

// Draws a single tree
void Geometry::Tree(double angle)
{
	glPushMatrix();

	SetMaterial(WOOD);

	glTranslated(0.0, 15.0, 0.0);
	glRotated(angle, 0.0, 1.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);

	gluCylinder(cylinder, 2.0, 3.0, 15.0, 12, 12);

	SetMaterial(FOREST);

	glutSolidSphere(6.0, 12, 12);
	glTranslated(2.0, 1.0, 1.0);
	glutSolidSphere(6.0, 12, 12);
	glTranslated(-5.0, -3.0, -1.0);
	glutSolidSphere(4.0, 12, 12);
	
	glPopMatrix();
}

// Draws a moat around the castle
void Geometry::Moat()
{
	glPushMatrix();

	SetMaterial(WATER);

	glTranslated(0.0, 0.04, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, water);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-100, 0, 53);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(-68, 0, 53);
	glTexCoord2f(1.0, 10.0);
	glVertex3d(-68, 0, -121);
	glTexCoord2f(0.0, 10.0);
	glVertex3d(-100, 0, -121);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2.0);
	glVertex3d(-100, 0, 93);
	glTexCoord2f(10.0, 2.0);
	glVertex3d(146, 0, 93);
	glTexCoord2f(10.0, 0.0);
	glVertex3d(146, 0, 53);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-100, 0, 53);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(106, 0, 53);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(146, 0, 53);
	glTexCoord2f(1.0, 10.0);
	glVertex3d(146, 0, -121);
	glTexCoord2f(0.0, 10.0);
	glVertex3d(106, 0, -121);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-100, 0, -156);
	glTexCoord2f(0.0, 2.0);
	glVertex3d(-100, 0, -121);
	glTexCoord2f(10.0, 2.0);
	glVertex3d(146, 0, -121);
	glTexCoord2f(10.0, 0.0);
	glVertex3d(146, 0, -156);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

// Draws the entire castle
void Geometry::Castle()
{
	// Front Wall
	glPushMatrix();
	glTranslated(-62.0, 0.0, 53.0);
	Wall(60.0);
	glTranslated(100.0, 0.0, 0.0);
	Wall(60.0);
	glPopMatrix();

	// Right Wall
	glPushMatrix();
	glTranslated(107.0, 0.0, 42.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	Wall(80.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(107.0, 0.0, -38.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	Wall(80.0);
	glPopMatrix();

	// Left Wall
	glPushMatrix();
	glTranslated(-73.0, 0.0, -38.0);
	glRotated(270.0, 0.0, 1.0, 0.0);
	Wall(80.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-73.0, 0.0, -118.0);
	glRotated(270.0, 0.0, 1.0, 0.0);
	Wall(80.0);
	glPopMatrix();

	// Back Wall
	glPushMatrix();
	glTranslated(18, 0, -126);
	glRotated(180, 0, 1, 0);
	Wall(80);
	glPopMatrix();

	glPushMatrix();
	glTranslated(98.0, 0.0, -126.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	Wall(80.0);
	glPopMatrix();

	// Front Left Tower
	glPushMatrix();
	glTranslated(-70.0, 0.0, 50.0);
	Tower();
	glPopMatrix();

	// Front Right Tower
	glPushMatrix();
	glTranslated(106.0, 0.0, 50.0);
	Tower();
	glPopMatrix();

	// Back Left Tower
	glPushMatrix();
	glTranslated(-70.0, 0.0, -126.0);
	Tower();
	glPopMatrix();

	// Back Right Tower
	glPushMatrix();
	glTranslated(106.0, 0.0, -126.0);
	Tower();
	glPopMatrix();

	// Keep
	glPushMatrix();
	glTranslated(-20.0, 0.0, -80.0);
	Keep();
	glPopMatrix();

	// Gatehouse
	glPushMatrix();
	glTranslated(-2.0, 0.0, 53.0);
	Gatehouse();
	glPopMatrix();
}

// Draws a single tower of the castle
void Geometry::Tower()
{
	glPushMatrix();

	SetMaterial(STONE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stone_large);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslated(0.0, 40.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);

	// Start with the base cylinder
	gluCylinder(cylinder, 10.0, 10.0, 40.0, 12, 12);
	gluDisk(disk, 0.0, 10.0, 12, 12);

	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 41.5, 0.0);

	// Add the jagged edge
	for (int i = 0; i < 6; i++)
	{
		glPushMatrix();
		glRotated(i*60, 0.0, 1.0, 0.0);
		glTranslated(8.5, 0.0, 0.0);
		Block(3.0);
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Draws a single wall of the castle
void Geometry::Wall(double length)
{
	glPushMatrix();

	SetMaterial(STONE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stone);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Front
	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2f(length/12, 0.0);
	glVertex3d(length, 0.0, 0.0);
	glTexCoord2f(length/12, 3.0);
	glVertex3d(length, 25.0, 0.0);
	glTexCoord2f(0.0, 3.0);
	glVertex3d(0.0, 25.0, 0.0);
	glEnd();

	// Back
	glNormal3d(0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, -6.0);
	glTexCoord2f(length/12, 0.0);
	glVertex3d(length, 0.0, -6.0);
	glTexCoord2f(length/12, 3.0);
	glVertex3d(length, 25.0, -6.0);
	glTexCoord2f(0.0, 3.0);
	glVertex3d(0.0, 25.0, -6.0);
	glEnd();

	// Left
	glNormal3d(-1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, -6.0);
	glVertex3d(0.0, 25.0, -6.0);
	glVertex3d(0.0, 25.0, 0.0);
	glEnd();

	// Right
	glNormal3d(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(length, 0.0, 0.0);
	glVertex3d(length, 0.0, -6.0);
	glVertex3d(length, 25.0, -6.0);
	glVertex3d(length, 25.0, 0.0);
	glEnd();

	// Top
	glNormal3d(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 25.0, 0.0);
	glTexCoord2f(length/12, 0.0);
	glVertex3d(length, 25.0, 0.0);
	glTexCoord2f(length/12, 1.0);
	glVertex3d(length, 25.0, -6.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 25.0, -6.0);
	glEnd();

	glTranslated(3.0, 26.5, -1.5);

	// Add the jagged edge
	for (double i = 0; i < length - 3.0; i += 6.0)
	{
		Block(3.0);
		glTranslated(6.0, 0.0, 0.0);
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// Draws a window
void Geometry::Window()
{
	glPushMatrix();

	SetMaterial(WINDOW);

	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(4.0, 0.0, 0.0);
	glVertex3d(4.0, 10.0, 0.0);
	glVertex3d(0.0, 10.0, 0.0);
	glEnd();

	SetMaterial(STONE);

	glTranslated(2.0, -2.0, 0.0);
	glScaled(1.5, 1.0, 1.0);
	Block(4.0);

	glPopMatrix();
}

// Draws the keep of the castle
void Geometry::Keep()
{
	glPushMatrix();

	glTranslated(0.0, 0.04, 0.0);

	SetMaterial(STONE);

	// Start with the basic shape
	glTranslated(0, 20, 0);
	Block(40);
	glTranslated(40, 0, 0);
	Block(40);
	glTranslated(40, 0, 0);
	Block(40);
	glTranslated(0, 0, 40);
	Block(40);
	glTranslated(-40, 0, 0);
	Block(40);
	glTranslated(-40, 0, 0);
	Block(40);

	glPushMatrix();
	glTranslated(-20, 21.5, 18.5);

	for (double i = 0; i < 120.0; i += 6.0)
	{
		Block(3.0);
		glTranslated(0.0, 0.0, -77.0);
		Block(3.0);
		glTranslated(6.0, 0.0, 77.0);
	}

	glPopMatrix();

	glPushMatrix();
	glTranslated(-18.5, 21.5, -60);

	for (double j = 0; j < 80.0; j += 6.0)
	{
		Block(3.0);
		glTranslated(117.0, 0.0, 0.0);
		Block(3.0);
		glTranslated(-117.0, 0.0, 6.0);
	}

	glPopMatrix();

	glPushMatrix();
	
	// Draws the keep towers
	glTranslated(-20.0, -20.0, -60.0);
	Spire();
	glTranslated(120.0, 0.0, 0.0);
	Spire();
	glTranslated(0.0, 0.0, 80.0);
	Spire();
	glTranslated(-120.0, 0.0, 0.0);
	Spire();

	glPopMatrix();

	glPushMatrix();

	glTranslated(40.0, 0.0, -20.0);
	glScaled(2.0, 1.3, 2.0);
	Spire();

	glPopMatrix();

	// Draw the door
	glPushMatrix();
	glTranslated(30, -20, 21);
	Door();
	glPopMatrix();

	glPushMatrix();
	glTranslated(37.0, 70.0, 0.1);
	glScaled(2.0, 1.2, 1.0);
	Window();
	glPopMatrix();

	glPopMatrix();
}

// Draws a door
void Geometry::Door()
{
	SetMaterial(WOOD);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(20.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(20.0, 30.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 30.0, 0.0);
	glEnd();

	SetMaterial(METAL);
	
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.02);
	glVertex3d(0.0, 30.0, 0.02);
	glVertex3d(20.0, 30.0, 0.02);
	glVertex3d(20.0, 0.0, 0.02);
	glEnd();

	glBegin(GL_LINES);
	glVertex3d(10.0, 0.0, 0.02);
	glVertex3d(10.0, 30.0, 0.02);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslated(8.0, 8.0, 0.5);
	glutSolidCube(1.0);
	glTranslated(4.0, 0.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

}

// Draws a spire for the keep
void Geometry::Spire()
{
	glPushMatrix();

	SetMaterial(STONE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stone_large);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslated(0.0, 75.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);

	gluCylinder(cylinder, 10.0, 10.0, 75.0, 12, 12);

	glPopMatrix();
	glPushMatrix();

	SetMaterial(BRICK);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, brick);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslated(0.0, 75.0, 0.0);
	glRotated(270.0, 1.0, 0.0, 0.0);

	gluCylinder(cylinder, 15, 0, 30, 12, 12);
	//glutSolidCone(15.0, 30.0, 12, 12);

	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

// Draws the gatehouse of the castle
void Geometry::Gatehouse()
{
	glPushMatrix();

	Tower();
	glTranslated(12.0, 0.0, 0.0);
	Gate();
	glTranslated(28.0, 0.0, 0.0);
	Tower();

	glPopMatrix();

	glPushMatrix();

	SetMaterial(STONE);

	glTranslated(20.0, 32.0, 0.0);
	glScaled(5.0, 1.0, 1.0);
	Block(6.0);

	glPopMatrix();

	glPushMatrix();

	glTranslated(10.0, 0.0, 0.0);
	Bridge();

	glPopMatrix();

	glPushMatrix();

	SetMaterial(METAL);
	glBegin(GL_LINES);
	glVertex3d(12.0, 0.0, 38.0);
	glVertex3d(0.0, 35.0, 5.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3d(28.0, 0.0, 38.0);
	glVertex3d(40.0, 35.0, 5.0);
	glEnd();

	glPopMatrix();
}

// Draws the gate
void Geometry::Gate()
{
	glPushMatrix();

	SetMaterial(METAL);

	glTranslated(0.0, 30.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);

	for (int i = 0; i < 6; i++)
	{
		gluCylinder(cylinder, 1.0, 1.0, 30.0, 12, 12);
		glTranslated(4, 0, 0);
	}

	glPopMatrix();

	glPushMatrix();

	SetMaterial(METAL);

	glTranslated(0.0, 4.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);

	for (int j = 0; j < 7; j++)
	{
		gluCylinder(cylinder, 1.0, 1.0, 16.0, 12, 12);
		glTranslated(0.0, 4.0, 0.0);
	}

	glPopMatrix();
}

// Draws the drawbridge
void Geometry::Bridge()
{
	glPushMatrix();

	SetMaterial(WOOD);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	// Top
	glNormal3d(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.5, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(20.0, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(20.0, 0.5, 40.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 0.5, 40.0);
	glEnd();

	// Left
	glNormal3d(-1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(0.0, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(0.0, 0.5, 40.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 0.0, 40.0);
	glEnd();

	// Right
	glNormal3d(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(20.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(20.0, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(20.0, 0.5, 40.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(20.0, 0.0, 40.0);
	glEnd();

	// Front
	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, 40.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 0.5, 40.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(20.0, 0.5, 40.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(20.0, 0.0, 40.0);
	glEnd();

	// Back
	glNormal3d(0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(0.0, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(20.0, 0.5, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(20.0, 0.0, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Geometry::Block(float size)
{
	glPushMatrix();

	SetMaterial(STONE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stone);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	float d = size/2;

	glNormal3f(0.0, 0.0, -1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-d, -d, -d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(d, -d, -d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(d, d, -d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(-d, d, -d);
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-d, -d, d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(d, -d, d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(d, d, d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(-d, d, d);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-d, -d, -d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(-d, d, -d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(-d, d, d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(-d, -d, d);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(d, -d, -d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(d, d, -d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(d, d, d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(d, -d, d);
	glEnd();

	glNormal3f(0.0, -1.0, 0.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-d, -d, -d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(d, -d, -d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(d, -d, d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(-d, -d, d);
	glEnd();

	glNormal3f(0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-d, d, -d);
	glTexCoord2f(d/6, 0.0);
	glVertex3d(d, d, -d);
	glTexCoord2f(d/6, d/6);
	glVertex3d(d, d, d);
	glTexCoord2f(0.0, d/6);
	glVertex3d(-d, d, d);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
