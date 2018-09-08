//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
	// TODO: Create your vertices for a triangle strip representation.
    // use the vertex array object vaoID[0] to store the model
	float* vertices = new float[138];
	float *colors = new float[138];

	//Back Front
	vertices[0] = -1.0; vertices[1] = 1.0; vertices[2] = -1.0; //V0
	colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0;

	vertices[3] = -1.0; vertices[4] = 0.0; vertices[5] = -1.0; //V1
	colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0;

	vertices[6] = 0.0; vertices[7] = 1.0; vertices[8] = -1.0; //V2
	colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0;

	vertices[9] = 0.0; vertices[10] = -1.0; vertices[11] = -1.0; //V3
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0;

	vertices[12] = 2.0; vertices[13] = 0.0; vertices[14] = -1.0; //V4
	colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0;

	vertices[15] = 2.0; vertices[16] = -1.0; vertices[17] = -1.0; //V5
	colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0;

	//Back Right
	vertices[18] = 2.0; vertices[19] = 0.0; vertices[20] = -2.0; //V6
	colors[18] = 0.0; colors[19] = 1.0; colors[20] = 0.0;

	vertices[21] = 2.0; vertices[22] = -1.0; vertices[23] = -2.0; //V7
	colors[21] = 0.0; colors[22] = 1.0; colors[23] = 0.0;

	//Back Back
	vertices[24] = 0.0; vertices[25] = 1.0; vertices[26] = -2.0; //V8
	colors[24] = 1.0; colors[25] = 0.0; colors[26] = 0.0;

	vertices[27] = 0.0; vertices[28] = -1.0; vertices[29] = -2.0; //V9
	colors[27] = 1.0; colors[28] = 0.0; colors[29] = 0.0;

	vertices[30] = -1.0; vertices[31] = 1.0; vertices[32] = -2.0; //V10
	colors[30] = 1.0; colors[31] = 0.0; colors[32] = 0.0;

	vertices[33] = -1.0; vertices[34] = -1.0; vertices[35] = -2.0; //V11
	colors[33] = 1.0; colors[34] = 1.0; colors[35] = 0.0;

	//Left
	vertices[36] = -1.0; vertices[37] = 1.0; vertices[38] = -1.0; //V12
	colors[36] = 1.0; colors[37] = 1.0; colors[38] = 0.0;

	vertices[39] = -1.0; vertices[40] = 0.0; vertices[41] = -1.0; //V13
	colors[39] = 1.0; colors[40] = 1.0; colors[41] = 0.0;

	vertices[42] = -1.0; vertices[43] = -1.0; vertices[44] = -2.0; //V14
	colors[42] = 1.0; colors[43] = 1.0; colors[44] = 0.0;

	vertices[45] = -1.0; vertices[46] = -1.0; vertices[47] = -1.0; //V15
	colors[45] = 1.0; colors[46] = 1.0; colors[47] = 0.0;

	vertices[48] = -1.0; vertices[49] = 0.0; vertices[50] = -1.0; //V16
	colors[48] = 1.0; colors[49] = 1.0; colors[50] = 0.0;

	vertices[51] = -1.0; vertices[52] = -1.0; vertices[53] = 1.0; //V17
	colors[51] = 1.0; colors[52] = 1.0; colors[53] = 0.0;

	vertices[54] = -1.0; vertices[55] = 0.0; vertices[56] = 1.0; //V18
	colors[54] = 1.0; colors[55] = 1.0; colors[56] = 0.0;

	//Front front
	vertices[57] = 0.0; vertices[58] = -1.0; vertices[59] = 1.0; //V19
	colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0;

	vertices[60] = 0.0; vertices[61] = 0.0; vertices[62] = 1.0; //V20
	colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0;

	//Front Right
	vertices[63] = 0.0; vertices[64] = -1.0; vertices[65] = -1.0; //V21
	colors[63] = 0.0; colors[64] = 1.0; colors[65] = 0.0;

	vertices[66] = 0.0; vertices[67] = 0.0; vertices[68] = -1.0; //V22
	colors[66] = 1.0; colors[67] = 0.0; colors[68] = 1.0;

	//Front Top
	vertices[69] = -1.0; vertices[70] = 0.0; vertices[71] = -1.0; //V23
	colors[69] = 1.0; colors[70] = 0.0; colors[71] = 1.0;

	vertices[72] = -1.0; vertices[73] = 0.0; vertices[74] = 1.0; //V24
	colors[72] = 1.0; colors[73] = 0.0; colors[74] = 1.0;

	vertices[75] = 0.0; vertices[76] = 0.0; vertices[77] = -1.0; //V25
	colors[75] = 1.0; colors[76] = 0.0; colors[77] = 1.0;

	vertices[78] = 0.0; vertices[79] = 0.0; vertices[80] = 1.0; //V26
	colors[78] = 1.0; colors[79] = 0.0; colors[80] = 1.0;

	//Bottom
	vertices[81] = -1.0; vertices[82] = -1.0; vertices[83] = 1.0; //V27
	colors[81] = 1.0; colors[82] = 1.0; colors[83] = 1.0;

	vertices[84] = -1.0; vertices[85] = -1.0; vertices[86] = -2.0; //V28
	colors[84] = 1.0; colors[85] = 1.0; colors[86] = 1.0;

	vertices[87] = 0.0; vertices[88] = -1.0; vertices[89] = 1.0; //V29
	colors[87] = 1.0; colors[88] = 1.0; colors[89] = 1.0;

	vertices[90] = 0.0; vertices[91] = -1.0; vertices[92] = -1.0; //V30
	colors[90] = 1.0; colors[91] = 1.0; colors[92] = 1.0;

	vertices[93] = -1.0; vertices[94] = -1.0; vertices[95] = -2.0; //V31
	colors[93] = 1.0; colors[94] = 1.0; colors[95] = 1.0;

	vertices[96] = 0.0; vertices[97] = -1.0; vertices[98] = -2.0; //V32
	colors[96] = 1.0; colors[97] = 1.0; colors[98] = 1.0;

	vertices[99] = 0.0; vertices[100] = -1.0; vertices[101] = -1.0; //V33
	colors[99] = 1.0; colors[100] = 1.0; colors[101] = 1.0;

	vertices[102] = 2.0; vertices[103] = -1.0; vertices[104] = -2.0; //V34
	colors[102] = 1.0; colors[103] = 1.0; colors[104] = 1.0;

	vertices[105] = 2.0; vertices[106] = -1.0; vertices[107] = -1.0; //V35
	colors[105] = 1.0; colors[106] = 1.0; colors[107] = 1.0;

	//Back Top
	vertices[108] = 0.0; vertices[109] = 1.0; vertices[110] = -2.0; //V36
	colors[108] = 1.0; colors[109] = 0.0; colors[110] = 1.0;

	vertices[111] = 0.0; vertices[112] = 1.0; vertices[113] = -1.0; //V37
	colors[111] = 1.0; colors[112] = 0.0; colors[113] = 1.0;

	vertices[114] = 2.0; vertices[115] = 0.0; vertices[116] = -2.0; //V38
	colors[114] = 1.0; colors[115] = 0.0; colors[116] = 1.0;

	vertices[117] = 2.0; vertices[118] = 0.0; vertices[119] = -1.0; //V39
	colors[117] = 1.0; colors[118] = 0.0; colors[119] = 1.0;

	//Center Top
	vertices[120] = 0.0; vertices[121] = 1.0; vertices[122] = -2.0; //V40
	colors[120] = 1.0; colors[121] = 0.0; colors[122] = 1.0;

	vertices[123] = 0.0; vertices[124] = 1.0; vertices[125] = -1.0; //V41
	colors[123] = 1.0; colors[124] = 0.0; colors[125] = 1.0;

	vertices[126] = -1.0; vertices[127] = 1.0; vertices[128] = -2.0; //V42
	colors[126] = 1.0; colors[127] = 0.0; colors[128] = 1.0;

	vertices[129] = -1.0; vertices[130] = 1.0; vertices[131] = -1.0; //V43
	colors[129] = 1.0; colors[130] = 0.0; colors[131] = 1.0;

	vertices[132] = 0.0; vertices[133] = 1.0; vertices[134] = -2.0; //V44
	colors[132] = 1.0; colors[133] = 0.0; colors[134] = 1.0;

	vertices[135] = 0.0; vertices[136] = 1.0; vertices[137] = -2.0; //V45
	colors[135] = 1.0; colors[136] = 0.0; colors[137] = 1.0;


    //TODO: Prepare the vertex buffer object etc. and relate the results to vaoID[0]
    //vaoID[0];
	glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(4, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 138 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 138 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING TRIANGLE PRIMITIVES 
 */
unsigned int createTriangleModel(void)
{
	// TODO: Create your vertices
	float* vertices = new float[261];  // Vertices for our square
	float *colors = new float[261]; // Colors for our vertices

	//Back
	vertices[0] = -1.0; vertices[1] = 1.0; vertices[2] = -0.5; //V0
	colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0;

	vertices[3] = -1.0; vertices[4] = -1.0; vertices[5] = -0.5; //V1
	colors[3] = 1.0; colors[4] = 0.0; colors[5] = 0.0;

	vertices[6] = -2.0; vertices[7] = 1.0; vertices[8] = -0.5; //V2
	colors[6] = 1.0; colors[7] = 0.0; colors[8] = 0.0;

	vertices[9] = -2.0; vertices[10] = 1.0; vertices[11] = -0.5; //V3
	colors[9] = 1.0; colors[10] = 0.0; colors[11] = 0.0;

	vertices[12] = -2.0; vertices[13] = -1.0; vertices[14] = -0.5; //V4
	colors[12] = 1.0; colors[13] = 0.0; colors[14] = 0.0;

	vertices[15] = -1.0; vertices[16] = -1.0; vertices[17] = -0.5; //V5
	colors[15] = 1.0; colors[16] = 0.0; colors[17] = 0.0;

	vertices[18] = -1.0; vertices[19] = 1.0; vertices[20] = -0.5; //V6
	colors[18] = 1.0; colors[19] = 0.0; colors[20] = 0.0;

	vertices[21] = -1.0; vertices[22] = -1.0; vertices[23] = -0.5; //V7
	colors[21] = 1.0; colors[22] = 0.0; colors[23] = 0.0;

	vertices[24] = 1.0; vertices[25] = 0.0; vertices[26] = -0.5; //V8
	colors[24] = 1.0; colors[25] = 0.0; colors[26] = 0.0;

	vertices[27] = 1.0; vertices[28] = 0.0; vertices[29] = -0.5; //V9
	colors[27] = 1.0; colors[28] = 0.0; colors[29] = 0.0;

	vertices[30] = 1.0; vertices[31] = -1.0; vertices[32] = -0.5; //V10
	colors[30] = 1.0; colors[31] = 0.0; colors[32] = 0.0;

	vertices[33] = -1.0; vertices[34] = -1.0; vertices[35] = -0.5; //V11
	colors[33] = 1.0; colors[34] = 0.0; colors[35] = 0.0;

	//Back Right
	vertices[36] = 1.0; vertices[37] = 0.0; vertices[38] = -0.5; //V12
	colors[36] = 0.0; colors[37] = 1.0; colors[38] = 0.0;

	vertices[39] = 1.0; vertices[40] = -1.0; vertices[41] = -0.5; //V13
	colors[39] = 0.0; colors[40] = 1.0; colors[41] = 0.0;

	vertices[42] = 1.0; vertices[43] = 0.0; vertices[44] = 0.5; //V14
	colors[42] = 0.0; colors[43] = 1.0; colors[44] = 0.0;

	vertices[45] = 1.0; vertices[46] = 0.0; vertices[47] = 0.5; //V15
	colors[45] = 0.0; colors[46] = 1.0; colors[47] = 0.0;

	vertices[48] = 1.0; vertices[49] = -1.0; vertices[50] = 0.5; //V16
	colors[48] = 0.0; colors[49] = 1.0; colors[50] = 0.0;

	vertices[51] = 1.0; vertices[52] = -1.0; vertices[53] = -0.5; //V17
	colors[51] = 0.0; colors[52] = 1.0; colors[53] = 0.0;

	//Back Front
	vertices[54] = 1.0; vertices[55] = 0.0; vertices[56] = 0.5; //V18
	colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0;

	vertices[57] = 1.0; vertices[58] = -1.0; vertices[59] = 0.5; //V19
	colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0;

	vertices[60] = -1.0; vertices[61] = -1.0; vertices[62] = 0.5; //V20
	colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0;

	vertices[63] = -1.0; vertices[64] = -1.0; vertices[65] = 0.5; //V21
	colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0;

	vertices[66] = 1.0; vertices[67] = 0.0; vertices[68] = 0.5; //V22
	colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0;

	vertices[69] = -1.0; vertices[70] = 0.0; vertices[71] = 0.5; //V23
	colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0;

	vertices[72] = -1.0; vertices[73] = 0.0; vertices[74] = 0.5; //V24
	colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0;

	vertices[75] = 1.0; vertices[76] = 0.0; vertices[77] = 0.5; //V25
	colors[75] = 0.0; colors[76] = 0.0; colors[77] = 1.0;

	vertices[78] = -1.0; vertices[79] = 1.0; vertices[80] = 0.5; //V26
	colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0;

	vertices[81] = -1.0; vertices[82] = 1.0; vertices[83] = 0.5; //V27
	colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0;

	vertices[84] = -1.0; vertices[85] = 0.0; vertices[86] = 0.5; //V28
	colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0;

	vertices[87] = -2.0; vertices[88] = 0.0; vertices[89] = 0.5; //V29
	colors[87] = 0.0; colors[88] = 0.0; colors[89] = 1.0;

	vertices[90] = -2.0; vertices[91] = 0.0; vertices[92] = 0.5; //V30
	colors[90] = 0.0; colors[91] = 0.0; colors[92] = 1.0;

	vertices[93] = -1.0; vertices[94] = 1.0; vertices[95] = 0.5; //V31
	colors[93] = 0.0; colors[94] = 0.0; colors[95] = 1.0;

	vertices[96] = -2.0; vertices[97] = 1.0; vertices[98] = 0.5; //V32
	colors[96] = 0.0; colors[97] = 0.0; colors[98] = 1.0;

	//Back Top
	vertices[99] = -2.0; vertices[100] = 1.0; vertices[101] = 0.5; //V33
	colors[99] = 1.0; colors[100] = 0.0; colors[101] = 1.0;

	vertices[102] = -1.0; vertices[103] = 1.0; vertices[104] = 0.5; //V34
	colors[102] = 1.0; colors[103] = 0.0; colors[104] = 1.0;

	vertices[105] = -1.0; vertices[106] = 1.0; vertices[107] = -0.5; //V35
	colors[105] = 1.0; colors[106] = 0.0; colors[107] = 1.0;

	vertices[108] = -1.0; vertices[109] = 1.0; vertices[110] = -0.5; //V36
	colors[108] = 1.0; colors[109] = 0.0; colors[110] = 1.0;

	vertices[111] = -2.0; vertices[112] = 1.0; vertices[113] = 0.5; //V37
	colors[111] = 1.0; colors[112] = 0.0; colors[113] = 1.0;

	vertices[114] = -2.0; vertices[115] = 1.0; vertices[116] = -0.5; //V38
	colors[114] = 1.0; colors[115] = 0.0; colors[116] = 1.0;

	vertices[117] = -1.0; vertices[118] = 1.0; vertices[119] = -0.5; //V39
	colors[117] = 1.0; colors[118] = 0.0; colors[119] = 1.0;

	vertices[120] = -1.0; vertices[121] = 1.0; vertices[122] = 0.5; //V40
	colors[120] = 1.0; colors[121] = 0.0; colors[122] = 1.0;

	vertices[123] = 1.0; vertices[124] = 0.0; vertices[125] = -0.5; //V41
	colors[123] = 1.0; colors[124] = 0.0; colors[125] = 1.0;

	vertices[126] = 1.0; vertices[127] = 0.0; vertices[128] = -0.5; //V42
	colors[126] = 1.0; colors[127] = 0.0; colors[128] = 1.0;

	vertices[129] = 1.0; vertices[130] = 0.0; vertices[131] = 0.5; //V43
	colors[129] = 1.0; colors[130] = 0.0; colors[131] = 1.0;

	vertices[132] = -1.0; vertices[133] = 1.0; vertices[134] = 0.5; //V44
	colors[132] = 1.0; colors[133] = 0.0; colors[134] = 1.0;

	//Back Left
	vertices[135] = -2.0; vertices[136] = 1.0; vertices[137] = -0.5; //V45
	colors[135] = 1.0; colors[136] = 1.0; colors[137] = 0.0;

	vertices[138] = -2.0; vertices[139] = 1.0; vertices[140] = 0.5; //V46
	colors[138] = 1.0; colors[139] = 1.0; colors[140] = 0.0;

	vertices[141] = -2.0; vertices[142] = -1.0; vertices[143] = -0.5; //V47
	colors[141] = 1.0; colors[142] = 1.0; colors[143] = 0.0;

	vertices[144] = -2.0; vertices[145] = -1.0; vertices[146] = -0.5; //V48
	colors[144] = 1.0; colors[145] = 1.0; colors[146] = 0.0;

	vertices[147] = -2.0; vertices[148] = 1.0; vertices[149] = 0.5; //V49
	colors[147] = 1.0; colors[148] = 1.0; colors[149] = 0.0;

	vertices[150] = -2.0; vertices[151] = -1.0; vertices[152] = 0.5; //V50
	colors[150] = 1.0; colors[151] = 1.0; colors[152] = 0.0;

	//Front Top
	vertices[153] = -1.0; vertices[154] = 0.0; vertices[155] = 0.5; //V51
	colors[153] = 1.0; colors[154] = 0.0; colors[155] = 1.0;

	vertices[156] = -2.0; vertices[157] = 0.0; vertices[158] = 0.5; //V52
	colors[156] = 1.0; colors[157] = 0.0; colors[158] = 1.0;

	vertices[159] = -1.0; vertices[160] = -0.0; vertices[161] = 2.5; //V53
	colors[159] = 1.0; colors[160] = 0.0; colors[161] = 1.0;

	vertices[162] = -2.0; vertices[163] = -0.0; vertices[164] = 0.5; //V54
	colors[162] = 1.0; colors[163] = 0.0; colors[164] = 1.0;

	vertices[165] = -1.0; vertices[166] = 0.0; vertices[167] = 2.5; //V55
	colors[165] = 1.0; colors[166] = 0.0; colors[167] = 1.0;

	vertices[168] = -2.0; vertices[169] = -0.0; vertices[170] = 2.5; //V56
	colors[168] = 1.0; colors[169] = 0.0; colors[170] = 1.0;

	//Front Left
	vertices[171] = -2.0; vertices[172] = 0.0; vertices[173] = 2.5; //V57
	colors[171] = 1.0; colors[172] = 1.0; colors[173] = 0.0;

	vertices[174] = -2.0; vertices[175] = 0.0; vertices[176] = 0.5; //V58
	colors[174] = 1.0; colors[175] = 1.0; colors[176] = 0.0;

	vertices[177] = -2.0; vertices[178] = -1.0; vertices[179] = 0.5; //V59
	colors[177] = 1.0; colors[178] = 1.0; colors[179] = 0.0;

	vertices[180] = -2.0; vertices[181] = -1.0; vertices[182] = 0.5; //V60
	colors[180] = 1.0; colors[181] = 1.0; colors[182] = 0.0;

	vertices[183] = -2.0; vertices[184] = -1.0; vertices[185] = 2.5; //V61
	colors[183] = 1.0; colors[184] = 1.0; colors[185] = 0.0;

	vertices[186] = -2.0; vertices[187] = 0.0; vertices[188] = 2.5; //V62
	colors[186] = 1.0; colors[187] = 1.0; colors[188] = 0.0;

	//Front Right
	vertices[189] = -1.0; vertices[190] = 0.0; vertices[191] = 2.5; //V63
	colors[189] = 0.0; colors[190] = 1.0; colors[191] = 0.0;

	vertices[192] = -1.0; vertices[193] = 0.0; vertices[194] = 0.5; //V64
	colors[192] = 0.0; colors[193] = 1.0; colors[194] = 0.0;

	vertices[195] = -1.0; vertices[196] = -1.0; vertices[197] = 0.5; //V65
	colors[195] = 0.0; colors[196] = 1.0; colors[197] = 0.0;

	vertices[198] = -1.0; vertices[199] = -1.0; vertices[200] = 0.5; //V66
	colors[198] = 0.0; colors[199] = 1.0; colors[200] = 0.0;

	vertices[201] = -1.0; vertices[202] = -1.0; vertices[203] = 2.5; //V67
	colors[201] = 0.0; colors[202] = 1.0; colors[203] = 0.0;

	vertices[204] = -1.0; vertices[205] = 0.0; vertices[206] = 2.5; //V68
	colors[204] = 0.0; colors[205] = 1.0; colors[206] = 0.0;

	//Front Front
	vertices[207] = -2.0; vertices[208] = 0.0; vertices[209] = 2.5; //V69
	colors[207] = 0.0; colors[208] = 0.0; colors[209] = 1.0;

	vertices[210] = -1.0; vertices[211] = 0.0; vertices[212] = 2.5; //V70
	colors[210] = 0.0; colors[211] = 0.0; colors[212] = 1.0;

	vertices[213] = -2.0; vertices[214] = -1.0; vertices[215] = 2.5; //V71
	colors[213] = 0.0; colors[214] = 0.0; colors[215] = 1.0;

	vertices[216] = -2.0; vertices[217] = -1.0; vertices[218] = 2.5; //V72
	colors[216] = 0.0; colors[217] = 0.0; colors[218] = 1.0;

	vertices[219] = -1.0; vertices[220] = -1.0; vertices[221] = 2.5; //V73
	colors[219] = 0.0; colors[220] = 0.0; colors[221] = 1.0;

	vertices[222] = -1.0; vertices[223] = 0.0; vertices[224] = 2.5; //V74
	colors[222] = 0.0; colors[223] = 0.0; colors[224] = 1.0;

	//Bottom
	vertices[225] = -2.0; vertices[226] = -1.0; vertices[227] = 2.5; //V75
	colors[225] = 1.0; colors[226] = 1.0; colors[227] = 1.0;

	vertices[228] = -1.0; vertices[229] = -1.0; vertices[230] = 2.5; //V76
	colors[228] = 1.0; colors[229] = 1.0; colors[230] = 1.0;

	vertices[231] = -2.0; vertices[232] = -1.0; vertices[233] = -0.5; //V77
	colors[231] = 1.0; colors[232] = 1.0; colors[233] = 1.0;

	vertices[234] = -2.0; vertices[235] = -1.0; vertices[236] = -0.5; //V78
	colors[234] = 1.0; colors[235] = 1.0; colors[236] = 1.0;

	vertices[237] = -1.0; vertices[238] = -1.0; vertices[239] = -0.5; //V79
	colors[237] = 1.0; colors[238] = 1.0; colors[239] = 1.0;

	vertices[240] = -1.0; vertices[241] = -1.0; vertices[242] = 2.5; //V80
	colors[240] = 1.0; colors[241] = 1.0; colors[242] = 1.0;

	vertices[243] = -1.0; vertices[244] = -1.0; vertices[245] = 0.5; //V81
	colors[243] = 1.0; colors[244] = 1.0; colors[245] = 1.0;

	vertices[246] = -1.0; vertices[247] = -1.0; vertices[248] = -0.5; //V82
	colors[246] = 1.0; colors[247] = 1.0; colors[248] = 1.0;

	vertices[249] = 1.0; vertices[250] = -1.0; vertices[251] = 0.5; //V83
	colors[249] = 1.0; colors[250] = 1.0; colors[251] = 1.0;

	vertices[252] = 1.0; vertices[253] = -1.0; vertices[254] = 0.5; //V84
	colors[252] = 1.0; colors[253] = 1.0; colors[254] = 1.0;

	vertices[255] = 1.0; vertices[256] = -1.0; vertices[257] = -0.5; //V85
	colors[255] = 1.0; colors[256] = 1.0; colors[257] = 1.0;

	vertices[258] = -1.0; vertices[259] = -1.0; vertices[260] = -0.5; //V86
	colors[258] = 1.0; colors[259] = 1.0; colors[260] = 1.0;

  
    //TODO: Prepare the vertex buffer object etc. and relate the results to vaoID[1]
    //vaoID[1];
	glGenVertexArrays(2, &vaoID[1]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it


	glGenBuffers(4, vboID); // Generate our Vertex Buffer Object

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 261 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


	//Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[3]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 261 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 46);


    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE MODEL TO THIS FUNCTION
 */
void renderTriangleModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0 , 87);

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
	createTriangleModel();
    
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
		renderTriangleModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

