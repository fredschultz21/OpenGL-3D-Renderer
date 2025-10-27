// If TEXTURE_CLASS_H is not yet defined, define it.
// This prevents multiple definitions of the class during compilation.
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

// Include OpenGL functionality and image loading support.
#include<glad/glad.h>
#include<stb/stb_image.h>

// Include the Shader class to connect textures with shader uniforms.
#include"shaderClass.h"


// The Texture class is responsible for loading an image file,
// generating an OpenGL texture, and binding it to a shader.
// It also manages texture cleanup and unbinding.
class Texture
{
public:
	// The unique OpenGL ID reference for this texture.
	GLuint ID;

	// The type of texture (for example: "diffuse", "specular", etc.)
	const char* type;

	// The texture unit slot that this texture will be bound to.
	GLuint unit;

	// Constructor that loads the image from file, generates the texture,
	// and assigns it to a texture slot.
	Texture(const char* image, const char* texType, GLuint slot);

	// Assigns a texture unit to a texture uniform in the shader.
	// Links this texture to a specific uniform variable in the shader program.
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// Binds this texture so it becomes active for rendering.
	void Bind();

	// Unbinds the currently bound texture, resetting the active texture slot.
	void Unbind();

	// Deletes this texture from OpenGL memory to free up resources.
	void Delete();
};

// Ends the header guard — if the class was already defined, skip everything above.
#endif
