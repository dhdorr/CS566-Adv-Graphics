#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>
#include <GL/glut.h>
#include "particleSystem.h"

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	int cloth_width;
	int cloth_height;

	ClothSystem();
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();

	vector<Vector3f> getConnectedParticles(vector<Vector3f> state, int s, bool getVelocities);

	vector<int> convertStateTo2D(int s);
	vector<int> getFlexionSprings(vector<int> coords);
	vector<int> getShearSprings (vector<int> coords);
	vector<int> getStructureSprings (vector<int> coords);
	vector<int> appendVector(vector<int> a, vector<int> b);

private:

};


#endif
