#include "ClothSystem.h"
#include <iostream>

//TODO: Initialize here
ClothSystem::ClothSystem()
{
	m_numParticles = 4;
	vector<Vector3f> temp_vecs;

	// fill in code for initializing the state based on the number of particles
	for ( int i = 0; i < m_numParticles; i++) {
		temp_vecs.push_back(Vector3f(-1.0f + (0.5f * i), 1.0f, 0));
	}
	for ( int i = 0; i < m_numParticles; i++) {
		temp_vecs.push_back(Vector3f(0, 0, 0));
	}


	this->setState(temp_vecs);
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	for (int s = 0; s < state.size(); s += 2) {
		f.push_back(Vector3f(0));
		f.push_back(Vector3f(0));
	}

	
	return f;
}

///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
	vector<Vector3f> cloth_particles = this->getState();

	for (int p = 0; p < m_numParticles; p++) {
		//  position of particle i.
		glPushMatrix();

		glTranslatef(cloth_particles[p][0], cloth_particles[p][1], cloth_particles[p][2]);
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}


}

