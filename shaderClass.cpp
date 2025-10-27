// Header is included.
#include"shaderClass.h"

// The header already includes everything needed for this file,
// so no other includes are necessary here.


// This function reads the contents of a text file and returns
// the entire file as a single string. It's used to load shader code
// from a vertex or fragment shader file into memory.
std::string get_file_contents(const char* filename)
{
	// Create an input file stream in binary mode.
	std::ifstream in(filename, std::ios::binary);
	// If the file opens successfully:
	if (in)
	{
		std::string contents;
		// Move the file pointer to the end to find its total size.
		in.seekg(0, std::ios::end);
		// Resize the string to hold all file data.
		contents.resize(in.tellg());
		// Move the file pointer back to the start.
		in.seekg(0, std::ios::beg);
		// Read all of the file contents into the string.
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	// If the file cannot be opened, throw an error.
	throw(errno);
}


// Constructor that creates a Shader Program from a vertex and fragment shader file.
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read the vertex and fragment shader source files into strings.
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the std::string shader source code into C-style strings.
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create a new Vertex Shader object and store its ID.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach the vertex shader source code to the shader object.
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the vertex shader into machine code.
	glCompileShader(vertexShader);
	// Check for any compilation errors.
	compileErrors(vertexShader, "VERTEX");


	// Create a new Fragment Shader object and store its ID.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach the fragment shader source code to the shader object.
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the fragment shader into machine code.
	glCompileShader(fragmentShader);
	// Check for any compilation errors.
	compileErrors(fragmentShader, "FRAGMENT");


	// Create a Shader Program and store its ID.
	ID = glCreateProgram();
	// Attach both compiled shaders (vertex and fragment) to the program.
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link both shaders into a single executable program.
	glLinkProgram(ID);
	// Check for any linking errors.
	compileErrors(ID, "PROGRAM");

	// After linking, the individual shader objects are no longer needed,
	// so they are deleted to free up memory.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


// Activates this shader program for use in rendering.
// After calling this, all draw calls will use this shader until another is activated.
void Shader::Activate()
{
	glUseProgram(ID);
}


// Deletes this shader program from OpenGL memory.
void Shader::Delete()
{
	glDeleteProgram(ID);
}


// This function checks whether a shader (or shader program) compiled or linked successfully.
// If there was an error, it prints the corresponding error message to the console.
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Variable to store whether compilation or linking succeeded.
	GLint hasCompiled;
	// Buffer to store error messages.
	char infoLog[1024];

	// If the type is not "PROGRAM", check an individual shader's compile status.
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		// If compilation failed, print an error message.
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
	// Otherwise, check the link status of the overall shader program.
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		// If linking failed, print an error message.
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
}
