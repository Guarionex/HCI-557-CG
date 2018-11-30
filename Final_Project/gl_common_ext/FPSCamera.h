#pragma once
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;



namespace cs557
{
	class FPSCamera {

	public:

		FPSCamera(vec3 eye, float pitch, float yaw);
		mat4 GetViewMatrix() const;
		void KeyPressed(const unsigned char key);
		void MouseMove(int x, int y, int width, int height);
		void MousePressed(int button, int state, int x, int y);

	private:
		mat4 viewMatrix;
		vec3 _eye;
		float _pitch;
		float _yaw;
		bool isMousePressed;
		vec2 mousePosition;
		void UpdateView();
	};
}