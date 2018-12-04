#pragma once
#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

using namespace glm;
using namespace std;
namespace cs557
{
	class SkyBox
	{
	public:
		SkyBox();
		SkyBox(string left, string right, string up, string down, string front, string back, int shader_program);
		void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
		unsigned int GetCubeMap() const;

	private:
		unsigned int cubemapTexture;
		unsigned int sky_VAO;
		unsigned int sky_VBO;
		int skyBox_program;
		GLint skyBoxViewMatrixLocation;
		GLint skyBoxProjMatrixLocation;
		unsigned int loadCubemap(vector<string> faces);
		void createCube();
	};
}
