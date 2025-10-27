// Header is included.
#include"VAO.h"

// mycoolclass::dosomething()
// This means the function dosomething() belongs to the mycoolclass class.

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


// VAOs are held in OpenGL's memory. It is like a set of arrays.
// VAOs hold attribute pointers (the way the program can figure out how to navigate VBOs), 
// the VBOs that were bound, and the EBOs that were bound

// When you later on do vao.Bind(), it makes that VAO active again, and restores the state to how it was, ready to go.

// The reason we need to link attributes in the first place, and why we can't just go through the VBO directly 
// is because the VAO needs to know how to interpret the data in the VBO. The VBO is just 
// a list of numbers, and the VAO needs to know which numbers are positions, which are colors, etc., 
// and how to group them together for each vertex.
// The attribute pointer doesn't actually read any data, it just tells the VAO how to read the data later on when rendering.
// The glVertexAttribPointer tells you how to skip around and the units to use to do it in order to find each attribute.
// For example, when looknig in a VBO, if a vertex has 11 floats in total, to get to the second vertex, you need to skip forward 11 floats (the stride).
// From there, if you want to get the the color attribute, you need to skip the first 6 floats (3 for position, 3 for normal), which is the offset.
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Puts the VBO data on deck to be linked to the VAO.
	VBO.Bind();
	// This function is ran one time for each atribute (one time for all positions, 
	// one time for all colors, etc) in a single mesh.
	// 
	// layout defines our locations, for example, all position go in index 0, 
	// all colors in 1, etc.
	// 
	// numComponents is how many components there are per attribute, for example,
	// a position has 3 (x,y,z) and a color has 3 (r,g,b) and a texture UV has 2 (u,v).
	// 
	// type is the data type, usually GL_FLOAT.
	// 
	// GL_FALSE means the data is not to be  normalized (meaning sent to between 0 and 1).
	// 
	// stride tells you the actual size of the data for each vertex. For example,
	// if each vertex has a position (3 floats), normal (3 floats), color (3 floats), and texUV (2 floats),
	// then the stride is 3+3+3+2 = 11 floats, and 11 * sizeof(float) bytes.
	//
	// offset says many bytes to skip at the beginning of each vertex 
	// before reading this specific attribute
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	// All the data is linked, so we can unbind the VBO.
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	// OpenGL function that binds the VAO by its ID from header (GLuint ID).
	// The VAO already exists here, we don't have to write into int, so we just
	// need ID, not &ID. Here, we are just making this VAO active.
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	// 0 is the convention for unbinding any buffer or array in OpenGL.
	// Makes it so the thing that is currently bound is now 0.
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	// Means delete 1 VAO, and the VAO to delete is &ID (the address of the current VAO in memory).
	glDeleteVertexArrays(1, &ID);
}