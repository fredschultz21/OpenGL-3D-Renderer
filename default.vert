#version 330 core

// Vertex position in 3D space
layout (location = 0) in vec3 aPos;
// Normal vector of the vertex
layout (location = 1) in vec3 aNormal;
// Color value of the vertex
layout (location = 2) in vec3 aColor;
// Texture coordinates of the vertex
layout (location = 3) in vec2 aTex;

// Passes the current vertex position to the Fragment Shader
out vec3 crntPos;
// Passes the vertex normal to the Fragment Shader
out vec3 Normal;
// Passes the vertex color to the Fragment Shader
out vec3 color;
// Passes the texture coordinates to the Fragment Shader
out vec2 texCoord;

// Camera matrix used for transforming vertices into view space
uniform mat4 camMatrix;

// Model transformation matrices for translating, rotating, and scaling
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	// Calculate the current world-space position of the vertex
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));

	// Pass the normal from the vertex data
	Normal = aNormal;

	// Pass the vertex color
	color = aColor;

	// Pass texture coordinates, rotated to match the texture orientation
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	// Calculate the final position of the vertex on screen
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}
