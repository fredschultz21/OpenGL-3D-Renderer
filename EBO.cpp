#include"EBO.h"

// glDrawElements is like to EBO what glVertexAttribPointer is to VBO

// When you call glDrawElements(), OpenGL looks for the currently bound EBO,
// and whatever you pass in for the params tells it how to interpret the data in that EBO,
// (it's likely that you'll tell it that the data is made of triangles, and therfore, it should
// read 3 indices at a time to make each triangle, then move on to the next 3 indices for the next triangle, etc.)

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint>& indices) {
	// We're using the GLuint id from the header file.
	// We need the address of the ID so we can actually write to that memory location.
	// A buffer is just a chunk of memory that stores data.
	// glGenBuffers(1, &ID) generates 1 buffer and stores the ID (the reference number to that buffer).
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}