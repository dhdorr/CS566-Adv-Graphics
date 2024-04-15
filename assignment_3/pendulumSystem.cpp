
#include "pendulumSystem.h"
//#include "springs.h"
#include <iostream>

#define NUM_OBJECTS 	2
#define NUM_SPRINGS 	1
#define SPRING_K 		1000
#define SPRING_D		100

//Particle Objects[2];
//Spring Springs[NUM_SPRINGS];


PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	vector<Vector3f> temp_vecs;
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {
		
		// for this system, we care about the position and the velocity
		temp_vecs.push_back(Vector3f(cos(M_PI) - (1.0f * i), -sin(M_PI), 0));
		temp_vecs.push_back(Vector3f(0, 0, 0));

	}

	this->setState(temp_vecs);
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	float mass = 0.01f;
	float gravity_acceleration = -1.0f * 9.8f;
	float drag_constant = 0.1f;
	float spring_constant = 100.0f;
	float spring_dampening = 0.01f;
	float rest_length = 0.5f;

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
		force_y += 1.0f * spring_constant * ((prev_state[1] - state[s][1]) - rest_length) * spring_dampening;
		force_x += 1.0f * spring_constant * ((prev_state[0] - state[s][0])) * spring_dampening; 
	

		// push back velocity then sum of forces
		f.push_back(state[s+1] + Vector3f(force_x, force_y, 0));
		f.push_back(Vector3f(force_x, force_y, 0));
	}

	
	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	vector<Vector3f> pendulum_particles = this->getState();
	// cout << "draw vecs: " << cloth_particles.size() << endl;

	for (int p = 0; p < pendulum_particles.size(); p += 2) {
		cout << "\nDraw STATE: " << p << endl;
		pendulum_particles[p].print();
		// pendulum_particles[p + 1].print();

		//  position of particle i.
		glPushMatrix();
		glTranslatef(pendulum_particles[p][0], pendulum_particles[p][1], pendulum_particles[p][2]);
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();

		// draw line
		Vector3f prev_particle = Vector3f(0);
		if (p > 0) {
			prev_particle = pendulum_particles[p - 2];
		}
		Vector3f spring_position = Vector3f((prev_particle[0] + pendulum_particles[p][0]) / 2, (prev_particle[1] + pendulum_particles[p][1]) / 2, 0);
		cout << "\nSpring position: " << p << endl;
		spring_position.print();

		float dx = prev_particle[0] - pendulum_particles[p][0];
		float dy = prev_particle[1] - pendulum_particles[p][1];

		float len = sqrt(pow(dx, 2) + pow(dy, 2));
		cout << len << endl;
		float size = 0.1f;
		float radians = atan2(prev_particle[0] - pendulum_particles[p][0], prev_particle[1] - pendulum_particles[p][1]);
		float degrees = -1 * radians * 180.0f / M_PI;

		glPushMatrix();
		glTranslatef(spring_position[0], spring_position[1], spring_position[2]);
		glRotatef(degrees, 0, 0, 1);
		glScalef(1, len / size, 1);
		glutSolidCube(size);
		glPopMatrix();

	}

}
