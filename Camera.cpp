// Header is included.
#include"Camera.h"


// Constructor that initializes camera dimensions and position.
// Sets the initial position and window size values for the camera object.
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}


// Updates the camera's transformation matrix (view + projection).
// This matrix determines how the 3D world is viewed through the camera.
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initialize both matrices to identity to ensure they start clean.
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// The view matrix defines where the camera is positioned and which direction it’s looking.
	// Position = current camera position.
	// Orientation = forward direction vector.
	// Up = world up direction.
	view = glm::lookAt(Position, Position + Orientation, Up);

	// The projection matrix adds perspective to the scene.
	// Converts 3D points into 2D by simulating depth.
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Combine both matrices to form the camera matrix used in the shader.
	cameraMatrix = projection * view;
}


// Sends the camera matrix to the shader program as a uniform.
// This allows the GPU to transform all rendered vertices from world space to camera space.
void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


// Handles all keyboard and mouse input for camera movement and rotation.
void Camera::Inputs(GLFWwindow* window)
{

	// Move forward (W)
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	// Move left (A)
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	// Move backward (S)
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	// Move right (D)
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	// Move upward (Space)
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	// Move downward (Left Control)
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	// Sprint (Hold Left Shift)
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	// Return to normal speed when Left Shift is released
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}



	// When left mouse button is held down, enable camera rotation.
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hide the cursor so movement isn’t visually distracting.
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevent camera from instantly jumping the first time the button is pressed.
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Variables to store the mouse’s position on screen.
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalize mouse coordinates so the center of the screen is (0, 0).
		// The mouse’s movement is scaled by sensitivity to control camera rotation speed.
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Compute a new vertical rotation of the camera.
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Prevents the camera from flipping upside down when looking too far up or down.
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotate the camera horizontally (left/right) around the Up axis.
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Reset the mouse position to the center of the screen
		// so rotation continues smoothly without the cursor hitting screen edges.
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	// When left mouse button is released, stop rotating and show the cursor again.
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Show the cursor again.
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Reset firstClick to true so next time rotation begins smoothly again.
		firstClick = true;
	}
}
