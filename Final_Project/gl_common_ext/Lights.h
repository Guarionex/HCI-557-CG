#pragma once
#include <glm/detail/type_vec3.hpp>

struct Lights
{
	glm::vec3 lightPositions;
	glm::vec3 lightColors;
	float radius;
	float pi_cuts_per_second;
	float angle;
};
