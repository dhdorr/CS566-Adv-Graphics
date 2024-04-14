#ifndef SPRING_H
#define SPRING_H

#include <vector>
#include <vecmath.h>

using namespace std;

class TestSpring
{
public:

	TestSpring(int numParticles=0);

	int End1;
    int End2;
    float k;
    float d;
    float InitialLength;
	
	
};

class TestObject
{
public:

	TestObject(int numParticles=0);

	Vector3f vPosition;
    Vector3f vVelocity;
    Vector3f vSprings;
	
	
};

#endif