
// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GLFW/glfw3.h>

// local
#define GLM_ENABLE_EXPERIMENTAL
#include "Window.h"
#include "OpenGLDefaults.h"
#include "VertexBuffers.h"
#include "ShaderProgram.h"
#include "Texture2D.h"


// Geometry
#include "ModelCoordinateSystem.h"
#include "ModelPlane.h"
#include <GL/glut.h>
#include "FPSCamera.h"

using namespace std;
using namespace cs557;

mat4 projectionMatrix;
mat4 viewMatrix;
mat4 modelMatrix;
mat4 modelMatrixCoord;

float eye_x = 0.0f;
float eye_y = 0.0f;
float eye_z = -4.0f;

int xOrigin = 1280 / 2;
int yOrigin = 1024 / 2;

FPSCamera camera = FPSCamera(vec3(eye_x, eye_y, eye_z), 0, 0, 0);

CoordinateSystem coordinateSystem;

int texture_program = -1;

Plane plane0;

GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

void Init(void)
{
	initGlew();
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 100.f);
	modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	modelMatrixCoord = translate(mat4(1.0f), vec3(.0f, 0.0f, 0.0f));

	coordinateSystem.create(2.5);

	texture_program = LoadAndCreateShaderProgram("shaders/texture_program.vs", "shaders/texture_program.fs");

	plane0.create(4.0, 4.0, texture_program);
}

void Draw(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, clear_depth);

	mat4 rotated_view = camera.GetViewMatrix();
	
	coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrixCoord);
	plane0.draw(projectionMatrix, rotated_view, modelMatrix);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	camera.KeyPressed(key);

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (GLfloat)w / (GLfloat)h, 0.10, 100.0);
}

void mouse(int button, int state, int x, int y)
{
	camera.MousePressed(button, state, x, y);
}

void mouse_motion(int x, int y)
{
	camera.MouseMove(x, y, 1280, 1024);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 1024);
	glutCreateWindow("CprE 557 Final Project");
	Init();
	glutWarpPointer(xOrigin, yOrigin);
	glutReshapeFunc(reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutMainLoop();
	return 1;
}