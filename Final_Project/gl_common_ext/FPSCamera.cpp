#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>

using namespace cs557;
FPSCamera::FPSCamera()
{
}

FPSCamera::FPSCamera(vec3 eye, float pitch, float yaw)
{
	_eye = eye;
	_pitch = pitch;
	_yaw = yaw;
	isLeftMousePressed = false;
	isRightMousePressed = false;
	UpdateView();
}

void FPSCamera::UpdateView()
{
	mat4 matPitch = mat4(1.0f);
	mat4 matYaw = mat4(1.0f);

	matPitch = glm::rotate(matPitch, _pitch, vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, _yaw, vec3(0.0f, 1.0f, 0.0f));

	mat4 rotation = matPitch * matYaw;

	mat4 translation = mat4(1.0f);
	translation = translate(translation, -_eye);

	viewMatrix = rotation * translation;
}

mat4 FPSCamera::GetViewMatrix() const
{
	return viewMatrix;
}

void FPSCamera::KeyPressed(bool* keyStates)
{
	float dx = 0;
	float dz = 0;

	if(keyStates['w'] && !keyStates['s'])
	{
		dz = 2;
	}
	else if(keyStates['s'] && !keyStates['w'])
	{
		dz = -2;
	}

	if(keyStates['a'] && !keyStates['d'])
	{
		dx = -2;
	}
	else if(keyStates['d'] && !keyStates['a'])
	{
		dx = 2;
	}

	mat4 mat = GetViewMatrix();
	
	vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f;

	_eye += (-dz * forward + dx * strafe) * speed;

	UpdateView();
}

void FPSCamera::MouseMove(int x, int y, int width, int height)
{
	if (isLeftMousePressed)
	{

		vec2 mouse_delta = vec2(x, y) - mousePosition;

		const float mouseX_Sensitivity = 0.01f;
		const float mouseY_Sensitivity = 0.01f;

		_yaw += mouseX_Sensitivity * mouse_delta.x;
		_pitch += mouseY_Sensitivity * mouse_delta.y;

		mousePosition = vec2(x, y);

		UpdateView();
	}
	else if(isRightMousePressed)
	{
		vec2 mouse_delta = vec2(x, y) - mousePosition;

		const float mouseX_Sensitivity = 0.01f;
		const float mouseY_Sensitivity = 0.01f;

		float horizontalDrag = mouseX_Sensitivity * mouse_delta.x;
		float verticalDrag = mouseY_Sensitivity * mouse_delta.y;

		mousePosition = vec2(x, y);

		mat4 mat = GetViewMatrix();

		vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
		vec3 vert(mat[0][1], mat[1][1], mat[2][1]);

		const float speed = 0.24f;

		_eye += (-horizontalDrag * strafe + verticalDrag * vert) * speed;

		UpdateView();
	}
}
void FPSCamera::MousePressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isLeftMousePressed = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isLeftMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isRightMousePressed = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isRightMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}

vec3 FPSCamera::GetPosition() const
{
	return _eye;
}
