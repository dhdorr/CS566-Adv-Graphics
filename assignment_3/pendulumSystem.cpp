
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
		temp_vecs.push_back(Vector3f(cos(M_PI) - (1.0f * i), -sin(M_PI), 0));

	}
	this->setState(temp_vecs);

}


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
		float initial_x = 0;
		float initial_y = 0;
		float dx = initial_x - state[p][0];
		float dy = initial_y - state[p][1];
		if (p > 0) {
			temp = p - 2;
			initial_x = state[0][0];
			initial_y = state[0][1];
			dx = initial_x - state[p][0];
			dy = -1 * (initial_y - state[p][1]);
		}
		

		float len = sqrt(dx*dx + dy*dy);
		// cout << "dx: " << dx << "| dy: " << dy << "| len: " << len << endl;


		// gravity
		force[1] += mass *  -1.0f * 9.8f;

		// viscous drag
		force[1] -= -1.0f * k * state[p + 1][1];
		force[0] += -1.0f * k * state[p + 1][0];

		// springs
		// force[1] *= -1.0f * k * (initial_y + (-1.0f * state[p][1]) - rest_len);
		force[1] *= -1.0f * k * -1 * (initial_y - dy - rest_len);
		force[0] -= (-1.0f * dx); //-1.0f * k *
		

		// cout << "gravity + drag * spring: "; force.print();

		f.push_back(state[p + 1] + force);	
		f.push_back(force);	

	}

	
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

		Vector3f pos = temp_vec[i];
		// cout << "pos " << i << ": "; pos.print();

		// line
		float radians = atan2(pos[0], pos[1]);
		float degrees = radians * 180.0f / M_PI;
		float size = 0.1f;
		float initial_x = 0;
		float initial_y = 0;
		float dx = initial_x - pos[0];
		float dy = initial_y - pos[1];
		int temp = 0;
		if (i > 0) {
			temp = i - 1;
			initial_x = 0 - temp_vec[temp][0];
			initial_y = 0 - temp_vec[temp][1];
			dx = initial_x - pos[0];
			dy = initial_y - pos[1];
		}
		float len = sqrt(dx*dx + dy*dy);
		// cout << i << " len: " << len << endl;
		radians = atan2(dx, dy);
		degrees = radians * 180.0f / M_PI;
		cout << "rotation degrees: " << degrees << endl;
		
		glPushMatrix();
		// glTranslatef(pos[0], pos[1], pos[2] );
		glTranslatef(initial_x - (-1 * dx / 2.0f), initial_y - (-1 * dy / 2.0f), pos[2] );
		glRotatef(-1 * degrees, 0, 0, 1);
		glScalef(1, len / size, 1);
		glutSolidCube(size);
		glPopMatrix();
		
		//  position of particle i. YOUR CODE HERE
		glPushMatrix();

		glTranslatef(initial_x - (-1 * dx), initial_y - (-1 * dy), pos[2] );
		// glTranslatef(0 - pos[0], 0 - pos[1], pos[2] );
		
		// glTranslatef(initial_x + (-1 * dx), initial_y + (-1 * dy), pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}

}
