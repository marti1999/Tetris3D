//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Març 2020)
// eixos.frag: Fragment Program en GLSL per a dibuixar eixos Coordenades Món en versió OpenGL 3.3 o 4.00

#version 330 core

// in Variables
in vec4 VertexColor;

// out Variables
out vec4 FragColor;

void main ()

{
// Intensitat sense textura
    FragColor = VertexColor; 
}
