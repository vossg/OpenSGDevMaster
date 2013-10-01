#version 400 compatibility

in float gLightIntensity;

layout(location = 0) out vec4 fFragColor;

const vec3 COLOR = vec3(1., 1., 0.);

void main(void)
{
    fFragColor = vec4(gLightIntensity * COLOR, 1.);
}
