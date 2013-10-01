#version 400 compatibility

void main(void)
{
    gl_Position = gl_ModelViewMatrix * gl_Vertex;
}
