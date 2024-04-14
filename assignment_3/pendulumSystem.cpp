
#include "pendulumSystem.h"
#include "springs.h"
#include <iostream>

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	test_velocity = 0;
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {
		
		// for this system, we care about the position and the velocity
		m_vVecState.push_back(Vector3f(cos(M_PI/4), -sin(M_PI/4), 0));
		test_velocity = Vector3f(0);
	}
}

TestSpring::TestSpring(int numParticles) {

}

TestObject::TestObject(int numParticles) {
	
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	cout << "state: ";
	state[0].print();
	// YOUR CODE HERE
	Vector3f force = Vector3f(0);
	for(int i = 0; i < state.size(); i ++) {

		
		// gravitation
		force[1] += 9.8f * 1.0f * -1.0f;

		// viscous drag
		// force -= Vector3f(0.01f, 0.01f, 0.01f);

		
		float dx = 0 - state[0][0];
		float dy = 0 - state[0][1];

		float len = sqrt(dx*dx + dy*dy);
		force[0] = 1.7 * (len - 1.5);


		force[1] = 1.7 * (len - 1.5);

		force[2] = 0;

		f.push_back(force);	
		
	
	}


	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		m_vVecState[i].print();
		Vector3f pos =  Vector3f(m_vVecState[i][0], m_vVecState[i][1], 0) ;//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
