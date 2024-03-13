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

void SkeletalModel::recursiveDrawJoints(Joint* parent) {
	m_matrixStack.push(m_matrixStack.top() * parent->transform);
	glLoadMatrixf(m_matrixStack.top());
	glutSolidSphere( 0.025f, 12, 12 );

	for( int i = 0; i < parent->children.size(); i++) {
		recursiveDrawJoints(parent->children[i]);
		m_matrixStack.pop();
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

	recursiveDrawJoints(m_rootJoint);

}

void SkeletalModel::recursiveDrawSkeleton(Joint* parent) {
	if (parent != m_rootJoint) {

		Matrix4f testme = parent->transform;

		float test_diff_y = testme.getCol(3).y();
		float test_diff_x = testme.getCol(3).x();
		float test_diff_z = testme.getCol(3).z();
		float test_mag_a = sqrt(pow(test_diff_x, 2.0f) + pow(test_diff_y, 2.0f) + pow(test_diff_z, 2.0f));
		float test_mag_c = 1;
		
		float denom = test_mag_a * test_mag_c;
		float test_cos_angle = 0.0f;
		float test_angle = 0;

		if (denom != 0) {
			test_cos_angle = Vector3f().dot(testme.getCol(3).xyz(), Vector3f(0,0,1)) / denom;
			test_angle = acos(test_cos_angle);
		}
		
		Vector3f testVec = testme.getCol(3).xyz();
		Vector3f rotation_axis = Vector3f().cross(Vector3f(0,0,1), testVec);

		m_matrixStack.push(m_matrixStack.top() * testme);
		m_matrixStack.push(m_matrixStack.top() * testme.translation( -test_diff_x/2, -test_diff_y/2, -test_diff_z/2));
		m_matrixStack.push(m_matrixStack.top() * testme.identity().rotation(rotation_axis, test_angle));
		m_matrixStack.push(m_matrixStack.top() * testme.identity().scaling(1.0f, 1.0f, test_mag_a/0.025f));
		
		glLoadMatrixf(m_matrixStack.top());
		glutSolidCube(0.025f);

		m_matrixStack.pop();
		m_matrixStack.pop();
		m_matrixStack.pop();

	}


	for( int i = 0; i < parent->children.size(); i++) {

		recursiveDrawSkeleton(parent->children[i]);
		m_matrixStack.pop();

	}

}

void SkeletalModel::drawSkeleton( )
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
	
	recursiveDrawSkeleton(m_rootJoint);
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.

    // Convert Euler angles to radians
    float radianX = rX * (180.0f / M_PI);
    float radianY = rY * (180.0f / M_PI);
    float radianZ = rZ * (180.0f / M_PI);

    // Compute sine and cosine values for optimization
    float cx = cos(radianX);
    float cy = cos(radianY);
    float cz = cos(radianZ);
    float sx = sin(radianX);
    float sy = sin(radianY);
    float sz = sin(radianZ);

	Matrix3f rotation_matrix = Matrix3f(Vector3f(cy * cz, -cy * sz, sy), Vector3f(cx * sz + cz * sx * sy, cx * cz - sx * sy * sz, -cy * sx), Vector3f(sx * sz - cx * cz * sy, cz * sx + cx * sy * sz, cx * cy));

	m_joints[jointIndex]->transform.setSubmatrix3x3(0, 0, rotation_matrix);

	m_joints[jointIndex]->transform.print();
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

