#pragma once
#include <glm/detail/type_vec3.hpp>
#include <vector>

struct Lights
{
	std::vector<glm::vec3> lightPositions;
	std::vector <glm::vec3> lightColors;
	std::vector<float> radius;
	std::vector<float> pi_cuts_per_second;
	std::vector<float> angle;
};
