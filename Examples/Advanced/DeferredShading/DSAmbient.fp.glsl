#version 120
#extension GL_ARB_texture_rectangle : require
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect  texBufNorm;

void main(void)
{
    vec3  norm  = texture2DRect(texBufNorm, gl_FragCoord.xy).xyz;

    if(dot(norm, norm) < 0.95)
    {
        discard;
    }
    else
    {
        gl_FragColor = vec4(0.02, 0.02, 0.02, 1.);
    }
}
