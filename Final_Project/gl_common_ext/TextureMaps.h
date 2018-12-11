#pragma once
#include <string>

struct TextureMaps
{
	std::string AlbedoMap;
	std::string NormalMap;
	std::string MetallicMap;
	std::string RoughnessMap;
	std::string AmbientOcclusionMap;
	std::string SpecularMap;
	std::string EmissionMap;
	unsigned int IrradianceTexture;
};
