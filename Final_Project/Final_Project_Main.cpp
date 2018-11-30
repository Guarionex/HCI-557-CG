
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

FPSCamera camera = FPSCamera(vec3(eye_x, eye_y, eye_z), 0, 0);

CoordinateSystem coordinateSystem;

int texture_program = -1;
int skyBox_program = -1;

Plane plane0;

GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

unsigned int cubemapTexture = -1;
unsigned int sky_VAO;
unsigned int sky_VBO;
unsigned int loadCubemap(vector<std::string> faces);
void createCube();
GLint skyBoxViewMatrixLocation;
GLint skyBoxProjMatrixLocation;



void Init(void)
{
	initGlew();
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 200.f);
	modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	modelMatrixCoord = translate(mat4(1.0f), vec3(.0f, 0.0f, 0.0f));

	coordinateSystem.create(2.5);

	texture_program = LoadAndCreateShaderProgram("shaders/texture_program.vs", "shaders/texture_program.fs");
	skyBox_program = LoadAndCreateShaderProgram("shaders/skybox.vs", "shaders/skybox.fs");

	plane0.create(4.0, 4.0, texture_program);

	vector<std::string> faces
	{
		"textures/leftImage.png",
		"textures/rightImage.png",
		"textures/upImage.png",
		"textures/downImage.png",
		"textures/frontImage.png",
		"textures/backImage.png"
	};
	cubemapTexture = loadCubemap(faces);
	createCube();
	skyBoxViewMatrixLocation = glGetUniformLocation(skyBox_program, "view"); // Get the location of our view matrix in the shader
	skyBoxProjMatrixLocation = glGetUniformLocation(skyBox_program, "projection"); // Get the location of our projection matrix in the shader
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

	glDepthFunc(GL_LEQUAL);
	glUseProgram(skyBox_program);

	mat4 skyBoxView = mat4(mat3(rotated_view));
	glUniformMatrix4fv(skyBoxViewMatrixLocation, 1, GL_FALSE, &skyBoxView[0][0]);
	glUniformMatrix4fv(skyBoxProjMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glBindVertexArray(sky_VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthFunc(GL_LESS);

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

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void createCube()
{
	float skyboxVertices[] = {
		// positions          
	-100.0f,  100.0f, -100.0f,
	-100.0f, -100.0f, -100.0f,
	 100.0f, -100.0f, -100.0f,
	 100.0f, -100.0f, -100.0f,
	 100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,

	-100.0f, -100.0f,  100.0f,
	-100.0f, -100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f,  100.0f,
	-100.0f, -100.0f,  100.0f,

	 100.0f, -100.0f, -100.0f,
	 100.0f, -100.0f,  100.0f,
	 100.0f,  100.0f,  100.0f,
	 100.0f,  100.0f,  100.0f,
	 100.0f,  100.0f, -100.0f,
	 100.0f, -100.0f, -100.0f,

	-100.0f, -100.0f,  100.0f,
	-100.0f,  100.0f,  100.0f,
	 100.0f,  100.0f,  100.0f,
	 100.0f,  100.0f,  100.0f,
	 100.0f, -100.0f,  100.0f,
	-100.0f, -100.0f,  100.0f,

	-100.0f,  100.0f, -100.0f,
	 100.0f,  100.0f, -100.0f,
	 100.0f,  100.0f,  100.0f,
	 100.0f,  100.0f,  100.0f,
	-100.0f,  100.0f,  100.0f,
	-100.0f,  100.0f, -100.0f,

	-100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f,  100.0f,
	 100.0f, -100.0f, -100.0f,
	 100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f,  100.0f,
	 100.0f, -100.0f,  100.0f
	};

	glGenVertexArrays(1, &sky_VAO);
	glBindVertexArray(sky_VAO);

	glGenBuffers(1, &sky_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, sky_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
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