#include "curve.h"
#include "extra.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
using namespace std;

namespace
{
    // Approximately equal to.  We don't want to use == because of
    // precision issues with floating point.
    inline bool approx( const Vector3f& lhs, const Vector3f& rhs )
    {
        const float eps = 1e-8f;
        return ( lhs - rhs ).absSquared() < eps;
    }

    
}

// Helper function to compute factorial
int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Helper function for binomial coefficient
int binomialCoefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// Helper function to calculate a point on the Bezier curve
Vector3f calculateBezierPoint(const std::vector<Vector3f>& P, float t) {
    Vector3f point(0.0f, 0.0f, 0.0f);
    int n = P.size() - 1; // Degree of the curve
    for (int i = 0; i <= n; i++) {
        // Compute the Bernstein basis polynomial
        float bernstein = binomialCoefficient(n, i) * pow(t, i) * pow(1 - t, n - i);
        point += P[i] * bernstein;
    }
    return point;
}

// Helper function to compute a single point on a Bezier curve
// Vector3f computeBSplinePoint(const vector<Vector3f>& controlPoints, float t) {
//     // Assuming controlPoints.size() == 4 for a single segment
//     Vector3f point(0.0f, 0.0f, 0.0f);
//     float oneMinusT = 1.0f - t;
//     point = oneMinusT * oneMinusT * oneMinusT * controlPoints[0] + 
//             3 * oneMinusT * oneMinusT * t * controlPoints[1] + 
//             3 * oneMinusT * t * t * controlPoints[2] + 
//             t * t * t * controlPoints[3];
//     return point;
// }
    
// // Helper function to compute a single point on a Bezier curve
// Vector3f computeBezierPoint(const vector<Vector3f>& controlPoints, float t) {
//     // Assuming controlPoints.size() == 4 for a single segment
//     Vector3f point(0.0f, 0.0f, 0.0f);
//     float oneMinusT = 1.0f - t;
//     point = oneMinusT * oneMinusT * oneMinusT * controlPoints[0] + 
//             3 * oneMinusT * oneMinusT * t * controlPoints[1] + 
//             3 * oneMinusT * t * t * controlPoints[2] + 
//             t * t * t * controlPoints[3];
//     return point;
// }

// // Function to compute the derivative of a Bezier curve (for tangents)
// Vector3f computeBezierTangent(const vector<Vector3f>& controlPoints, float t) {
//     Vector3f tangent(0.0f, 0.0f, 0.0f);
//     float oneMinusT = 1.0f - t;
//     tangent = -3 * oneMinusT * oneMinusT * controlPoints[0] + 
//               (3 * oneMinusT * oneMinusT - 6 * t * oneMinusT) * controlPoints[1] + 
//               (6 * t * oneMinusT - 3 * t * t) * controlPoints[2] + 
//               3 * t * t * controlPoints[3];
//     return tangent.normalized(); // Ensure it's a unit vector
// }

Curve evalBezier( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 || P.size() % 3 != 1 )
    {
        cerr << "evalBezier must be called with 3n+1 control points. " << P.size() << "\n" << endl;
        exit( 0 );
    }

    // TODO:
    // You should implement this function so that it returns a Curve
    // (e.g., a vector< CurvePoint >).  The variable "steps" tells you
    // the number of points to generate on each piece of the spline.
    // At least, that's how the sample solution is implemented and how
    // the SWP files are written.  But you are free to interpret this
    // variable however you want, so long as you can control the
    // "resolution" of the discretized spline curve with it.

    // Make sure that this function computes all the appropriate
    // Vector3fs for each CurvePoint: V,T,N,B.
    // [NBT] should be unit and orthogonal.

    // Also note that you may assume that all Bezier curves that you
    // receive have G1 continuity.  Otherwise, the TNB will not be
    // be defined at points where this does not hold.


    cerr << "\t>>> evalBezier has been called with the following input:" << endl;

    cerr << "\t>>> Control points (type vector< Vector3f >): "<< endl;
    for( unsigned i = 0; i < P.size(); ++i )
    {
        cerr << "\t>>> " << P[i] << endl;
    }

    cerr << "\t>>> Steps (type steps): " << steps << endl;
    cerr << "\t>>> Returning empty curve." << endl;

    // Right now this will just return this empty curve.
    //return Curve();

    // vector<float> bCurveX;
    // vector<float> bCurveY;
    // vector<float> bCurveZ;
    // float bCurveXt;
    // float bCurveYt;
    // float bCurveZt;

    // Curve curve1;

    // for(int i = 0; i <= steps; i++) {
    //     float t = i / steps;
    //     bCurveXt = pow((1 - t), 3) * P[0].x() + 3 * pow((1 - t), 2) * t * P[1].x() + 3 * pow((1 - t), 1) * pow(t, 2) * P[2].x() + pow(t, 3) * P[3].x();
    //     bCurveYt = pow((1 - t), 3) * P[0].y() + 3 * pow((1 - t), 2) * t * P[1].y() + 3 * pow((1 - t), 1) * pow(t, 2) * P[2].y() + pow(t, 3) * P[3].y();
    //     bCurveZt = pow((1 - t), 3) * P[0].z() + 3 * pow((1 - t), 2) * t * P[1].z() + 3 * pow((1 - t), 1) * pow(t, 2) * P[2].z() + pow(t, 3) * P[3].z();
    
    //     bCurveX.push_back(bCurveXt);
    //     bCurveY.push_back(bCurveYt);
    //     bCurveZ.push_back(bCurveZt);

    //     Vector3f tangent = computeBezierTangent(P, t);

    //     // Initialize normal and binormal
    //     Vector3f normal(0.0f, 0.0f, 0.0f);
    //     Vector3f binormal(0.0f, 0.0f, 0.0f);

    //     if (i == 0) {
    //         // For the first point, choose an arbitrary normal
    //         normal = Vector3f(0.0f, 0.0f, 1.0f); // This is arbitrary and might need adjustment
    //     } else {
    //         // Compute normal and binormal based on previous tangent and binormal
    //         normal = Vector3f::cross(curve1.back().B, tangent).normalized();
    //     }
    //     binormal = Vector3f::cross(tangent, normal).normalized();

    //     // Append the computed CurvePoint to the curve
    //     //curve1.push_back({point, tangent, normal, binormal});
    // }

    // Chat GPT created this...
    // Curve curve;

    // for (size_t i = 0; i < P.size(); i += steps) {

    //     for (unsigned step = 0; step <= steps; ++step) {
    //         float t = step / static_cast<float>(steps);
    //         Vector3f point = computeBezierPoint(P, t);
    //         Vector3f tangent = computeBezierTangent(P, t);

    //         // Initialize normal and binormal
    //         Vector3f normal(0.0f, 0.0f, 0.0f);
    //         Vector3f binormal(0.0f, 0.0f, 0.0f);

    //         if (step == 0) {
    //             // For the first point, choose an arbitrary normal
    //             normal = Vector3f(0.0f, 0.0f, 1.0f); // This is arbitrary and might need adjustment
    //         } else {
    //             // Compute normal and binormal based on previous tangent and binormal
    //             normal = Vector3f::cross(curve.back().B, tangent).normalized();
    //         }
    //         binormal = Vector3f::cross(tangent, normal).normalized();

    //         // Append the computed CurvePoint to the curve
    //         curve.push_back({point, tangent, normal, binormal});
    //     }
    // }

    // return curve;


    Curve curve;
    // Loop through each segment
    for (size_t i = 0; i < P.size() - 1; i += 3) {
        std::vector<Vector3f> controlPoints(P.begin() + i, P.begin() + i + 4);
        for (unsigned step = 0; step <= steps; ++step) {
            float t = (float)step / (float)steps;
            // Calculate the vertex
            Vector3f V = calculateBezierPoint(controlPoints, t);

            // Calculate the tangent, which is the derivative of V
            Vector3f T = 3 * pow(1 - t, 2) * (controlPoints[1] - controlPoints[0]) +
                         6 * (1 - t) * t * (controlPoints[2] - controlPoints[1]) +
                         3 * pow(t, 2) * (controlPoints[3] - controlPoints[2]);
            T.normalize();

            // Assume an arbitrary normal for the first point
            Vector3f N = (step == 0) ? Vector3f(1, 0, 0) : curve.back().N;
            // Correct the normal to be orthogonal to T
            N = Vector3f::cross(Vector3f::cross(T, N), T);
            N.normalize();

            // Calculate the binormal
            Vector3f B = Vector3f::cross(T, N);
            B.normalize();

            // Add the curve point to the curve
            curve.push_back({V, T, N, B});
        }
    }
    return curve;
}



Curve evalBspline( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 )
    {
        cerr << "evalBspline must be called with 4 or more control points." << endl;
        exit( 0 );
    }

    // TODO:
    // It is suggested that you implement this function by changing
    // basis from B-spline to Bezier.  That way, you can just call
    // your evalBezier function.

    cerr << "\t>>> evalBSpline has been called with the following input:" << endl;

    cerr << "\t>>> Control points (type vector< Vector3f >): "<< endl;
    for( unsigned i = 0; i < P.size(); ++i )
    {
        cerr << "\t>>> " << *P[i] << endl;
    }

    cerr << "\t>>> Steps (type steps): " << steps << endl;
    cerr << "\t>>> Returning empty curve." << endl;

    // Return an empty curve right now.
    //return Curve();
    // vector<Vector3f> helpme;
    // for (int i = 0; i < steps; i++) { 
    //     float t = i / static_cast<float>(steps);
    //     Vector3f testP = P[i] * t;
    //     helpme.push_back(testP);
    // }
    // vector<CurvePoint> testme = evalBezier(P, steps);
    // return testme;

    // Container for the converted Bezier control points
    std::vector<Vector3f> bezierControlPoints;

    // Convert B-spline control points to Bezier control points
    for (size_t i = 0; i <= P.size()-4; i++) {
        if (i == 0) { // For the first segment
            bezierControlPoints.push_back(P[i]);
            bezierControlPoints.push_back((P[i] + 2 * P[i + 1]) / 3);
            bezierControlPoints.push_back((2 * P[i + 1] + P[i + 2]) / 3);
            bezierControlPoints.push_back((P[i + 1] + 4 * P[i + 2] + P[i + 3]) / 6);
        } else {
            bezierControlPoints.push_back((P[i] + 4 * P[i + 1] + P[i + 2]) / 6);
            bezierControlPoints.push_back((P[i + 1] + 2 * P[i + 2]) / 3);
            bezierControlPoints.push_back((2 * P[i + 2] + P[i + 3]) / 3);
            if (i == P.size() - 4) { // For the last segment
                //bezierControlPoints.push_back(P[i + 3]);
            } else {
                bezierControlPoints.push_back((P[i + 2] + 4 * P[i + 3] + P[i + 4]) / 6);
            }
        }
    }

    // Use the evalBezier function to generate the curve
    return evalBezier(bezierControlPoints, steps);
    
}

Curve evalCircle( float radius, unsigned steps )
{
    // This is a sample function on how to properly initialize a Curve
    // (which is a vector< CurvePoint >).
    
    // Preallocate a curve with steps+1 CurvePoints
    Curve R( steps+1 );

    // Fill it in counterclockwise
    for( unsigned i = 0; i <= steps; ++i )
    {
        // step from 0 to 2pi
        float t = 2.0f * M_PI * float( i ) / steps;

        // Initialize position
        // We're pivoting counterclockwise around the y-axis
        R[i].V = radius * Vector3f( cos(t), sin(t), 0 );
        
        // Tangent vector is first derivative
        R[i].T = Vector3f( -sin(t), cos(t), 0 );
        
        // Normal vector is second derivative
        R[i].N = Vector3f( -cos(t), -sin(t), 0 );

        // Finally, binormal is facing up.
        R[i].B = Vector3f( 0, 0, 1 );
    }

    return R;
}

void drawCurve( const Curve& curve, float framesize )
{
    // Save current state of OpenGL
    glPushAttrib( GL_ALL_ATTRIB_BITS );

    // Setup for line drawing
    glDisable( GL_LIGHTING ); 
    glColor4f( 1, 1, 1, 1 );
    glLineWidth( 1 );
    
    // Draw curve
    glBegin( GL_LINE_STRIP );
    for( unsigned i = 0; i < curve.size(); ++i )
    {
        glVertex( curve[ i ].V );
    }
    glEnd();

    glLineWidth( 1 );

    // Draw coordinate frames if framesize nonzero
    if( framesize != 0.0f )
    {
        Matrix4f M;

        for( unsigned i = 0; i < curve.size(); ++i )
        {
            M.setCol( 0, Vector4f( curve[i].N, 0 ) );
            M.setCol( 1, Vector4f( curve[i].B, 0 ) );
            M.setCol( 2, Vector4f( curve[i].T, 0 ) );
            M.setCol( 3, Vector4f( curve[i].V, 1 ) );

            glPushMatrix();
            glMultMatrixf( M );
            glScaled( framesize, framesize, framesize );
            glBegin( GL_LINES );
            glColor3f( 1, 0, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 1, 0, 0 );
            glColor3f( 0, 1, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 1, 0 );
            glColor3f( 0, 0, 1 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 0, 1 );
            glEnd();
            glPopMatrix();
        }
    }
    
    // Pop state
    glPopAttrib();
}

