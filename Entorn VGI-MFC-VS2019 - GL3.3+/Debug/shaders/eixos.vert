//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interficie MFC i Qt amb Status Bar
//******** Enric Marti (Març 2020)
// eixos.vert: Vertex Program en GLSL per a dibuixar eixos Coordenades Món en versió OpenGL 3.3 o 4.00

#version 330 core
//#version 400 core

// --- L9
// in Variables
layout (location = 0) in vec3 in_Vertex; 	// Coordenades (x,y,z) posicio Vertex
layout (location = 1) in vec4 in_Color; 	// Coordenades (r,g,b,a) Color

// --- L14
// Variables uniform
uniform mat4 projectionMatrix;	// Projection Matrix
uniform mat4 viewMatrix; 	// View Matrix

// --- L19
// Variables out
out vec4 VertexColor;

// --- L23
void main ()
{

// --- L27- Transformacio de Visualitzacio amb Matriu Projeccio (projectionMatrix), Matriu Càmera (viewMatrix) i Matriu TG (modelMatrix)
    gl_Position = vec4(projectionMatrix * viewMatrix * vec4(in_Vertex,1.0));

// ---L30- Calcul intensitat final del vertex
    VertexColor = in_Color;
}
