
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
int red_directional_light_program = -1;
int blue_directional_light_program = -1;
int green_spotlight_program = -1;
int yellow_spotlight_program = -1;





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
    sphere1.create(1.0, 100, 100, shader_program_index);
    
   //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn
	vec3 diffuseMaterial = vec3(1.0, 0.0, 0.0);
	vec3 ambientMaterial = vec3(1.0, 0.0, 0.0);
	vec3 specularMaterial = vec3(1.0, 1.0, 1.0);
	float shininess = 150.0;

	int diffuseColorPos = glGetUniformLocation(shader_program_index, "diffuse_color");
	int ambientColorPos = glGetUniformLocation(shader_program_index, "ambient_color");
	int specularColorPos = glGetUniformLocation(shader_program_index, "specular_color");
	int shininessPos = glGetUniformLocation(shader_program_index, "shininess");

	glUniform3fv(diffuseColorPos, 1, &diffuseMaterial[0]);
	glUniform3fv(ambientColorPos, 1, &ambientMaterial[0]);
	glUniform3fv(specularColorPos, 1, &specularMaterial[0]);
	glUniform1f(shininessPos, shininess);

	vec4 lightPos = vec4(-4.0, 0.0, -4.5, 1.0);
	float diffuseIntensity = 4.0;
	float ambientIntensity = 0.1;
	float specularIntensity = 10.0;
	float attenuationCoeff = 0.02;

	int lightPosId = glGetUniformLocation(shader_program_index, "light_position");
	int diffuseIntesityId = glGetUniformLocation(shader_program_index, "diffuse_intensity");
	int ambientIntesityId = glGetUniformLocation(shader_program_index, "ambient_intensity");
	int specularIntesityId = glGetUniformLocation(shader_program_index, "specular_intensity");
	int attenuationCoeffId = glGetUniformLocation(shader_program_index, "attenuation_Coefficient");

	glUniform4fv(lightPosId, 1, &lightPos[0]);
	glUniform1f(diffuseIntesityId, diffuseIntensity);
	glUniform1f(ambientIntesityId, ambientIntensity);
	glUniform1f(specularIntesityId, specularIntensity);
	glUniform1f(attenuationCoeffId, attenuationCoeff);

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
	vec3 diffuseMaterial = vec3(0.0, 0.0, 1.0);
	vec3 ambientMaterial = vec3(0.0, 0.0, 1.0);
	vec3 specularMaterial = vec3(1.0, 1.0, 1.0);
	float shininess = 150.0;

	int diffuseColorPos = glGetUniformLocation(shader_program_index, "diffuse_color");
	int ambientColorPos = glGetUniformLocation(shader_program_index, "ambient_color");
	int specularColorPos = glGetUniformLocation(shader_program_index, "specular_color");
	int shininessPos = glGetUniformLocation(shader_program_index, "shininess");

	glUniform3fv(diffuseColorPos, 1, &diffuseMaterial[0]);
	glUniform3fv(ambientColorPos, 1, &ambientMaterial[0]);
	glUniform3fv(specularColorPos, 1, &specularMaterial[0]);
	glUniform1f(shininessPos, shininess);

	vec4 lightPos = vec4(-1.5, 0.0, -2.0, 0.0);
	float diffuseIntensity = 1.0;
	float ambientIntensity = 0.0;
	float specularIntensity = 0.0;
	float attenuationCoeff = 0.02;

	int lightPosId = glGetUniformLocation(shader_program_index, "light_position");
	int diffuseIntesityId = glGetUniformLocation(shader_program_index, "diffuse_intensity");
	int ambientIntesityId = glGetUniformLocation(shader_program_index, "ambient_intensity");
	int specularIntesityId = glGetUniformLocation(shader_program_index, "specular_intensity");
	int attenuationCoeffId = glGetUniformLocation(shader_program_index, "attenuation_Coefficient");

	glUniform4fv(lightPosId, 1, &lightPos[0]);
	glUniform1f(diffuseIntesityId, diffuseIntensity);
	glUniform1f(ambientIntesityId, ambientIntensity);
	glUniform1f(specularIntesityId, specularIntensity);
	glUniform1f(attenuationCoeffId, attenuationCoeff);

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
    sphere3.create(1.0, 500, 500, shader_program_index);
    
    //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn
	vec3 diffuseMaterial = vec3(0.0, 1.0, 0.0);
	vec3 ambientMaterial = vec3(0.0, 1.0, 0.0);
	vec3 specularMaterial = vec3(1.0, 1.0, 1.0);
	float shininess = 150.0;

	int diffuseColorPos = glGetUniformLocation(shader_program_index, "diffuse_color");
	int ambientColorPos = glGetUniformLocation(shader_program_index, "ambient_color");
	int specularColorPos = glGetUniformLocation(shader_program_index, "specular_color");
	int shininessPos = glGetUniformLocation(shader_program_index, "shininess");

	glUniform3fv(diffuseColorPos, 1, &diffuseMaterial[0]);
	glUniform3fv(ambientColorPos, 1, &ambientMaterial[0]);
	glUniform3fv(specularColorPos, 1, &specularMaterial[0]);
	glUniform1f(shininessPos, shininess);

	vec4 lightPos = vec4(-2.5, 0.0, -4.5, 1.0);
	float diffuseIntensity = 20.0;
	float ambientIntensity = 0.0;
	float specularIntensity = 5.0;
	float attenuationCoeff = 0.02;
	float coneAngle = 13.0;
	vec3 coneDirection = vec3(0.3, 0.15, 1.0);

	int lightPosId = glGetUniformLocation(shader_program_index, "light_position");
	int diffuseIntesityId = glGetUniformLocation(shader_program_index, "diffuse_intensity");
	int ambientIntesityId = glGetUniformLocation(shader_program_index, "ambient_intensity");
	int specularIntesityId = glGetUniformLocation(shader_program_index, "specular_intensity");
	int attenuationCoeffId = glGetUniformLocation(shader_program_index, "attenuation_Coefficient");
	int coneAngleId = glGetUniformLocation(shader_program_index, "cone_angle");
	int coneDirectionId = glGetUniformLocation(shader_program_index, "cone_direction");

	glUniform4fv(lightPosId, 1, &lightPos[0]);
	glUniform1f(diffuseIntesityId, diffuseIntensity);
	glUniform1f(ambientIntesityId, ambientIntensity);
	glUniform1f(specularIntesityId, specularIntensity);
	glUniform1f(attenuationCoeffId, attenuationCoeff);
	glUniform1f(coneAngleId, coneAngle);
	glUniform3fv(coneDirectionId, 1, &coneDirection[0]);

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
    sphere4.create(1.0, 500, 500, shader_program_index);
    
    //********************************************************************************
    // TODO:
    // Define all paramters that you need to render the light and material for the sphere
    // and copy the values to your shader program. 

    // Your turn
	vec3 diffuseMaterial = vec3(0.5, 0.5, 0.05);
	vec3 ambientMaterial = vec3(0.5, 0.5, 0.05);
	vec3 specularMaterial = vec3(1.0, 1.0, 1.0);
	float shininess = 150.0;

	int diffuseColorPos = glGetUniformLocation(shader_program_index, "diffuse_color");
	int ambientColorPos = glGetUniformLocation(shader_program_index, "ambient_color");
	int specularColorPos = glGetUniformLocation(shader_program_index, "specular_color");
	int shininessPos = glGetUniformLocation(shader_program_index, "shininess");

	glUniform3fv(diffuseColorPos, 1, &diffuseMaterial[0]);
	glUniform3fv(ambientColorPos, 1, &ambientMaterial[0]);
	glUniform3fv(specularColorPos, 1, &specularMaterial[0]);
	glUniform1f(shininessPos, shininess);

	vec4 lightPosSpotlight = vec4(-4.5, 0.0, -4.5, 1.0);
	float diffuseIntensitySpotlight = 15.0;
	float ambientIntensitySpotlight = 0.3;
	float specularIntensitySpotlight = 5.0;
	float attenuationCoeffSpotlight = 0.02;
	float coneAngle = 13.0;
	vec3 coneDirection = vec3(0.25, 0.3, 1.0);

	int lightPosSpotlightId = glGetUniformLocation(shader_program_index, "light_position_spotlight");
	int diffuseIntesitySpotlightId = glGetUniformLocation(shader_program_index, "diffuse_intensity_spotlight");
	int ambientIntesitySpotlightId = glGetUniformLocation(shader_program_index, "ambient_intensity_spotlight");
	int specularIntesitySpotlightId = glGetUniformLocation(shader_program_index, "specular_intensity_spotlight");
	int attenuationCoeffSpotlightId = glGetUniformLocation(shader_program_index, "attenuation_Coefficient_spotlight");
	int coneAngleId = glGetUniformLocation(shader_program_index, "cone_angle");
	int coneDirectionId = glGetUniformLocation(shader_program_index, "cone_direction");

	glUniform4fv(lightPosSpotlightId, 1, &lightPosSpotlight[0]);
	glUniform1f(diffuseIntesitySpotlightId, diffuseIntensitySpotlight);
	glUniform1f(ambientIntesitySpotlightId, ambientIntensitySpotlight);
	glUniform1f(specularIntesitySpotlightId, specularIntensitySpotlight);
	glUniform1f(attenuationCoeffSpotlightId, attenuationCoeffSpotlight);
	glUniform1f(coneAngleId, coneAngle);
	glUniform3fv(coneDirectionId, 1, &coneDirection[0]);

	vec4 lightPosDirectional = vec4(4.0, -4.0, -5.0, 1.0);
	float diffuseIntensityDirectional = 10.0;
	float ambientIntensityDirectional = 0.0;
	float specularIntensityDirectional = 1.5;
	float attenuationCoeffDirectional = 0.02;

	int lightPosDirectionalId = glGetUniformLocation(shader_program_index, "light_position_directional");
	int diffuseIntesityDirectionalId = glGetUniformLocation(shader_program_index, "diffuse_intensity_directional");
	int ambientIntesityDirectionalId = glGetUniformLocation(shader_program_index, "ambient_intensity_directional");
	int specularIntesityDirectionalId = glGetUniformLocation(shader_program_index, "specular_intensity_directional");
	int attenuationCoeffDirectionalId = glGetUniformLocation(shader_program_index, "attenuation_Coefficient_directional");

	glUniform4fv(lightPosDirectionalId, 1, &lightPosDirectional[0]);
	glUniform1f(diffuseIntesityDirectionalId, diffuseIntensityDirectional);
	glUniform1f(ambientIntesityDirectionalId, ambientIntensityDirectional);
	glUniform1f(specularIntesityDirectionalId, specularIntensityDirectional);
	glUniform1f(attenuationCoeffDirectionalId, attenuationCoeffDirectional);

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

	red_directional_light_program = LoadAndCreateShaderProgram("Shaders/DirectionalLight.vs", "Shaders/DirectionalLight.fs");
	blue_directional_light_program = LoadAndCreateShaderProgram("Shaders/DirectionalLight.vs", "Shaders/DirectionalLight.fs");
	green_spotlight_program = LoadAndCreateShaderProgram("Shaders/Spotlight.vs", "Shaders/Spotlight.fs");
	yellow_spotlight_program = LoadAndCreateShaderProgram("Shaders/DirectionalSpotlightMix.vs", "Shaders/DirectionalSpotlightMix.fs");
    per_vertex_light_program = LoadAndCreateShaderProgram("Shaders/homework_shader.vs", "Shaders/homework_shader.fs");


    //-----------------------------------------------------------------------------------------------------------------------
    // Create models

    CreateSphere1(red_directional_light_program);
    CreateSphere2(blue_directional_light_program);
    CreateSphere3(green_spotlight_program);
    CreateSphere4(yellow_spotlight_program);

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
