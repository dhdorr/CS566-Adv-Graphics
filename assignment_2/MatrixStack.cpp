#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
	m_matrices.push_back(Matrix4f(0).identity());
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
	m_matrices.clear();
	MatrixStack();
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	
	//return Matrix4f();
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
}

void MatrixStack::pop()
{
	// Remove the top element from the stack
}
