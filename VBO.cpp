#include"VBO.h"

// Constructor that creates a Vertex Buffer Object (VBO)
// and uploads the provided vertex data to the GPU.
VBO::VBO(std::vector<Vertex>& vertices)
{
	// Generate a new buffer and store its ID reference
	glGenBuffers(1, &ID);

	// Bind this buffer as the active array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Copy all vertex data into the buffer's memory on the GPU
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Bind the VBO so it becomes the current active array buffer
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbind the VBO to prevent accidental modification
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete the VBO from GPU memory to free resources
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
