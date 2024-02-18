#include "surf.h"
#include "extra.h"
using namespace std;

namespace
{
    
    // We're only implenting swept surfaces where the profile curve is
    // flat on the xy-plane.  This is a check function.
    static bool checkFlat(const Curve &profile)
    {
        for (unsigned i=0; i<profile.size(); i++)
            if (profile[i].V[2] != 0.0 ||
                profile[i].T[2] != 0.0 ||
                profile[i].N[2] != 0.0)
                return false;
    
        return true;
    }
}

Surface makeSurfRev(const Curve &profile, unsigned steps)
{
    Surface surface;
    
    if (!checkFlat(profile))
    {
        cerr << "surfRev profile curve must be flat on xy plane." << endl;
        exit(0);
    }

    // TODO: Here you should build the surface.  See surf.h for details.
    
    cerr << "\t>>> makeSurfRev called (but not implemented).\n\t>>> Returning empty surface." << endl;
 
    return surface;
}

Vector3f transformProfilePoint(const Vector3f &profilePoint, const Vector3f &sweepPos, const Vector3f &sweepTangent, const Vector3f &sweepNormal, const Vector3f &sweepBinormal) {
    // Create a rotation matrix from the sweep curve's frame
    Matrix3f rotationMatrix;
    rotationMatrix.setCol(0, sweepNormal);
    rotationMatrix.setCol(1, sweepBinormal);
    rotationMatrix.setCol(2, sweepTangent);

    // Transform the profile point using the rotation matrix and translate it
    Vector3f transformedPoint = rotationMatrix * profilePoint + sweepPos;

    return transformedPoint;
}

Vector3f calculateNormal(const CurvePoint &profilePoint, const Vector3f &sweepTangent, const Vector3f &sweepNormal, const Vector3f &sweepBinormal) {
    // Since the profile is on the XY plane, its normal would be in the Z direction (0, 0, 1)
    Vector3f profileNormal(0, 0, 1); // Assuming Z is up

    // Create a rotation matrix from the sweep curve's frame
    Matrix3f rotationMatrix;
    rotationMatrix.setCol(0, sweepNormal);
    rotationMatrix.setCol(1, sweepBinormal);
    rotationMatrix.setCol(2, sweepTangent);

    // Rotate the profile normal
    Vector3f transformedNormal = rotationMatrix * profileNormal;

    return transformedNormal.normalized();
}


Surface makeGenCyl(const Curve &profile, const Curve &sweep )
{
    Surface surface;

    if (!checkFlat(profile))
    {
        cerr << "genCyl profile curve must be flat on xy plane." << endl;
        //exit(0);
    }

    // TODO: Here you should build the surface.  See surf.h for details.
    //
    
    // For each point on the sweep curve
    for (size_t i = 0; i < sweep.size(); ++i) {
        // Position and orientation for this section of the sweep
        Vector3f sweepPos = sweep[i].V;
        Vector3f sweepTangent = sweep[i].T;
        Vector3f sweepNormal = sweep[i].N;
        Vector3f sweepBinormal = sweep[i].B;

        // For each point in the profile curve
        for (size_t j = 0; j < profile.size(); ++j) {
            // Transform profile point to the current position on the sweep curve
            // This involves translating and rotating the profile points
            Vector3f transformedVertex = transformProfilePoint(profile[j].V, sweepPos, sweepTangent, sweepNormal, sweepBinormal);
            surface.VV.push_back(transformedVertex);

            // Calculate normals for each vertex
            Vector3f normal = calculateNormal(profile[j], sweepTangent, sweepNormal, sweepBinormal);
            surface.VN.push_back(normal);
        }
    }

    // Generate faces
    unsigned profileSize = profile.size();
    for (size_t sweepIndex = 0; sweepIndex < sweep.size() - 1; ++sweepIndex) {
        for (size_t profileIndex = 0; profileIndex < profileSize - 1; ++profileIndex) {
            unsigned curr = sweepIndex * profileSize + profileIndex;
            unsigned nextProfile = curr + 1;
            unsigned nextSweep = curr + profileSize;
            unsigned diagonal = nextSweep + 1;

            // Add two faces for each quad
            surface.VF.push_back(Tup3u(curr, nextProfile, nextSweep));
            surface.VF.push_back(Tup3u(nextProfile, diagonal, nextSweep));
        }
    }

    return surface;

    cerr << "\t>>> makeGenCyl called (but not implemented).\n\t>>> Returning empty surface." <<endl;

    return surface;
}

void drawSurface(const Surface &surface, bool shaded)
{
    // Save current state of OpenGL
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    if (shaded)
    {
        // This will use the current material color and light
        // positions.  Just set these in drawScene();
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // This tells openGL to *not* draw backwards-facing triangles.
        // This is more efficient, and in addition it will help you
        // make sure that your triangles are drawn in the right order.
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {        
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glColor4f(0.4f,0.4f,0.4f,1.f);
        glLineWidth(1);
    }

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<surface.VF.size(); i++)
    {
        glNormal(surface.VN[surface.VF[i][0]]);
        glVertex(surface.VV[surface.VF[i][0]]);
        glNormal(surface.VN[surface.VF[i][1]]);
        glVertex(surface.VV[surface.VF[i][1]]);
        glNormal(surface.VN[surface.VF[i][2]]);
        glVertex(surface.VV[surface.VF[i][2]]);
    }
    glEnd();

    glPopAttrib();
}

void drawNormals(const Surface &surface, float len)
{
    // Save current state of OpenGL
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glColor4f(0,1,1,1);
    glLineWidth(1);

    glBegin(GL_LINES);
    for (unsigned i=0; i<surface.VV.size(); i++)
    {
        glVertex(surface.VV[i]);
        glVertex(surface.VV[i] + surface.VN[i] * len);
    }
    glEnd();

    glPopAttrib();
}

void outputObjFile(ostream &out, const Surface &surface)
{
    
    for (unsigned i=0; i<surface.VV.size(); i++)
        out << "v  "
            << surface.VV[i][0] << " "
            << surface.VV[i][1] << " "
            << surface.VV[i][2] << endl;

    for (unsigned i=0; i<surface.VN.size(); i++)
        out << "vn "
            << surface.VN[i][0] << " "
            << surface.VN[i][1] << " "
            << surface.VN[i][2] << endl;

    out << "vt  0 0 0" << endl;
    
    for (unsigned i=0; i<surface.VF.size(); i++)
    {
        out << "f  ";
        for (unsigned j=0; j<3; j++)
        {
            unsigned a = surface.VF[i][j]+1;
            out << a << "/" << "1" << "/" << a << " ";
        }
        out << endl;
    }
}
