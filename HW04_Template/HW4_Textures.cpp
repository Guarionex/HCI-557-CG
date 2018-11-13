
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
//#include "Texture.h"

using namespace std;
using namespace cs557;
//------------------------------------------------------------
//
//	Some global variables to keep track of

// The handle to the window object
GLFWwindow *window = NULL;

// Transformation pipeline variables

glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix;       // Store the view matrix
glm::mat4 modelMatrix;      // Store the model matrix
glm::mat4 modelMatrixCoord;


//------------------------------------------------------------
//
//	Some model  to keep track of

// a corodinate system
cs557::CoordinateSystem coordinateSystem;



int texture_program = -1;

cs557::Plane plane0;


// Set up our green background color
GLfloat clear_color[] = {0.6f, 0.7f, 1.0f, 1.0f};
static const GLfloat clear_depth[] = {1.0f, 1.0f, 1.0f, 1.0f};

bool MultiLoadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2, string path_and_file_texture_3,
	unsigned int* dst_texture_id, unsigned int* dst_texture_id2, unsigned int* dst_texture_id3);
// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   //cout << key ;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if(key == 84 && action == GLFW_PRESS) // t
    {
        
    }
    else if(key == 46 && action == GLFW_PRESS)
    {
        
    }
    else if(key == 44 && action == GLFW_PRESS)
    {
       
        
    }
    else if(key == 66 && action == GLFW_PRESS)
    {
    

    }


}





//------------------------------------------------------------
//
//	INIT THE SCENE

void Init(void)
{

    // Init the GLFW Window
    window = cs557::initWindow();

    // set a keyboard callback
    glfwSetKeyCallback(window, my_key_callback);

    // Initialize the GLEW apis
    cs557::initGlew();


    //-----------------------------------------------------------------------------------------------------------------------
	// Projection transformations
	projectionMatrix = glm::perspective(1.57f, (float)800 / (float)600, 0.1f, 100.f);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -4.f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrixCoord = glm::translate(glm::mat4(1.0f), glm::vec3(.0f, 0.0f, 0.0f)); 


    // create a coordinate system
    coordinateSystem.create(2.5);

    //--------------------------------------------------------------------------------
    // Note that you have to modify the default texture program since it only 
    // renders a single texture
    // Load the shader program
    texture_program = cs557::LoadAndCreateShaderProgram("multi_texture.vs", "multi_texture.fs");

    

    // create a plane.
    // PASS THE TEXTURE PROGRAM AS VARIABLE TO THE PLANE
    plane0.create(4.0, 4.0, texture_program);


    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //
    // TODO
    //
    // 1. Load the textures
	//GLMultiTexture* texture = new GLMultiTexture();
	glUseProgram(texture_program);
	unsigned int texture_id = -1;
	unsigned int texture_id2 = -1;
	unsigned int texture_id3 = -1;
	//LoadAndCreateTexture2D("Texture/Ozzy3.bmp", &texture_id);
	//LoadAndCreateTexture2D("Texture/ColorGradient.bmp", &texture_id2);
	MultiLoadAndCreateTextures("Texture/ColorGradient.bmp", "Texture/Ozzy3.bmp", "Texture/LakeNightLandscapeSquared.bmp", &texture_id, &texture_id2, &texture_id3);
    // 2. Bind them to texture targets and texture units.
	//glActiveTexture(GL_TEXTURE0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture_id);
	//glBindTexture(GL_TEXTURE_2D, texture_id2);
    // 3. Assign the texture unit to a glsl uniform sampler 2D variable. 
	int texture_location = glGetUniformLocation(texture_program, "texture_background");
	int texture_location2 = glGetUniformLocation(texture_program, "texture_foreground");
	int texture_location3 = glGetUniformLocation(texture_program, "texture_midground");
	int blend_mode = glGetUniformLocation(texture_program, "texture_blend");
	glUniform1i(texture_location, 0);
	glUniform1i(texture_location2, 1);
	glUniform1i(texture_location3, 2);
	glUniform1i(blend_mode, 2);




}

bool MultiLoadAndCreateTextures(string path_and_file_texture_1, string path_and_file_texture_2, string path_and_file_texture_3,
                                     unsigned int* dst_texture_id, unsigned int* dst_texture_id2, unsigned int* dst_texture_id3)
{

	int channels1;
	int width1;
	int height1;

	int channels2;
	int width2;
	int height2;

	int channels3;
	int width3;
	int height3;

	unsigned char* data1;
	unsigned char* data2;
	unsigned char* data3;

	LoadBMPFromFile(path_and_file_texture_1, &width1, &height1, &channels1, &data1);
	LoadBMPFromFile(path_and_file_texture_2, &width2, &height2, &channels2, &data2);
	LoadBMPFromFile(path_and_file_texture_3, &width3, &height3, &channels3, &data3);

	if (data1 == NULL || data2 == NULL || data3 == NULL)return false;


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



	//**********************************************************************************************

	// Activate a texture unit
	glActiveTexture(GL_TEXTURE2);

	// Generate a texture, this function allocates the memory and
	// associates the texture with a variable.
	glGenTextures(1, dst_texture_id3);

	// Set a texture as active texture.
	glBindTexture(GL_TEXTURE_2D, *dst_texture_id3);

	// Change the parameters of your texture units.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Create a texture and load it to your graphics hardware. This texture is automatically associated
	// with texture 0 and the textuer variable "texture" / the active texture.
	if (channels2 == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_BGR, GL_UNSIGNED_BYTE, data3);
	else if (channels2 == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_BGRA, GL_UNSIGNED_BYTE, data3);

	//**********************************************************************************************
	// Create a midmap texture pyramid and load it to the graphics hardware.
	// Note, the MIN and MAG filter must be set to one of the available midmap filters.
	//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );

	// Delete your loaded data
	free(data3);



	return true;



}

//------------------------------------------------------------
//
//	RENDER THE SCENE

void Draw(void)
{

    

    // Enable depth test
    glEnable(GL_DEPTH_TEST); // ignore this line

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        //----------------------------------------------------------------------------------------------------------------------------
        // Object 0
        // This draws a coordinate system
        coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrixCoord);



        // draw the plane
        plane0.draw(projectionMatrix, rotated_view, modelMatrix);


        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}








//------------------------------------------------------------
//
//	RENDER THE SCENE
int main(int argc, const char *argv[])
{
    cout << "This code example demonstrates texture mapping." << endl;
    cout << "Rafael Radkowski\nrafael@iastate.edu\nIowa State University" << endl;
    cout << "This example is part of ME/CS/CPRE557" << endl;



    Init();

    Draw();

    return 1;
}
