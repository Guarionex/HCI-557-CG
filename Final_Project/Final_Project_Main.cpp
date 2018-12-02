
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

Plane plane0;
OBJModel obj_model;

GLfloat const clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
GLfloat const clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

int mode = 0;
int use_normalmap = 1;
bool MultiLoadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2,
	unsigned int* dst_texture_id, unsigned int* dst_texture_id2);

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

	//plane0.create(4.0, 4.0, texture_program);

	camera = FPSCamera(vec3(0.0f, 0.0f, -4.0f), 0, 0);

	skyBox = SkyBox("textures/leftImage.png", "textures/rightImage.png", "textures/upImage.png",
	                "textures/downImage.png", "textures/frontImage.png", "textures/backImage.png", skyBox_program);

	glUseProgram(normal_map_program);
	obj_model.create("models/asteroid/A7.obj", normal_map_program);
	unsigned int texture_id = -1;
	unsigned int texture_normal_id = -1;
	MultiLoadAndCreateTextures("textures/asteroid/Albedo.bmp", "textures/asteroid/Normal.bmp", &texture_id, &texture_normal_id);
	int texture_location = glGetUniformLocation(normal_map_program, "tex");
	int texture_normal_location = glGetUniformLocation(normal_map_program, "tex_normalmap");
	glUniform1i(texture_location, 0);
	glUniform1i(texture_normal_location, 1);

	glUniform1i(glGetUniformLocation(normal_map_program, "use_normalmap"), use_normalmap);
	glUniform1i(glGetUniformLocation(normal_map_program, "mode"), mode);
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
	obj_model.draw(projectionMatrix, rotated_view, modelMatrix);
	skyBox.Draw(projectionMatrix, rotated_view);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	camera.KeyPressed(key);

	if (key == 'r')
	{
		mode = 0;

		glUseProgram(normal_map_program);
		glUniform1i(glGetUniformLocation(normal_map_program, "mode"), mode);
		glUseProgram(0);

	}
	else if (key == 'm')
	{
		mode += 1;
		if (mode > 5) mode = 0;

		glUseProgram(normal_map_program);
		glUniform1i(glGetUniformLocation(normal_map_program, "mode"), mode);
		glUseProgram(0);
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

bool MultiLoadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2,
	unsigned int* dst_texture_id, unsigned int* dst_texture_id2)
{

	int channels1;
	int width1;
	int height1;

	int channels2;
	int width2;
	int height2;

	unsigned char* data1;
	unsigned char* data2;

	LoadBMPFromFile(path_and_file_texture_1, &width1, &height1, &channels1, &data1);
	LoadBMPFromFile(path_and_file_texture_2, &width2, &height2, &channels2, &data2);

	if (data1 == NULL || data2 == NULL)return false;


	//**********************************************************************************************
	// Texture generation - background

	// Activate a texture unit
	glActiveTexture(GL_TEXTURE0);

	// Generate a texture, this function allocates the memory and
	// associates the texture with a variable.
	glGenTextures(1, dst_texture_id);

	// Set a texture as active texture.
	glBindTexture(GL_TEXTURE_2D, *dst_texture_id);

	// Change the parameters of your texture units.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Create a texture and load it to your graphics hardware. This texture is automatically associated
	// with texture 0 and the textuer variable "texture" / the active texture.
	if (channels1 == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_BGR, GL_UNSIGNED_BYTE, data1);
	else if (channels1 == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_BGRA, GL_UNSIGNED_BYTE, data1);

	//**********************************************************************************************
	// Create a midmap texture pyramid and load it to the graphics hardware.
	// Note, the MIN and MAG filter must be set to one of the available midmap filters.
	//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );

	// Delete your loaded data
	free(data1);




	//**********************************************************************************************
	// Texture light

	// Activate a texture unit
	glActiveTexture(GL_TEXTURE1);

	// Generate a texture, this function allocates the memory and
	// associates the texture with a variable.
	glGenTextures(1, dst_texture_id2);

	// Set a texture as active texture.
	glBindTexture(GL_TEXTURE_2D, *dst_texture_id2);

	// Change the parameters of your texture units.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Create a texture and load it to your graphics hardware. This texture is automatically associated
	// with texture 0 and the textuer variable "texture" / the active texture.
	if (channels2 == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_BGR, GL_UNSIGNED_BYTE, data2);
	else if (channels2 == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_BGRA, GL_UNSIGNED_BYTE, data2);

	//**********************************************************************************************
	// Create a midmap texture pyramid and load it to the graphics hardware.
	// Note, the MIN and MAG filter must be set to one of the available midmap filters.
	//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );

	// Delete your loaded data
	free(data2);

	return true;
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
	glutMainLoop();
	return 1;
}