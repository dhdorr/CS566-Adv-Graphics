#include "ClothSystem.h"
#include <iostream>

//TODO: Initialize here
ClothSystem::ClothSystem()
{
	int i = 0;
	int j = 0;
	vector<Vector3f> temp_vecs;

	// fill in code for initializing the state based on the number of particles
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			temp_vecs.push_back(Vector3f(-1.0f + (0.5f * j), 1.0f + (0.5f * i), 0));
			temp_vecs.push_back(Vector3f(0, 0, 0));
		}
		// temp_vecs.push_back(Vector3f(-1.0f + (0.5f * i), 1.0f - (0.5f), 0));
		// temp_vecs.push_back(Vector3f(0, 0, 0));
	}

	m_numParticles = i * j;

	this->setState(temp_vecs);
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	float mass = 0.1f;
	float gravity_acceleration = -1.0f * 9.8f;
	float drag_constant = 5.5f;
	float spring_constant = 1000.0f;
	float spring_dampening = 0.01f;
	float rest_length = 0.3f;

	for (int s = 0; s < state.size(); s += 2) {
		Vector3f prev_state = Vector3f(0);
		if (s > 0) {
			prev_state = state[s - 2];
		}

		float force_y = 0;
		float force_x = 0;

		// GRAVITY
		force_y += mass * gravity_acceleration;

		// VISCOUS DRAG
		force_y += -1.0f * drag_constant * state[s + 1][1];
		force_x += -1.0f * drag_constant * state[s + 1][0];

		// SPRING FORCE >:(
		/*****************
		|   | 0 | 1 | 2 |
		| 0 |   |   |   |
		| 1 |   |   |   |
		| 2 |   |   |   |
		******************/
	
		force_y += 1.0f * spring_constant * ((prev_state[1] - state[s][1]) - rest_length) * spring_dampening;
		force_x += 1.0f * spring_constant * ((prev_state[0] - state[s][0])) * spring_dampening; 

		// Calculate force to 2nd anchor
		if (s >= state.size() - 2) {
			force_y += -1.0f * spring_constant * ((state[s][1] - 0) - rest_length) * spring_dampening;
			force_x += -1.0f * spring_constant * ((state[s][0] - 2.0f)) * spring_dampening; 
		} 
	

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

	for (int p = 0; p < cloth_particles.size(); p += 2) {
		//  position of particle i.
		glPushMatrix();
		glTranslatef(cloth_particles[p][0], cloth_particles[p][1], cloth_particles[p][2]);
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();

		// draw line
		Vector3f prev_particle = Vector3f(0);
		if (p > 0) {
			prev_particle = cloth_particles[p - 2];
		}
		Vector3f spring_position = Vector3f((prev_particle[0] + cloth_particles[p][0]) / 2, (prev_particle[1] + cloth_particles[p][1]) / 2, 0);

		float dx = prev_particle[0] - cloth_particles[p][0];
		float dy = prev_particle[1] - cloth_particles[p][1];

		float len = sqrt(pow(dx, 2) + pow(dy, 2));
		float size = 0.1f;
		float radians = atan2(dx, dy);
		float degrees = -1 * radians * 180.0f / M_PI;

		glPushMatrix();
		glTranslatef(spring_position[0], spring_position[1], spring_position[2]);
		glRotatef(degrees, 0, 0, 1);
		glScalef(1, len / size, 1);
		glutSolidCube(size);
		glPopMatrix();

		// Calculate spring to 2nd anchor
		if (p >= cloth_particles.size() - 2) {

			Vector3f spring_position = Vector3f((cloth_particles[p][0] + 2.0f) / 2, (cloth_particles[p][1]) / 2, 0);

			float dx = cloth_particles[p][0] - 2.0f;
			float dy = cloth_particles[p][1];

			float len = sqrt(pow(dx, 2) + pow(dy, 2));
			float size = 0.1f;
			float radians = atan2(dx, dy);
			float degrees = -1 * radians * 180.0f / M_PI;

			glPushMatrix();
			glTranslatef(spring_position[0], spring_position[1], spring_position[2]);
			glRotatef(degrees, 0, 0, 1);
			glScalef(1, len / size, 1);
			glutSolidCube(size);
			glPopMatrix();
		}
	}


}

