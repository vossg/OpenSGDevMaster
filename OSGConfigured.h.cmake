#ifndef _OSGCONFIGURED_H_
#define _OSGCONFIGURED_H_

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

#cmakedefine OSG_WITH_GDAL 

/* Do not use GL subdir for glut */
/* #define OSG_NO_GLUT_GLSUBDIR 0 */

#cmakedefine OSG_WITH_PNG 

#cmakedefine OSG_WITH_JPG 

#cmakedefine OSG_OGL2_SHADERFUNCS 1

#cmakedefine OSG_WITH_ZLIB 

#cmakedefine OSG_WITH_TIF 

#cmakedefine OSG_WITH_FONTCONFIG 

#cmakedefine OSG_NEW_SHADER 1

#define OSG_MT_CPTR_ASPECT 1

#cmakedefine OSG_1_COMPAT 1

/* #define OSG_WITH_NVPERFSDK 0 */

#cmakedefine OSG_WITH_VTK 1

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

#define OSG_WITH_GIF 1

#cmakedefine OSG_PREBUILD_SCANPARSE 1

#cmakedefine OSG_WITH_COLLADA 1

#cmakedefine OSG_WITH_FT2 1

/* Use elf tls with pthreads. */
#cmakedefine OSG_PTHREAD_ELF_TLS 1
#cmakedefine OSG_WIN32_ASPECT_USE_LOCALSTORAGE 1

#cmakedefine OSG_DEPRECATED_PROPS 1

#endif
