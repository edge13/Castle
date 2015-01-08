// **********************************
// File: geometry.h
// Submitted as part of Project 4 for EECS 672
// May 9, 2007
// By Joel Angelone, KUID 1311419
// **********************************

#include "BMPLoader.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

// Enumeration of material types
#define STONE	1
#define BRICK	2
#define METAL	3
#define WOOD	4
#define GRASS	5
#define WATER	6
#define FOREST	7
#define FLAME	8
#define WINDOW	9
#define CLOUD	10

struct Particle
{
	float x, y, z;
	float r, g, b, a;

	float xbias, zbias;

	int lifespan;
	bool alive;
};

// Geometry class is responsible for rendering all models
class Geometry
{
	public:

		// Constructor/Destructor
		Geometry();
		~Geometry();

		void LoadTextures();

		// Sets the current material properties
		void SetMaterial(int type);

		// Basic objects
		void Ground();
		void Moat();
		void Forest();
		void Castle();
		void Clouds();
		void Torches();

		// Mirror transformation and matrix math
		void Mirror(double x, double y, double z, double nx, double ny, double nz);
		void Tensor(double x1, double y1, double z1, double x2, double y2, double z2, double m[9]);
		void Subtract(double m1[9], double m2[9], double result[9]);
		void Subtract(double &x1, double &y1, double &z1, double x2, double y2, double z2);
		void Multiply(double m[9], double &x, double &y, double &z);
		void Multiply(double m[9], int scalar);

		void Block(float size);

		void UpdateParticles();
		void SpawnParticle();

	protected:

		GLUquadricObj *cylinder;
		GLUquadricObj *disk;

		// Small objects called heirarchically
		void Tree(double angle);
		void Tower();
		void Wall(double length);
		void Torch();
		void Door();
		void Spire();
		void Keep();
		void Gate();
		void Bridge();
		void Gatehouse();
		void Window();

		//void Block(float size);

		GLuint grass;
		GLuint stone;
		GLuint water;
		GLuint wood;
		GLuint brick;
		GLuint stone_large;

		Particle particles[5000];
		int num_particles;
};

#endif
