#include "Asteroid_PBR_OBJ.h"
#include <GL/glut.h>
#include "stb_image.h"
#include <GL/glew.h>

using namespace cs557;
Asteroid_PBR_OBJ::Asteroid_PBR_OBJ()
{
}

Asteroid_PBR_OBJ::Asteroid_PBR_OBJ(std::string obj_path, TextureMaps textures, Lights lights, ShaderFiles pbr_shader_files, InitialTransform initial_transform)
{
	pbr_shader = Shader(pbr_shader_files.vertex_shader.c_str(), pbr_shader_files.fragment_shader.c_str());
	emissionGlow = rand() % 25;
	original_transform = initial_transform;
	model_matrix = translate(mat4(1.0f), original_transform.position);
	model_matrix = scale(model_matrix, original_transform.scale);
	isFading = false;
	delta_angle = 0.0f;
	Setup_PBR_Shader(textures, lights);
	obj_model.create(obj_path, pbr_shader.ID);
	obj_model.setCubeMapTexture(textures.IrradianceTexture);
}

void Asteroid_PBR_OBJ::Draw(mat4 projectionMatrix, FPSCamera camera, Lights lights)
{
	pbr_shader.use();

	for (unsigned int i = 0; i < sizeof(lights.lightPositions) / sizeof(lights.lightPositions[0]); ++i)
	{
		pbr_shader.setVec3("lightPositions[" + std::to_string(i) + "]", lights.lightPositions[i]);
		pbr_shader.setVec3("lightColors[" + std::to_string(i) + "]", lights.lightColors[i]);
	}

	
	pbr_shader.setVec3("camPos", camera.GetPosition());
	obj_model.draw(projectionMatrix, camera.GetViewMatrix(), model_matrix);
}

void Asteroid_PBR_OBJ::animateAsteroid(int value)
{
	model_matrix = rotate(model_matrix, 0.005f * value, original_transform.rotation);
}

int Asteroid_PBR_OBJ::animateEmissionGlow(int value)
{
	int glowIncrement;
	if (isFading)
	{
		glowIncrement = -1;
	}
	else
	{
		glowIncrement = 1;
	}

	emissionGlow += glowIncrement;
	pbr_shader.use();
	pbr_shader.setInt("emissionGlow", emissionGlow);

	int callBackTime = value;
	if (emissionGlow >= 25)
	{
		isFading = true;
		callBackTime = 100;
	}
	else if (emissionGlow <= 0)
	{
		isFading = false;
		callBackTime = 1000;
	}

	return callBackTime;
}


Asteroid_PBR_OBJ::~Asteroid_PBR_OBJ()
{
}

void Asteroid_PBR_OBJ::Setup_PBR_Shader(TextureMaps textures, Lights lights)
{
	pbr_shader.use();
	pbr_shader.setInt("irradianceMap", 0);
	pbr_shader.setInt("albedoMap", 1);
	pbr_shader.setInt("normalMap", 2);
	pbr_shader.setInt("metallicMap", 3);
	pbr_shader.setInt("roughnessMap", 4);
	pbr_shader.setInt("aoMap", 5);
	pbr_shader.setInt("specularMap", 6);
	pbr_shader.setInt("emissionMap", 7);

	unsigned int albedo = loadTexture(textures.AlbedoMap.c_str());
	unsigned int normal = loadTexture("textures/asteroid/Normal180FlipHor.bmp");
	unsigned int metallic = loadTexture("textures/asteroid/Metalness180FlipHor.bmp");
	unsigned int roughness = loadTexture("textures/asteroid/Roughness.bmp");
	unsigned int ao = loadTexture("textures/asteroid/AO.bmp");
	unsigned int specular = loadTexture("textures/asteroid/Specular.bmp");
	unsigned int emission = loadTexture("textures/asteroid/Emission180FlipHor.bmp");

	for (unsigned int i = 0; i < sizeof(lights.lightPositions) / sizeof(lights.lightPositions[0]); ++i)
	{
		pbr_shader.setVec3("lightPositions[" + std::to_string(i) + "]", lights.lightPositions[i]);
		pbr_shader.setVec3("lightColors[" + std::to_string(i) + "]", lights.lightColors[i]);
	}

	pbr_shader.setInt("emissionGlow", emissionGlow);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, albedo);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, normal);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, metallic);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, roughness);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, ao);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, specular);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, emission);
}

unsigned int Asteroid_PBR_OBJ::loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
