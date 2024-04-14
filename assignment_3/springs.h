#ifndef SPRING_H
#define SPRING_H

#include <vector>
#include <vecmath.h>

using namespace std;

typedef struct _Spring {
    int End1;
    int End2;
    float k;
    float d;
    float InitialLength;

} Spring, *pSpring;

class Particle {
public:
    float fMass;
    Vector3f vPosition;
    Vector3f vVelocity;
    float fSpeed;
    Vector3f vForces;
    float fRadius;
    Vector3f vGravity;

    bool blocked;
    float fLength = 1.5f;
    Vector3f vSprings;

    Particle(void);
    void CalcLoads(void);
    void UpdateBodyEuler(float dt);
    //void Draw(void);

};

#endif