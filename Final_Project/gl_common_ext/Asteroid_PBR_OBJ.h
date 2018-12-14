#pragma once
#include <string>
#include "TextureMaps.h"
#include "shader.h"
#include "Lights.h"
#include "ModelOBJ.h"
#include "FPSCamera.h"
#include "InitialTransform.h"
#include "ShaderFiles.h"
#include <vector>

namespace cs557 {

	class Asteroid_PBR_OBJ
	{
	public:
		Asteroid_PBR_OBJ();
		Asteroid_PBR_OBJ(std::string obj_path, TextureMaps textures, vector<Lights> lights, ShaderFiles pbr_shader_files, InitialTransform initial_transform);
		void Draw(mat4 projectionMatrix, FPSCamera camera, vector<Lights> lights);
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
		int delta_angle;
		void setup_PBR_shader(TextureMaps textures, vector<Lights> lights);
		void setup_lights(vector<Lights> light);
		unsigned int loadTexture(char const * path);
	};
}

