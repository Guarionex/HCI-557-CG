#pragma once
#include <glm/detail/type_vec3.hpp>
#include <vector>

struct Lights
{
	std::vector<glm::vec3> lightPositions;
	std::vector <glm::vec3> lightColors;
	std::vector<int> radius;
	std::vector<int> radians_per_second;
	std::vector<float> angle;
};
