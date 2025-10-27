// EBO holds the connections and faces between points.

// Each instance of the EBO class typcally holds one mesh,
// for example, if that mesh was a cube, the EBO would look at and  
// organize 8 indices that reference vertices in one instance of the class.
// Therefore, one VBO would align perfectly with one EBO for a single mesh.

// Header files aren't ran, only copied into the corrosponding .cpp file
// before compilation. Header files define the class using 
// the class EBO {...} structure below, defining the EBO data type.

// If EBO_CLASS_H is not defined, define it 
// If it is already defined, it just skips to endif.
// These lines don't actually define anything, just avoid duplicate definitions.
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

// Includes copy contents of these files here before compiling.
// "" searches current directory then the library folder 
// and <> goes straight to library folder. 
// Using "" can cause an accident, like if we said #include "vector"
// and there was a file in this current directory called vector.
#include<glad/glad.h> // OpenGL functions.
#include<vector> // Include the vector data type.


class EBO
{
public:
	// GLuint is an OpenGL data type defined in glad.
	// It's an unsigned int meaning it can't be negative, and IDs don't need to be negative.
	// GLuint is an ID reference to our Elements Buffer Object
	GLuint ID;
	// Declares a constructor which needs a reference to a vector list
	// that contains GLuint integers, and the param is called indices.
	// The constructor generates an Elements Buffer Object and links it to indices.
	// The VBO holds all of the location and data for all of the vertices in space.
	// This allows the EBO to go one level higher, and not worry about all of that low level data,
	// but rather remember each of those vertices by their index number. Then, it organizes the 
	// vertex indices into which ones make up each face, edge, or connection.
	EBO(std::vector<GLuint>& indices);

	// Declare functions to be defined in the .cpp file.
	void Bind();
	void Unbind();
	void Delete();
};

// Skips to here if class is already defined (look at the top).
#endif