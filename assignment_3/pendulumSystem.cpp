
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
		// m_vVecState.push_back(Vector3f(cos(M_PI/4), -sin(M_PI/4), 0));
		
		temp_vecs.push_back(Vector3f(cos(M_PI) - (1.0f * i), -sin(M_PI), 0));
	}
	this->setState(temp_vecs);

}

// Particle::Particle(void) {
// 	fMass = 1.0f;
// 	vPosition = Vector3f(0);
// 	vVelocity = Vector3f(0);
// 	fSpeed = 0.0f;
// 	vForces = Vector3f(0);
// 	fRadius = 0.1f;
// 	vGravity = Vector3f(0, fMass * -9.8f, 0);
// }


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
	// cout << state.size() << endl;
	for (int p = 0; p < state.size(); p += 2) {
		Vector3f force = Vector3f(0);
		float k = 0.1f;
		int temp = 0;
		float mass = 1.0f;
		float rest_len = 1.5f;
		float dx = 0 - state[p][0];
		float dy = 0 - state[p][1];
		if (p > 0) {
			temp = p - 2;
			dx = state[temp][0] - state[p][0];
			dy = state[temp][0] - state[p][1];
		}
		

		if (abs(dx) > 6.0f) {
			dx = 6.0f;
		}
		
		if (abs(dy) > 6.0f) {
			dy = 6.0f;
		}

		float len = sqrt(dx*dx + dy*dy);
		// cout << "dx: " << dx << "| dy: " << dy << "| len: " << len << endl;


		// gravity
		force[1] += mass *  -1.0f * 9.8f;

		// viscous drag
		force[1] -= -1.0f * k * state[p + 1][1];
		force[0] += -1.0f * k * state[p + 1][0];

		// springs
		force[1] *= -1.0f * k * ((-1.0f * state[p][1]) - rest_len);
		force[0] -= (-1.0f * dx); //-1.0f * k *
		

		// cout << "gravity + drag * spring: "; force.print();

		f.push_back(state[p + 1] + force);	
		f.push_back(force);	

	}

	// // cout << state.size() << endl;
	// Vector3f force = Vector3f(0);
	// // force[0] = -0.01f * (state[0][0] - 1.5f) * state[0][0] / state[0].abs();
	// // force[1] = -0.01f * (state[0][1] - 1.5f) * state[0][1] / state[0].abs();
	// float k = 0.1f;
	// float mass = 1.0f;
	// float dx = 0 - state[0][0];
	// float dy = 0 - state[0][1];
	// float len = sqrt(dx*dx + dy*dy);

	// // gravity
	// force[1] += mass *  -1.0f * 9.8f;
	// // cout << "gravity: " << force[1] << endl;

	// // viscous drag
	// force[1] += -1.0f * k * state[1][1];
	// force[0] += -1.0f * k * state[1][0];
	// // cout << "gravity + drag: " << force[1] << endl;

	// // springs
	// force[1] *= -1.0f * k * ((-1.0f * state[0][1]) - 1.5f);
	// // force[0] += dx;
	// force[0] -= (-1.0f * dx); //-1.0f * k *
	// // force[0] += state[1][0];
	

	// cout << "gravity + drag * spring: "; force.print();

	// // if (state[0][1] < -2.0f) {
	// // 	force[1] = 0;
	// // }

	// // force[0] = 0.7 * (len - 1.5);

	// // force = -0.1f * ((state[0] - Vector3f(0)).abs() - 1.5f) * (state[0] - Vector3f(0)) / (state[0] - Vector3f(0)).abs();
	// // force[0] = -0.1f * ((state[0][0] - Vector3f(0)[0]) - 1.5f) * (state[0][0] - Vector3f(0)[0]) / (state[0][0] - Vector3f(0)[0]);
	// // force[1] = -0.1f * ((state[0][1] - Vector3f(0)[1]) - 1.5f) * (state[0][1] - Vector3f(0)[1]) / (state[0][1] - Vector3f(0)[1]);
	// // force[0] += 0.7 * (len - 1.5);
	// // force[1] -= 0.7 * (len - 1.5);
	// // force[1] += -0.001 * state[1][1];
	// // force[1] += -1.5f;
	// f.push_back(state[1] + force);	
	// f.push_back(force);	



	// // force[1] -= 1.8f;
	// // f.push_back(force);
	// // f.push_back(state[1]);

	// for(int i = 0; i < state.size(); i ++) {
	// 	// Vector3f velocity = state[i];
		
		
	// 	cout << "state: ";
	// 	state[i].print();

		
	// 	// gravitation
	// 	// force[1] += state[0][1] + 1.8f * 1.0f * -1.0f;
		
	// 	// float dx = 0 - state[i][0];
	// 	// float dy = 0 - state[i][1];

	// 	// float len = sqrt(dx*dx + dy*dy);
	// 	// force[0] = 0.7 * (len - 1.5);

	// 	// force[1] = 0.7 * (len - 1.5);
	// 	// // force[1] += -1.5f;
		

	// 	// force[2] = 0;
	// 	// // break;

	// 	// f.push_back(force);	
	// }

	// cout << endl;

	
	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	// cout << m_vVecState.size() << endl;
	vector<Vector3f> temp_vec = this->getState();
	for (int i = 0; i < m_numParticles; i++) {
		// cout << "particle draw: " << m_numParticles << endl;
		// cout << "vec state size: " << m_vVecState.size() << endl;
		// m_vVecState[i].print();
		
		Vector3f pos = temp_vec[i];//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}

}
