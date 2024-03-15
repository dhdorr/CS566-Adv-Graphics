#include "Mesh.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces
	
	ifstream file(filename);
	string line;

	if (file.is_open()) {
		
		while (getline(file, line)) {
			istringstream piss(line);
			char type;

			piss >> type;

			if(type == 'f') {
				uint u1;
				uint u2;
				uint u3;

				piss >> u1 >> u2 >> u3;

				faces.push_back(Tuple3u(u1, u2, u3));

			} else if (type == 'v') {
				float f1;
				float f2;
				float f3;

				piss >> f1 >> f2 >> f3;

				bindVertices.push_back(Vector3f(f1, f2, f3));
			}
		}
		file.close();
	}

	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;


}

void Mesh::draw()
{
	// glutCreateWindow("testme");
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".

	glBegin(GL_TRIANGLES);
 
    for (int k = 0; k < faces.size(); k++) {
		Tuple3u face = faces[k];
		Vector3f cvA = Vector3f(currentVertices[face[0] - 1].x(), currentVertices[face[0] - 1].y(), currentVertices[face[0] - 1].z());
		Vector3f cvB = Vector3f(currentVertices[face[1] - 1].x(), currentVertices[face[1] - 1].y(), currentVertices[face[1] - 1].z());
		Vector3f cvC = Vector3f(currentVertices[face[2] - 1].x(), currentVertices[face[2] - 1].y(), currentVertices[face[2] - 1].z());

		Vector3f edgeA = cvB - cvA;
		Vector3f edgeB = cvC - cvA;

		Vector3f normA = edgeA.cross(edgeA, edgeB).normalized();
		Vector3f normB = edgeA.cross(edgeA, edgeB).normalized();
		Vector3f normC = edgeA.cross(edgeA, edgeB).normalized();

        glNormal3d(normA.x(), normA.y(), normA.z());
        glVertex3d(cvA.x(), cvA.y(), cvA.z());
        glNormal3d(normB.x(), normB.y(), normB.z());
        glVertex3d(cvB.x(), cvB.y(), cvB.z());
        glNormal3d(normC.x(), normC.y(), normC.z());
        glVertex3d(cvC.x(), cvC.y(), cvC.z());

    }

	glEnd();

}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
	ifstream file(filename);
	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			istringstream iss(line);

			vector<float> helpmelol;

			for (int i = 0; i < numJoints - 1; i++) {
				float temp;
				iss >> temp;
				helpmelol.push_back(temp);
				
			}
			attachments.push_back(helpmelol);
		}
		file.close();
	}
	
}
