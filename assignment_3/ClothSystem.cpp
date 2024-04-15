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
		temp_vecs.push_back(Vector3f(0, 0, 0));
		// temp_vecs.push_back(Vector3f(-1.0f + (0.5f * i), 1.0f, 0));
	}
	for ( int i = 0; i < m_numParticles; i++) {
		// temp_vecs.push_back(Vector3f(0, 0, 0));
	}


	this->setState(temp_vecs);
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	float mass = 0.01f;
	float gravity_acceleration = -1.0f * 9.8f;
	float drag_constant = 0.1f;
	float spring_constant = 10.1f;
	float spring_dampening = 0.01f;
	float rest_length = 1.5f;

	for (int s = 0; s < state.size(); s += 2) {
		Vector3f prev_state = Vector3f(0);
		if (s > 0) {
			prev_state = state[s - 2];
		}

		// cout << "STATE: " << s << endl;
		// state[s].print();
		// state[s + 1].print();

		float force_y = 0;
		float force_x = 0;

		// GRAVITY
		force_y += mass * gravity_acceleration;

		// VISCOUS DRAG
		force_y += -1.0f * drag_constant * state[s + 1][1];
		force_x += -1.0f * drag_constant * state[s + 1][0];

		// SPRING FORCE >:(
		force_y += 1.0f * spring_constant * ((0 - state[s][1]) - rest_length) * spring_dampening;
		force_x += 1.0f * spring_constant * ((0 - state[s][0])) * spring_dampening; 
	

		// push back velocity then sum of forces
		f.push_back(state[s+1] + Vector3f(force_x, force_y, 0));
		f.push_back(Vector3f(force_x, force_y, 0));
	}

	
	return f;
}

///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
	vector<Vector3f> cloth_particles = this->getState();
	// cout << "draw vecs: " << cloth_particles.size() << endl;

	for (int p = 0; p < cloth_particles.size(); p += 2) {
		cout << "\nDraw STATE: " << p << endl;
		cloth_particles[p].print();
		cloth_particles[p + 1].print();
		//  position of particle i.
		glPushMatrix();
		glTranslatef(cloth_particles[p][0], cloth_particles[p][1], cloth_particles[p][2]);
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}


}

