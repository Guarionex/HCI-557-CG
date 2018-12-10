
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
#include "ModelOBJ.h"


// Geometry
#include "ModelCoordinateSystem.h"
#include "ModelPlane.h"
#include <GL/glut.h>
#include "FPSCamera.h"
#include "Skybox.h"
#include "Asteroid_PBR_OBJ.h"
#include "InitialTransform.h"

using namespace std;
using namespace cs557;

mat4 projectionMatrix;
mat4 viewMatrix;

int const WIDTH = 1280;
int const HEIGHT = 1024;

FPSCamera camera;
SkyBox skyBox;

int skyBox_program = -1;

Asteroid_PBR_OBJ asteroid;

void Init()
{
	initGlew();
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 200.f);

	skyBox_program = LoadAndCreateShaderProgram("shaders/skybox.vs", "shaders/skybox.fs");

	camera = FPSCamera(vec3(0.0f, 0.0f, 4.0f), 0, 0);

	skyBox = SkyBox("textures/leftImage.png", "textures/rightImage.png", "textures/upImage.png",
	                "textures/downImage.png", "textures/frontImage.png", "textures/backImage.png", skyBox_program);
	unsigned int cubeMapTexture = skyBox.GetCubeMap();

	TextureMaps textures
	{
		"textures/asteroid/Albedo180FlipHor.bmp",
		"textures/asteroid/Normal180FlipHor.bmp",
		"textures/asteroid/Metalness180FlipHor.bmp",
		"textures/asteroid/Roughness.bmp",
		"textures/asteroid/AO.bmp",
		"textures/asteroid/Specular.bmp",
		"textures/asteroid/Emission180FlipHor.bmp",
		cubeMapTexture
	};

	Lights lights
	{
		{
			vec3(0.0f, 0.0f, 10.0f),
			vec3(2.0f, 0.0f, 4.0f)
		},
		{
			vec3(75.0f, 75.0f, 75.0f),
			vec3(25.0f, 0.0f, 0.0f)
		}
	};

	InitialTransform initial_transform
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(-1.0, 1.0, 1.0),
		vec3(1.0f, 1.0f, 1.0f)
	};

	asteroid = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, "shaders/PBR.vs", "shaders/PBR.fs", initial_transform);
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	mat4 rotated_view = camera.GetViewMatrix();

	asteroid.Draw(projectionMatrix, camera);
	
	skyBox.Draw(projectionMatrix, rotated_view);

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
	float aspect_ratio = (float)w / (float)h;
	float fovy = 1.57f / aspect_ratio;
	projectionMatrix = perspective(fovy, (float)w / (float)h, 0.1f, 200.f);
}

void mouse(int button, int state, int x, int y)
{
	camera.MousePressed(button, state, x, y);
}

void mouse_motion(int x, int y)
{
	camera.MouseMove(x, y, WIDTH, HEIGHT);
	glutPostRedisplay();
}

void animateEmissionGlow(int value)
{
	int callBackTime = asteroid.animateEmissionGlow(value);
	glutPostRedisplay();
	glutTimerFunc(callBackTime, animateEmissionGlow, value);
}

void animateAsteroid(int value)
{
	asteroid.animateAsteroid(value);

	glutPostRedisplay();
	glutTimerFunc(value, animateAsteroid, value);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("CprE 557 Final Project");
	Init();
	glutWarpPointer(WIDTH / 2, HEIGHT / 2);
	glutReshapeFunc(reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutTimerFunc(100, animateEmissionGlow, 100);
	glutTimerFunc(100, animateAsteroid, 100);
	glutMainLoop();
	return 1;
}