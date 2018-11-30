#pragma once
#include <algorithm>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;



namespace cs557
{
	class FPSCamera {

	public:

		FPSCamera(vec3 eye, float roll, float pitch, float yaw);
		void UpdateView();
		mat4 GetViewMatrix();
		void KeyPressed(const unsigned char key);
		void MouseMove(int x, int y, int width, int height);
		void MousePressed(int button, int state, int x, int y);

	private:
		mat4 viewMatrix;
		vec3 eyeVector;
		float _roll;
		float _pitch;
		float _yaw;
		bool isMousePressed;
		vec2 mousePosition;
	};
}