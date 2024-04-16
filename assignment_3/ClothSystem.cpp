#include "ClothSystem.h"
#include <iostream>

// vector<int> convertStateTo2D(int s, int width, int height);
// vector<int> getFlexionSprings(vector<int> coords, int width, int height);
// vector<int> getShearSprings (vector<int> coords, int width, int height);
// vector<int> getStructureSprings (vector<int> coords, int width, int height);
// vector<int> appendVector(vector<int> a, vector<int> b);

//TODO: Initialize here
ClothSystem::ClothSystem()
{
	cloth_height = 4;
	cloth_width = 4;

	int i = 0;
	int j = 0;
	vector<Vector3f> temp_vecs;

	// fill in code for initializing the state based on the number of particles
	for (i = 0; i < cloth_height; i++) {
		for (j = 0; j < cloth_width; j++) {
			temp_vecs.push_back(Vector3f(-2.0f + (1.5f * j), 1.0f + (0.5f * i), 0));
			temp_vecs.push_back(Vector3f(0, 0, 0));
		}
	}

	m_numParticles = i * j;

	this->setState(temp_vecs);
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	float mass = 0.001f;
	float gravity_acceleration = -1.0f * 9.8f;
	float drag_constant = 0.01f;
	float spring_constant = 1.8f;
	float spring_dampening = 0.005f;
	float rest_length = 0.5f;

	for (int s = 0; s < state.size(); s += 2) {
		float force_y = 0;
		float force_x = 0;

		// GRAVITY
		force_y += mass * gravity_acceleration;

		// // VISCOUS DRAG
		// force_y += -1.0f * drag_constant * (state[s + 1][1]);
		// force_x += -1.0f * drag_constant * state[s + 1][0];

		// SPRING FORCE >:(
		/*****************
		|   | 0 | 1 | 2 |
		| 0 |   |   |   |
		| 1 |   |   |   |
		| 2 |   |   |   |
		******************/

		Vector3f prev_state = Vector3f(0);
		vector<Vector3f> connected_states = getConnectedParticles(state, s, false);
		vector<Vector3f> connected_velocities = getConnectedParticles(state, s, true);


		// cout << "\nParticle - " << s / 2 << " :: ";
		Vector3f SpringForce = Vector3f(0);
		for (int c = 0; c < connected_states.size(); c++) {
			float dx = connected_states[c][0] - state[s][0];
			float dy = connected_states[c][1] - state[s][1];
			float len = sqrt(dx * dx + dy * dy);
			
			// SpringForce[1] += 1.0f * spring_constant * ((connected_states[c][1] - state[s][1]) - rest_length) * spring_dampening;
			SpringForce[1] += 1.0f * spring_constant * (len - rest_length) * spring_dampening * (dy / len);
			SpringForce[0] *= (dy / len);
			SpringForce[0] += (spring_constant * (len - rest_length)) * spring_dampening * (dx / len); 
			SpringForce[0] *= (dx / len);
			// force_y += 1.0f * spring_constant * ((connected_states[c][1] - state[s][1]) - rest_length) * spring_dampening;
			// force_x += 1.0f * spring_constant * ((connected_states[c][0] - state[s][0])) * spring_dampening; 
			// cout << "Spring Force: "; SpringForce.print();

			// VISCOUS DRAG
			force_y += 1.0f * drag_constant * (state[s + 1][1] - connected_velocities[c][1]);
			force_x += -1.0f * drag_constant * state[s + 1][0] - connected_velocities[c][0];
		}
		force_y += SpringForce[1];
		force_x += SpringForce[0];

		Vector3f velocity = state[s+1];
		velocity += Vector3f(force_x, force_y, 0);

		// Calculate force to anchors
		if (s == (12) * 2 || s == 15 * 2) {
			//connected_states.push_back(Vector3f(0));
			// force_x = 0;
			// force_y = 0;
			velocity = Vector3f(0);
		} 


		// force_x = 0;
		// force_y = 0;
	

		// push back velocity then sum of forces
		f.push_back(velocity);
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
		vector<Vector3f> connected_states = getConnectedParticles(cloth_particles, p, false);

		// cout << "current: "; cloth_particles[p].print();
		for (int c = 0; c < connected_states.size(); c++) {
			prev_particle = connected_states[c];
			// prev_particle.print();
		
	
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

vector<Vector3f> ClothSystem::getConnectedParticles(vector<Vector3f> state, int s, bool getVelocities) {
	vector<Vector3f> connected_states;
	vector<int> connected_indicis;

	// TODO: make width and height global
	vector<int> partical_coords = convertStateTo2D(s/2);
	vector<int> flexions = getFlexionSprings(partical_coords);
	vector<int> shears = getShearSprings(partical_coords);
	vector<int> structures = getStructureSprings(partical_coords);

	connected_indicis = appendVector(connected_indicis, flexions);
	connected_indicis = appendVector(connected_indicis, shears);
	connected_indicis = appendVector(connected_indicis, structures);

	// cout << "\n" << s << " SIZE: " << connected_indicis.size() << endl; 
	for (int i = 0; i < connected_indicis.size(); i++) {
		if (getVelocities) {
			connected_states.push_back(state[(connected_indicis[i] * 2) + 1]);
		} else {
			connected_states.push_back(state[connected_indicis[i] * 2]);
		}
		
	}
	

	return connected_states;
}


// returns a vector containing x and y coordinates of current particle
vector<int> ClothSystem::convertStateTo2D(int s) {
	int count = 0;
	for(int outer = 0; outer < cloth_height; outer++) {
		for(int inner = 0; inner < cloth_width; inner++) {
			if (count == s) {
				vector<int> coords;
				coords.push_back(inner);
				coords.push_back(outer);
				// cout << "\n coords: " << coords[0] << ", " << coords[1] << endl;
				return coords;
			}
			count ++;
		}
	}
	return vector<int>{0, 0};
}

// using x and y coordinates of particle, build flexion list as cycle (... last -> first)
// returns a vector containing indicis of flexions for current state
vector<int> ClothSystem::getFlexionSprings(vector<int> coords) {
	vector<int> flexion_indicis;
	for(int outer = 0; outer < cloth_height; outer++) {
		for(int inner = 0; inner < cloth_width; inner++) {
			if (outer == coords[1] - 2) {
				if (inner == coords[0]) {
					flexion_indicis.push_back((outer * cloth_width) + inner);
				}
			} else if (outer == coords[1] + 2) {
				if (inner == coords[0]) {
					flexion_indicis.push_back((outer * cloth_width) + inner);
				}
			} else if (outer == coords[1]) {
				if (inner == coords[0] - 2) {
					flexion_indicis.push_back((outer * cloth_width) + inner);
				} else if (inner == coords[0] + 2) {
					flexion_indicis.push_back((outer * cloth_width) + inner);
				}
			} 
		}
	}

	// if(coords[0] == 0 && coords[1] == 3) {
	// 	cout << "num flexions: " << flexion_indicis.size() << " ||";
	// 	for (int f = 0; f < flexion_indicis.size(); f++) {
	// 		cout << flexion_indicis[f] << ", ";
	// 	}
	// 	cout << endl;
	// }

	return flexion_indicis;
}

vector<int> ClothSystem::getShearSprings (vector<int> coords) {
	vector<int> shear_indicis;
	for(int outer = 0; outer < cloth_height; outer++) {
		for(int inner = 0; inner < cloth_width; inner++) {
			if (outer == coords[1] - 1) {
				if (inner == coords[0] + 1) {
					shear_indicis.push_back((outer * cloth_width) + inner);
				} else if (inner == coords[0] - 1) {
					shear_indicis.push_back((outer * cloth_width) + inner);
				}
			} else if (outer == coords[1] + 1) {
				if (inner == coords[0] + 1) {
					shear_indicis.push_back((outer * cloth_width) + inner);
				} else if (inner == coords[0] - 1) {
					shear_indicis.push_back((outer * cloth_width) + inner);
				}
			}
		}
	}

	// if(coords[0] == 0 && coords[1] == 3) {
	// 	cout << "num shears: " << shear_indicis.size() << " ||";
	// 	for (int f = 0; f < shear_indicis.size(); f++) {
	// 		cout << shear_indicis[f] << ", ";
	// 	}
	// 	cout << endl;
	// }

	return shear_indicis;
}

vector<int> ClothSystem::getStructureSprings (vector<int> coords) {
	vector<int> structure_indicis;
	for(int outer = 0; outer < cloth_height; outer++) {
		for(int inner = 0; inner < cloth_width; inner++) {
			if (outer == coords[1] - 1) {
				if (inner == coords[0]) {
					structure_indicis.push_back((outer * cloth_width) + inner);
				}
			} else if (outer == coords[1] + 1) {
				if (inner == coords[0]) {
					structure_indicis.push_back((outer * cloth_width) + inner);
				}
			} else if (outer == coords[1]) {
				if (inner == coords[0] - 1) {
					structure_indicis.push_back((outer * cloth_width) + inner);
				} else if (inner == coords[0] + 1) {
					structure_indicis.push_back((outer * cloth_width) + inner);
				}
			}
		}
	}

	// if(coords[0] == 0 && coords[1] == 3) {
	// 	cout << "num structures: " << structure_indicis.size() << " ||";
	// 	for (int f = 0; f < structure_indicis.size(); f++) {
	// 		cout << structure_indicis[f] << ", ";
	// 	}
	// 	cout << endl;
	// }

	return structure_indicis;
}


vector<int> ClothSystem::appendVector(vector<int> a, vector<int> b) {
	for (int i = 0; i < b.size(); i++) {
		a.push_back(b[i]);
	}

	return a;
}