// If CAMERA_CLASS_H is not yet defined, define it.
// This prevents the header from being included more than once during compilation.
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

// Includes required libraries for OpenGL, input handling, and math operations.

// glad provides access to modern OpenGL functions.
#include<glad/glad.h>
// GLFW handles window creation, input, and events.
#include<GLFW/glfw3.h>
// glm provides vector and matrix types for math operations used by the camera.
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

// Include the Shader class so the camera can send its matrix to the shader.
#include"shaderClass.h"


// The Camera class controls the position, orientation, and perspective of the view in 3D space.
// It also handles keyboard and mouse input to move and rotate the camera in real time.
class Camera
{
public:
	// Stores the main directional vectors of the camera:
	// Position = where the camera currently is in world space.
	glm::vec3 Position;
	// Orientation = the direction the camera is currently facing.
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	// Up = the upward direction relative to the camera (usually +Y).
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	// The cameraMatrix combines view and projection transformations for rendering.
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Used to prevent sudden camera jumps when the mouse is first clicked.
	bool firstClick = true;

	// The width and height of the application window.
	// These values are needed to calculate the projection matrix correctly.
	int width;
	int height;

	// Movement speed of the camera and mouse sensitivity.
	// Higher values make the camera move faster or rotate more sharply.
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Constructor that sets up the camera's initial position and screen dimensions.
	Camera(int width, int height, glm::vec3 position);

	// Updates the cameraMatrix to include the latest position and orientation.
	// This matrix is used to transform 3D coordinates to the camera's point of view.
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Sends the cameraMatrix to a shader so the GPU can use it for rendering.
	// The 'uniform' parameter is the variable name inside the vertex shader.
	void Matrix(Shader& shader, const char* uniform);

	// Handles all camera input, including movement (WASD) and mouse rotation.
	// This function should be called once per frame in the game loop.
	void Inputs(GLFWwindow* window);
};

// Ends the header guard — if the class was already defined, the compiler skips to here.
#endif
