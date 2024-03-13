#include "Mesh.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces

	// Add your code here.
	
	// load the OBJ file here
	int MAX_BUFFER_SIZE = 128;

	// This is the list of points (3D vectors)
	vector<Vector3f> vecv;

	// This is the list of normals (also 3D vectors)
	vector<Vector3f> vecn;

	// This is the list of faces (indices into vecv and vecn)
	vector<vector<unsigned>> vecf;

    Vector3f v;
    char buffer[MAX_BUFFER_SIZE];

	ifstream file(filename);
	string line;
	bool rootIdentified = false;

	if (file.is_open()) {
		while (getline(file, line)) {
			istringstream iss(line);

			string s;

			iss >> s;
			if (s == "v") {
				iss >> v[0] >> v[1] >> v[2];

				// vecv.push_back(v);
				bindVertices.push_back(v);

			} else if (s == "f") {
				string faceLine;
				vector<unsigned> f;
				Tuple3u testFaces;

				while (getline(iss, faceLine, ' ')) {
					string elems;
					iss >> elems;
					istringstream tokenStream(elems);
					string number;
					while (getline(tokenStream, number, '/')) {                    
						unsigned elemUInt = stoul(number);
						f.push_back(elemUInt);
						
					}
				}
				// vecf.push_back(f);
				faces.push_back(Tuple3u(f[0], f[1], f[2]));
			}
		}
	}

	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;

}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".

	int i;
    

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

	gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
	
	// Here are some colors you might use - feel free to add more
    GLfloat diffColors[4][4] = { {0.2, 0.5, 0.9, 1.0},
                                 {0.9, 0.9, 0.5, 1.0},
                                 {0.5, 0.2, 0.3, 1.0},
                                 {0.3, 0.8, 0.1, 1.0} };
    
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[1]);

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	float lightPosX = 1.0f;
	float lightPosY = 1.0f;
	GLfloat Lt0pos[] = {lightPosX, lightPosY, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);


	glBegin(GL_TRIANGLES);
 
    for (int k = 0; k < faces.size(); k++) {
		Tuple3u face = faces[k];
        

        glNormal3d(0, 1, 0);
        glVertex3d(currentVertices[face[0]].x(), currentVertices[face[0]].y(), currentVertices[face[0]].z());
        glNormal3d(1, 1, 0);
        glVertex3d(currentVertices[face[1]].x(), currentVertices[face[1]].y(), currentVertices[face[1]].z());
        glNormal3d(0, 1, 1);
        glVertex3d(currentVertices[face[2]].x(), currentVertices[face[2]].y(), currentVertices[face[2]].z());

    }

	glEnd();
    
    
    // Dump the image to the screen.
    // glutSwapBuffers();

}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
}
