#pragma once
#include <string>
#include "TextureMaps.h"
#include "shader.h"
#include "Lights.h"
#include "ModelOBJ.h"
#include "FPSCamera.h"
#include "InitialTransform.h"
#include "ShaderFiles.h"

namespace cs557 {

	class Asteroid_PBR_OBJ
	{
	public:
		Asteroid_PBR_OBJ();
		Asteroid_PBR_OBJ(std::string obj_path, TextureMaps textures, Lights lights, ShaderFiles pbr_shader_files, InitialTransform initial_transform);
		void Draw(mat4 projectionMatrix, FPSCamera camera);
		void animateAsteroid(int value);
		int animateEmissionGlow(int value);
		~Asteroid_PBR_OBJ();

	private:
		Shader pbr_shader;
		int emissionGlow;
		OBJModel obj_model;
		InitialTransform original_transform;
		mat4 model_matrix;
		bool isFading;
		void Setup_PBR_Shader(TextureMaps textures, Lights lights);
		unsigned int loadTexture(char const * path);
	};
}

