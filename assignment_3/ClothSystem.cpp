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
			temp_vecs.push_back(Vector3f(-2.0f + (1.5f * j), 1.0f + (0.5f * i), 0));
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

	float mass = 0.01f;
	float gravity_acceleration = -1.0f * 9.8f;
	float drag_constant = 1.0f;
	float spring_constant = 0.55f;
	float spring_dampening = 0.01f;
	float rest_length = 0.8f;

	for (int s = 0; s < state.size(); s += 2) {
		float force_y = 0;
		float force_x = 0;

		// GRAVITY
		force_y += mass * gravity_acceleration;

		// VISCOUS DRAG
		force_y += -1.0f * drag_constant * (state[s + 1][1]);
		force_x += -1.0f * drag_constant * state[s + 1][0];

		// SPRING FORCE >:(
		/*****************
		|   | 0 | 1 | 2 |
		| 0 |   |   |   |
		| 1 |   |   |   |
		| 2 |   |   |   |
		******************/

		Vector3f prev_state = Vector3f(0);
		vector<Vector3f> connected_states = getConnectedParticles(state, s);


		// cout << "\nParticle - " << s / 2 << " :: ";
		Vector3f SpringForce = Vector3f(0);
		for (int c = 0; c < connected_states.size(); c++) {
			
			SpringForce[1] += 1.0f * spring_constant * ((connected_states[c][1] - state[s][1]) - rest_length);
			SpringForce[0] += 1.0f * spring_constant * ((connected_states[c][0] - state[s][0])) * spring_dampening; 
			// force_y += 1.0f * spring_constant * ((connected_states[c][1] - state[s][1]) - rest_length) * spring_dampening;
			// force_x += 1.0f * spring_constant * ((connected_states[c][0] - state[s][0])) * spring_dampening; 
			// cout << "Spring Force: "; SpringForce.print();
		}
		force_y += SpringForce[1];
		force_x += SpringForce[0];

		// Calculate force to anchors
		if (s == 12 || s == 16 ) {
			//connected_states.push_back(Vector3f(0));
			force_x = 0;
			force_y = 0;
		} 

		// force_x = 0;
		// force_y = 0;
	

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
		vector<Vector3f> connected_states = getConnectedParticles_Show(cloth_particles, p);


		for (int c = 0; c < connected_states.size(); c++) {
			prev_particle = connected_states[c];
		
	
			Vector3f spring_position = Vector3f((prev_particle[0] + cloth_particles[p][0]) / 2, (prev_particle[1] + cloth_particles[p][1]) / 2, 0);

			float dx = prev_particle[0] - cloth_particles[p][0];
			float dy = prev_particle[1] - cloth_particles[p][1];

			float len = sqrt(pow(dx, 2) + pow(dy, 2));
			float size = 0.03f;
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

vector<Vector3f> ClothSystem::getConnectedParticles(vector<Vector3f> state, int s) {
	vector<Vector3f> connected_states;

	for (int t = 0; t < state.size(); t += 2){
		int current_index = s/2;
		int other_index = t/2;
		// if (abs(current_index - other_index) > 4) {
		// 	continue;
		// }
		if (current_index == other_index) {
			continue;
		}
		// structural and shear springs
		if (abs((current_index % 3) - (other_index % 3)) <= 1) {
			// cout << "\nHELLO!? " << "true!" << " | index: " << current_index << " | other index: " << other_index << endl; 
			connected_states.push_back(state[t]);
		}
		// flexion springs
		int test_index_s = abs(current_index - other_index);
		if (test_index_s == 2 || test_index_s == 6 || test_index_s == 8) {
			if (test_index_s == 2 && (current_index % 3 != 0 || other_index % 3 != 0) ) {
				// cout << current_index << " " << other_index << endl;
				continue;
			}
			connected_states.push_back(state[t]);
			// cout << "\nFLEXIONS " << s << " | index: " << current_index << " | other index: " << other_index << endl; 
		}
	}

	return connected_states;
}

vector<Vector3f> ClothSystem::getConnectedParticles_Show(vector<Vector3f> state, int s) {
	vector<Vector3f> connected_states;

	for (int t = 0; t < state.size(); t += 2){
		int current_index = s/2;
		int other_index = t/2;
		// if (abs(current_index - other_index) > 4) {
		// 	continue;
		// }
		if (current_index == other_index) {
			continue;
		}
		// structural and shear springs
		if (abs((current_index % 3) - (other_index % 3)) <= 1) {
			// cout << "\nHELLO!? " << "true!" << " | index: " << current_index << " | other index: " << other_index << endl; 
			connected_states.push_back(state[t]);
		}
	}

	return connected_states;
}

