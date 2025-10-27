// Typically 1 EBO and 1 VBO are bound to 1 VAO for a single mesh.
// The VAO links the VBO and EBO together, and helps them work in sync.

// To bind a VBO and EBO to a VAO, first run vao.Bind(). It basically makes
// the VAO active and ready to be linked to. Then, run vbo.Bind() to
// bind the VBO to whatever's current ready to be linked to (our active VAO).
// 
// 
// 
// Header files aren't ran, only copied into the corrosponding .cpp file
// before compilation. Header files define the class using 
// the class VAO {...} structure below, defining the VAO data type.

// If VAO_CLASS_H is not defined, define it 
// If it is already defined, it just skips to endif.
// These lines don't actually define anything, just avoid duplicate definitions.
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h> // OpenGL functions.
#include"VBO.h" // Include the VBO class.

class VAO
{
public:
	// GLuint is an OpenGL data type defined in glad.
	// It's an unsigned int meaning it can't be negative, and IDs don't need to be negative.
	// GLuint is an ID reference to our Vertex Array Object.
	GLuint ID;

	// Constructor that generates a VAO ID
	VAO();

	// Just a function declaration, see the .cpp file for definition (VERY IMPORTANT).
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	
	// Declare functions to be defined in the .cpp file.
	void Bind();
	void Unbind();
	void Delete();
};

// Skips to here if class is already defined (look at the top).
#endif