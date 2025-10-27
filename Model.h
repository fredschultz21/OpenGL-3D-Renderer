// If MODEL_CLASS_H is not yet defined, define it.
// This prevents the header from being redefined multiple times during compilation.
#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

// Includes required libraries for model loading and data parsing.
#include<json/json.h>
#include"Mesh.h"

// Create a shorthand alias so we can write "json" instead of "nlohmann::json".
using json = nlohmann::json;


// The Model class is responsible for loading and managing 3D models.
// It stores all meshes, textures, and transformation data, and handles
// the process of traversing model nodes and preparing them for rendering.
class Model
{
public:
	// Constructor that loads a model from a file.
	// The model data is stored in 'data', 'JSON', and 'file',
	// and is then processed into meshes and transformations.
	Model(const char* file);

	// Draws the entire model to the screen using a given shader and camera.
	// Internally calls the Draw() function of each mesh in the model.
	void Draw(Shader& shader, Camera& camera);

private:
	// -------------------------------
	// Model Data Storage
	// -------------------------------

	// Stores the file path of the model.
	const char* file;

	// Stores the raw binary data read from the model file.
	std::vector<unsigned char> data;

	// Stores the parsed JSON structure that describes the model layout.
	json JSON;

	// -------------------------------
	// Mesh and Transformation Data
	// -------------------------------

	// A list of all meshes that make up the model.
	std::vector<Mesh> meshes;

	// Lists that store transformation data for each mesh.
	// These define where and how each mesh is positioned, rotated, and scaled.
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// -------------------------------
	// Texture Management
	// -------------------------------

	// Used to prevent the same texture from being loaded more than once.
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// -------------------------------
	// Model Loading Functions
	// -------------------------------

	// Loads a single mesh from the model based on its index in the file.
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, visiting all connected nodes in the scene graph.
	// This allows complex models made of multiple linked parts to be fully loaded.
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// -------------------------------
	// Data Extraction Helpers
	// -------------------------------

	// Reads the binary model data from the file and returns it as a byte array.
	std::vector<unsigned char> getData();

	// Converts JSON accessors into arrays of floats, indices, or textures.
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// -------------------------------
	// Vertex Assembly
	// -------------------------------

	// Combines all position, normal, and texture coordinate data into Vertex objects.
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	// -------------------------------
	// Float Grouping Utilities
	// -------------------------------

	// Converts flat float arrays into grouped vector types (vec2, vec3, vec4).
	// These are used to reconstruct position, normal, and UV coordinate data.
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

// Ends the header guard — if the Model class was already defined, skip everything above.
#endif
