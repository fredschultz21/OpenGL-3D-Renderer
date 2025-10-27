#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	// Assign the type of the texture to this texture object
	type = texType;

	// Store image dimensions and number of color channels
	int widthImg, heightImg, numColCh;

	// Flip the image vertically so it appears upright in OpenGL
	stbi_set_flip_vertically_on_load(true);

	// Load the image data from the given file path
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generate a new OpenGL texture object and store its ID
	glGenTextures(1, &ID);

	// Activate the specified texture unit and bind this texture to it
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// Set the filtering methods for resizing the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set how the texture repeats across surfaces
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Optional: lines for GL_CLAMP_TO_BORDER usage
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Load the texture into OpenGL depending on how many color channels it has
	if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// Generate mipmaps for smoother texture scaling
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the loaded image data from CPU memory (already sent to GPU)
	stbi_image_free(bytes);

	// Unbind the texture to prevent accidental modification
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Get the location of the texture uniform inside the shader
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// Activate the shader program before modifying uniforms
	shader.Activate();

	// Set the uniform to point to the correct texture unit
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	// Activate the texture unit and bind this texture
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	// Unbind the texture from the current texture unit
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	// Delete this texture object from GPU memory
	glDeleteTextures(1, &ID);
}
