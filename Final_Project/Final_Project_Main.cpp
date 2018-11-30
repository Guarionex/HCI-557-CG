
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
#include <glm/gtx/transform.hpp>  // transformation
#include <glm/gtx/quaternion.hpp> // quaternions

// glfw includes
#include <GLFW/glfw3.h>

// local
#define GLM_ENABLE_EXPERIMENTAL
#include "Window.h" // the windows
#include "OpenGLDefaults.h" // some open gl and glew defaults
#include "VertexBuffers.h"  // create vertex buffer object
#include "ShaderProgram.h"  // create a shader program
#include "Texture2D.h"


// Geometry
#include "ModelCoordinateSystem.h"
#include "ModelPlane.h"
#include <GL/glut.h>
#include "FPSCamera.h"

using namespace std;
using namespace cs557;
//------------------------------------------------------------
//
//	Some global variables to keep track of

// The handle to the window object
GLFWwindow *window = NULL;

// Transformation pipeline variables

mat4 projectionMatrix; // Store the projection matrix
mat4 viewMatrix;       // Store the view matrix
mat4 modelMatrix;      // Store the model matrix
mat4 modelMatrixCoord;

GLfloat X = 0.0f;		// Translate screen to x direction (left or right)
GLfloat Y = 0.0f;		// Translate screen to y direction (up or down)
GLfloat Z = 0.0f;		// Translate screen to z direction (zoom in or out)
GLfloat rotX = 0.0f;	// Rotate screen on x axis 
GLfloat rotY = 0.0f;	// Rotate screen on y axis
GLfloat rotZ = 0.0f;	// Rotate screen on z axis

GLfloat rotLx = 0.0f;   // Translate screen by using  the glulookAt function (left or right)
GLfloat rotLy = 0.0f;   // Translate screen by using  the glulookAt function (up or down)
GLfloat rotLz = 0.0f;   // Translate screen by using  the glulookAt function (zoom in or out)

float eye_x = 0.0f;
float eye_y = 0.0f;
float eye_z = -4.0f;
float center_x = 0.0f;
float center_y = 0.0f;
float center_z = 0.0f;

int xOrigin = 1280 / 2;
int yOrigin = 1024 / 2;

FPSCamera camera = FPSCamera(vec3(eye_x, eye_y, eye_z), 0, 0, 0);
//------------------------------------------------------------
//
//	Some model  to keep track of

// a corodinate system
CoordinateSystem coordinateSystem;



int texture_program = -1;

Plane plane0;


// Set up our green background color
GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };


// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//cout << key ;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == 84 && action == GLFW_PRESS) // t
	{

	}
	else if (key == 46 && action == GLFW_PRESS)
	{

	}
	else if (key == 44 && action == GLFW_PRESS)
	{


	}
	else if (key == 66 && action == GLFW_PRESS)
	{


	}


}





//------------------------------------------------------------
//
//	INIT THE SCENE

void Init(void)
{

	// Init the GLFW Window
	//window = cs557::initWindow();

	// set a keyboard callback
	//glfwSetKeyCallback(window, my_key_callback);

	// Initialize the GLEW apis
	initGlew();


	//-----------------------------------------------------------------------------------------------------------------------
	// Projection transformations
	projectionMatrix = perspective(1.57f, (float)800 / (float)600, 0.1f, 100.f);
	modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	viewMatrix = camera.GetViewMatrix();//lookAt(vec3(eye_x, eye_y, eye_z), vec3(center_x, center_y, center_z), vec3(0.0f, 1.0f, 0.0f));
	modelMatrixCoord = translate(mat4(1.0f), vec3(.0f, 0.0f, 0.0f));


	// create a coordinate system
	coordinateSystem.create(2.5);

	//--------------------------------------------------------------------------------
	// Note that you have to modify the default texture program since it only 
	// renders a single texture
	// Load the shader program
	texture_program = LoadAndCreateShaderProgram("shaders/texture_program.vs", "shaders/texture_program.fs");



	// create a plane.
	// PASS THE TEXTURE PROGRAM AS VARIABLE TO THE PLANE
	plane0.create(4.0, 4.0, texture_program);


	//-------------------------------------------------------------
	//-------------------------------------------------------------
	//
	// TODO
	//
	// 1. Load the textures
	// 2. Bind them to texture targets and texture units.
	// 3. Assign the texture unit to a glsl uniform sampler 2D variable. 





}

//------------------------------------------------------------
//
//	RENDER THE SCENE

void Draw(void)
{



	// Enable depth test
	glEnable(GL_DEPTH_TEST); // ignore this line

	//while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);				// Clear the Color Buffer 
		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		
		glPushMatrix();								// It is important to push the Matrix before calling glRotatef and glTranslatef
		//glRotatef(rotX, 1.0, 0.0, 0.0);				// Rotate on x
		//glRotatef(rotY, 0.0, 1.0, 0.0);				// Rotate on y
		//glRotatef(rotZ, 0.0, 0.0, 1.0);				// Rotate on z
		//glTranslatef(X, Y, Z);						// Translates the screen left or right, up or down or zoom in zoom out

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This renders the objects

		// update the camera values.
		// Note that this line changes the view matrix.
		mat4 otherViewMatrix = lookAt(vec3(eye_x, eye_y, eye_z), vec3(center_x, center_y, center_z), vec3(0.0f, 1.0f, 0.0f));
		mat4 rotated_view = camera.GetViewMatrix();
		//glm::mat4 rotated_view = viewMatrix * cs557::GetTrackball().getRotationMatrix();
		//rotated_view = rotate(rotated_view, rotX, vec3(1.0, 0.0, 0.0));
		//rotated_view = rotate(rotated_view, rotY, vec3(0.0, 1.0, 0.0));
		//rotated_view = rotate(rotated_view, rotZ, vec3(0.0, 0.0, 1.0));
		//rotated_view = translate(rotated_view, vec3(X, Y, Z));
		//rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0
		//rotated_view = lookAt(vec3(rotLx, rotLy, 15.0 + rotLz), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
		//----------------------------------------------------------------------------------------------------------------------------
		// Object 0
		// This draws a coordinate system
		coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrixCoord);



		// draw the plane
		plane0.draw(projectionMatrix, rotated_view, modelMatrix);


		// Swap the buffers so that what we drew will appear on the screen.
		glPopMatrix();							// Don't forget to pop the Matrix
		glutSwapBuffers();
	}
}

// This function is used for the navigation keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

		// x,X,y,Y,z,Z uses the glRotatef() function
	case 'x':				// Rotates screen on x axis 
		rotX -= 0.5f;
		break;
	case 'X':				// Opposite way 
		rotX += 0.5f;
		break;
	case 'y':				// Rotates screen on y axis
		rotY -= 0.5f;
		break;
	case 'Y':				// Opposite way
		rotY += 0.5f;
		break;
	case 'z':				// Rotates screen on z axis
		rotZ -= 0.5f;
		break;
	case 'Z':				// Opposite way
		rotZ += 0.5f;
		break;

		// j,J,k,K,l,L uses the gluLookAt function for navigation
	case 'j':
		rotLx -= 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'J':
		rotLx += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'k':
		rotLy -= 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'K':

		rotLy += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'l': // It has a special case when the rotLZ becames less than -15 the screen is viewed from the opposite side
			  // therefore this if statement below does not allow rotLz be less than -15
		if (rotLz + 14 >= 0)
			rotLz -= 0.2f;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'L':
		rotLz += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'b':				// Rotates on x axis by -90 degree
		rotX -= 90.0f;
		break;
	case 'B':				// Rotates on y axis by 90 degree
		rotX += 90.0f;
		break;
	case 'n':				// Rotates on y axis by -90 degree
		rotY -= 90.0f;
		break;
	case 'N':				// Rotates on y axis by 90 degree
		rotY += 90.0f;
		break;
	case 'm':				// Rotates on z axis by -90 degree
		rotZ -= 90.0f;
		break;
	case 'M':				// Rotates on z axis by 90 degree
		rotZ += 90.0f;
		break;
	case 'o':				// Default, resets the translations vies from starting view
	case 'O':
		X = Y = 0.0f;
		Z = 0.0f;
		rotX = 0.0f;
		rotY = 0.0f;
		rotZ = 0.0f;
		rotLx = 0.0f;
		rotLy = 0.0f;
		rotLz = 0.0f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0f + rotLz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		break;
	}

	camera.KeyPressed(key);

	glutPostRedisplay();	// Redraw the scene
}

// called on special key pressed
void specialKey(int key, int x, int y) {

	// The keys below are using the gluLookAt() function for navigation
	// Check which key is pressed
	switch (key) {
	case GLUT_KEY_LEFT:    // Rotate on x axis
		X -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:	// Rotate on x axis (opposite)
		X += 0.1f;
		break;
	case GLUT_KEY_UP:		// Rotate on y axis 
		Y += 0.1f;
		break;
	case GLUT_KEY_DOWN:	// Rotate on y axis (opposite)
		Y -= 0.1f;
		break;
	case GLUT_KEY_PAGE_UP:  // Roatae on z axis
		Z -= 0.1f;
		break;
	case GLUT_KEY_PAGE_DOWN:// Roatae on z axis (opposite)
		Z += 0.1f;
		break;
	}
	glutPostRedisplay();		// Redraw the scene
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);				// Set the viewport
	glMatrixMode(GL_PROJECTION);								// Set the Matrix mode
	glLoadIdentity();
	gluPerspective(75, (GLfloat)w / (GLfloat)h, 0.10, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{
	camera.MousePressed(button, state, x, y);
}

void passive_motion(int x, int y)
{
	cout << "Mouse is at (" << x << "," << y << ")";
	cout << " center_x = " << center_x << ", center_y = " << center_y << ", center_z = " << center_z << "";
	
	int delta_angle_x = (x - xOrigin);
	int delta_angle_y = (y - yOrigin);
	vec3 newCenter;
	if(delta_angle_x > 0)
	{
		//center_x -= 0.1f;
		newCenter = rotate(vec3(center_x, center_y, center_z), -1.1f, vec3(0.0, 1.0, 0.0));
		//viewMatrix = translate(viewMatrix, vec3(center_x, center_y, center_z));
	}
	else if (delta_angle_x < 0)
	{

		//center_x += 0.1f;
		newCenter = rotate(vec3(center_x, center_y, center_z), 1.1f, vec3(0.0, 1.0, 0.0));
		//viewMatrix = translate(viewMatrix, vec3(center_x, center_y, center_z));
	}
	
	cout << " New_x = " << newCenter.x << ", New_y = " << newCenter.y << ", New_z = " << newCenter.z << "\n";
	center_x = newCenter.x;
	center_y = newCenter.y;
	center_z = newCenter.z;

	//if (delta_angle_y > 0)
	//{
	//	center_y -= 0.1f;
	//}
	//else if (delta_angle_y < 0)
	//{
	//	center_y += 0.1f;
	//}

	if (x != xOrigin || y != yOrigin) glutWarpPointer(xOrigin, yOrigin);
	glutPostRedisplay();
}

void mouse_motion(int x, int y)
{
	camera.MouseMove(x, y, 1280, 1024);
	glutPostRedisplay();
}

//------------------------------------------------------------
//
//	RENDER THE SCENE
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);		// Setup display mode to double buffer and RGB color
	glutInitWindowSize(1280, 1024);						// Set the screen size
	glutCreateWindow("OpenGL 3D Navigation Program");
	Init();
	//glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(xOrigin, yOrigin);
	glutReshapeFunc(reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyboard);		// set window's key callback 
	glutSpecialFunc(specialKey);	// set window's to specialKey callback
	glutMouseFunc(mouse);
	//glutPassiveMotionFunc(passive_motion);
	glutMotionFunc(mouse_motion);
	glutMainLoop();
	return 1;
}