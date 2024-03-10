#include "SkeletalModel.h"

#include <FL/Fl.H>

using namespace std;

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
	loadSkeleton(skeletonFile);

	m_mesh.load(meshFile);
	m_mesh.loadAttachments(attachmentsFile, m_joints.size());

	computeBindWorldToJointTransforms();
	updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
	// draw() gets called whenever a redraw is required
	// (after an update() occurs, when the camera moves, the window is resized, etc)

	m_matrixStack.clear();

	m_matrixStack.push(cameraMatrix);

	if( skeletonVisible )
	{
		drawJoints();

		drawSkeleton();
	}
	else
	{
		// Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
		glLoadMatrixf(m_matrixStack.top());

		// Tell the mesh to draw itself.
		m_mesh.draw();
	}
}

void SkeletalModel::loadSkeleton( const char* filename )
{
	// Load the skeleton from file here.
	ifstream file(filename);
	string line;
	bool rootIdentified = false;

	if (file.is_open()) {
		while (getline(file, line)) {
			//cout << line << endl;
			istringstream iss(line);
			vector<float> floats;
			float temp;

			while (iss >> temp) {
				floats.push_back(temp);
			}

			Joint *joint = new Joint;
			joint->transform = joint->transform.translation(Vector3f(floats[0], floats[1], floats[2]));
			
			if (int(floats[3]) > -1) {
				m_joints[int(floats[3])]->children.push_back(joint);
			}
				

			m_joints.push_back(joint);
			//m_matrixStack.push(joint->transform);

			if (!rootIdentified && floats[3] == float(-1)) {
				rootIdentified = true;
				m_rootJoint = joint;
			}
		}
		file.close();
	} else {
		cout << "Unable to open file: " << filename << endl;
	}
}

void SkeletalModel::drawJoints( )
{
	// Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
	//
	// We recommend using glutSolidSphere( 0.025f, 12, 12 )
	// to draw a sphere of reasonable size.
	//
	// You are *not* permitted to use the OpenGL matrix stack commands
	// (glPushMatrix, glPopMatrix, glMultMatrix).
	// You should use your MatrixStack class
	// and use glLoadMatrix() before your drawing call.

	m_matrixStack.push(m_matrixStack.top() * m_joints[0]->transform);
	for(int i = 1; i < m_joints.size(); i++) {
		for (int j = 0; j < m_joints[i]->children.size(); j++) {
			// m_matrixStack.push( m_joints[i]->transform * m_joints[i]->children[j]->transform);
			// glLoadMatrixf(m_matrixStack.top());
			// glutSolidSphere( 0.025f, 12, 12 );
			// m_matrixStack.pop();
		}
		m_matrixStack.push(m_matrixStack.top() * m_joints[i]->transform);
		glLoadMatrixf(m_matrixStack.top());
		glutSolidSphere( 0.025f, 12, 12 );

		// for (int j = 0; j < m_joints[i]->children.size(); j++) {
		// 	m_matrixStack.pop();
		// }
		m_matrixStack.pop();
	}

	//cout << "joint" << endl;
	//m_joints[0]->transform.print();
	//cout << "matrix pre" << endl;
	//m_matrixStack.top().print();
	//m_matrixStack.push(m_matrixStack.top() * m_joints[0]->transform);
	//cout << "matrix post" << endl;
	//m_matrixStack.top().print();
	// cout << "TESTING" << endl;
	// Matrix4f testing = m_matrixStack.top() * m_joints[0]->transform;
	// testing.print();

	// glLoadMatrixf(m_matrixStack.top());
	// glutSolidSphere( 0.025f, 12, 12 );
}

void SkeletalModel::drawSkeleton( )
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
}


void SkeletalModel::computeBindWorldToJointTransforms()
{
	// 2.3.1. Implement this method to compute a per-joint transform from
	// world-space to joint space in the BIND POSE.
	//
	// Note that this needs to be computed only once since there is only
	// a single bind pose.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
	// 2.3.2. Implement this method to compute a per-joint transform from
	// joint space to world space in the CURRENT POSE.
	//
	// The current pose is defined by the rotations you've applied to the
	// joints and hence needs to be *updated* every time the joint angles change.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
}

void SkeletalModel::updateMesh()
{
	// 2.3.2. This is the core of SSD.
	// Implement this method to update the vertices of the mesh
	// given the current state of the skeleton.
	// You will need both the bind pose world --> joint transforms.
	// and the current joint --> world transforms.
}
