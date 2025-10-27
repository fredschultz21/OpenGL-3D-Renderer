// Header is included.
#include "Mesh.h"


// Constructor that initializes the mesh’s vertex, index, and texture data.
// It also sets up and links the necessary buffers (VBO, EBO, VAO) for rendering.
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	// Store the provided data in the class members.
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// Bind the VAO before linking buffers and attributes.
	VAO.Bind();

	// Generate a Vertex Buffer Object (VBO) and upload vertex data to GPU memory.
	VBO VBO(vertices);

	// Generate an Element Buffer Object (EBO) and upload index data to GPU memory.
	EBO EBO(indices);

	// Link vertex attributes to the VAO so the GPU knows how to interpret the VBO data.
	// Each call defines a specific attribute layout (position, normal, color, texture UVs).
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);					 // Position
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // Normal
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // Color
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // Texture coordinates

	// Unbind all to prevent accidental modifications.
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


// Draw function renders the mesh using the provided shader and camera.
// It also handles texture binding and applies transformations such as translation, rotation, and scaling.
void Mesh::Draw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	// Activate the shader program so we can set uniforms and draw with it.
	shader.Activate();
	// Bind the VAO associated with this mesh.
	VAO.Bind();


	// Counters to keep track of how many textures of each type are used.
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	// Loop through all textures in this mesh and bind them to the correct texture units.
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		// Assign unique numbers to each diffuse/specular texture (e.g., diffuse0, diffuse1).
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}

		// Connect the texture to the correct uniform in the shader and bind it to the GPU.
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}


	// Pass the camera’s position to the shader (used for lighting calculations).
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

	// Pass the camera matrix (view + projection) to the shader.
	camera.Matrix(shader, "camMatrix");


	// Initialize matrices for translation, rotation, and scaling.
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Apply transformations to position, orient, and size the mesh.
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);


	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));


	// Draw the mesh using the currently bound VAO, shader, and textures.
	// GL_TRIANGLES specifies the rendering mode, and indices.size() defines how many indices to draw.
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
