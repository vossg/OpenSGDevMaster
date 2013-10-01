#version 400 compatibility

#extension GL_EXT_gpu_shader4: enable
#extension GL_EXT_geometry_shader4: enable

layout(triangles)                          in;
layout(triangle_strip, max_vertices = 200) out;

uniform float fShrink;
uniform float uLightX, uLightY, uLightZ;

in  vec3  teNormal[3];
out float gLightIntensity;

vec3 LightPos = vec3(uLightX, uLightY, uLightZ);

vec3 V[3];
vec3 CG;

void GenerateVertex(int v)
{
    gLightIntensity  = abs(dot(normalize(LightPos - V[v]), teNormal[v]));

    gl_Position = gl_ProjectionMatrix * vec4(CG + fShrink * (V[v] - CG), 1.);

    EmitVertex();
}



void main(void)
{
    V[0] = gl_PositionIn[0].xyz;
    V[1] = gl_PositionIn[1].xyz;
    V[2] = gl_PositionIn[2].xyz;

    CG = 0.33333 * (V[0] + V[1] + V[2]);

    GenerateVertex(0);
    GenerateVertex(1);
    GenerateVertex(2);
}
