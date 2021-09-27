#version 330 core
layout (location = 0) in vec3 in_Vertex;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    TexCoords = in_Vertex;
    vec4 pos = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Vertex, 1.0);
    gl_Position = pos.xyww;
}  