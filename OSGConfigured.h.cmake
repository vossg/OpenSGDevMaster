#ifndef _OSGCONFIGURED_H_
#define _OSGCONFIGURED_H_

#cmakedefine OSG_USE_OSG2_NAMESPACE 1

/* Disable interface that will go away in the future */
#cmakedefine OSG_DISABLE_DEPRECATED 1

#cmakedefine OSG_SIMD_SSE 1

#cmakedefine OSG_SIMD_ALTIVEC 1

#cmakedefine OSG_ENABLE_VALGRIND_CHECKS 1

#cmakedefine OSG_NEW_OSB_IO 1

/* #define OSG_ELDK 0 */

#cmakedefine OSG_GL_DEFMAPPER 1

#cmakedefine OSG_WITH_GLUT 1

#cmakedefine OSG_ENABLE_MEMORY_DEBUGGING 1

#cmakedefine OSG_ENABLE_DOUBLE_MATRIX_STACK 1

#cmakedefine OSG_WITH_GDAL 1

/* Do not use GL subdir for glut */
/* #define OSG_NO_GLUT_GLSUBDIR 0 */

#cmakedefine OSG_WITH_PNG 1

#cmakedefine OSG_WITH_JPG 1

#cmakedefine OSG_MULTISHADER_VARCHUNK 1

#cmakedefine OSG_OGL_COREONLY 1

#cmakedefine OSG_OGL_ES2 1

#cmakedefine OSG_OGL_ES2_SIMGL3 1

#ifndef GL_GLEXT_PROTOTYPES
#cmakedefine GL_GLEXT_PROTOTYPES 1
#endif

#cmakedefine GL3_PROTOTYPES 1

#cmakedefine OSG_USE_OGL3_PROTOS 1

#cmakedefine OSG_USE_OGL4_PROTOS 1

#cmakedefine OSG_USE_OGLES_PROTOS 1

#if !defined(OSG_GL_INCLUDE_GLEW)
#cmakedefine OSG_GL_INCLUDE_GLEW 1
#endif

#cmakedefine OSG_OGL_NO_DOUBLE 1

#cmakedefine OSG_WITH_ZLIB 1

#cmakedefine OSG_WITH_TIF 1

#cmakedefine OSG_WITH_IMF 1

#cmakedefine OSG_WITH_FONTCONFIG 1

#define OSG_MT_CPTR_ASPECT 1

#cmakedefine OSG_1_COMPAT 1

#cmakedefine OSG_WITH_NVPERFSDK 1 

#cmakedefine OSG_WITH_VTK 1

#cmakedefine OSG_WITH_CUDA 1

#cmakedefine OSG_WITH_OPENCL 1

/* #define OSG_ICC_GNU_COMPAT 0 */

#cmakedefine OSG_SHC_MODE_0  1
#cmakedefine OSG_SHC_MODE_1  1
#cmakedefine OSG_SHC_MODE_2  1
#cmakedefine OSG_SHC_MODE_3  1
#cmakedefine OSG_SHC_MODE_4  1
#cmakedefine OSG_SHC_MODE_5  1
#cmakedefine OSG_SHC_MODE_6  1
#cmakedefine OSG_SHC_MODE_7  1
#cmakedefine OSG_SHC_MODE_8  1
#cmakedefine OSG_SHC_MODE_9  1
#cmakedefine OSG_SHC_MODE_10 1


#ifdef OSG_USE_OSG2_NAMESPACE
namespace OSG2 
{
#else
namespace OSG 
{
#endif
  static const unsigned int RenderPropertyBits = @OSG_RENDERPROPERTY_BITS@;
  static const unsigned int RenderPropertyUniqueBits = @OSG_RENDERPROPERTY_UNIQUE_BITS@;
}

#define OSG_WITH_GIF 1

#cmakedefine OSG_PREBUILD_SCANPARSE 1

#cmakedefine OSG_WITH_COLLADA 1

#cmakedefine OSG_WITH_COLLADA_NAMESPACE 1

#cmakedefine COLLADA_DOM_SUPPORT141 1

#cmakedefine OSG_WITH_FT2 1

/* Use elf tls with pthreads. */
#cmakedefine OSG_PTHREAD_ELF_TLS 1
#cmakedefine OSG_WIN32_ASPECT_USE_LOCALSTORAGE 1
#cmakedefine OSG_ENABLE_AUTOINIT_THREADS 1

#cmakedefine OSG_DEPRECATED_PROPS 1

#cmakedefine OSG_WITH_QT 1

#cmakedefine OSG_WITH_QT5 1

#cmakedefine OSG_ENABLE_DEFAULT_READONLY_CHANGELIST 1

#cmakedefine OSG_DISABLE_MICROSOFT_SECURE_CXXX 1

#cmakedefine OSG_DISABLE_MS_ITERATOR_DEBUGGING 1

#cmakedefine OSG_ENABLE_CSM_WIN7_FEATURES 1
