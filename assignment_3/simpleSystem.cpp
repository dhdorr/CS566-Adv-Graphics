
#include "simpleSystem.h"
#include <iostream>

using namespace std;

SimpleSystem::SimpleSystem()
{
	// m_vVecState.push_back(Vector3f(0.4, 0.4, 0));
	m_vVecState.push_back(Vector3f(0.6f, 0, 0));
	// m_vVecState.push_back(Vector3f(0.0, 0, 0));
	m_numParticles = 1;

}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
	for(int i = 0; i < state.size(); i ++) {
	
		f.push_back(Vector3f(-1.0f * state[i][1], state[i][0], 0));		
	}

	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
		Vector3f pos ;//YOUR PARTICLE POSITION
		pos[0] = m_vVecState[0][0];
		pos[1] = m_vVecState[0][1];
		pos[2] = 0;
	  glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
}
