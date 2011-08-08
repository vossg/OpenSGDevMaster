#version 120
#define OSG_HAS_DIFFUSE_MAP 1

#ifdef OSG_HAS_DIFFUSE_MAP
uniform sampler2D diffuseMap;
#endif
#ifdef OSG_HAS_NORMAL_MAP
uniform sampler2D normalMap;
#endif
#ifdef OSG_HAS_SPECULAR_MAP
uniform sampler2D specularMap;
#endif

varying vec4 vertPos;
varying vec3 vertNorm;

#ifdef OSG_HAS_NORMAL_MAP
varying vec3 vertTangent;
#endif

uniform int OSGLight0Active;
uniform int OSGLight1Active;
uniform int OSGLight2Active;
uniform int OSGLight3Active;

#ifdef OSG_HAS_SPECULAR_MAP
vec4 calcLight(int idx, vec3 normal, vec4 matDiff, float matSpec)
{
    vec4  color = vec4(0., 0., 0., 0.);
    float NdotL = max(dot(normal, gl_LightSource[idx].position.xyz), 0.);

    if(NdotL > 0.)
    {
        color += NdotL * matDiff * gl_LightSource[idx].diffuse;

        float NdotH = max(dot(normal, gl_LightSource[idx].halfVector.xyz), 0.);

        if(NdotH > 0.)
        {
            color += matSpec * pow(NdotH, 20.) * gl_LightSource[idx].specular;
        }
    }

    return color;
}
#else
vec4 calcLight(int idx, vec3 normal, vec4 matDiff)
{
    vec4  color = vec4(0., 0., 0., 0.);
    float NdotL = max(dot(normal, gl_LightSource[idx].position.xyz), 0.);

    if(NdotL > 0.)
    {
        color += NdotL * matDiff * gl_LightSource[idx].diffuse;
    }

    return color;
}
#endif

void main(void)
{
    vec3 pos     = vertPos.xyz / vertPos.w;

#ifdef OSG_HAS_DIFFUSE_MAP
    vec4 diffCol = texture2D(diffuseMap, gl_TexCoord[0].xy);
#else
    vec4 diffCol = gl_FrontMaterial.diffuse;
#endif

#ifdef OSG_HAS_ALPHA_TEST
    if(diffCol.a < 0.5)
    {
        discard;
    }
#endif

#ifdef OSG_HAS_NORMAL_MAP
    vec3 texNormal       = texture2D(normalMap, gl_TexCoord[0].xy).xyz * 2.0 - 1.0;

    vec3 vNormal         = normalize(vertNorm);
    vec3 vTangent        = normalize(vertTangent);
    vec3 vBitangent      = cross(vNormal, vTangent);

    mat3 matTangentSpace = mat3(vTangent, vBitangent, vNormal);
    vec3 normal          = normalize(matTangentSpace * texNormal);
#else
    vec3 normal = normalize(vertNorm);
#endif

#ifdef OSG_HAS_SPECULAR_MAP
    vec3  specular  = texture2D(specularMap, gl_TexCoord[0].xy).rgb;
    float luminance = dot(specular, vec3(0.212671,
                                         0.715160,
                                         0.072169 ));
#endif

    gl_FragColor = vec4(0., 0., 0., 0.);

#ifdef OSG_HAS_SPECULAR_MAP
    if(OSGLight0Active > 0)
        gl_FragColor += calcLight(0, normal, diffCol, luminance);
    if(OSGLight1Active > 0)
        gl_FragColor += calcLight(1, normal, diffCol, luminance);
    if(OSGLight2Active > 0)
        gl_FragColor += calcLight(2, normal, diffCol, luminance);
    if(OSGLight3Active > 0)
        gl_FragColor += calcLight(3, normal, diffCol, luminance);
#else
    if(OSGLight0Active > 0)
        gl_FragColor += calcLight(0, normal, diffCol);
    if(OSGLight1Active > 0)
        gl_FragColor += calcLight(1, normal, diffCol);
    if(OSGLight2Active > 0)
        gl_FragColor += calcLight(2, normal, diffCol);
    if(OSGLight3Active > 0)
        gl_FragColor += calcLight(3, normal, diffCol);
#endif
}
