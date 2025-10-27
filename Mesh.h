// If MESH_CLASS_H is not yet defined, define it.
// This prevents multiple definitions of the same class during compilation.
#ifndef MESH_CLASS_H
#define MESH_CLASS_H

// Include standard and custom headers needed for the Mesh class.
#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"


// The Mesh class represents a single 3D object that can be drawn.
// Each Mesh contains vertex data, texture data, and index data,
// and handles its own VAO (Vertex Array Object) setup and rendering.
class Mesh
{
public:
	// Stores all vertices that make up this mesh.
	// Each Vertex holds position, normal, color, and texture coordinate data.
	std::vector <Vertex> vertices;

	// Stores the order in which vertices are drawn to form triangles.
	// The indices refer to the vertex list above.
	std::vector <GLuint> indices;

	// Stores all textures used by this mesh (e.g., diffuse, specular, normal maps).
	std::vector <Texture> textures;

	// The VAO stores attribute configurations for the vertices.
	// It is public so the Draw() function can access and bind it directly.
	VAO VAO;

	// Constructor that initializes the mesh by linking vertices, indices, and textures.
	// Sets up all buffers and attribute pointers needed for rendering.
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draw function that renders the mesh to the screen using a given shader and camera.
	// It applies transformations such as translation, rotation, and scaling.
	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),				 // Base model matrix (identity by default)
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f), // Move the mesh in world space
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), // Rotate the mesh with a quaternion
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)     // Scale the mesh size
	);
};

// Ends the header guard — if this class was already defined, skip everything above.
#endif
