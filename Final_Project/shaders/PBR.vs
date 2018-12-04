#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_Texture;
layout (location = 2) in vec3 in_Normal;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    TexCoords = in_Texture;
    WorldPos = vec3(modelMatrix * vec4(in_Position, 1.0));
    Normal = mat3(modelMatrix) * in_Normal;   

    gl_Position =  projectionMatrix * viewMatrix * vec4(WorldPos, 1.0);
}