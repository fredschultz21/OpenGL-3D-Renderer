// VBO is a box full of points in space that is packaged up 
// and sent to the GPU for rendering all in one go as an array.

// Each instance of the VBO class typcally holds one mesh,
// for example, if that mesh was a cube, the VBO would hold 8 vertices in one instance of the class.

// Header files aren't ran, only copied into the corrosponding .cpp file
// before compilation. Header files define the class using 
// the class VBO {...} structure below, defining the VBO data type.

// If VBO_CLASS_H is not defined, define it 
// If it is already defined, it just skips to endif.
// These lines don't actually define anything, just avoid duplicate definitions.
#ifndef VBO_CLASS_H
#define VBO_CLASS_H


// Includes copy contents of these files here before compiling.
// "" searches current directory then the library folder 
// and <> goes straight to library folder. 
// Using "" can cause an accident, like if we said #include "vector"
// and there was a file in this current directory called vector.
#include<glm/glm.hpp> // Library for transformations.
#include<glad/glad.h> // OpenGL functions.
#include<vector> // Include the vector data type.


// struct is a custom data type that holds multiple pieces of data.
// We call this one Vertex.
// We want these values to travel together, so we make a struct.
struct Vertex
{
	// glm::vec3 -> Internally equivalent to 3 floats for each variable (12 in total).
	// Ex. You can set Vertex v's v.position to a certain vector with 
	// your own vector that has 3 float values, or set each value individually,
	// by doing v.position.x = 1.0f etc.
	glm::vec3 position;
	glm::vec3 normal; // Not actually the normal for a single vertex, but rather the normal 
	// that's derived from looking at the other vertices around the single vertex, because if it was
	// literally the normal for a single vertex in space, it would be undefined and meaningless.
	glm::vec3 color;
	glm::vec2 texUV;
};



class VBO
{
public:
	// GLuint is an OpenGL data type defined in glad.
	// It's an unsigned int meaning it can't be negative, and IDs don't need to be negative.
	// GLuint is an ID reference to our Vertex Buffer Object.
	GLuint ID;
	// Declares a constructor which needs a reference to a vector list
	// that contains Vertex objects, and the param is called vertices.
	VBO(std::vector<Vertex>& vertices);

	// Declare functions to be defined in the .cpp file.
	void Bind();
	void Unbind();
	void Delete();
};

// Skips to here if class is already defined (look at the top).
#endif