// If not defined, define, if defined, skip to endif.
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h> // OpenGL functions.
#include<string> // Include the string data type (C++ is very low level).
#include<fstream>  // Enables file reading and writing.
#include<sstream> //  Enables string reading and writing.
#include<iostream> // Enables input and output streams to the console (terminal).
#include<cerrno> // Gives access to c errors.

// Function declaration named get_file_contents that takes in a const char* filename 
// and returns a std::string. Defined in the .cpp file.
// char* means string literal in C/C++, and const means it won't be changed (it's named filename).
std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Functions defined in the .cpp file:
	void Activate(); // Activates the Shader Program
	void Delete(); // Deletes the Shader Program
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

// Skips to here if class is already defined (look at the top).
#endif