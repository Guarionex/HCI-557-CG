
// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>  // transformation
#include <glm/gtx/quaternion.hpp> // quaternions

// glfw includes
#include <GLFW/glfw3.h>

// local
#include "Window.h" // the windows
#include "OpenGLDefaults.h" // some open gl and glew defaults
#include "VertexBuffers.h"  // create vertex buffer object
#include "ShaderProgram.h"  // create a shader program

// Geometry
#include "ModelCoordinateSystem.h"
#include "ModelSphere.h"

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

 // Store the model matrix, one per sphere
glm::mat4 modelMatrixSphere1;   
glm::mat4 modelMatrixSphere2;   
glm::mat4 modelMatrixSphere3;   
glm::mat4 modelMatrixSphere4;     
glm::mat4 modelMatrixCoordSystem; // for the coordinate system



//------------------------------------------------------------
//
//	Some model  to keep track of

// a corodinate system
cs557::CoordinateSystem coordinateSystem;

cs557::Sphere sphere1;
cs557::Sphere sphere2;
cs557::Sphere sphere3;
cs557::Sphere sphere4;

//------------------------------------------------------------
// Light and Material for the spheres
// Feel free to user more or different shader programs if you need to .
int per_vertex_light_program = -1;





// Set up our green background color
GLfloat clear_color[] = {0.6f, 0.7f, 1.0f, 1.0f};
GLfloat clear_depth[] = {1.0f, 1.0f, 1.0f, 1.0f};




/*--------------------------------------------------------------------------------------------------------
This function creates the first sphere
*/
void CreateSphere1(int shader_program_index)
{

    glUseProgram(shader_program_index);

    // create a sphere
    // Parameters
    // 1st: Radius of the sphere
    // 2nd: Number of segments
    // 3rd: Number of rows
    // 4th: The shader program index
    sphere1.create(1.0, 20, 20, shader_program_index);
    
   //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn


    //********************************************************************************


    // create a model matrix for the sphere
    modelMatrixSphere1 = glm::translate(glm::mat4(1.0f), glm::vec3(4.5f, 0.0f, 0.0f)); 


    glUseProgram(0);
}


/*--------------------------------------------------------------------------------------------------------
This function creates the first two
*/
void CreateSphere2(int shader_program_index)
{

    glUseProgram(shader_program_index);

    // create a sphere
    // Parameters
    // 1st: Radius of the sphere
    // 2nd: Number of segments
    // 3rd: Number of rows
    // 4th: The shader program index
    sphere2.create(1.0, 20, 20, shader_program_index);
    
    //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn


    //********************************************************************************


    // create a model matrix for the sphere
    modelMatrixSphere2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f)); 


    glUseProgram(0);
}


/*--------------------------------------------------------------------------------------------------------
This function creates the first two
*/
void CreateSphere3(int shader_program_index)
{

    glUseProgram(shader_program_index);

    // create a sphere
    // Parameters
    // 1st: Radius of the sphere
    // 2nd: Number of segments
    // 3rd: Number of rows
    // 4th: The shader program index
    sphere3.create(1.0, 20, 20, shader_program_index);
    
    //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn


    //********************************************************************************


    // create a model matrix for the sphere
    modelMatrixSphere3 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f)); 


    glUseProgram(0);
}



/*--------------------------------------------------------------------------------------------------------
This function creates the first two
*/
void CreateSphere4(int shader_program_index)
{

    glUseProgram(shader_program_index);

    // create a sphere
    // Parameters
    // 1st: Radius of the sphere
    // 2nd: Number of segments
    // 3rd: Number of rows
    // 4th: The shader program index
    sphere4.create(1.0, 20, 20, shader_program_index);
    
    //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn


    //********************************************************************************

    // create a model matrix for the sphere
    modelMatrixSphere4 = glm::translate(glm::mat4(1.0f), glm::vec3(-4.5f, 0.0f, 0.0f)); 


    glUseProgram(0);
}

//------------------------------------------------------------
//
//	INIT THE SCENE

void Init(void)
{

    // Init the GLFW Window
    window = cs557::initWindow();

    // Initialize the GLEW apis
    cs557::initGlew();

    //-----------------------------------------------------------------------------------------------------------------------
	// Projection transformations
	projectionMatrix = glm::perspective(1.2f, (float)800 / (float)600, 0.1f, 100.f);
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -9.f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrixCoordSystem = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 


    // create a coordinate system
    coordinateSystem.create(2.5);



    //-----------------------------------------------------------------------------------------------------------------------
	// Load a shader program from a file
    // This function is part of the file ShaderProgram.cpp/.h
    //
    // NOTE: BE AWARE OF THE FILE LOCATION AND THE STARTING POINT OF YOUR PROGRAM.
    // THE RELATIVE PATH ../homework_shader.vs/fs  EXPECTS THE SHADER TO BE ONE FOLDER UP IN THE HIERARCHY STARTING IN YOUR EXECUTABLE
    // FOLDER.
    per_vertex_light_program = LoadAndCreateShaderProgram("../homework_shader.vs", "../homework_shader.fs");


    //-----------------------------------------------------------------------------------------------------------------------
    // Create models

    CreateSphere1(per_vertex_light_program);
    CreateSphere2(per_vertex_light_program);
    CreateSphere3(per_vertex_light_program);
    CreateSphere4(per_vertex_light_program);

}

//------------------------------------------------------------
//
//	RENDER THE SCENE

void Draw(void)
{

    

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

        
        // This draws a coordinate system
        coordinateSystem.draw(projectionMatrix, rotated_view, modelMatrixCoordSystem);

        //----------------------------------------------------------------------------------------------------------------------------
        // update values
        glUseProgram(per_vertex_light_program);

        // NOTE, CURRENTLY ONLY ONE SHADER PROGRAM IS ACTIVE. IF YOU NEED ANOTHER ONE, SWITCH BEFORE YOU RENDER

        // draw the spheres
        sphere1.draw(projectionMatrix, rotated_view, modelMatrixSphere1);
        sphere2.draw(projectionMatrix, rotated_view, modelMatrixSphere2);
        sphere3.draw(projectionMatrix, rotated_view, modelMatrixSphere3);
        sphere4.draw(projectionMatrix, rotated_view, modelMatrixSphere4);

        //----------------------------------------------------------------------------------------------------------------------------

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


    Init();

    Draw();

    return 1;
}
