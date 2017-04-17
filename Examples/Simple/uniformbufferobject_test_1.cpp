// OpenSG Test Example: UniformBufferObject_Test_1
//
// This example allows to research the capabilities of the uniform
// buffer object extension on your graphics platform.
//
// This example is similar to the UniformBufferObject_Test
// example which uses a non array block layout, whereas this
// example uses an even more complex setup with an array
// block layout.
//
// The example does use the UniformBufferObjChunk which allows the
// host application to provide the uniform block member values 
// directly to the chunk. The layout of the uniform block is determined 
// by the shader code. Any of the layout values of the specification (shared, 
// packed, std140) are allowed.
//
// Outcome on running this example:
//  1. animated green cylinder and torus
//      => your platform provides all GLSL capabilities used in this
//         example. Congratulations :-)
//
//  2. animated red cylinder and torus
//      => the shader is actively working but some detail is not
//         working properly. E.g.:
//          - On ATI/AMD the usage of bvec2 fails at the time of writing
//            the example on the authors Radeon 5700 series 
//            platform, iff the 'std140' layout is used.
//          - On ATI/AMD the usage of double and dvec2 fails at the time
//            writing the example on the authors Radeon 5700 series
//            platform.
//
//  3. animated gold looking cylinder and torus
//      => the shader is not working at all. Something is miserabely
//         wrong on your platform.
//
// The example uses the following uniform block named 'ExampleBlock' 
// which is declared in the shader code below.
//
// struct TestA
// {
//     float a;
//     ivec3 b[3];
//     int   c;
// };
//
// struct TestB
// {
//     bvec2 a;
//     TestA b[2];
//     float c;
// };
//
// struct TestC
// {
//     float a;
//     bvec2 b;
//     TestB c[2];
// };
//
// struct TestD
// {
//     uvec3 a;
//     vec2  b;
//     float c[2];
//     vec2  d;
//     mat3  e[2];
// };
//
// struct TestE
// {
//     dvec2 a;
//     int   b;
//     TestA c[4];
// };
//
// struct Example
// {
//     float  a;
//     vec2   b;
//     vec3   c;
//     TestC  d;
//     float  e;
//     float  f[2];
//     mat2x3 g;
//     TestD  h[2];
//     double i;
//     bool   j;
//     TestE  k;
// } example;
//
// layout(shared) uniform Examples
// {
//     Example example[3];
// } examples;
//
// For this example the values must be provided in the exact order for the
// following data slots (second column):
//
// Example[0].a float                                   Examples.example[0].a
// Example[0].b vec2                                    Examples.example[0].b
// Example[0].c vec3                                    Examples.example[0].c
// Example[0].TestC.a float                             Examples.example[0].d.a
// Example[0].TestC.b bvec2                             Examples.example[0].d.b
// Example[0].TestC.TestB[0].a bvec2                    Examples.example[0].d.c[0].a
// Example[0].TestC.TestB[0].TestA[0].a float           Examples.example[0].d.c[0].b[0].a
// Example[0].TestC.TestB[0].TestA[0].b[0] ivec3[3]     Examples.example[0].d.c[0].b[0].b[0]
// Example[0].TestC.TestB[0].TestA[0].b[1]              Examples.example[0].d.c[0].b[0].b[1]
// Example[0].TestC.TestB[0].TestA[0].b[2]              Examples.example[0].d.c[0].b[0].b[2]
// Example[0].TestC.TestB[0].TestA[0].c int             Examples.example[0].d.c[0].b[0].c
// Example[0].TestC.TestB[0].TestA[1].a float           Examples.example[0].d.c[0].b[1].a
// Example[0].TestC.TestB[0].TestA[1].b[0] ivec3[3]     Examples.example[0].d.c[0].b[1].b[0]
// Example[0].TestC.TestB[0].TestA[1].b[1]              Examples.example[0].d.c[0].b[1].b[1]
// Example[0].TestC.TestB[0].TestA[1].b[2]              Examples.example[0].d.c[0].b[1].b[2]
// Example[0].TestC.TestB[0].TestA[1].c int             Examples.example[0].d.c[0].b[1].c
// Example[0].TestC.TestB[0].c float                    Examples.example[0].d.c[0].c
// Example[0].TestC.TestB[1].a bvec2                    Examples.example[0].d.c[1].a
// Example[0].TestC.TestB[1].TestA[0].a float           Examples.example[0].d.c[1].b[0].a
// Example[0].TestC.TestB[1].TestA[0].b[0] ivec3[3]     Examples.example[0].d.c[1].b[0].b[0]
// Example[0].TestC.TestB[1].TestA[0].b[1]              Examples.example[0].d.c[1].b[0].b[1]
// Example[0].TestC.TestB[1].TestA[0].b[2]              Examples.example[0].d.c[1].b[0].b[2]
// Example[0].TestC.TestB[1].TestA[0].c int             Examples.example[0].d.c[1].b[0].c
// Example[0].TestC.TestB[1].TestA[1].a float           Examples.example[0].d.c[1].b[1].a
// Example[0].TestC.TestB[1].TestA[1].b[0] ivec3[3]     Examples.example[0].d.c[1].b[1].b[0]
// Example[0].TestC.TestB[1].TestA[1].b[1]              Examples.example[0].d.c[1].b[1].b[1]
// Example[0].TestC.TestB[1].TestA[1].b[2]              Examples.example[0].d.c[1].b[1].b[2]
// Example[0].TestC.TestB[1].TestA[1].c int             Examples.example[0].d.c[1].b[1].c
// Example[0].TestC.TestB[1].c float                    Examples.example[0].d.c[1].c
// Example[0].e float                                   Examples.example[0].e
// Example[0].f[0] float[2]                             Examples.example[0].f[0]
// Example[0].f[1]                                      Examples.example[0].f[1]
// Example[0].g mat2x3                                  Examples.example[0].g
// Example[0].TestD[0].a uvec3                          Examples.example[0].h[0].a
// Example[0].TestD[0].b vec2                           Examples.example[0].h[0].b
// Example[0].TestD[0].c[0] float[2]                    Examples.example[0].h[0].c[0]
// Example[0].TestD[0].c[1]                             Examples.example[0].h[0].c[1]
// Example[0].TestD[0].d vec2                           Examples.example[0].h[0].d
// Example[0].TestD[0].e[0] mat3[2]                     Examples.example[0].h[0].e[0]
// Example[0].TestD[0].e[1]                             Examples.example[0].h[0].e[1]
// Example[0].TestD[1].a uvec3                          Examples.example[0].h[1].a
// Example[0].TestD[1].b vec2                           Examples.example[0].h[1].b
// Example[0].TestD[1].c[0] float[2]                    Examples.example[0].h[1].c[0]
// Example[0].TestD[1].c[1]                             Examples.example[0].h[1].c[1]
// Example[0].TestD[1].d vec2                           Examples.example[0].h[1].d
// Example[0].TestD[1].e[0] mat3[2]                     Examples.example[0].h[1].e[0]
// Example[0].TestD[1].e[1]                             Examples.example[0].h[1].e[1]
// Example[0].i double                                  Examples.example[0].i
// Example[0].j bool                                    Examples.example[0].j
// Example[0].TestE.a dvec2                             Examples.example[0].k.a
// Example[0].TestE.b int                               Examples.example[0].k.b
// Example[0].TestE.TestA[0].a float                    Examples.example[0].k.c[0].a
// Example[0].TestE.TestA[0].b[0] ivec3[3]              Examples.example[0].k.c[0].b[0]
// Example[0].TestE.TestA[0].b[1]                       Examples.example[0].k.c[0].b[1]
// Example[0].TestE.TestA[0].b[2]                       Examples.example[0].k.c[0].b[2]
// Example[0].TestE.TestA[0].c int                      Examples.example[0].k.c[0].c
// Example[0].TestE.TestA[1].a float                    Examples.example[0].k.c[1].a
// Example[0].TestE.TestA[1].b[0] ivec3[3]              Examples.example[0].k.c[1].b[0]
// Example[0].TestE.TestA[1].b[1]                       Examples.example[0].k.c[1].b[1]
// Example[0].TestE.TestA[1].b[2]                       Examples.example[0].k.c[1].b[2]
// Example[0].TestE.TestA[1].c int                      Examples.example[0].k.c[1].c
// Example[0].TestE.TestA[2].a float                    Examples.example[0].k.c[2].a
// Example[0].TestE.TestA[2].b[0] ivec3[3]              Examples.example[0].k.c[2].b[0]
// Example[0].TestE.TestA[2].b[1]                       Examples.example[0].k.c[2].b[1]
// Example[0].TestE.TestA[2].b[2]                       Examples.example[0].k.c[2].b[2]
// Example[0].TestE.TestA[2].c int                      Examples.example[0].k.c[2].c
// Example[0].TestE.TestA[3].a float                    Examples.example[0].k.c[3].a
// Example[0].TestE.TestA[3].b[0] ivec3[3]              Examples.example[0].k.c[3].b[0]
// Example[0].TestE.TestA[3].b[1]                       Examples.example[0].k.c[3].b[1]
// Example[0].TestE.TestA[3].b[2]                       Examples.example[0].k.c[3].b[2]
// Example[0].TestE.TestA[3].c int                      Examples.example[0].k.c[3].c
// Example[1].a float                                   Examples.example[1].a
// Example[1].b vec2                                    Examples.example[1].b
// Example[1].c vec3                                    Examples.example[1].c
// Example[1].TestC.a float                             Examples.example[1].d.a
// Example[1].TestC.b bvec2                             Examples.example[1].d.b
// Example[1].TestC.TestB[0].a bvec2                    Examples.example[1].d.c[0].a
// Example[1].TestC.TestB[0].TestA[0].a float           Examples.example[1].d.c[0].b[0].a
// Example[1].TestC.TestB[0].TestA[0].b[0] ivec3[3]     Examples.example[1].d.c[0].b[0].b[0]
// Example[1].TestC.TestB[0].TestA[0].b[1]              Examples.example[1].d.c[0].b[0].b[1]
// Example[1].TestC.TestB[0].TestA[0].b[2]              Examples.example[1].d.c[0].b[0].b[2]
// Example[1].TestC.TestB[0].TestA[0].c int             Examples.example[1].d.c[0].b[0].c
// Example[1].TestC.TestB[0].TestA[1].a float           Examples.example[1].d.c[0].b[1].a
// Example[1].TestC.TestB[0].TestA[1].b[0] ivec3[3]     Examples.example[1].d.c[0].b[1].b[0]
// Example[1].TestC.TestB[0].TestA[1].b[1]              Examples.example[1].d.c[0].b[1].b[1]
// Example[1].TestC.TestB[0].TestA[1].b[2]              Examples.example[1].d.c[0].b[1].b[2]
// Example[1].TestC.TestB[0].TestA[1].c int             Examples.example[1].d.c[0].b[1].c
// Example[1].TestC.TestB[0].c float                    Examples.example[1].d.c[0].c
// Example[1].TestC.TestB[1].a bvec2                    Examples.example[1].d.c[1].a
// Example[1].TestC.TestB[1].TestA[0].a float           Examples.example[1].d.c[1].b[0].a
// Example[1].TestC.TestB[1].TestA[0].b[0] ivec3[3]     Examples.example[1].d.c[1].b[0].b[0]
// Example[1].TestC.TestB[1].TestA[0].b[1]              Examples.example[1].d.c[1].b[0].b[1]
// Example[1].TestC.TestB[1].TestA[0].b[2]              Examples.example[1].d.c[1].b[0].b[2]
// Example[1].TestC.TestB[1].TestA[0].c int             Examples.example[1].d.c[1].b[0].c
// Example[1].TestC.TestB[1].TestA[1].a float           Examples.example[1].d.c[1].b[1].a
// Example[1].TestC.TestB[1].TestA[1].b[0] ivec3[3]     Examples.example[1].d.c[1].b[1].b[0]
// Example[1].TestC.TestB[1].TestA[1].b[1]              Examples.example[1].d.c[1].b[1].b[1]
// Example[1].TestC.TestB[1].TestA[1].b[2]              Examples.example[1].d.c[1].b[1].b[2]
// Example[1].TestC.TestB[1].TestA[1].c int             Examples.example[1].d.c[1].b[1].c
// Example[1].TestC.TestB[1].c float                    Examples.example[1].d.c[1].c
// Example[1].e float                                   Examples.example[1].e
// Example[1].f[0] float[2]                             Examples.example[1].f[0]
// Example[1].f[1]                                      Examples.example[1].f[1]
// Example[1].g mat2x3                                  Examples.example[1].g
// Example[1].TestD[0].a uvec3                          Examples.example[1].h[0].a
// Example[1].TestD[0].b vec2                           Examples.example[1].h[0].b
// Example[1].TestD[0].c[0] float[2]                    Examples.example[1].h[0].c[0]
// Example[1].TestD[0].c[1]                             Examples.example[1].h[0].c[1]
// Example[1].TestD[0].d vec2                           Examples.example[1].h[0].d
// Example[1].TestD[0].e[0] mat3[2]                     Examples.example[1].h[0].e[0]
// Example[1].TestD[0].e[1]                             Examples.example[1].h[0].e[1]
// Example[1].TestD[1].a uvec3                          Examples.example[1].h[1].a
// Example[1].TestD[1].b vec2                           Examples.example[1].h[1].b
// Example[1].TestD[1].c[0] float[2]                    Examples.example[1].h[1].c[0]
// Example[1].TestD[1].c[1]                             Examples.example[1].h[1].c[1]
// Example[1].TestD[1].d vec2                           Examples.example[1].h[1].d
// Example[1].TestD[1].e[0] mat3[2]                     Examples.example[1].h[1].e[0]
// Example[1].TestD[1].e[1]                             Examples.example[1].h[1].e[1]
// Example[1].i double                                  Examples.example[1].i
// Example[1].j bool                                    Examples.example[1].j
// Example[1].TestE.a dvec2                             Examples.example[1].k.a
// Example[1].TestE.b int                               Examples.example[1].k.b
// Example[1].TestE.TestA[0].a float                    Examples.example[1].k.c[0].a
// Example[1].TestE.TestA[0].b[0] ivec3[3]              Examples.example[1].k.c[0].b[0]
// Example[1].TestE.TestA[0].b[1]                       Examples.example[1].k.c[0].b[1]
// Example[1].TestE.TestA[0].b[2]                       Examples.example[1].k.c[0].b[2]
// Example[1].TestE.TestA[0].c int                      Examples.example[1].k.c[0].c
// Example[1].TestE.TestA[1].a float                    Examples.example[1].k.c[1].a
// Example[1].TestE.TestA[1].b[0] ivec3[3]              Examples.example[1].k.c[1].b[0]
// Example[1].TestE.TestA[1].b[1]                       Examples.example[1].k.c[1].b[1]
// Example[1].TestE.TestA[1].b[2]                       Examples.example[1].k.c[1].b[2]
// Example[1].TestE.TestA[1].c int                      Examples.example[1].k.c[1].c
// Example[1].TestE.TestA[2].a float                    Examples.example[1].k.c[2].a
// Example[1].TestE.TestA[2].b[0] ivec3[3]              Examples.example[1].k.c[2].b[0]
// Example[1].TestE.TestA[2].b[1]                       Examples.example[1].k.c[2].b[1]
// Example[1].TestE.TestA[2].b[2]                       Examples.example[1].k.c[2].b[2]
// Example[1].TestE.TestA[2].c int                      Examples.example[1].k.c[2].c
// Example[1].TestE.TestA[3].a float                    Examples.example[1].k.c[3].a
// Example[1].TestE.TestA[3].b[0] ivec3[3]              Examples.example[1].k.c[3].b[0]
// Example[1].TestE.TestA[3].b[1]                       Examples.example[1].k.c[3].b[1]
// Example[1].TestE.TestA[3].b[2]                       Examples.example[1].k.c[3].b[2]
// Example[1].TestE.TestA[3].c int                      Examples.example[1].k.c[3].c
// Example[2].a float                                   Examples.example[2].a
// Example[2].b vec2                                    Examples.example[2].b
// Example[2].c vec3                                    Examples.example[2].c
// Example[2].TestC.a float                             Examples.example[2].d.a
// Example[2].TestC.b bvec2                             Examples.example[2].d.b
// Example[2].TestC.TestB[0].a bvec2                    Examples.example[2].d.c[0].a
// Example[2].TestC.TestB[0].TestA[0].a float           Examples.example[2].d.c[0].b[0].a
// Example[2].TestC.TestB[0].TestA[0].b[0] ivec3[3]     Examples.example[2].d.c[0].b[0].b[0]
// Example[2].TestC.TestB[0].TestA[0].b[1]              Examples.example[2].d.c[0].b[0].b[1]
// Example[2].TestC.TestB[0].TestA[0].b[2]              Examples.example[2].d.c[0].b[0].b[2]
// Example[2].TestC.TestB[0].TestA[0].c int             Examples.example[2].d.c[0].b[0].c
// Example[2].TestC.TestB[0].TestA[1].a float           Examples.example[2].d.c[0].b[1].a
// Example[2].TestC.TestB[0].TestA[1].b[0] ivec3[3]     Examples.example[2].d.c[0].b[1].b[0]
// Example[2].TestC.TestB[0].TestA[1].b[1]              Examples.example[2].d.c[0].b[1].b[1]
// Example[2].TestC.TestB[0].TestA[1].b[2]              Examples.example[2].d.c[0].b[1].b[2]
// Example[2].TestC.TestB[0].TestA[1].c int             Examples.example[2].d.c[0].b[1].c
// Example[2].TestC.TestB[0].c float                    Examples.example[2].d.c[0].c
// Example[2].TestC.TestB[1].a bvec2                    Examples.example[2].d.c[1].a
// Example[2].TestC.TestB[1].TestA[0].a float           Examples.example[2].d.c[1].b[0].a
// Example[2].TestC.TestB[1].TestA[0].b[0] ivec3[3]     Examples.example[2].d.c[1].b[0].b[0]
// Example[2].TestC.TestB[1].TestA[0].b[1]              Examples.example[2].d.c[1].b[0].b[1]
// Example[2].TestC.TestB[1].TestA[0].b[2]              Examples.example[2].d.c[1].b[0].b[2]
// Example[2].TestC.TestB[1].TestA[0].c int             Examples.example[2].d.c[1].b[0].c
// Example[2].TestC.TestB[1].TestA[1].a float           Examples.example[2].d.c[1].b[1].a
// Example[2].TestC.TestB[1].TestA[1].b[0] ivec3[3]     Examples.example[2].d.c[1].b[1].b[0]
// Example[2].TestC.TestB[1].TestA[1].b[1]              Examples.example[2].d.c[1].b[1].b[1]
// Example[2].TestC.TestB[1].TestA[1].b[2]              Examples.example[2].d.c[1].b[1].b[2]
// Example[2].TestC.TestB[1].TestA[1].c int             Examples.example[2].d.c[1].b[1].c
// Example[2].TestC.TestB[1].c float                    Examples.example[2].d.c[1].c
// Example[2].e float                                   Examples.example[2].e
// Example[2].f[0] float[2]                             Examples.example[2].f[0]
// Example[2].f[1]                                      Examples.example[2].f[1]
// Example[2].g mat2x3                                  Examples.example[2].g
// Example[2].TestD[0].a uvec3                          Examples.example[2].h[0].a
// Example[2].TestD[0].b vec2                           Examples.example[2].h[0].b
// Example[2].TestD[0].c[0] float[2]                    Examples.example[2].h[0].c[0]
// Example[2].TestD[0].c[1]                             Examples.example[2].h[0].c[1]
// Example[2].TestD[0].d vec2                           Examples.example[2].h[0].d
// Example[2].TestD[0].e[0] mat3[2]                     Examples.example[2].h[0].e[0]
// Example[2].TestD[0].e[1]                             Examples.example[2].h[0].e[1]
// Example[2].TestD[1].a uvec3                          Examples.example[2].h[1].a
// Example[2].TestD[1].b vec2                           Examples.example[2].h[1].b
// Example[2].TestD[1].c[0] float[2]                    Examples.example[2].h[1].c[0]
// Example[2].TestD[1].c[1]                             Examples.example[2].h[1].c[1]
// Example[2].TestD[1].d vec2                           Examples.example[2].h[1].d
// Example[2].TestD[1].e[0] mat3[2]                     Examples.example[2].h[1].e[0]
// Example[2].TestD[1].e[1]                             Examples.example[2].h[1].e[1]
// Example[2].i double                                  Examples.example[2].i
// Example[2].j bool                                    Examples.example[2].j
// Example[2].TestE.a dvec2                             Examples.example[2].k.a
// Example[2].TestE.b int                               Examples.example[2].k.b
// Example[2].TestE.TestA[0].a float                    Examples.example[2].k.c[0].a
// Example[2].TestE.TestA[0].b[0] ivec3[3]              Examples.example[2].k.c[0].b[0]
// Example[2].TestE.TestA[0].b[1]                       Examples.example[2].k.c[0].b[1]
// Example[2].TestE.TestA[0].b[2]                       Examples.example[2].k.c[0].b[2]
// Example[2].TestE.TestA[0].c int                      Examples.example[2].k.c[0].c
// Example[2].TestE.TestA[1].a float                    Examples.example[2].k.c[1].a
// Example[2].TestE.TestA[1].b[0] ivec3[3]              Examples.example[2].k.c[1].b[0]
// Example[2].TestE.TestA[1].b[1]                       Examples.example[2].k.c[1].b[1]
// Example[2].TestE.TestA[1].b[2]                       Examples.example[2].k.c[1].b[2]
// Example[2].TestE.TestA[1].c int                      Examples.example[2].k.c[1].c
// Example[2].TestE.TestA[2].a float                    Examples.example[2].k.c[2].a
// Example[2].TestE.TestA[2].b[0] ivec3[3]              Examples.example[2].k.c[2].b[0]
// Example[2].TestE.TestA[2].b[1]                       Examples.example[2].k.c[2].b[1]
// Example[2].TestE.TestA[2].b[2]                       Examples.example[2].k.c[2].b[2]
// Example[2].TestE.TestA[2].c int                      Examples.example[2].k.c[2].c
// Example[2].TestE.TestA[3].a float                    Examples.example[2].k.c[3].a
// Example[2].TestE.TestA[3].b[0] ivec3[3]              Examples.example[2].k.c[3].b[0]
// Example[2].TestE.TestA[3].b[1]                       Examples.example[2].k.c[3].b[1]
// Example[2].TestE.TestA[3].b[2]                       Examples.example[2].k.c[3].b[2]
// Example[2].TestE.TestA[3].c int                      Examples.example[2].k.c[3].c
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>

// new headers: 
#include <OSGGLEXT.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGUniformBufferObjChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>

#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 
#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGUniformBufferObjChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#endif

#define HAS_FP64_EXTENSION

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// Create a OpenSG UniformBufferObjChunk object which does
// perform the uniform buffer object abstraction.
// For each block member entry (declared in the shader) a
// corresponding addXXX call is to be performed on the
// ubo chunk. The cardinality for arrays must be provided
// to the function calls (defaults to 1). 
// The matrix functions are defined in column-major order
// matching the default definition of GLSL. I.e. a addMat2x3(2)
// call would request space and layout for an array of two
// matrices with two columns and three rows.
//
OSG::UniformBufferObjChunkTransitPtr create_example_block_state()
{
    OSG::UniformBufferObjChunkRefPtr ubo = OSG::UniformBufferObjChunk::create();

    ubo->setBlockName("Examples");
    ubo->setUsage(GL_STREAM_DRAW);

    ubo->addFloat   ("Examples.example[0].a");
    ubo->addVec2    ("Examples.example[0].b");
    ubo->addVec3    ("Examples.example[0].c");
    ubo->addFloat   ("Examples.example[0].d.a");
    ubo->addBVec2   ("Examples.example[0].d.b");
    ubo->addBVec2   ("Examples.example[0].d.c[0].a");
    ubo->addFloat   ("Examples.example[0].d.c[0].b[0].a");
    ubo->addIVec3   ("Examples.example[0].d.c[0].b[0].b", 3);
    ubo->addInt     ("Examples.example[0].d.c[0].b[0].c");
    ubo->addFloat   ("Examples.example[0].d.c[0].b[1].a");
    ubo->addIVec3   ("Examples.example[0].d.c[0].b[1].b", 3);
    ubo->addInt     ("Examples.example[0].d.c[0].b[1].c");
    ubo->addFloat   ("Examples.example[0].d.c[0].c");
    ubo->addBVec2   ("Examples.example[0].d.c[1].a");
    ubo->addFloat   ("Examples.example[0].d.c[1].b[0].a");
    ubo->addIVec3   ("Examples.example[0].d.c[1].b[0].b", 3);
    ubo->addInt     ("Examples.example[0].d.c[1].b[0].c");
    ubo->addFloat   ("Examples.example[0].d.c[1].b[1].a");
    ubo->addIVec3   ("Examples.example[0].d.c[1].b[1].b", 3);
    ubo->addInt     ("Examples.example[0].d.c[1].b[1].c");
    ubo->addFloat   ("Examples.example[0].d.c[1].c");
    ubo->addFloat   ("Examples.example[0].e");
    ubo->addFloat   ("Examples.example[0].f", 2);
    ubo->addMat2x3  ("Examples.example[0].g");
    ubo->addUVec3   ("Examples.example[0].h[0].a");
    ubo->addVec2    ("Examples.example[0].h[0].b");
    ubo->addFloat   ("Examples.example[0].h[0].c", 2);
    ubo->addVec2    ("Examples.example[0].h[0].d");
    ubo->addMat3    ("Examples.example[0].h[0].e", 2);
    ubo->addUVec3   ("Examples.example[0].h[1].a");
    ubo->addVec2    ("Examples.example[0].h[1].b");
    ubo->addFloat   ("Examples.example[0].h[1].c", 2);
    ubo->addVec2    ("Examples.example[0].h[1].d");
    ubo->addMat3    ("Examples.example[0].h[1].e", 2);
#ifdef HAS_FP64_EXTENSION
    ubo->addDouble  ("Examples.example[0].i");
#endif
    ubo->addBool    ("Examples.example[0].j");
#ifdef HAS_FP64_EXTENSION
    ubo->addDVec2   ("Examples.example[0].k.a");
#endif
    ubo->addInt     ("Examples.example[0].k.b");
    ubo->addFloat   ("Examples.example[0].k.c[0].a");
    ubo->addIVec3   ("Examples.example[0].k.c[0].b", 3);
    ubo->addInt     ("Examples.example[0].k.c[0].c");
    ubo->addFloat   ("Examples.example[0].k.c[1].a");
    ubo->addIVec3   ("Examples.example[0].k.c[1].b", 3);
    ubo->addInt     ("Examples.example[0].k.c[1].c");
    ubo->addFloat   ("Examples.example[0].k.c[2].a");
    ubo->addIVec3   ("Examples.example[0].k.c[2].b", 3);
    ubo->addInt     ("Examples.example[0].k.c[2].c");
    ubo->addFloat   ("Examples.example[0].k.c[3].a");
    ubo->addIVec3   ("Examples.example[0].k.c[3].b", 3);
    ubo->addInt     ("Examples.example[0].k.c[3].c");

    ubo->addFloat   ("Examples.example[1].a");
    ubo->addVec2    ("Examples.example[1].b");
    ubo->addVec3    ("Examples.example[1].c");
    ubo->addFloat   ("Examples.example[1].d.a");
    ubo->addBVec2   ("Examples.example[1].d.b");
    ubo->addBVec2   ("Examples.example[1].d.c[0].a");
    ubo->addFloat   ("Examples.example[1].d.c[0].b[0].a");
    ubo->addIVec3   ("Examples.example[1].d.c[0].b[0].b", 3);
    ubo->addInt     ("Examples.example[1].d.c[0].b[0].c");
    ubo->addFloat   ("Examples.example[1].d.c[0].b[1].a");
    ubo->addIVec3   ("Examples.example[1].d.c[0].b[1].b", 3);
    ubo->addInt     ("Examples.example[1].d.c[0].b[1].c");
    ubo->addFloat   ("Examples.example[1].d.c[0].c");
    ubo->addBVec2   ("Examples.example[1].d.c[1].a");
    ubo->addFloat   ("Examples.example[1].d.c[1].b[0].a");
    ubo->addIVec3   ("Examples.example[1].d.c[1].b[0].b", 3);
    ubo->addInt     ("Examples.example[1].d.c[1].b[0].c");
    ubo->addFloat   ("Examples.example[1].d.c[1].b[1].a");
    ubo->addIVec3   ("Examples.example[1].d.c[1].b[1].b", 3);
    ubo->addInt     ("Examples.example[1].d.c[1].b[1].c");
    ubo->addFloat   ("Examples.example[1].d.c[1].c");
    ubo->addFloat   ("Examples.example[1].e");
    ubo->addFloat   ("Examples.example[1].f", 2);
    ubo->addMat2x3  ("Examples.example[1].g");
    ubo->addUVec3   ("Examples.example[1].h[0].a");
    ubo->addVec2    ("Examples.example[1].h[0].b");
    ubo->addFloat   ("Examples.example[1].h[0].c", 2);
    ubo->addVec2    ("Examples.example[1].h[0].d");
    ubo->addMat3    ("Examples.example[1].h[0].e", 2);
    ubo->addUVec3   ("Examples.example[1].h[1].a");
    ubo->addVec2    ("Examples.example[1].h[1].b");
    ubo->addFloat   ("Examples.example[1].h[1].c", 2);
    ubo->addVec2    ("Examples.example[1].h[1].d");
    ubo->addMat3    ("Examples.example[1].h[1].e", 2);
#ifdef HAS_FP64_EXTENSION
    ubo->addDouble  ("Examples.example[1].i");
#endif
    ubo->addBool    ("Examples.example[1].j");
#ifdef HAS_FP64_EXTENSION
    ubo->addDVec2   ("Examples.example[1].k.a");
#endif
    ubo->addInt     ("Examples.example[1].k.b");
    ubo->addFloat   ("Examples.example[1].k.c[0].a");
    ubo->addIVec3   ("Examples.example[1].k.c[0].b", 3);
    ubo->addInt     ("Examples.example[1].k.c[0].c");
    ubo->addFloat   ("Examples.example[1].k.c[1].a");
    ubo->addIVec3   ("Examples.example[1].k.c[1].b", 3);
    ubo->addInt     ("Examples.example[1].k.c[1].c");
    ubo->addFloat   ("Examples.example[1].k.c[2].a");
    ubo->addIVec3   ("Examples.example[1].k.c[2].b", 3);
    ubo->addInt     ("Examples.example[1].k.c[2].c");
    ubo->addFloat   ("Examples.example[1].k.c[3].a");
    ubo->addIVec3   ("Examples.example[1].k.c[3].b", 3);
    ubo->addInt     ("Examples.example[1].k.c[3].c");

    ubo->addFloat   ("Examples.example[2].a");
    ubo->addVec2    ("Examples.example[2].b");
    ubo->addVec3    ("Examples.example[2].c");
    ubo->addFloat   ("Examples.example[2].d.a");
    ubo->addBVec2   ("Examples.example[2].d.b");
    ubo->addBVec2   ("Examples.example[2].d.c[0].a");
    ubo->addFloat   ("Examples.example[2].d.c[0].b[0].a");
    ubo->addIVec3   ("Examples.example[2].d.c[0].b[0].b", 3);
    ubo->addInt     ("Examples.example[2].d.c[0].b[0].c");
    ubo->addFloat   ("Examples.example[2].d.c[0].b[1].a");
    ubo->addIVec3   ("Examples.example[2].d.c[0].b[1].b", 3);
    ubo->addInt     ("Examples.example[2].d.c[0].b[1].c");
    ubo->addFloat   ("Examples.example[2].d.c[0].c");
    ubo->addBVec2   ("Examples.example[2].d.c[1].a");
    ubo->addFloat   ("Examples.example[2].d.c[1].b[0].a");
    ubo->addIVec3   ("Examples.example[2].d.c[1].b[0].b", 3);
    ubo->addInt     ("Examples.example[2].d.c[1].b[0].c");
    ubo->addFloat   ("Examples.example[2].d.c[1].b[1].a");
    ubo->addIVec3   ("Examples.example[2].d.c[1].b[1].b", 3);
    ubo->addInt     ("Examples.example[2].d.c[1].b[1].c");
    ubo->addFloat   ("Examples.example[2].d.c[1].c");
    ubo->addFloat   ("Examples.example[2].e");
    ubo->addFloat   ("Examples.example[2].f", 2);
    ubo->addMat2x3  ("Examples.example[2].g");
    ubo->addUVec3   ("Examples.example[2].h[0].a");
    ubo->addVec2    ("Examples.example[2].h[0].b");
    ubo->addFloat   ("Examples.example[2].h[0].c", 2);
    ubo->addVec2    ("Examples.example[2].h[0].d");
    ubo->addMat3    ("Examples.example[2].h[0].e", 2);
    ubo->addUVec3   ("Examples.example[2].h[1].a");
    ubo->addVec2    ("Examples.example[2].h[1].b");
    ubo->addFloat   ("Examples.example[2].h[1].c", 2);
    ubo->addVec2    ("Examples.example[2].h[1].d");
    ubo->addMat3    ("Examples.example[2].h[1].e", 2);
#ifdef HAS_FP64_EXTENSION
    ubo->addDouble  ("Examples.example[2].i");
#endif
    ubo->addBool    ("Examples.example[2].j");
#ifdef HAS_FP64_EXTENSION
    ubo->addDVec2   ("Examples.example[2].k.a");
#endif
    ubo->addInt     ("Examples.example[2].k.b");
    ubo->addFloat   ("Examples.example[2].k.c[0].a");
    ubo->addIVec3   ("Examples.example[2].k.c[0].b", 3);
    ubo->addInt     ("Examples.example[2].k.c[0].c");
    ubo->addFloat   ("Examples.example[2].k.c[1].a");
    ubo->addIVec3   ("Examples.example[2].k.c[1].b", 3);
    ubo->addInt     ("Examples.example[2].k.c[1].c");
    ubo->addFloat   ("Examples.example[2].k.c[2].a");
    ubo->addIVec3   ("Examples.example[2].k.c[2].b", 3);
    ubo->addInt     ("Examples.example[2].k.c[2].c");
    ubo->addFloat   ("Examples.example[2].k.c[3].a");
    ubo->addIVec3   ("Examples.example[2].k.c[3].b", 3);
    ubo->addInt     ("Examples.example[2].k.c[3].c");

    return OSG::UniformBufferObjChunkTransitPtr(ubo);
}

//
// Fill the ubo chunk with values.
//
void update_example_block_state(OSG::UniformBufferObjChunk* ubo)
{
    ubo->setFloat   ("Examples.example[0].a", 1234.56f);
    ubo->setVec2    ("Examples.example[0].b", OSG::Vec2f(1.4f, 8.6f));
    ubo->setVec3    ("Examples.example[0].c", OSG::Vec3f(0.1f, 0.2f, 0.3f));
    ubo->setFloat   ("Examples.example[0].d.a", 8123.45f);
    ubo->setBVec2   ("Examples.example[0].d.b", OSG::Vec2b(true, false));
    ubo->setBVec2   ("Examples.example[0].d.c[0].a", OSG::Vec2b(true, true));
    ubo->setFloat   ("Examples.example[0].d.c[0].b[0].a", 7812.34f);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[0].b", OSG::Vec3i(0,-1,2), 0);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[0].b", OSG::Vec3i(1,-2,3), 1);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[0].b", OSG::Vec3i(4,-5,6), 2);
    ubo->setInt     ("Examples.example[0].d.c[0].b[0].c", 6781);
    ubo->setFloat   ("Examples.example[0].d.c[0].b[1].a", 5678.12f);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[1].b", OSG::Vec3i(-7,8,9),    0);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[1].b", OSG::Vec3i(-10,11,12), 1);
    ubo->setIVec3   ("Examples.example[0].d.c[0].b[1].b", OSG::Vec3i(-13,14,15), 2);
    ubo->setInt     ("Examples.example[0].d.c[0].b[1].c", 4567);
    ubo->setFloat   ("Examples.example[0].d.c[0].c", 3456.78f);
    ubo->setBVec2   ("Examples.example[0].d.c[1].a", OSG::Vec2b(false, true));
    ubo->setFloat   ("Examples.example[0].d.c[1].b[0].a", 2345.67f);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[0].b", OSG::Vec3i(16,17,-18), 0);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[0].b", OSG::Vec3i(19,20,-21), 1);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[0].b", OSG::Vec3i(22,23,-24), 2);
    ubo->setInt     ("Examples.example[0].d.c[1].b[0].c", 123);
    ubo->setFloat   ("Examples.example[0].d.c[1].b[1].a", 812.34f);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[1].b", OSG::Vec3i(25,-26,27), 0);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[1].b", OSG::Vec3i(28,-29,30), 1);
    ubo->setIVec3   ("Examples.example[0].d.c[1].b[1].b", OSG::Vec3i(31,-32,33), 2);
    ubo->setInt     ("Examples.example[0].d.c[1].b[1].c", 781);
    ubo->setFloat   ("Examples.example[0].d.c[1].c", 678.12f);
    ubo->setFloat   ("Examples.example[0].e", 567.81f);
    ubo->setFloat   ("Examples.example[0].f", 456.78f, 0);
    ubo->setFloat   ("Examples.example[0].f", 345.67f, 1);

    // Matrix mxn (m rows and n columns): 
    // ----------------------------------
    // test_mat = a11 a12 a13 a14
    //            a21 a22 a23 a24
    //            a31 a32 a33 a34
    //            a41 a42 a43 a44
    // OpenSG takes rows...
    OSG::Matrix4f mat01( 11.1f,12.2f,13.3f,14.4f,    // row 1
                         21.1f,22.2f,23.3f,24.4f,    // row 2
                         31.1f,32.2f,33.3f,34.4f,    // row 3
                         41.1f,42.2f,43.3f,44.4f );  // row 4

    // ... and provides elements in column-major order
    //    OSG::Real32* storage = mat1.getValues();
    OSG::Vec4f   column01 = mat01[1];
    OSG::Vec4f   column02 = mat01[2];
    OSG::Vec4f   column03 = mat01[3];
    OSG::Vec4f   column04 = mat01[4];

    // GLSL uses column-major layout, i.e. mat2x3 is a matrix with 2 colums and 3 rows
    //
    // mat2x3   = a11 a12
    //            a21 a22
    //            a31 a32

    ubo->setMat2x3  ("Examples.example[0].g", mat01);
    ubo->setUVec3   ("Examples.example[0].h[0].a", OSG::Vec3u(91,82,73));
    ubo->setVec2    ("Examples.example[0].h[0].b", OSG::Vec2f(2.5f, 9.7f));
    ubo->setFloat   ("Examples.example[0].h[0].c", 234.56f, 0);
    ubo->setFloat   ("Examples.example[0].h[0].c", 12.34f, 1);
    ubo->setVec2    ("Examples.example[0].h[0].d", OSG::Vec2f(3.6f, 1.3f));

    OSG::Matrix4f mat02( 1.1f, 1.2f, 1.3f, 1.4f,     // row 1
                         2.1f, 2.2f, 2.3f, 2.4f,     // row 2
                         3.1f, 3.2f, 3.3f, 3.4f,     // row 3
                         4.1f, 4.2f, 4.3f, 4.4f );   // row 4

    OSG::Matrix4f mat03( 1.2f, 1.3f, 1.4f, 1.5f,     // row 1
                        -2.2f,-2.3f,-2.4f,-2.5f,     // row 2
                         3.2f, 3.3f, 3.4f, 3.5f,     // row 3
                         4.2f, 4.3f, 4.4f, 4.5f );   // row 4

    ubo->setMat3    ("Examples.example[0].h[0].e", mat02, 0);
    ubo->setMat3    ("Examples.example[0].h[0].e", mat03, 1);
    ubo->setUVec3   ("Examples.example[0].h[1].a", OSG::Vec3u(71,82,93));
    ubo->setVec2    ("Examples.example[0].h[1].b", OSG::Vec2f(4.5f, 2.4f));
    ubo->setFloat   ("Examples.example[0].h[1].c", 81.23f, 0);
    ubo->setFloat   ("Examples.example[0].h[1].c", 78.12f, 1);
    ubo->setVec2    ("Examples.example[0].h[1].d", OSG::Vec2f(5.7f, 3.5f));

    OSG::Matrix4f mat04( 1.3f, 1.4f, 1.5f, 1.6f,     // row 1
                         2.3f, 2.4f, 2.5f, 2.6f,     // row 2
                        -3.3f,-3.4f,-3.5f,-3.6f,     // row 3
                         4.3f, 4.4f, 4.5f, 4.6f );   // row 4

    OSG::Matrix4f mat05( 1.4f, 1.5f, 1.6f, 1.7f,     // row 1
                         2.4f, 2.5f, 2.6f, 2.7f,     // row 2
                         3.4f, 3.5f, 3.6f, 3.7f,     // row 3
                        -4.4f,-4.5f,-4.6f,-4.7f );   // row 4

    ubo->setMat3    ("Examples.example[0].h[1].e", mat04, 0);
    ubo->setMat3    ("Examples.example[0].h[1].e", mat05, 1);
#ifdef HAS_FP64_EXTENSION
    ubo->setDouble  ("Examples.example[0].i", 94.345678);
#endif
    ubo->setBool    ("Examples.example[0].j", true);
#ifdef HAS_FP64_EXTENSION
    ubo->setDVec2   ("Examples.example[0].k.a", OSG::Vec2d(12.874, -2346.985633));
#endif
    ubo->setInt     ("Examples.example[0].k.b", 3);
    ubo->setFloat   ("Examples.example[0].k.c[0].a", 67.81f);
    ubo->setIVec3   ("Examples.example[0].k.c[0].b", OSG::Vec3i(34,35,-36), 0);
    ubo->setIVec3   ("Examples.example[0].k.c[0].b", OSG::Vec3i(37,38,-39), 1);
    ubo->setIVec3   ("Examples.example[0].k.c[0].b", OSG::Vec3i(40,41,-42), 2);
    ubo->setInt     ("Examples.example[0].k.c[0].c", -4);
    ubo->setFloat   ("Examples.example[0].k.c[1].a", 56.78f);
    ubo->setIVec3   ("Examples.example[0].k.c[1].b", OSG::Vec3i(-43,44,45), 0);
    ubo->setIVec3   ("Examples.example[0].k.c[1].b", OSG::Vec3i(-46,47,48), 1);
    ubo->setIVec3   ("Examples.example[0].k.c[1].b", OSG::Vec3i(-49,50,51), 2);
    ubo->setInt     ("Examples.example[0].k.c[1].c", -5);
    ubo->setFloat   ("Examples.example[0].k.c[2].a", 45.67f);
    ubo->setIVec3   ("Examples.example[0].k.c[2].b", OSG::Vec3i(52,-53,54), 0);
    ubo->setIVec3   ("Examples.example[0].k.c[2].b", OSG::Vec3i(55,-56,57), 1);
    ubo->setIVec3   ("Examples.example[0].k.c[2].b", OSG::Vec3i(58,-59,60), 2);
    ubo->setInt     ("Examples.example[0].k.c[2].c", -6);
    ubo->setFloat   ("Examples.example[0].k.c[3].a", 34.56f);
    ubo->setIVec3   ("Examples.example[0].k.c[3].b", OSG::Vec3i(61,62,-63), 0);
    ubo->setIVec3   ("Examples.example[0].k.c[3].b", OSG::Vec3i(64,-65,66), 1);
    ubo->setIVec3   ("Examples.example[0].k.c[3].b", OSG::Vec3i(-67,68,69), 2);
    ubo->setInt     ("Examples.example[0].k.c[3].c", 7);



    ubo->setFloat   ("Examples.example[1].a", 91234.56f);
    ubo->setVec2    ("Examples.example[1].b", OSG::Vec2f(91.4f, 98.6f));
    ubo->setVec3    ("Examples.example[1].c", OSG::Vec3f(90.1f, 90.2f, 90.3f));
    ubo->setFloat   ("Examples.example[1].d.a", 98123.45f);
    ubo->setBVec2   ("Examples.example[1].d.b", OSG::Vec2b(false, false));
    ubo->setBVec2   ("Examples.example[1].d.c[0].a", OSG::Vec2b(true, false));
    ubo->setFloat   ("Examples.example[1].d.c[0].b[0].a", 97812.34f);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[0].b", OSG::Vec3i(90,-91,92), 0);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[0].b", OSG::Vec3i(91,-92,93), 1);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[0].b", OSG::Vec3i(94,-95,96), 2);
    ubo->setInt     ("Examples.example[1].d.c[0].b[0].c", 6781);
    ubo->setFloat   ("Examples.example[1].d.c[0].b[1].a", 5678.12f);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[1].b", OSG::Vec3i(-97,98,99),    0);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[1].b", OSG::Vec3i(-910,911,912), 1);
    ubo->setIVec3   ("Examples.example[1].d.c[0].b[1].b", OSG::Vec3i(-913,914,915), 2);
    ubo->setInt     ("Examples.example[1].d.c[0].b[1].c", 94567);
    ubo->setFloat   ("Examples.example[1].d.c[0].c", 93456.78f);
    ubo->setBVec2   ("Examples.example[1].d.c[1].a", OSG::Vec2b(false, true));
    ubo->setFloat   ("Examples.example[1].d.c[1].b[0].a", 92345.67f);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[0].b", OSG::Vec3i(916,917,-918), 0);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[0].b", OSG::Vec3i(919,920,-921), 1);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[0].b", OSG::Vec3i(922,923,-924), 2);
    ubo->setInt     ("Examples.example[1].d.c[1].b[0].c", 9123);
    ubo->setFloat   ("Examples.example[1].d.c[1].b[1].a", 9812.34f);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[1].b", OSG::Vec3i(925,-926,927), 0);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[1].b", OSG::Vec3i(928,-929,930), 1);
    ubo->setIVec3   ("Examples.example[1].d.c[1].b[1].b", OSG::Vec3i(931,-932,933), 2);
    ubo->setInt     ("Examples.example[1].d.c[1].b[1].c", 9781);
    ubo->setFloat   ("Examples.example[1].d.c[1].c", 9678.12f);
    ubo->setFloat   ("Examples.example[1].e", 9567.81f);
    ubo->setFloat   ("Examples.example[1].f", 9456.78f, 0);
    ubo->setFloat   ("Examples.example[1].f", 9345.67f, 1);

    // Matrix mxn (m rows and n columns): 
    // ----------------------------------
    // test_mat = a11 a12 a13 a14
    //            a21 a22 a23 a24
    //            a31 a32 a33 a34
    //            a41 a42 a43 a44
    // OpenSG takes rows...
    OSG::Matrix4f mat11( 911.1f,912.2f,913.3f,914.4f,    // row 1
                         921.1f,922.2f,923.3f,924.4f,    // row 2
                         931.1f,932.2f,933.3f,934.4f,    // row 3
                         941.1f,942.2f,943.3f,944.4f );  // row 4

    // ... and provides elements in column-major order
    //    OSG::Real32* storage = mat1.getValues();
    OSG::Vec4f   column11 = mat11[1];
    OSG::Vec4f   column12 = mat11[2];
    OSG::Vec4f   column13 = mat11[3];
    OSG::Vec4f   column14 = mat11[4];

    // GLSL uses column-major layout, i.e. mat2x3 is a matrix with 2 colums and 3 rows
    //
    // mat2x3   = a11 a12
    //            a21 a22
    //            a31 a32

    ubo->setMat2x3  ("Examples.example[1].g", mat11);
    ubo->setUVec3   ("Examples.example[1].h[0].a", OSG::Vec3u(991,982,973));
    ubo->setVec2    ("Examples.example[1].h[0].b", OSG::Vec2f(92.5f, 99.7f));
    ubo->setFloat   ("Examples.example[1].h[0].c", 9234.56f, 0);
    ubo->setFloat   ("Examples.example[1].h[0].c", 912.34f,  1);
    ubo->setVec2    ("Examples.example[1].h[0].d", OSG::Vec2f(93.6f, 91.3f));

    OSG::Matrix4f mat12( 91.1f, 91.2f, 91.3f, 91.4f,     // row 1
                         92.1f, 92.2f, 92.3f, 92.4f,     // row 2
                         93.1f, 93.2f, 93.3f, 93.4f,     // row 3
                         94.1f, 94.2f, 94.3f, 94.4f );   // row 4

    OSG::Matrix4f mat13( 91.2f, 91.3f, 91.4f, 91.5f,     // row 1
                        -92.2f,-92.3f,-92.4f,-92.5f,     // row 2
                         93.2f, 93.3f, 93.4f, 93.5f,     // row 3
                         94.2f, 94.3f, 94.4f, 94.5f );   // row 4

    ubo->setMat3    ("Examples.example[1].h[0].e", mat12, 0);
    ubo->setMat3    ("Examples.example[1].h[0].e", mat13, 1);
    ubo->setUVec3   ("Examples.example[1].h[1].a", OSG::Vec3u(971,982,93));
    ubo->setVec2    ("Examples.example[1].h[1].b", OSG::Vec2f(94.5f, 92.4f));
    ubo->setFloat   ("Examples.example[1].h[1].c", 981.23f, 0);
    ubo->setFloat   ("Examples.example[1].h[1].c", 978.12f, 1);
    ubo->setVec2    ("Examples.example[1].h[1].d", OSG::Vec2f(95.7f, 93.5f));

    OSG::Matrix4f mat14( 91.3f, 91.4f, 91.5f, 91.6f,     // row 1
                         92.3f, 92.4f, 92.5f, 92.6f,     // row 2
                        -93.3f,-93.4f,-93.5f,-93.6f,     // row 3
                         94.3f, 94.4f, 94.5f, 94.6f );   // row 4

    OSG::Matrix4f mat15( 91.4f, 91.5f, 91.6f, 91.7f,     // row 1
                         92.4f, 92.5f, 92.6f, 92.7f,     // row 2
                         93.4f, 93.5f, 93.6f, 93.7f,     // row 3
                        -94.4f,-94.5f,-94.6f,-94.7f );   // row 4

    ubo->setMat3    ("Examples.example[1].h[1].e", mat14, 0);
    ubo->setMat3    ("Examples.example[1].h[1].e", mat15, 1);
#ifdef HAS_FP64_EXTENSION
    ubo->setDouble  ("Examples.example[1].i", 994.345678);
#endif
    ubo->setBool    ("Examples.example[1].j", false);
#ifdef HAS_FP64_EXTENSION
    ubo->setDVec2   ("Examples.example[1].k.a", OSG::Vec2d(912.874, -92346.985633));
#endif
    ubo->setInt     ("Examples.example[1].k.b", 93);
    ubo->setFloat   ("Examples.example[1].k.c[0].a", 967.81f);
    ubo->setIVec3   ("Examples.example[1].k.c[0].b", OSG::Vec3i(934,935,-936), 0);
    ubo->setIVec3   ("Examples.example[1].k.c[0].b", OSG::Vec3i(937,938,-939), 1);
    ubo->setIVec3   ("Examples.example[1].k.c[0].b", OSG::Vec3i(940,941,-942), 2);
    ubo->setInt     ("Examples.example[1].k.c[0].c", -94);
    ubo->setFloat   ("Examples.example[1].k.c[1].a", 956.78f);
    ubo->setIVec3   ("Examples.example[1].k.c[1].b", OSG::Vec3i(-943,944,945), 0);
    ubo->setIVec3   ("Examples.example[1].k.c[1].b", OSG::Vec3i(-946,947,948), 1);
    ubo->setIVec3   ("Examples.example[1].k.c[1].b", OSG::Vec3i(-949,950,951), 2);
    ubo->setInt     ("Examples.example[1].k.c[1].c", -95);
    ubo->setFloat   ("Examples.example[1].k.c[2].a", 945.67f);
    ubo->setIVec3   ("Examples.example[1].k.c[2].b", OSG::Vec3i(952,-953,954), 0);
    ubo->setIVec3   ("Examples.example[1].k.c[2].b", OSG::Vec3i(955,-956,957), 1);
    ubo->setIVec3   ("Examples.example[1].k.c[2].b", OSG::Vec3i(958,-959,960), 2);
    ubo->setInt     ("Examples.example[1].k.c[2].c", -96);
    ubo->setFloat   ("Examples.example[1].k.c[3].a", 934.56f);
    ubo->setIVec3   ("Examples.example[1].k.c[3].b", OSG::Vec3i(961,962,-963), 0);
    ubo->setIVec3   ("Examples.example[1].k.c[3].b", OSG::Vec3i(964,-965,966), 1);
    ubo->setIVec3   ("Examples.example[1].k.c[3].b", OSG::Vec3i(-967,968,969), 2);
    ubo->setInt     ("Examples.example[1].k.c[3].c", 97);



    ubo->setFloat   ("Examples.example[2].a", 71234.56f);
    ubo->setVec2    ("Examples.example[2].b", OSG::Vec2f(71.4f, 78.6f));
    ubo->setVec3    ("Examples.example[2].c", OSG::Vec3f(70.1f, 70.2f, 70.3f));
    ubo->setFloat   ("Examples.example[2].d.a", 78123.45f);
    ubo->setBVec2   ("Examples.example[2].d.b", OSG::Vec2b(true, true));
    ubo->setBVec2   ("Examples.example[2].d.c[0].a", OSG::Vec2b(true, false));
    ubo->setFloat   ("Examples.example[2].d.c[0].b[0].a", 77812.34f);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[0].b", OSG::Vec3i(70,-71,72), 0);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[0].b", OSG::Vec3i(71,-72,73), 1);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[0].b", OSG::Vec3i(74,-75,76), 2);
    ubo->setInt     ("Examples.example[2].d.c[0].b[0].c", 76781);
    ubo->setFloat   ("Examples.example[2].d.c[0].b[1].a", 75678.12f);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[1].b", OSG::Vec3i(-77,78,79),    0);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[1].b", OSG::Vec3i(-710,711,712), 1);
    ubo->setIVec3   ("Examples.example[2].d.c[0].b[1].b", OSG::Vec3i(-713,714,715), 2);
    ubo->setInt     ("Examples.example[2].d.c[0].b[1].c", 74567);
    ubo->setFloat   ("Examples.example[2].d.c[0].c", 73456.78f);
    ubo->setBVec2   ("Examples.example[2].d.c[1].a",OSG::Vec2b(true, true));
    ubo->setFloat   ("Examples.example[2].d.c[1].b[0].a", 72345.67f);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[0].b", OSG::Vec3i(716,717,-718), 0);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[0].b", OSG::Vec3i(719,720,-721), 1);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[0].b", OSG::Vec3i(722,723,-724), 2);
    ubo->setInt     ("Examples.example[2].d.c[1].b[0].c", 7123);
    ubo->setFloat   ("Examples.example[2].d.c[1].b[1].a", 7812.34f);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[1].b", OSG::Vec3i(725,-726,727), 0);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[1].b", OSG::Vec3i(728,-729,730), 1);
    ubo->setIVec3   ("Examples.example[2].d.c[1].b[1].b", OSG::Vec3i(731,-732,733), 2);
    ubo->setInt     ("Examples.example[2].d.c[1].b[1].c", 7781);
    ubo->setFloat   ("Examples.example[2].d.c[1].c", 7678.12f);
    ubo->setFloat   ("Examples.example[2].e", 7567.81f);
    ubo->setFloat   ("Examples.example[2].f", 7456.78f, 0);
    ubo->setFloat   ("Examples.example[2].f", 7345.67f, 1);

    // Matrix mxn (m rows and n columns): 
    // ----------------------------------
    // test_mat = a11 a12 a13 a14
    //            a21 a22 a23 a24
    //            a31 a32 a33 a34
    //            a41 a42 a43 a44
    // OpenSG takes rows...
    OSG::Matrix4f mat21( 711.1f,712.2f,713.3f,714.4f,    // row 1
                         721.1f,722.2f,723.3f,724.4f,    // row 2
                         731.1f,732.2f,733.3f,734.4f,    // row 3
                         741.1f,742.2f,743.3f,744.4f );  // row 4

    // ... and provides elements in column-major order
    //    OSG::Real32* storage = mat1.getValues();
    OSG::Vec4f   column21 = mat21[1];
    OSG::Vec4f   column22 = mat21[2];
    OSG::Vec4f   column23 = mat21[3];
    OSG::Vec4f   column24 = mat21[4];

    // GLSL uses column-major layout, i.e. mat2x3 is a matrix with 2 colums and 3 rows
    //
    // mat2x3   = a11 a12
    //            a21 a22
    //            a31 a32

    ubo->setMat2x3  ("Examples.example[2].g", mat21);
    ubo->setUVec3   ("Examples.example[2].h[0].a", OSG::Vec3u(791,782,73));
    ubo->setVec2    ("Examples.example[2].h[0].b", OSG::Vec2f(72.5f, 79.7f));
    ubo->setFloat   ("Examples.example[2].h[0].c", 7234.56f, 0);
    ubo->setFloat   ("Examples.example[2].h[0].c", 712.34f,  1);
    ubo->setVec2    ("Examples.example[2].h[0].d", OSG::Vec2f(73.6f, 71.3f));

    OSG::Matrix4f mat22( 71.1f, 71.2f, 71.3f, 71.4f,     // row 1
                         72.1f, 72.2f, 72.3f, 72.4f,     // row 2
                         73.1f, 73.2f, 73.3f, 73.4f,     // row 3
                         74.1f, 74.2f, 74.3f, 74.4f );   // row 4

    OSG::Matrix4f mat23( 71.2f, 71.3f, 71.4f, 71.5f,     // row 1
                        -72.2f,-72.3f,-72.4f,-72.5f,     // row 2
                         73.2f, 73.3f, 73.4f, 73.5f,     // row 3
                         74.2f, 74.3f, 74.4f, 74.5f );   // row 4

    ubo->setMat3    ("Examples.example[2].h[0].e", mat22, 0);
    ubo->setMat3    ("Examples.example[2].h[0].e", mat23, 1);
    ubo->setUVec3   ("Examples.example[2].h[1].a", OSG::Vec3u(771,782,793));
    ubo->setVec2    ("Examples.example[2].h[1].b", OSG::Vec2f(74.5f, 72.4f));
    ubo->setFloat   ("Examples.example[2].h[1].c", 781.23f, 0);
    ubo->setFloat   ("Examples.example[2].h[1].c", 778.12f, 1);
    ubo->setVec2    ("Examples.example[2].h[1].d", OSG::Vec2f(75.7f, 73.5f));

    OSG::Matrix4f mat24( 71.3f, 71.4f, 71.5f, 71.6f,     // row 1
                         72.3f, 72.4f, 72.5f, 72.6f,     // row 2
                        -73.3f,-73.4f,-73.5f,-73.6f,     // row 3
                         74.3f, 74.4f, 74.5f, 74.6f );   // row 4

    OSG::Matrix4f mat25( 71.4f, 71.5f, 71.6f, 71.7f,     // row 1
                         72.4f, 72.5f, 72.6f, 72.7f,     // row 2
                         73.4f, 73.5f, 73.6f, 73.7f,     // row 3
                        -74.4f,-74.5f,-74.6f,-74.7f );   // row 4

    ubo->setMat3    ("Examples.example[2].h[1].e", mat24, 0);
    ubo->setMat3    ("Examples.example[2].h[1].e", mat25, 1);
#ifdef HAS_FP64_EXTENSION
    ubo->setDouble  ("Examples.example[2].i", 794.345678);
#endif
    ubo->setBool    ("Examples.example[2].j", true);
#ifdef HAS_FP64_EXTENSION
    ubo->setDVec2   ("Examples.example[2].k.a", OSG::Vec2d(712.874, -72346.985633));
#endif
    ubo->setInt     ("Examples.example[2].k.b", 73);
    ubo->setFloat   ("Examples.example[2].k.c[0].a", 767.81f);
    ubo->setIVec3   ("Examples.example[2].k.c[0].b", OSG::Vec3i(734,735,-736), 0);
    ubo->setIVec3   ("Examples.example[2].k.c[0].b", OSG::Vec3i(737,738,-739), 1);
    ubo->setIVec3   ("Examples.example[2].k.c[0].b", OSG::Vec3i(740,741,-742), 2);
    ubo->setInt     ("Examples.example[2].k.c[0].c", -74);
    ubo->setFloat   ("Examples.example[2].k.c[1].a", 756.78f);
    ubo->setIVec3   ("Examples.example[2].k.c[1].b", OSG::Vec3i(-743,744,745), 0);
    ubo->setIVec3   ("Examples.example[2].k.c[1].b", OSG::Vec3i(-746,747,748), 1);
    ubo->setIVec3   ("Examples.example[2].k.c[1].b", OSG::Vec3i(-749,750,751), 2);
    ubo->setInt     ("Examples.example[2].k.c[1].c", -75);
    ubo->setFloat   ("Examples.example[2].k.c[2].a", 745.67f);
    ubo->setIVec3   ("Examples.example[2].k.c[2].b", OSG::Vec3i(752,-753,754), 0);
    ubo->setIVec3   ("Examples.example[2].k.c[2].b", OSG::Vec3i(755,-756,757), 1);
    ubo->setIVec3   ("Examples.example[2].k.c[2].b", OSG::Vec3i(758,-759,760), 2);
    ubo->setInt     ("Examples.example[2].k.c[2].c", -76);
    ubo->setFloat   ("Examples.example[2].k.c[3].a", 734.56f);
    ubo->setIVec3   ("Examples.example[2].k.c[3].b", OSG::Vec3i(761,762,-763), 0);
    ubo->setIVec3   ("Examples.example[2].k.c[3].b", OSG::Vec3i(764,-765,766), 1);
    ubo->setIVec3   ("Examples.example[2].k.c[3].b", OSG::Vec3i(-767,768,769), 2);
    ubo->setInt     ("Examples.example[2].k.c[3].c", 7);
}

//
// vertex shader program.
//
std::string get_vp_program();

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program();

//
// a separate transformation for every object
//
OSG::TransformRefPtr cyltrans, tortrans;

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

//
// redraw the window
//
void display(void)
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                   OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

    tortrans->setMatrix(m);

    OSG::commitChanges();
    
    mgr->redraw();
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);

        //
        // create the shader program
        //
        OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
        OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

        vertShader->setProgram(get_vp_program());
        fragShader->setProgram(get_fp_program());

        //
        // binding the uniform block to a buffer binding point can be performed 
        // either by calling the shaders's addUniformBlock method or by
        // adding a 'buffer block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        fragShader->addUniformBlock("Examples", 1); // block binding point

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        //
        // create uniform buffer object for block 'Examples'
        //
        OSG::UniformBufferObjChunkRefPtr ubo_example_block = create_example_block_state();

        update_example_block_state(ubo_example_block);

        OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
        polygon_chunk->setFrontMode(GL_FILL);
        polygon_chunk->setBackMode(GL_FILL);
        polygon_chunk->setCullFace(GL_NONE);

        OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
        depth_chunk->setEnable(true);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(ubo_example_block, 1);      // buffer binding point 1
        prog_state->addChunk(prog_chunk);
        prog_state->addChunk(polygon_chunk);
        prog_state->addChunk(depth_chunk);

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);
        scene->setCore(mgrp);

        OSG::commitChanges();
    
        mgr->setRoot(scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            cyltrans = NULL;
            tortrans = NULL;
            mgr      = NULL;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

//
// vertex shader program.
//
std::string get_vp_program()
{
        std::string vp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = ftransform();\n"
            "}\n"
            "\n"
            ;

    return vp_program;
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    std::string fp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
#ifdef HAS_FP64_EXTENSION
            "#extension GL_ARB_gpu_shader_fp64:              enable\n"
#endif
            "\n"
            "struct TestA\n"
            "{\n"
            "    float a;\n"
            "    ivec3 b[3];\n"
            "    int   c;\n"
            "};\n"
            "\n"
            "struct TestB\n"
            "{\n"
            "    bvec2 a;\n"
            "    TestA b[2];\n"
            "    float c;\n"
            "};\n"
            "\n"
            "struct TestC\n"
            "{\n"
            "    float a;\n"
            "    bvec2 b;\n"
            "    TestB c[2];\n"
            "};\n"
            "\n"
            "struct TestD\n"
            "{\n"
            "    uvec3 a;\n"
            "    vec2  b;\n"
            "    float c[2];\n"
            "    vec2  d;\n"
            "    mat3  e[2];\n"
            "};\n"
            "\n"
            "struct TestE\n"
            "{\n"
#ifdef HAS_FP64_EXTENSION
            "    dvec2 a;\n"
#endif
            "    int   b;\n"
            "    TestA c[4];\n"
            "};\n"
            "\n"
            "struct Example\n"
            "{\n"
            "    float  a;\n"
            "    vec2   b;\n"
            "    vec3   c;\n"
            "    TestC  d;\n"
            "    float  e;\n"
            "    float  f[2];\n"
            "    mat2x3 g;\n"
            "    TestD  h[2];\n"
#ifdef HAS_FP64_EXTENSION
            "    double i;\n"
#endif
            "    bool   j;\n"
            "    TestE  k;\n"
            "};\n"
            "\n"
            "layout (shared) uniform Examples\n"
            "{\n"
            "    Example example[3];\n"
            "} examples;\n"
            "\n"
            "\n"
            "layout(location = 0) out vec4 vFragColor;\n"
            "\n"
            "\n"
            "void main()\n"
            "{\n"
            "\n"
            "    vec4 error = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "    vec4 color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "\n"
            "\n"
            "     float   examples_example_0_a                = examples.example[0].a;\n"
            "     vec2    examples_example_0_b                = examples.example[0].b;\n"
            "     vec3    examples_example_0_c                = examples.example[0].c;\n"
            "     float   examples_example_0_d_a              = examples.example[0].d.a;\n"
            "     bvec2   examples_example_0_d_b              = examples.example[0].d.b;\n"
            "     bvec2   examples_example_0_d_c_0_a          = examples.example[0].d.c[0].a;\n"
            "     float   examples_example_0_d_c_0_b_0_a      = examples.example[0].d.c[0].b[0].a;\n"
            "     ivec3   examples_example_0_d_c_0_b_0_b_0    = examples.example[0].d.c[0].b[0].b[0];\n"
            "     ivec3   examples_example_0_d_c_0_b_0_b_1    = examples.example[0].d.c[0].b[0].b[1];\n"
            "     ivec3   examples_example_0_d_c_0_b_0_b_2    = examples.example[0].d.c[0].b[0].b[2];\n"
            "     int     examples_example_0_d_c_0_b_0_c      = examples.example[0].d.c[0].b[0].c;\n"
            "     float   examples_example_0_d_c_0_b_1_a      = examples.example[0].d.c[0].b[1].a;\n"
            "     ivec3   examples_example_0_d_c_0_b_1_b_0    = examples.example[0].d.c[0].b[1].b[0];\n"
            "     ivec3   examples_example_0_d_c_0_b_1_b_1    = examples.example[0].d.c[0].b[1].b[1];\n"
            "     ivec3   examples_example_0_d_c_0_b_1_b_2    = examples.example[0].d.c[0].b[1].b[2];\n"
            "     int     examples_example_0_d_c_0_b_1_c      = examples.example[0].d.c[0].b[1].c;\n"
            "     float   examples_example_0_d_c_0_c          = examples.example[0].d.c[0].c;\n"
            "     bvec2   examples_example_0_d_c_1_a          = examples.example[0].d.c[1].a;\n"
            "     float   examples_example_0_d_c_1_b_0_a      = examples.example[0].d.c[1].b[0].a;\n"
            "     ivec3   examples_example_0_d_c_1_b_0_b_0    = examples.example[0].d.c[1].b[0].b[0];\n"
            "     ivec3   examples_example_0_d_c_1_b_0_b_1    = examples.example[0].d.c[1].b[0].b[1];\n"
            "     ivec3   examples_example_0_d_c_1_b_0_b_2    = examples.example[0].d.c[1].b[0].b[2];\n"
            "     int     examples_example_0_d_c_1_b_0_c      = examples.example[0].d.c[1].b[0].c;\n"
            "     float   examples_example_0_d_c_1_b_1_a      = examples.example[0].d.c[1].b[1].a;\n"
            "     ivec3   examples_example_0_d_c_1_b_1_b_0    = examples.example[0].d.c[1].b[1].b[0];\n"
            "     ivec3   examples_example_0_d_c_1_b_1_b_1    = examples.example[0].d.c[1].b[1].b[1];\n"
            "     ivec3   examples_example_0_d_c_1_b_1_b_2    = examples.example[0].d.c[1].b[1].b[2];\n"
            "     int     examples_example_0_d_c_1_b_1_c      = examples.example[0].d.c[1].b[1].c;\n"
            "     float   examples_example_0_d_c_1_c          = examples.example[0].d.c[1].c;\n"
            "     float   examples_example_0_e                = examples.example[0].e;\n"
            "     float   examples_example_0_f_0              = examples.example[0].f[0];\n"
            "     float   examples_example_0_f_1              = examples.example[0].f[1];\n"
            "     mat2x3  examples_example_0_g                = examples.example[0].g;\n"
            "     uvec3   examples_example_0_h_0_a            = examples.example[0].h[0].a;\n"
            "     vec2    examples_example_0_h_0_b            = examples.example[0].h[0].b;\n"
            "     float   examples_example_0_h_0_c_0          = examples.example[0].h[0].c[0];\n"
            "     float   examples_example_0_h_0_c_1          = examples.example[0].h[0].c[1];\n"
            "     vec2    examples_example_0_h_0_d            = examples.example[0].h[0].d;\n"
            "     mat3    examples_example_0_h_0_e_0          = examples.example[0].h[0].e[0];\n"
            "     mat3    examples_example_0_h_0_e_1          = examples.example[0].h[0].e[1];\n"
            "     uvec3   examples_example_0_h_1_a            = examples.example[0].h[1].a;\n"
            "     vec2    examples_example_0_h_1_b            = examples.example[0].h[1].b;\n"
            "     float   examples_example_0_h_1_c_0          = examples.example[0].h[1].c[0];\n"
            "     float   examples_example_0_h_1_c_1          = examples.example[0].h[1].c[1];\n"
            "     vec2    examples_example_0_h_1_d            = examples.example[0].h[1].d;\n"
            "     mat3    examples_example_0_h_1_e_0          = examples.example[0].h[1].e[0];\n"
            "     mat3    examples_example_0_h_1_e_1          = examples.example[0].h[1].e[1];\n"
#ifdef HAS_FP64_EXTENSION
            "     double  examples_example_0_i                = examples.example[0].i;\n"
#endif
            "     bool    examples_example_0_j                = examples.example[0].j;\n"
#ifdef HAS_FP64_EXTENSION
            "     dvec2   examples_example_0_k_a              = examples.example[0].k.a;\n"
#endif
            "     int     examples_example_0_k_b              = examples.example[0].k.b;\n"
            "     float   examples_example_0_k_c_0_a          = examples.example[0].k.c[0].a;\n"
            "     ivec3   examples_example_0_k_c_0_b_0        = examples.example[0].k.c[0].b[0];\n"
            "     ivec3   examples_example_0_k_c_0_b_1        = examples.example[0].k.c[0].b[1];\n"
            "     ivec3   examples_example_0_k_c_0_b_2        = examples.example[0].k.c[0].b[2];\n"
            "     int     examples_example_0_k_c_0_c          = examples.example[0].k.c[0].c;\n"
            "     float   examples_example_0_k_c_1_a          = examples.example[0].k.c[1].a;\n"
            "     ivec3   examples_example_0_k_c_1_b_0        = examples.example[0].k.c[1].b[0];\n"
            "     ivec3   examples_example_0_k_c_1_b_1        = examples.example[0].k.c[1].b[1];\n"
            "     ivec3   examples_example_0_k_c_1_b_2        = examples.example[0].k.c[1].b[2];\n"
            "     int     examples_example_0_k_c_1_c          = examples.example[0].k.c[1].c;\n"
            "     float   examples_example_0_k_c_2_a          = examples.example[0].k.c[2].a;\n"
            "     ivec3   examples_example_0_k_c_2_b_0        = examples.example[0].k.c[2].b[0];\n"
            "     ivec3   examples_example_0_k_c_2_b_1        = examples.example[0].k.c[2].b[1];\n"
            "     ivec3   examples_example_0_k_c_2_b_2        = examples.example[0].k.c[2].b[2];\n"
            "     int     examples_example_0_k_c_2_c          = examples.example[0].k.c[2].c;\n"
            "     float   examples_example_0_k_c_3_a          = examples.example[0].k.c[3].a;\n"
            "     ivec3   examples_example_0_k_c_3_b_0        = examples.example[0].k.c[3].b[0];\n"
            "     ivec3   examples_example_0_k_c_3_b_1        = examples.example[0].k.c[3].b[1];\n"
            "     ivec3   examples_example_0_k_c_3_b_2        = examples.example[0].k.c[3].b[2];\n"
            "     int     examples_example_0_k_c_3_c          = examples.example[0].k.c[3].c;\n"
            "\n"
            "     float   examples_example_1_a                = examples.example[1].a;\n"
            "     vec2    examples_example_1_b                = examples.example[1].b;\n"
            "     vec3    examples_example_1_c                = examples.example[1].c;\n"
            "     float   examples_example_1_d_a              = examples.example[1].d.a;\n"
            "     bvec2   examples_example_1_d_b              = examples.example[1].d.b;\n"
            "     bvec2   examples_example_1_d_c_0_a          = examples.example[1].d.c[0].a;\n"
            "     float   examples_example_1_d_c_0_b_0_a      = examples.example[1].d.c[0].b[0].a;\n"
            "     ivec3   examples_example_1_d_c_0_b_0_b_0    = examples.example[1].d.c[0].b[0].b[0];\n"
            "     ivec3   examples_example_1_d_c_0_b_0_b_1    = examples.example[1].d.c[0].b[0].b[1];\n"
            "     ivec3   examples_example_1_d_c_0_b_0_b_2    = examples.example[1].d.c[0].b[0].b[2];\n"
            "     int     examples_example_1_d_c_0_b_0_c      = examples.example[1].d.c[0].b[0].c;\n"
            "     float   examples_example_1_d_c_0_b_1_a      = examples.example[1].d.c[0].b[1].a;\n"
            "     ivec3   examples_example_1_d_c_0_b_1_b_0    = examples.example[1].d.c[0].b[1].b[0];\n"
            "     ivec3   examples_example_1_d_c_0_b_1_b_1    = examples.example[1].d.c[0].b[1].b[1];\n"
            "     ivec3   examples_example_1_d_c_0_b_1_b_2    = examples.example[1].d.c[0].b[1].b[2];\n"
            "     int     examples_example_1_d_c_0_b_1_c      = examples.example[1].d.c[0].b[1].c;\n"
            "     float   examples_example_1_d_c_0_c          = examples.example[1].d.c[0].c;\n"
            "     bvec2   examples_example_1_d_c_1_a          = examples.example[1].d.c[1].a;\n"
            "     float   examples_example_1_d_c_1_b_0_a      = examples.example[1].d.c[1].b[0].a;\n"
            "     ivec3   examples_example_1_d_c_1_b_0_b_0    = examples.example[1].d.c[1].b[0].b[0];\n"
            "     ivec3   examples_example_1_d_c_1_b_0_b_1    = examples.example[1].d.c[1].b[0].b[1];\n"
            "     ivec3   examples_example_1_d_c_1_b_0_b_2    = examples.example[1].d.c[1].b[0].b[2];\n"
            "     int     examples_example_1_d_c_1_b_0_c      = examples.example[1].d.c[1].b[0].c;\n"
            "     float   examples_example_1_d_c_1_b_1_a      = examples.example[1].d.c[1].b[1].a;\n"
            "     ivec3   examples_example_1_d_c_1_b_1_b_0    = examples.example[1].d.c[1].b[1].b[0];\n"
            "     ivec3   examples_example_1_d_c_1_b_1_b_1    = examples.example[1].d.c[1].b[1].b[1];\n"
            "     ivec3   examples_example_1_d_c_1_b_1_b_2    = examples.example[1].d.c[1].b[1].b[2];\n"
            "     int     examples_example_1_d_c_1_b_1_c      = examples.example[1].d.c[1].b[1].c;\n"
            "     float   examples_example_1_d_c_1_c          = examples.example[1].d.c[1].c;\n"
            "     float   examples_example_1_e                = examples.example[1].e;\n"
            "     float   examples_example_1_f_0              = examples.example[1].f[0];\n"
            "     float   examples_example_1_f_1              = examples.example[1].f[1];\n"
            "     mat2x3  examples_example_1_g                = examples.example[1].g;\n"
            "     uvec3   examples_example_1_h_0_a            = examples.example[1].h[0].a;\n"
            "     vec2    examples_example_1_h_0_b            = examples.example[1].h[0].b;\n"
            "     float   examples_example_1_h_0_c_0          = examples.example[1].h[0].c[0];\n"
            "     float   examples_example_1_h_0_c_1          = examples.example[1].h[0].c[1];\n"
            "     vec2    examples_example_1_h_0_d            = examples.example[1].h[0].d;\n"
            "     mat3    examples_example_1_h_0_e_0          = examples.example[1].h[0].e[0];\n"
            "     mat3    examples_example_1_h_0_e_1          = examples.example[1].h[0].e[1];\n"
            "     uvec3   examples_example_1_h_1_a            = examples.example[1].h[1].a;\n"
            "     vec2    examples_example_1_h_1_b            = examples.example[1].h[1].b;\n"
            "     float   examples_example_1_h_1_c_0          = examples.example[1].h[1].c[0];\n"
            "     float   examples_example_1_h_1_c_1          = examples.example[1].h[1].c[1];\n"
            "     vec2    examples_example_1_h_1_d            = examples.example[1].h[1].d;\n"
            "     mat3    examples_example_1_h_1_e_0          = examples.example[1].h[1].e[0];\n"
            "     mat3    examples_example_1_h_1_e_1          = examples.example[1].h[1].e[1];\n"
#ifdef HAS_FP64_EXTENSION
            "     double  examples_example_1_i                = examples.example[1].i;\n"
#endif
            "     bool    examples_example_1_j                = examples.example[1].j;\n"
#ifdef HAS_FP64_EXTENSION
            "     dvec2   examples_example_1_k_a              = examples.example[1].k.a;\n"
#endif
            "     int     examples_example_1_k_b              = examples.example[1].k.b;\n"
            "     float   examples_example_1_k_c_0_a          = examples.example[1].k.c[0].a;\n"
            "     ivec3   examples_example_1_k_c_0_b_0        = examples.example[1].k.c[0].b[0];\n"
            "     ivec3   examples_example_1_k_c_0_b_1        = examples.example[1].k.c[0].b[1];\n"
            "     ivec3   examples_example_1_k_c_0_b_2        = examples.example[1].k.c[0].b[2];\n"
            "     int     examples_example_1_k_c_0_c          = examples.example[1].k.c[0].c;\n"
            "     float   examples_example_1_k_c_1_a          = examples.example[1].k.c[1].a;\n"
            "     ivec3   examples_example_1_k_c_1_b_0        = examples.example[1].k.c[1].b[0];\n"
            "     ivec3   examples_example_1_k_c_1_b_1        = examples.example[1].k.c[1].b[1];\n"
            "     ivec3   examples_example_1_k_c_1_b_2        = examples.example[1].k.c[1].b[2];\n"
            "     int     examples_example_1_k_c_1_c          = examples.example[1].k.c[1].c;\n"
            "     float   examples_example_1_k_c_2_a          = examples.example[1].k.c[2].a;\n"
            "     ivec3   examples_example_1_k_c_2_b_0        = examples.example[1].k.c[2].b[0];\n"
            "     ivec3   examples_example_1_k_c_2_b_1        = examples.example[1].k.c[2].b[1];\n"
            "     ivec3   examples_example_1_k_c_2_b_2        = examples.example[1].k.c[2].b[2];\n"
            "     int     examples_example_1_k_c_2_c          = examples.example[1].k.c[2].c;\n"
            "     float   examples_example_1_k_c_3_a          = examples.example[1].k.c[3].a;\n"
            "     ivec3   examples_example_1_k_c_3_b_0        = examples.example[1].k.c[3].b[0];\n"
            "     ivec3   examples_example_1_k_c_3_b_1        = examples.example[1].k.c[3].b[1];\n"
            "     ivec3   examples_example_1_k_c_3_b_2        = examples.example[1].k.c[3].b[2];\n"
            "     int     examples_example_1_k_c_3_c          = examples.example[1].k.c[3].c;\n"
            "\n"
            "     float   examples_example_2_a                = examples.example[2].a;\n"
            "     vec2    examples_example_2_b                = examples.example[2].b;\n"
            "     vec3    examples_example_2_c                = examples.example[2].c;\n"
            "     float   examples_example_2_d_a              = examples.example[2].d.a;\n"
            "     bvec2   examples_example_2_d_b              = examples.example[2].d.b;\n"
            "     bvec2   examples_example_2_d_c_0_a          = examples.example[2].d.c[0].a;\n"
            "     float   examples_example_2_d_c_0_b_0_a      = examples.example[2].d.c[0].b[0].a;\n"
            "     ivec3   examples_example_2_d_c_0_b_0_b_0    = examples.example[2].d.c[0].b[0].b[0];\n"
            "     ivec3   examples_example_2_d_c_0_b_0_b_1    = examples.example[2].d.c[0].b[0].b[1];\n"
            "     ivec3   examples_example_2_d_c_0_b_0_b_2    = examples.example[2].d.c[0].b[0].b[2];\n"
            "     int     examples_example_2_d_c_0_b_0_c      = examples.example[2].d.c[0].b[0].c;\n"
            "     float   examples_example_2_d_c_0_b_1_a      = examples.example[2].d.c[0].b[1].a;\n"
            "     ivec3   examples_example_2_d_c_0_b_1_b_0    = examples.example[2].d.c[0].b[1].b[0];\n"
            "     ivec3   examples_example_2_d_c_0_b_1_b_1    = examples.example[2].d.c[0].b[1].b[1];\n"
            "     ivec3   examples_example_2_d_c_0_b_1_b_2    = examples.example[2].d.c[0].b[1].b[2];\n"
            "     int     examples_example_2_d_c_0_b_1_c      = examples.example[2].d.c[0].b[1].c;\n"
            "     float   examples_example_2_d_c_0_c          = examples.example[2].d.c[0].c;\n"
            "     bvec2   examples_example_2_d_c_1_a          = examples.example[2].d.c[1].a;\n"
            "     float   examples_example_2_d_c_1_b_0_a      = examples.example[2].d.c[1].b[0].a;\n"
            "     ivec3   examples_example_2_d_c_1_b_0_b_0    = examples.example[2].d.c[1].b[0].b[0];\n"
            "     ivec3   examples_example_2_d_c_1_b_0_b_1    = examples.example[2].d.c[1].b[0].b[1];\n"
            "     ivec3   examples_example_2_d_c_1_b_0_b_2    = examples.example[2].d.c[1].b[0].b[2];\n"
            "     int     examples_example_2_d_c_1_b_0_c      = examples.example[2].d.c[1].b[0].c;\n"
            "     float   examples_example_2_d_c_1_b_1_a      = examples.example[2].d.c[1].b[1].a;\n"
            "     ivec3   examples_example_2_d_c_1_b_1_b_0    = examples.example[2].d.c[1].b[1].b[0];\n"
            "     ivec3   examples_example_2_d_c_1_b_1_b_1    = examples.example[2].d.c[1].b[1].b[1];\n"
            "     ivec3   examples_example_2_d_c_1_b_1_b_2    = examples.example[2].d.c[1].b[1].b[2];\n"
            "     int     examples_example_2_d_c_1_b_1_c      = examples.example[2].d.c[1].b[1].c;\n"
            "     float   examples_example_2_d_c_1_c          = examples.example[2].d.c[1].c;\n"
            "     float   examples_example_2_e                = examples.example[2].e;\n"
            "     float   examples_example_2_f_0              = examples.example[2].f[0];\n"
            "     float   examples_example_2_f_1              = examples.example[2].f[1];\n"
            "     mat2x3  examples_example_2_g                = examples.example[2].g;\n"
            "     uvec3   examples_example_2_h_0_a            = examples.example[2].h[0].a;\n"
            "     vec2    examples_example_2_h_0_b            = examples.example[2].h[0].b;\n"
            "     float   examples_example_2_h_0_c_0          = examples.example[2].h[0].c[0];\n"
            "     float   examples_example_2_h_0_c_1          = examples.example[2].h[0].c[1];\n"
            "     vec2    examples_example_2_h_0_d            = examples.example[2].h[0].d;\n"
            "     mat3    examples_example_2_h_0_e_0          = examples.example[2].h[0].e[0];\n"
            "     mat3    examples_example_2_h_0_e_1          = examples.example[2].h[0].e[1];\n"
            "     uvec3   examples_example_2_h_1_a            = examples.example[2].h[1].a;\n"
            "     vec2    examples_example_2_h_1_b            = examples.example[2].h[1].b;\n"
            "     float   examples_example_2_h_1_c_0          = examples.example[2].h[1].c[0];\n"
            "     float   examples_example_2_h_1_c_1          = examples.example[2].h[1].c[1];\n"
            "     vec2    examples_example_2_h_1_d            = examples.example[2].h[1].d;\n"
            "     mat3    examples_example_2_h_1_e_0          = examples.example[2].h[1].e[0];\n"
            "     mat3    examples_example_2_h_1_e_1          = examples.example[2].h[1].e[1];\n"
#ifdef HAS_FP64_EXTENSION
            "     double  examples_example_2_i                = examples.example[2].i;\n"
#endif
            "     bool    examples_example_2_j                = examples.example[2].j;\n"
#ifdef HAS_FP64_EXTENSION
            "     dvec2   examples_example_2_k_a              = examples.example[2].k.a;\n"
#endif
            "     int     examples_example_2_k_b              = examples.example[2].k.b;\n"
            "     float   examples_example_2_k_c_0_a          = examples.example[2].k.c[0].a;\n"
            "     ivec3   examples_example_2_k_c_0_b_0        = examples.example[2].k.c[0].b[0];\n"
            "     ivec3   examples_example_2_k_c_0_b_1        = examples.example[2].k.c[0].b[1];\n"
            "     ivec3   examples_example_2_k_c_0_b_2        = examples.example[2].k.c[0].b[2];\n"
            "     int     examples_example_2_k_c_0_c          = examples.example[2].k.c[0].c;\n"
            "     float   examples_example_2_k_c_1_a          = examples.example[2].k.c[1].a;\n"
            "     ivec3   examples_example_2_k_c_1_b_0        = examples.example[2].k.c[1].b[0];\n"
            "     ivec3   examples_example_2_k_c_1_b_1        = examples.example[2].k.c[1].b[1];\n"
            "     ivec3   examples_example_2_k_c_1_b_2        = examples.example[2].k.c[1].b[2];\n"
            "     int     examples_example_2_k_c_1_c          = examples.example[2].k.c[1].c;\n"
            "     float   examples_example_2_k_c_2_a          = examples.example[2].k.c[2].a;\n"
            "     ivec3   examples_example_2_k_c_2_b_0        = examples.example[2].k.c[2].b[0];\n"
            "     ivec3   examples_example_2_k_c_2_b_1        = examples.example[2].k.c[2].b[1];\n"
            "     ivec3   examples_example_2_k_c_2_b_2        = examples.example[2].k.c[2].b[2];\n"
            "     int     examples_example_2_k_c_2_c          = examples.example[2].k.c[2].c;\n"
            "     float   examples_example_2_k_c_3_a          = examples.example[2].k.c[3].a;\n"
            "     ivec3   examples_example_2_k_c_3_b_0        = examples.example[2].k.c[3].b[0];\n"
            "     ivec3   examples_example_2_k_c_3_b_1        = examples.example[2].k.c[3].b[1];\n"
            "     ivec3   examples_example_2_k_c_3_b_2        = examples.example[2].k.c[3].b[2];\n"
            "     int     examples_example_2_k_c_3_c          = examples.example[2].k.c[3].c;\n"
            "\n"
            "\n"
            "     if (examples_example_0_a              != 1234.56)                         color = error;\n"
            "     if (examples_example_0_b              != vec2(1.4, 8.6))                  color = error;\n"
            "     if (examples_example_0_c              != vec3(0.1, 0.2, 0.3))             color = error;\n"
            "     if (examples_example_0_d_a            != 8123.45)                         color = error;\n"
            "     if (examples_example_0_d_b            != bvec2(true, false))              color = error;\n"
            "     if (examples_example_0_d_c_0_a        != bvec2(true, true))               color = error;\n"
            "     if (examples_example_0_d_c_0_b_0_a    != 7812.34)                         color = error;\n"
            "     if (examples_example_0_d_c_0_b_0_b_0  != ivec3(0,-1,2))                   color = error;\n"
            "     if (examples_example_0_d_c_0_b_0_b_1  != ivec3(1,-2,3))                   color = error;\n"
            "     if (examples_example_0_d_c_0_b_0_b_2  != ivec3(4,-5,6))                   color = error;\n"
            "     if (examples_example_0_d_c_0_b_0_c    != 6781)                            color = error;\n"
            "     if (examples_example_0_d_c_0_b_1_a    != 5678.12)                         color = error;\n"
            "     if (examples_example_0_d_c_0_b_1_b_0  != ivec3(-7,8,9))                   color = error;\n"
            "     if (examples_example_0_d_c_0_b_1_b_1  != ivec3(-10,11,12))                color = error;\n"
            "     if (examples_example_0_d_c_0_b_1_b_2  != ivec3(-13,14,15))                color = error;\n"
            "     if (examples_example_0_d_c_0_b_1_c    != 4567)                            color = error;\n"
            "     if (examples_example_0_d_c_0_c        != 3456.78)                         color = error;\n"
            "     if (examples_example_0_d_c_1_a        != bvec2(false, true))              color = error;\n"
            "     if (examples_example_0_d_c_1_b_0_a    != 2345.67)                         color = error;\n"
            "     if (examples_example_0_d_c_1_b_0_b_0  != ivec3(16,17,-18))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_0_b_1  != ivec3(19,20,-21))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_0_b_2  != ivec3(22,23,-24))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_0_c    != 123)                             color = error;\n"
            "     if (examples_example_0_d_c_1_b_1_a    != 812.34)                          color = error;\n"
            "     if (examples_example_0_d_c_1_b_1_b_0  != ivec3(25,-26,27))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_1_b_1  != ivec3(28,-29,30))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_1_b_2  != ivec3(31,-32,33))                color = error;\n"
            "     if (examples_example_0_d_c_1_b_1_c    != 781)                             color = error;\n"
            "     if (examples_example_0_d_c_1_c        != 678.12)                          color = error;\n"
            "     if (examples_example_0_e              != 567.81)                          color = error;\n"
            "     if (examples_example_0_f_0            != 456.78)                          color = error;\n"
            "     if (examples_example_0_f_1            != 345.67)                          color = error;\n"
            "     if (examples_example_0_g[0][0]        != 11.1)                            color = error;\n"
            "     if (examples_example_0_g[0][1]        != 21.1)                            color = error;\n"
            "     if (examples_example_0_g[0][2]        != 31.1)                            color = error;\n"
            "     if (examples_example_0_g[1][0]        != 12.2)                            color = error;\n"
            "     if (examples_example_0_g[1][1]        != 22.2)                            color = error;\n"
            "     if (examples_example_0_g[1][2]        != 32.2)                            color = error;\n"
            "     if (examples_example_0_h_0_a          != uvec3(91,82,73))                 color = error;\n"
            "     if (examples_example_0_h_0_b          != vec2(2.5, 9.7))                  color = error;\n"
            "     if (examples_example_0_h_0_c_0        != 234.56)                          color = error;\n"
            "     if (examples_example_0_h_0_c_1        != 12.34)                           color = error;\n"
            "     if (examples_example_0_h_0_d          != vec2(3.6, 1.3))                  color = error;\n"
            "     if (examples_example_0_h_0_e_0[0][0]  != 1.1)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[0][1]  != 2.1)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[0][2]  != 3.1)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[1][0]  != 1.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[1][1]  != 2.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[1][2]  != 3.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[2][0]  != 1.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[2][1]  != 2.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_0[2][2]  != 3.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[0][0]  != 1.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[0][1]  !=-2.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[0][2]  != 3.2)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[1][0]  != 1.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[1][1]  !=-2.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[1][2]  != 3.3)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[2][0]  != 1.4)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[2][1]  !=-2.4)                             color = error;\n"
            "     if (examples_example_0_h_0_e_1[2][2]  != 3.4)                             color = error;\n"
            "     if (examples_example_0_h_1_a          != uvec3(71,82,93))                 color = error;\n"
            "     if (examples_example_0_h_1_b          != vec2(4.5, 2.4))                  color = error;\n"
            "     if (examples_example_0_h_1_c_0        != 81.23)                           color = error;\n"
            "     if (examples_example_0_h_1_c_1        != 78.12)                           color = error;\n"
            "     if (examples_example_0_h_1_d          != vec2(5.7, 3.5))                  color = error;\n"
            "     if (examples_example_0_h_1_e_0[0][0]  != 1.3)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[0][1]  != 2.3)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[0][2]  !=-3.3)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[1][0]  != 1.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[1][1]  != 2.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[1][2]  !=-3.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[2][0]  != 1.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[2][1]  != 2.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_0[2][2]  !=-3.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[0][0]  != 1.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[0][1]  != 2.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[0][2]  != 3.4)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[1][0]  != 1.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[1][1]  != 2.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[1][2]  != 3.5)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[2][0]  != 1.6)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[2][1]  != 2.6)                             color = error;\n"
            "     if (examples_example_0_h_1_e_1[2][2]  != 3.6)                             color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_0_i              != 94.345678LF)                     color = error;\n"
//#endif
            "     if (examples_example_0_j              != true)                            color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_0_k_a            != dvec2(12.874LF, -2346.985633LF)) color = error;\n"
//#endif
            "     if (examples_example_0_k_b            != 3)                               color = error;\n"
            "     if (examples_example_0_k_c_0_a        != 67.81)                           color = error;\n"
            "     if (examples_example_0_k_c_0_b_0      != ivec3(34,35,-36))                color = error;\n"
            "     if (examples_example_0_k_c_0_b_1      != ivec3(37,38,-39))                color = error;\n"
            "     if (examples_example_0_k_c_0_b_2      != ivec3(40,41,-42))                color = error;\n"
            "     if (examples_example_0_k_c_0_c        != -4)                              color = error;\n"
            "     if (examples_example_0_k_c_1_a        != 56.78)                           color = error;\n"
            "     if (examples_example_0_k_c_1_b_0      != ivec3(-43,44,45))                color = error;\n"
            "     if (examples_example_0_k_c_1_b_1      != ivec3(-46,47,48))                color = error;\n"
            "     if (examples_example_0_k_c_1_b_2      != ivec3(-49,50,51))                color = error;\n"
            "     if (examples_example_0_k_c_1_c        != -5)                              color = error;\n"
            "     if (examples_example_0_k_c_2_a        != 45.67)                           color = error;\n"
            "     if (examples_example_0_k_c_2_b_0      != ivec3(52,-53,54))                color = error;\n"
            "     if (examples_example_0_k_c_2_b_1      != ivec3(55,-56,57))                color = error;\n"
            "     if (examples_example_0_k_c_2_b_2      != ivec3(58,-59,60))                color = error;\n"
            "     if (examples_example_0_k_c_2_c        != -6)                              color = error;\n"
            "     if (examples_example_0_k_c_3_a        != 34.56)                           color = error;\n"
            "     if (examples_example_0_k_c_3_b_0      != ivec3(61,62,-63))                color = error;\n"
            "     if (examples_example_0_k_c_3_b_1      != ivec3(64,-65,66))                color = error;\n"
            "     if (examples_example_0_k_c_3_b_2      != ivec3(-67,68,69))                color = error;\n"
            "     if (examples_example_0_k_c_3_c        != 7)                               color = error;\n"
            "     if (examples_example_1_a              != 91234.56)                        color = error;\n"
            "     if (examples_example_1_b              != vec2(91.4, 98.6))                color = error;\n"
            "     if (examples_example_1_c              != vec3(90.1, 90.2, 90.3))          color = error;\n"
            "     if (examples_example_1_d_a            != 98123.45)                        color = error;\n"
            "     if (examples_example_1_d_b            != bvec2(false, false))             color = error;\n"
            "     if (examples_example_1_d_c_0_a        != bvec2(true, false))              color = error;\n"
            "     if (examples_example_1_d_c_0_b_0_a    != 97812.34)                        color = error;\n"
            "     if (examples_example_1_d_c_0_b_0_b_0  != ivec3(90,-91,92))                color = error;\n"
            "     if (examples_example_1_d_c_0_b_0_b_1  != ivec3(91,-92,93))                color = error;\n"
            "     if (examples_example_1_d_c_0_b_0_b_2  != ivec3(94,-95,96))                color = error;\n"
            "     if (examples_example_1_d_c_0_b_0_c    != 6781)                            color = error;\n"
            "     if (examples_example_1_d_c_0_b_1_a    != 5678.12)                         color = error;\n"
            "     if (examples_example_1_d_c_0_b_1_b_0  != ivec3(-97,98,99))                color = error;\n"
            "     if (examples_example_1_d_c_0_b_1_b_1  != ivec3(-910,911,912))             color = error;\n"
            "     if (examples_example_1_d_c_0_b_1_b_2  != ivec3(-913,914,915))             color = error;\n"
            "     if (examples_example_1_d_c_0_b_1_c    != 94567)                           color = error;\n"
            "     if (examples_example_1_d_c_0_c        != 93456.78)                        color = error;\n"
            "     if (examples_example_1_d_c_1_a        != bvec2(false, true))              color = error;\n"
            "     if (examples_example_1_d_c_1_b_0_a    != 92345.67)                        color = error;\n"
            "     if (examples_example_1_d_c_1_b_0_b_0  != ivec3(916,917,-918))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_0_b_1  != ivec3(919,920,-921))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_0_b_2  != ivec3(922,923,-924))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_0_c    != 9123)                            color = error;\n"
            "     if (examples_example_1_d_c_1_b_1_a    != 9812.34)                         color = error;\n"
            "     if (examples_example_1_d_c_1_b_1_b_0  != ivec3(925,-926,927))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_1_b_1  != ivec3(928,-929,930))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_1_b_2  != ivec3(931,-932,933))             color = error;\n"
            "     if (examples_example_1_d_c_1_b_1_c    != 9781)                            color = error;\n"
            "     if (examples_example_1_d_c_1_c        != 9678.12)                         color = error;\n"
            "     if (examples_example_1_e              != 9567.81)                         color = error;\n"
            "     if (examples_example_1_f_0            != 9456.78)                         color = error;\n"
            "     if (examples_example_1_f_1            != 9345.67)                         color = error;\n"
            "     if (examples_example_1_g[0][0]        != 911.1)                           color = error;\n"
            "     if (examples_example_1_g[0][1]        != 921.1)                           color = error;\n"
            "     if (examples_example_1_g[0][2]        != 931.1)                           color = error;\n"
            "     if (examples_example_1_g[1][0]        != 912.2)                           color = error;\n"
            "     if (examples_example_1_g[1][1]        != 922.2)                           color = error;\n"
            "     if (examples_example_1_g[1][2]        != 932.2)                           color = error;\n"
            "     if (examples_example_1_h_0_a          != uvec3(991,982,973))              color = error;\n"
            "     if (examples_example_1_h_0_b          != vec2(92.5, 99.7))                color = error;\n"
            "     if (examples_example_1_h_0_c_0        != 9234.56)                         color = error;\n"
            "     if (examples_example_1_h_0_c_1        != 912.34)                          color = error;\n"
            "     if (examples_example_1_h_0_d          != vec2(93.6, 91.3))                color = error;\n"
            "     if (examples_example_1_h_0_e_0[0][0]  != 91.1)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[0][1]  != 92.1)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[0][2]  != 93.1)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[1][0]  != 91.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[1][1]  != 92.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[1][2]  != 93.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[2][0]  != 91.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[2][1]  != 92.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_0[2][2]  != 93.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[0][0]  != 91.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[0][1]  !=-92.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[0][2]  != 93.2)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[1][0]  != 91.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[1][1]  !=-92.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[1][2]  != 93.3)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[2][0]  != 91.4)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[2][1]  !=-92.4)                            color = error;\n"
            "     if (examples_example_1_h_0_e_1[2][2]  != 93.4)                            color = error;\n"
            "     if (examples_example_1_h_1_a          != uvec3(971,982,93))               color = error;\n"
            "     if (examples_example_1_h_1_b          != vec2(94.5, 92.4))                color = error;\n"
            "     if (examples_example_1_h_1_c_0        != 981.23)                          color = error;\n"
            "     if (examples_example_1_h_1_c_1        != 978.12)                          color = error;\n"
            "     if (examples_example_1_h_1_d          != vec2(95.7, 93.5))                color = error;\n"
            "     if (examples_example_1_h_1_e_0[0][0]  != 91.3)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[0][1]  != 92.3)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[0][2]  !=-93.3)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[1][0]  != 91.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[1][1]  != 92.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[1][2]  !=-93.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[2][0]  != 91.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[2][1]  != 92.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_0[2][2]  !=-93.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[0][0]  != 91.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[0][1]  != 92.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[0][2]  != 93.4)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[1][0]  != 91.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[1][1]  != 92.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[1][2]  != 93.5)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[2][0]  != 91.6)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[2][1]  != 92.6)                            color = error;\n"
            "     if (examples_example_1_h_1_e_1[2][2]  != 93.6)                            color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_1_i              != 994.345678LF)                    color = error;\n"
//#endif
            "     if (examples_example_1_j              != false)                           color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_1_k_a            != dvec2(912.874LF,-92346.985633LF))color = error;\n"
//#endif
            "     if (examples_example_1_k_b            != 93)                              color = error;\n"
            "     if (examples_example_1_k_c_0_a        != 967.81)                          color = error;\n"
            "     if (examples_example_1_k_c_0_b_0      != ivec3(934,935,-936))             color = error;\n"
            "     if (examples_example_1_k_c_0_b_1      != ivec3(937,938,-939))             color = error;\n"
            "     if (examples_example_1_k_c_0_b_2      != ivec3(940,941,-942))             color = error;\n"
            "     if (examples_example_1_k_c_0_c        != -94)                             color = error;\n"
            "     if (examples_example_1_k_c_1_a        != 956.78)                          color = error;\n"
            "     if (examples_example_1_k_c_1_b_0      != ivec3(-943,944,945))             color = error;\n"
            "     if (examples_example_1_k_c_1_b_1      != ivec3(-946,947,948))             color = error;\n"
            "     if (examples_example_1_k_c_1_b_2      != ivec3(-949,950,951))             color = error;\n"
            "     if (examples_example_1_k_c_1_c        != -95)                             color = error;\n"
            "     if (examples_example_1_k_c_2_a        != 945.67)                          color = error;\n"
            "     if (examples_example_1_k_c_2_b_0      != ivec3(952,-953,954))             color = error;\n"
            "     if (examples_example_1_k_c_2_b_1      != ivec3(955,-956,957))             color = error;\n"
            "     if (examples_example_1_k_c_2_b_2      != ivec3(958,-959,960))             color = error;\n"
            "     if (examples_example_1_k_c_2_c        != -96)                             color = error;\n"
            "     if (examples_example_1_k_c_3_a        != 934.56)                          color = error;\n"
            "     if (examples_example_1_k_c_3_b_0      != ivec3(961,962,-963))             color = error;\n"
            "     if (examples_example_1_k_c_3_b_1      != ivec3(964,-965,966))             color = error;\n"
            "     if (examples_example_1_k_c_3_b_2      != ivec3(-967,968,969))             color = error;\n"
            "     if (examples_example_1_k_c_3_c        != 97)                              color = error;\n"
            "     if (examples_example_2_a              != 71234.56)                        color = error;\n"
            "     if (examples_example_2_b              != vec2(71.4, 78.6))                color = error;\n"
            "     if (examples_example_2_c              != vec3(70.1, 70.2, 70.3))          color = error;\n"
            "     if (examples_example_2_d_a            != 78123.45)                        color = error;\n"
            "     if (examples_example_2_d_b            != bvec2(true, true))               color = error;\n"
            "     if (examples_example_2_d_c_0_a        != bvec2(true, false))              color = error;\n"
            "     if (examples_example_2_d_c_0_b_0_a    != 77812.34)                        color = error;\n"
            "     if (examples_example_2_d_c_0_b_0_b_0  != ivec3(70,-71,72))                color = error;\n"
            "     if (examples_example_2_d_c_0_b_0_b_1  != ivec3(71,-72,73))                color = error;\n"
            "     if (examples_example_2_d_c_0_b_0_b_2  != ivec3(74,-75,76))                color = error;\n"
            "     if (examples_example_2_d_c_0_b_0_c    != 76781)                           color = error;\n"
            "     if (examples_example_2_d_c_0_b_1_a    != 75678.12)                        color = error;\n"
            "     if (examples_example_2_d_c_0_b_1_b_0  != ivec3(-77,78,79))                color = error;\n"
            "     if (examples_example_2_d_c_0_b_1_b_1  != ivec3(-710,711,712))             color = error;\n"
            "     if (examples_example_2_d_c_0_b_1_b_2  != ivec3(-713,714,715))             color = error;\n"
            "     if (examples_example_2_d_c_0_b_1_c    != 74567)                           color = error;\n"
            "     if (examples_example_2_d_c_0_c        != 73456.78)                        color = error;\n"
            "     if (examples_example_2_d_c_1_a        != bvec2(true, true))               color = error;\n"
            "     if (examples_example_2_d_c_1_b_0_a    != 72345.67)                        color = error;\n"
            "     if (examples_example_2_d_c_1_b_0_b_0  != ivec3(716,717,-718))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_0_b_1  != ivec3(719,720,-721))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_0_b_2  != ivec3(722,723,-724))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_0_c    != 7123)                            color = error;\n"
            "     if (examples_example_2_d_c_1_b_1_a    != 7812.34)                         color = error;\n"
            "     if (examples_example_2_d_c_1_b_1_b_0  != ivec3(725,-726,727))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_1_b_1  != ivec3(728,-729,730))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_1_b_2  != ivec3(731,-732,733))             color = error;\n"
            "     if (examples_example_2_d_c_1_b_1_c    != 7781)                            color = error;\n"
            "     if (examples_example_2_d_c_1_c        != 7678.12)                         color = error;\n"
            "     if (examples_example_2_e              != 7567.81)                         color = error;\n"
            "     if (examples_example_2_f_0            != 7456.78)                         color = error;\n"
            "     if (examples_example_2_f_1            != 7345.67)                         color = error;\n"
            "     if (examples_example_2_g[0][0]        != 711.1)                           color = error;\n"
            "     if (examples_example_2_g[0][1]        != 721.1)                           color = error;\n"
            "     if (examples_example_2_g[0][2]        != 731.1)                           color = error;\n"
            "     if (examples_example_2_g[1][0]        != 712.2)                           color = error;\n"
            "     if (examples_example_2_g[1][1]        != 722.2)                           color = error;\n"
            "     if (examples_example_2_g[1][2]        != 732.2)                           color = error;\n"
            "     if (examples_example_2_h_0_a          != uvec3(791,782,73))               color = error;\n"
            "     if (examples_example_2_h_0_b          != vec2(72.5, 79.7))                color = error;\n"
            "     if (examples_example_2_h_0_c_0        != 7234.56)                         color = error;\n"
            "     if (examples_example_2_h_0_c_1        != 712.34)                          color = error;\n"
            "     if (examples_example_2_h_0_d          != vec2(73.6, 71.3))                color = error;\n"
            "     if (examples_example_2_h_0_e_0[0][0]  != 71.1)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[0][1]  != 72.1)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[0][2]  != 73.1)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[1][0]  != 71.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[1][1]  != 72.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[1][2]  != 73.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[2][0]  != 71.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[2][1]  != 72.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_0[2][2]  != 73.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[0][0]  != 71.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[0][1]  !=-72.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[0][2]  != 73.2)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[1][0]  != 71.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[1][1]  !=-72.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[1][2]  != 73.3)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[2][0]  != 71.4)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[2][1]  !=-72.4)                            color = error;\n"
            "     if (examples_example_2_h_0_e_1[2][2]  != 73.4)                            color = error;\n"
            "     if (examples_example_2_h_1_a          != uvec3(771,782,793))              color = error;\n"
            "     if (examples_example_2_h_1_b          != vec2(74.5, 72.4))                color = error;\n"
            "     if (examples_example_2_h_1_c_0        != 781.23)                          color = error;\n"
            "     if (examples_example_2_h_1_c_1        != 778.12)                          color = error;\n"
            "     if (examples_example_2_h_1_d          != vec2(75.7, 73.5))                color = error;\n"
            "     if (examples_example_2_h_1_e_0[0][0]  != 71.3)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[0][1]  != 72.3)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[0][2]  !=-73.3)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[1][0]  != 71.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[1][1]  != 72.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[1][2]  !=-73.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[2][0]  != 71.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[2][1]  != 72.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_0[2][2]  !=-73.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[0][0]  != 71.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[0][1]  != 72.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[0][2]  != 73.4)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[1][0]  != 71.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[1][1]  != 72.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[1][2]  != 73.5)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[2][0]  != 71.6)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[2][1]  != 72.6)                            color = error;\n"
            "     if (examples_example_2_h_1_e_1[2][2]  != 73.6)                            color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_2_i              != 794.345678LF)                    color = error;\n"
//#endif
            "     if (examples_example_2_j              != true)                            color = error;\n"
//#ifdef HAS_FP64_EXTENSION
            "     if (examples_example_2_k_a            != dvec2(712.874LF,-72346.985633LF))color = error;\n"
//#endif
            "     if (examples_example_2_k_b            != 73)                              color = error;\n"
            "     if (examples_example_2_k_c_0_a        != 767.81)                          color = error;\n"
            "     if (examples_example_2_k_c_0_b_0      != ivec3(734,735,-736))             color = error;\n"
            "     if (examples_example_2_k_c_0_b_1      != ivec3(737,738,-739))             color = error;\n"
            "     if (examples_example_2_k_c_0_b_2      != ivec3(740,741,-742))             color = error;\n"
            "     if (examples_example_2_k_c_0_c        != -74)                             color = error;\n"
            "     if (examples_example_2_k_c_1_a        != 756.78)                          color = error;\n"
            "     if (examples_example_2_k_c_1_b_0      != ivec3(-743,744,745))             color = error;\n"
            "     if (examples_example_2_k_c_1_b_1      != ivec3(-746,747,748))             color = error;\n"
            "     if (examples_example_2_k_c_1_b_2      != ivec3(-749,750,751))             color = error;\n"
            "     if (examples_example_2_k_c_1_c        != -75)                             color = error;\n"
            "     if (examples_example_2_k_c_2_a        != 745.67)                          color = error;\n"
            "     if (examples_example_2_k_c_2_b_0      != ivec3(752,-753,754))             color = error;\n"
            "     if (examples_example_2_k_c_2_b_1      != ivec3(755,-756,757))             color = error;\n"
            "     if (examples_example_2_k_c_2_b_2      != ivec3(758,-759,760))             color = error;\n"
            "     if (examples_example_2_k_c_2_c        != -76)                             color = error;\n"
            "     if (examples_example_2_k_c_3_a        != 734.56)                          color = error;\n"
            "     if (examples_example_2_k_c_3_b_0      != ivec3(761,762,-763))             color = error;\n"
            "     if (examples_example_2_k_c_3_b_1      != ivec3(764,-765,766))             color = error;\n"
            "     if (examples_example_2_k_c_3_b_2      != ivec3(-767,768,769))             color = error;\n"
            "     if (examples_example_2_k_c_3_c        != 7)                               color = error;\n"
            "\n"
            "\n"
            "    vFragColor = color;\n"
            "}\n"
            "\n"
            ;

    return fp_program;
}
