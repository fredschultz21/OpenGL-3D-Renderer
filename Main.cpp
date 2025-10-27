// Ignore this section — only used for handling file paths
#include<filesystem>
namespace fs = std::filesystem;

#include"Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW which version of OpenGL to use (3.3 in this case)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Use the core profile, which gives access only to modern OpenGL functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window with a resolution of 800x800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL 3D Rendering", NULL, NULL);

	// Check if the window failed to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window the current OpenGL context
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers using GLAD
	gladLoadGL();

	// Set the OpenGL viewport (the drawable area inside the window)
	glViewport(0, 0, width, height);

	// Create a Shader object and load the vertex and fragment shaders
	Shader shaderProgram("default.vert", "default.frag");

	// Define properties for the light source
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	// Activate the shader and send the light data to it
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enable the depth buffer so OpenGL can handle which objects are in front or behind
	glEnable(GL_DEPTH_TEST);

	// Create a camera at position (0, 0, 2)
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	/*
	* This relative path setup keeps all resources in one centralized folder.
	* It prevents duplicating assets between tutorial folders.
	* Make sure your compiler uses C++17 (Project Properties -> C/C++ -> Language -> C++17).
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/OpenGL3DRenderer/models/scroll/scene.gltf";

	// Load the 3D model
	Model model((parentDir + modelPath).c_str());

	// Main render loop — runs every frame until the window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clear the color and depth buffers to prepare for a new frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handle user input for the camera (keyboard and mouse)
		camera.Inputs(window);

		// Update the camera’s matrix and send it to the shader
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		// Draw the loaded model
		model.Draw(shaderProgram, camera);

		// Swap the back buffer (the drawn frame) with the front buffer (the displayed frame)
		glfwSwapBuffers(window);

		// Process all pending GLFW events (input, resize, etc.)
		glfwPollEvents();
	}

	// Clean up resources before closing the program
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}