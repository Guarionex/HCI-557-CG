#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>

using namespace cs557;

FPSCamera::FPSCamera(vec3 eye, float roll, float pitch, float yaw)
{
	eyeVector = eye;
	_roll = roll;
	_pitch = pitch;
	_yaw = yaw;
	UpdateView();
}

void FPSCamera::UpdateView()
{
	mat4 matRoll = mat4(1.0f);
	mat4 matPitch = mat4(1.0f);
	mat4 matYaw = mat4(1.0f);

	matRoll = glm::rotate(matRoll, _roll, vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, _pitch, vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, _yaw, vec3(0.0f, 1.0f, 0.0f));

	mat4 rotation = matRoll * matPitch * matYaw;

	mat4 translation = mat4(1.0f);
	translation = translate(translation, eyeVector);

	viewMatrix = rotation * translation;
}

mat4 FPSCamera::GetViewMatrix()
{
	return viewMatrix;
}

void FPSCamera::KeyPressed(const unsigned char key)
{
	float dx = 0;
	float dz = 0;
	switch (key)
	{
	case 'w':
	{
		dz = 2;
		break;
	}

	case 's':
	{
		dz = -2;
		break;
	}
	case 'a':
	{
		dx = -2;
		break;
	}

	case 'd':
	{
		dx = 2;
		break;
	}
	default:
		break;
	}

	
	mat4 mat = GetViewMatrix();
	
	vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f;

	eyeVector += (dz * forward + -dx * strafe) * speed;

	UpdateView();
}

void FPSCamera::MouseMove(int x, int y, int width, int height)
{
	if (isMousePressed == false)
		return;
	//always compute delta
	//mousePosition is the last mouse position
	vec2 mouse_delta = vec2(x, y) - mousePosition;

	const float mouseX_Sensitivity = 0.01f;
	const float mouseY_Sensitivity = 0.01f;
	//note that yaw and pitch must be converted to radians.
	//this is done in UpdateView() by glm::rotate
	_yaw += mouseX_Sensitivity * mouse_delta.x;
	_pitch += mouseY_Sensitivity * mouse_delta.y;

	mousePosition = vec2(x, y);
	UpdateView();
}
void FPSCamera::MousePressed(int button, int state, int x, int y)
{

	if (state == GLUT_UP)
	{
		isMousePressed = false;
	}
	if (state == GLUT_DOWN)
	{
		isMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}
