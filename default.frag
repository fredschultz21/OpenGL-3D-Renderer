#version 330 core

// Output color in RGBA format
out vec4 FragColor;

// Inputs received from the Vertex Shader
in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

// Texture units passed from the main program
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Light and camera information
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{	
	// Vector from the fragment to the light source
	vec3 lightVec = lightPos - crntPos;

	// Calculate light intensity based on distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// Ambient light (base brightness)
	float ambient = 0.20f;

	// Diffuse lighting (brightness based on angle)
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting (reflective highlights)
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// Combine ambient, diffuse, and specular lighting with textures
	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight()
{
	// Ambient light
	float ambient = 0.20f;

	// Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// Combine lighting and textures
	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	// Defines the sharpness and size of the light cone
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// Ambient lighting
	float ambient = 0.20f;

	// Diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// Determine how strongly the fragment is lit based on its angle inside the cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// Combine textures with lighting values
	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main()
{
	// Output the final fragment color using directional lighting
	FragColor = direcLight();
}
