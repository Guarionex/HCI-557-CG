
// stl include
#include <iostream>
#include <string>
#include <vector>

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
#include "ShaderFiles.h"

using namespace std;
using namespace cs557;

mat4 projectionMatrix;
mat4 viewMatrix;

int const WIDTH = 1280;
int const HEIGHT = 1024;
bool* keyStates;

FPSCamera camera;
SkyBox skyBox;

int skyBox_program = -1;

Asteroid_PBR_OBJ asteroid;
Asteroid_PBR_OBJ asteroid2;
Asteroid_PBR_OBJ asteroid3;
Asteroid_PBR_OBJ asteroid4;
Asteroid_PBR_OBJ asteroid5;

vector<Lights> lights;
float const PI = 3.14159f;
int const ONE_SECOND_IN_MILLISECOND = 1000;

void Init()
{
	initGlew();
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 200.f);

	keyStates = new bool[256];
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

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

	lights = 
	{
		{
			{ vec3(0.0f, 0.0f, 10.0f)},
			{ vec3(75.0f, 75.0f, 75.0f)},
			{ 10.0f},
			{ 8.0f},
			{ 1.570796326794896619231321691639751442098584699687552910487f}
		},
		{
			{ vec3(2.0f, 0.0f, 4.0f) },
			{ vec3(25.0f, 0.0f, 0.0f) },
			{ 4.47213595f},
			{ -8.0f },
			{ 1.10714871f }
		}
	};

	InitialTransform initial_transform {vec3(0.0f, 0.0f, 0.0f), vec3(-1.0, 1.0, 1.0), vec3(1.0f, 1.0f, 1.0f)};

	InitialTransform initial_transform2 {vec3(10.0f, 0.0f, 0.0f), vec3(1.0, -1.0, -1.0), vec3(2.0f, 2.0f, 2.0f)};

	InitialTransform initial_transform3	{vec3(3.0f, 4.0f, 14.0f), vec3(-1.0, 1.0, 0.0), vec3(3.0f, 3.0f, 3.0f)};
	
	InitialTransform initial_transform4 {vec3(20.0f, 4.0f, -13.0f), vec3(-1.0, 1.0, -1.0), vec3(4.0f, 4.0f, 4.0f)};

	InitialTransform initial_transform5 {vec3(-16.0f, 7.0f, 0.0f), vec3(1.0, -1.0, 1.0), vec3(5.0f, 5.0f, 5.0f)};

	ShaderFiles pbr_shader {"shaders/PBR.vs", "shaders/PBR.fs"};

	asteroid = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, pbr_shader, initial_transform);
	asteroid2 = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, pbr_shader, initial_transform2);
	asteroid3 = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, pbr_shader, initial_transform3);
	asteroid4 = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, pbr_shader, initial_transform4);
	asteroid5 = Asteroid_PBR_OBJ("models/asteroid/A7.obj", textures, lights, pbr_shader, initial_transform5);
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	mat4 rotated_view = camera.GetViewMatrix();

	asteroid.Draw(projectionMatrix, camera, lights);
	asteroid2.Draw(projectionMatrix, camera, lights);
	asteroid3.Draw(projectionMatrix, camera, lights);
	asteroid4.Draw(projectionMatrix, camera, lights);
	asteroid5.Draw(projectionMatrix, camera, lights);
	
	skyBox.Draw(projectionMatrix, rotated_view);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	camera.KeyPressed(keyStates);
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
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
	asteroid2.animateEmissionGlow(value);
	asteroid3.animateEmissionGlow(value);
	asteroid4.animateEmissionGlow(value);
	asteroid5.animateEmissionGlow(value);

	glutPostRedisplay();
	glutTimerFunc(callBackTime, animateEmissionGlow, value);
}

void animateAsteroid(int value)
{
	asteroid.animateAsteroid(value);
	asteroid2.animateAsteroid(value * 10);
	asteroid3.animateAsteroid(value * 2);
	asteroid4.animateAsteroid(value * 4);
	asteroid5.animateAsteroid(value * 6);

	glutPostRedisplay();
	glutTimerFunc(value, animateAsteroid, value);
}

void animateLights(int time)
{

	for (unsigned int i = 0; i < lights.size(); ++i)
	{
		float x = lights[i].radius * cos(lights[i].angle);
		float z = lights[i].radius * sin(lights[i].angle);

		lights[i].lightPositions.x = x;
		lights[i].lightPositions.z = z;

		int steps_in_a_second = ONE_SECOND_IN_MILLISECOND / time;
		float angle_per_second = 2 * PI / lights[i].pi_cuts_per_second;
		lights[i].angle += angle_per_second / steps_in_a_second;
	}
	glutPostRedisplay();
	glutTimerFunc(time, animateLights, time);
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
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutTimerFunc(100, animateEmissionGlow, 100);
	glutTimerFunc(100, animateAsteroid, 1);
	glutTimerFunc(100, animateLights, 100);
	glutMainLoop();
	return 1;
}