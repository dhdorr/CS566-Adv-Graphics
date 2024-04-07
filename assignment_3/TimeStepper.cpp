#include "TimeStepper.hpp"

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
}

// RK4 is given to you
void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{	
	vector<Vector3f> X1 = particleSystem->getState();	
	vector<Vector3f> f1 = particleSystem->evalF(X1);
	if (f1.size() >= 1) {		
		vector<Vector3f> X2;
		for (unsigned int i = 0; i < 2 * particleSystem->m_numParticles; i++)
		{
			X2.push_back(X1[i] + (stepSize * f1[i] / 2.0));
		}		
		vector<Vector3f> f2 = particleSystem->evalF(X2);		
		vector<Vector3f> X3;
		for (unsigned int i = 0; i < 2 * particleSystem->m_numParticles; i++)
		{
			X3.push_back(X1[i] + (stepSize * f2[i] / 2.0));
		}		
		vector<Vector3f> f3 = particleSystem->evalF(X3);		
		vector<Vector3f> X4;
		for (unsigned int i = 0; i < 2 * particleSystem->m_numParticles; i++)
		{
			X4.push_back(X1[i] + (stepSize * f3[i]));
		}		
		vector<Vector3f> f4 = particleSystem->evalF(X4);		
		for (unsigned int i = 0; i < 2 * particleSystem->m_numParticles; i++)
		{
			X1[i] = X1[i] + stepSize * ((f1[i] + f2[i] * 2 + f3[i] * 2 + f4[i]) / 6);
		}
	}
	particleSystem->setState(X1);
}


