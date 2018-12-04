
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
#include "stb_image.h"
#include "shader.h";

using namespace std;
using namespace cs557;

mat4 projectionMatrix;
mat4 viewMatrix;
mat4 modelMatrix;
mat4 modelMatrixCoord;

int const WIDTH = 1280;
int const HEIGHT = 1024;

FPSCamera camera;
SkyBox skyBox;
CoordinateSystem coordinateSystem;

int texture_program = -1;
int normal_map_program = -1;
int skyBox_program = -1;
int pbr_program = -1;

Plane plane0;
OBJModel obj_model;

GLfloat const clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
GLfloat const clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

int mode = 0;
int use_normalmap = 1;
bool MultiLoadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2,
	unsigned int* dst_texture_id, unsigned int* dst_texture_id2);
unsigned int loadTexture(char const * path);

unsigned int albedo;
unsigned int normal;
unsigned int metallic;
unsigned int roughness;
unsigned int ao;
unsigned int specular;
unsigned int emission;
Shader pbr_shader;
vec3 lightPositions[4];
vec3 lightColors[4];
unsigned int cubeMapTexture;
int emissionGlow = 1;
bool isFading = false;

void Init()
{
	initGlew();
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 200.f);
	modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	modelMatrixCoord = translate(mat4(1.0f), vec3(.0f, 0.0f, 0.0f));

	coordinateSystem.create(2.5);

	texture_program = LoadAndCreateShaderProgram("shaders/texture_program.vs", "shaders/texture_program.fs");
	normal_map_program = LoadAndCreateShaderProgram("shaders/normal_map_program.vs", "shaders/normal_map_program.fs");
	skyBox_program = LoadAndCreateShaderProgram("shaders/skybox.vs", "shaders/skybox.fs");
	pbr_shader = Shader("shaders/PBR.vs", "shaders/PBR.fs");
	//plane0.create(4.0, 4.0, texture_program);

	camera = FPSCamera(vec3(0.0f, 0.0f, 4.0f), 0, 0);

	skyBox = SkyBox("textures/leftImage.png", "textures/rightImage.png", "textures/upImage.png",
	                "textures/downImage.png", "textures/frontImage.png", "textures/backImage.png", skyBox_program);
	cubeMapTexture = skyBox.GetCubeMap();

	pbr_shader.use();
	pbr_shader.setInt("irradianceMap", 0);
	pbr_shader.setInt("albedoMap", 1);
	pbr_shader.setInt("normalMap", 2);
	pbr_shader.setInt("metallicMap", 3);
	pbr_shader.setInt("roughnessMap", 4);
	pbr_shader.setInt("aoMap", 5);
	pbr_shader.setInt("specularMap", 6);
	pbr_shader.setInt("emissionMap", 7);

	albedo = loadTexture("textures/asteroid/Albedo180FlipHor.bmp");
	normal = loadTexture("textures/asteroid/Normal180FlipHor.bmp");
	metallic = loadTexture("textures/asteroid/Metalness180FlipHor.bmp");
	roughness = loadTexture("textures/asteroid/Roughness.bmp");
	ao = loadTexture("textures/asteroid/AO.bmp");
	specular = loadTexture("textures/asteroid/Specular.bmp");
	emission = loadTexture("textures/asteroid/Emission180FlipHor.bmp");
	lightPositions[0] = vec3(0.0f, 0.0f, 10.0f);
	lightColors[0] = vec3(75.0f, 75.0f, 75.0f);
	lightPositions[1] = vec3(2.0f, 0.0f, 4.0f);
	lightColors[1] = vec3(25.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{
		pbr_shader.setVec3("lightPositions[" + std::to_string(i) + "]", lightPositions[i]);
		pbr_shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
	}
	pbr_shader.setInt("emissionGlow", emissionGlow);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, albedo);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, normal);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, metallic);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, roughness);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, ao);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, specular);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, emission);

	obj_model.create("models/asteroid/A7.obj", pbr_shader.ID);
	obj_model.setCubeMapTexture(cubeMapTexture);
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	mat4 rotated_view = camera.GetViewMatrix();
	
	coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrixCoord);
	//plane0.draw(projectionMatrix, rotated_view, modelMatrix);

	pbr_shader.use();
	pbr_shader.setVec3("camPos", camera.GetPosition());

	obj_model.draw(projectionMatrix, rotated_view, modelMatrix);
	
	skyBox.Draw(projectionMatrix, rotated_view);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	camera.KeyPressed(key);

	if (key == 'r')
	{
		emissionGlow = 0;
		pbr_shader.use();
		pbr_shader.setInt("emissionGlow", emissionGlow);

	}
	else if (key == 'm')
	{
		emissionGlow += 1;
		pbr_shader.use();
		pbr_shader.setInt("emissionGlow", emissionGlow);
	}
	else if (key == 'n')
	{
		emissionGlow -= 1;
		pbr_shader.use();
		pbr_shader.setInt("emissionGlow", emissionGlow);
	}

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
	camera.MouseMove(x, y, WIDTH, HEIGHT);
	glutPostRedisplay();
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void animateEmissionGlow(int value)
{
	int glowIncrement = 0;
	if(isFading)
	{
		glowIncrement = -1;
	}
	else
	{
		glowIncrement = 1;
	}

	emissionGlow += glowIncrement;
	pbr_shader.use();
	pbr_shader.setInt("emissionGlow", emissionGlow);

	int callBackTime = value;
	if(emissionGlow >= 25)
	{
		isFading = true;
		callBackTime = 100;
	}
	else if(emissionGlow <= 0)
	{
		isFading = false;
		callBackTime = 1000;
	}
	glutPostRedisplay();
	glutTimerFunc(callBackTime, animateEmissionGlow, value);
}

void animateAsteroid(int value)
{
	modelMatrix = rotate(modelMatrix, 0.005f, vec3(-1.0, 1.0, 1.0));

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