#pragma once
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;



namespace cs557
{
	class FPSCamera {

	public:
		FPSCamera();
		FPSCamera(vec3 eye, float pitch, float yaw);
		mat4 GetViewMatrix() const;
		void KeyPressed(bool* keyStates);
		void MouseMove(int x, int y, int width, int height);
		void MousePressed(int button, int state, int x, int y);
		vec3 GetPosition() const;

	private:
		mat4 viewMatrix;
		vec3 _eye;
		float _pitch;
		float _yaw;
		bool isLeftMousePressed;
		bool isRightMousePressed;
		vec2 mousePosition;
		void UpdateView();
	};
}