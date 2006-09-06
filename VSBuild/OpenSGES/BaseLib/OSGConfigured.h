/* Builds/i686-pc-cygwin-cl.net2003/Base/OSGConfigured.h.  Generated automatically by configure.  */
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
 *                                                                           *
 *   contact: reiners@igd.fhg.de, gerrit.voss@vossg.org, jbehr@zgdv.de       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGCONFIGURED_H_
#define _OSGCONFIGURED_H_

#if defined (OSG_USE_WINTHREADS)
#define OSG_ASPECT_USE_LOCALSTORAGE 1
/* #undef OSG_ASPECT_USE_DECLSPEC */
#endif

#if defined(OSG_WIN_TYPES)
/* #undef OSG_BOOL_IS_UNSIGNED */
#endif

#define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#define OSG_DEFAULT_LOG_TYPE LOG_STDERR 

#ifndef OSG_DEFAULT_LOG_LEVEL
#    define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#endif

#ifndef OSG_DEFAULT_LOG_TYPE
#    define OSG_DEFAULT_LOG_TYPE LOG_STDERR 
#endif

#define OSG_DISABLE_DEPRECATED 1

#if defined(OSG_DEBUG)
/* #undef OSG_DEBUG_FCPTR */
/* #undef OSG_DEBUG_NO_FCPTR_ARITHM */
#endif

#define OSG_OPT_DRAWTREE 1
/* #undef OSG_PTHREAD_ELF_TLS */

/* #undef OSG_NO_GLUT_GLSUBDIR */

#if defined(WIN32) && ! defined(__ICL)
#pragma warning( disable : 4786 4661 4305 )
#endif

/* #undef OSG_SGI_USE_PTHREAD */
#define OSG_SGI_USE_SPROC 1

#if defined(__sgi)
#   if defined(OSG_SGI_USE_PTHREAD)
#       define OSG_USE_PTHREADS
#       define OSG_ASPECT_USE_PTHREADKEY
/* #       undef  OSG_USE_SPROC */
#   else
#       define OSG_USE_SPROC
#   endif
#endif

/* #undef OSG_USE_MPATROL */

#if defined(OSG_USE_MPATROL)
#define MP_NONEWDELETE 1
#include <mpatrol.h>
#endif

/* #undef OSG_ICC_GNU_COMPAT */

#define OSG_OLD_RENDER_ACTION 1

#define OSG_CLEANED_RENDERACTION 1

#define OSG_1_COMPAT 1
#define OSG_DEPRECIATED_PROPS 1
#define OSG_DISABLE_DEPRECIATED 1

#endif


