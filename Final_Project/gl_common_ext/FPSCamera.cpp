#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>

using namespace cs557;

FPSCamera::FPSCamera(vec3 eye, float pitch, float yaw)
{
	_eye = eye;
	_pitch = pitch;
	_yaw = yaw;
	isMousePressed = false;
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
	translation = translate(translation, _eye);

	viewMatrix = rotation * translation;
}

mat4 FPSCamera::GetViewMatrix() const
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
			dz = 2;
			break;
		case 's':
			dz = -2;
			break;
		case 'a':
			dx = -2;
			break;
		case 'd':
			dx = 2;
			break;
		default:
			break;
	}

	mat4 mat = GetViewMatrix();
	
	vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f;

	_eye += (dz * forward + -dx * strafe) * speed;

	UpdateView();
}

void FPSCamera::MouseMove(int x, int y, int width, int height)
{
	if (isMousePressed)
	{

		vec2 mouse_delta = vec2(x, y) - mousePosition;

		const float mouseX_Sensitivity = 0.01f;
		const float mouseY_Sensitivity = 0.01f;

		_yaw += mouseX_Sensitivity * mouse_delta.x;
		_pitch += mouseY_Sensitivity * mouse_delta.y;

		mousePosition = vec2(x, y);

		UpdateView();
	}
}
void FPSCamera::MousePressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isMousePressed = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}
