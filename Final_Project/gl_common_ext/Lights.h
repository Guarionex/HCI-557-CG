#pragma once
#include <glm/detail/type_vec3.hpp>

struct Lights
{
	glm::vec3 lightPositions[4];
	glm::vec3 lightColors[4];
	int radius[4];
	int radians_per_second[4];
	float angle[4];
};
