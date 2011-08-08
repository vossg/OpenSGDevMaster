#version 120
#define OSG_HAS_DIFFUSE_MAP 1

#ifdef OSG_HAS_NORMAL_MAP
void calcSkin(inout vec4 pos,    inout vec3 norm,
              inout vec3 tang,
              in    vec4 matIdx, in    vec4 weight );
#else
void calcSkin(inout vec4 pos,    inout vec3 norm,
              in    vec4 matIdx, in    vec4 weight );
#endif

varying vec4 vertPos;
varying vec3 vertNorm;

#ifdef OSG_HAS_NORMAL_MAP
varying vec3 vertTangent;
#endif

void main(void)
{
    vertPos          = gl_Vertex;
    vertNorm         = gl_Normal;

#ifdef OSG_HAS_DIFFUSE_MAP
    gl_TexCoord[0]   = gl_MultiTexCoord0;
#endif

#ifdef OSG_HAS_NORMAL_MAP
    vertTangent      = gl_MultiTexCoord1.xyz;
#endif

    vec4 jointIdx    = gl_MultiTexCoord2;
    vec4 jointWeight = gl_MultiTexCoord3;

#ifdef OSG_HAS_NORMAL_MAP
    calcSkin(vertPos, vertNorm, vertTangent, jointIdx, jointWeight);
#else
    calcSkin(vertPos, vertNorm, jointIdx, jointWeight);
#endif

    vertPos  = gl_ModelViewMatrix * vertPos;
    vertNorm = gl_NormalMatrix    * vertNorm;

#ifdef OSG_HAS_NORMAL_MAP
    vertTangent = gl_NormalMatrix * vertTangent;
#endif

    gl_Position = gl_ProjectionMatrix * vertPos;
}
