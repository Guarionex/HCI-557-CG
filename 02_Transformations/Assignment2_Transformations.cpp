
// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>			// transformation
#include <glm/gtx/quaternion.hpp>			// quaternions

// glfw includes
#include <GLFW/glfw3.h>

// local
#include "Window.h"					// the windows
#include "OpenGLDefaults.h"			// some open gl and glew defaults
#include "VertexBuffers.h"			// create vertex buffer object
#include "ShaderProgram.h"			// create a shader program
#include "ShaderCode.h"				// file containing shader code

// Geometry
#include "ModelCoordinateSystem.h"

using namespace std;


//------------------------------------------------------------
// 
//	Some global variables to keep track of 

glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix
int projectionMatrixLocation;
int viewMatrixLocation;
int modelMatrixLocation;

// The handle to the window object
GLFWwindow*         window = NULL;




// Memory to store the vertex array objects and buffer object ids

int vaoID[2]; // Our Vertex Array Object

int vboID[4]; // Our Vertex Buffer Object

int program;




//------------------------------------------------------------
// 
//	Some model  to keep track of 

// a corodinate system
cs557::CoordinateSystem coordinateSystem;




//------------------------------------------------------------
// 
//	INIT THE SCENE

void Init(void)
{

	// Init the GLFW Window
	window = cs557::initWindow();


	// Initialize the GLEW apis
	cs557::initGlew();

	// create a coordinate system
	coordinateSystem.create(2.0);


	float _width = 1.0;
	float _height = 1.0;
	float _length = 1.0;

	float center_x = 0.0;
	float center_y = 0.0;
	float center_z = 0.0;

	float vertices[] = {
		//--------------------------------------------------------
		// xy-plane, positive z direction
		-_width / 2.0 + center_x, -_height / 2.0 + center_y, _length / 2.0 + center_z,
		-_width / 2.0 + center_x, _height / 2.0 + center_y, _length / 2.0 + center_z,
		_width / 2.0 + center_x, -_height / 2.0 + center_y,  _length / 2.0 + center_z,
		_width / 2.0 + center_x, _height / 2.0 + center_y, _length / 2.0 + center_z,
		//--------------------------------------------------------
		// xy-plane, negative z direction
		_width / 2.0 + center_x, -_height / 2.0 + center_y, -_length / 2.0 + center_z,
		_width / 2.0 + center_x, _height / 2.0 + center_y,  -_length / 2.0 + center_z,
		-_width / 2.0 + center_x, -_height / 2.0 + center_y,  -_length / 2.0 + center_z,
		-_width / 2.0 + center_x, _height / 2.0 + center_y, -_length / 2.0 + center_z,
		//--------------------------------------------------------
		// yz-plane, positive x direction
		_width / 2.0 + center_x, -_height / 2.0 + center_y,  _length / 2.0 + center_z,
		_width / 2.0 + center_x, _height / 2.0 + center_y, _length / 2.0 + center_z,
		_width / 2.0 + center_x, -_height / 2.0 + center_y, -_length / 2.0 + center_z,
		_width / 2.0 + center_x,  _height / 2.0 + center_y, -_length / 2.0 + center_z,
		//--------------------------------------------------------
		// yz-plane, negative x direction
		-_width / 2.0 + center_x, -_height / 2.0 + center_y,  _length / 2.0 + center_z,
		-_width / 2.0 + center_x, _height / 2.0 + center_y, _length / 2.0 + center_z,
		-_width / 2.0 + center_x, -_height / 2.0 + center_y, -_length / 2.0 + center_z,
		-_width / 2.0 + center_x,  _height / 2.0 + center_y, -_length / 2.0 + center_z,
		//--------------------------------------------------------
		// xz-plane, positive y direction
		-_width / 2.0 + center_x, _height / 2.0 + center_y, _length / 2.0 + center_z,
		-_width / 2.0 + center_x, _height / 2.0 + center_y, -_length / 2.0 + center_z,
		_width / 2.0 + center_x, _height / 2.0 + center_y,  _length / 2.0 + center_z,
		_width / 2.0 + center_x, _height / 2.0 + center_y, -_length / 2.0 + center_z,
		//--------------------------------------------------------
		// xz-plane, negative y direction
		-_width / 2.0 + center_x, -_height / 2.0 + center_y, _length / 2.0 + center_z,
		-_width / 2.0 + center_x, -_height / 2.0 + center_y, -_length / 2.0 + center_z,
		_width / 2.0 + center_x, -_height / 2.0 + center_y,  _length / 2.0 + center_z,
		_width / 2.0 + center_x, -_height / 2.0 + center_y, -_length / 2.0 + center_z,
	};





	float colors[] = { 1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0 ,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0 ,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, 1.0, 0.0 ,
		1.0, 1.0, 0.0,
		1.0, 1.0, 0.0,
		1.0, 0.0, 1.0,
		1.0, 0.0, 1.0 ,
		1.0, 0.0, 1.0,
		1.0, 0.0, 1.0,
		0.2, 0.5, 0.5,
		0.2, 0.5, 0.5 ,
		0.2, 0.5, 0.5,
		0.2, 0.5, 0.5
	};


	// create a vertex buffer object
	cs557::CreateVertexObjects33(vaoID, vboID, vertices, colors, 24);


	// create a shader program
	program = cs557::CreateShaderProgram(cs557::vs_string_simple_shader_410, cs557::fs_string_simple_shader_410);


	// Update the location of all attributes, the vertex position and the colors in our case
	int pos_location = glGetAttribLocation(program, "in_Position");
	int col_location = glGetAttribLocation(program, "in_Color");
	glBindAttribLocation(program, pos_location, "in_Position");
	glBindAttribLocation(program, col_location, "in_Color");



	//-----------------------------------------------------------------------------------------------------------------------
	// Projection transformations
	// TODO: ADD TRANSFORMATIONS HERE
	projectionMatrix = perspective(1.57f, 800.0f / 600.0f, 0.1f, 100.f);
	viewMatrix = lookAt(vec3(0.0f, 0.0f, 1.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));





	//-----------------------------------------------------------------------------------------------------------------------
	// Shader source locations
	// TODO: Get the location of your gpu (fragment shader code and vertex shader code) variables here. 
	projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
	modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");




	//-----------------------------------------------------------------------------------------------------------------------
	// Update all variables
	// TODO: Send all varibales, it content to the gpu
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);



	


}




//------------------------------------------------------------
// 
//	ReNDER THE SCENE

void Draw(void)
{

	// Set up our green background color
	static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	// Enable depth test
	glEnable(GL_DEPTH_TEST); // ignore this line

	while (!glfwWindowShouldClose(window))
	{

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This renders the objects

		// update the camera values. 
		// Note that this line changes the view matrix.
		glm::mat4 rotated_view = viewMatrix * cs557::GetTrackball().getRotationMatrix();
		
		//First transform
		mat4 translatedModel = translate(modelMatrix, vec3(0.0f, 0.0f, 0.5f));
		mat4 firstTransform = glm::rotate(translatedModel, radians(45.0f), vec3(0, 1, 0));
		
		//Quaternion Transform
		quat quatRotation(cos(radians(45.0f / 2.0f)), 0, sin(radians(45.0f / 2.0f)), 0);
		mat4 secondTransform = translatedModel * toMat4(quatRotation);

		//Manual Transformation
		GLfloat manualTranslation[16] = {cos(radians(45.0f)), 0.0f, -sin(radians(45.0f)), 0.0f,
										 0.0f, 1.0f, 0.0f, 0.0f,
										 sin(radians(45.0f)), 0.0f, cos(radians(45.0f)), 0.0f,
										 0.0f, 0.0f, 0.5f, 1.0f};
		mat4 thirdTransform = modelMatrix * make_mat4(manualTranslation);

		// This draws a coordinate system
		coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrix);




		//-----------------------------------------------------------------------------------------------------------------------
		// Update all variables
		// TODO: Send all varibales, it content to the gpu
		glUseProgram(program);

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]);
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

		//Original model matrix
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

		//Model rotated 45 degrees on Y-axis and moved 0.5 along Z-axis
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &firstTransform[0][0]);

		//Model rotated 45 degrees on Y-axis using quaternion and moved 0.5 along Z-axis
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &secondTransform[0][0]);

		//Model rotated 45 degrees on Y-axis and moved 0.5 along Z-axis with manual matrix
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &thirdTransform[0][0]);

		glBindVertexArray(vaoID[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
		glBindVertexArray(0);

		glUseProgram(0);

		//// This renders the objects
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}




int main(int argc, char * argv[])
{

	// Initialization
	Init();

	// Rendering loop
	Draw();

	return 1;
}