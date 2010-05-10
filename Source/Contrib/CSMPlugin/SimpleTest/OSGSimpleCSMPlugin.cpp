/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
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

#include "OSGSimpleCSMPlugin.h"

#include "OSGComplexSceneManager.h"
#include "OSGOSGSceneFileType.h"

#include "OSGBaseInitFunctions.h"
#include "OSGGLU.h"

OSG_BEGIN_NAMESPACE

void dumpGLError(GLenum glError, const GLubyte *glErrorString)
{
    fprintf(stderr, "Custom error dump\n");
    fprintf(stderr, "-----------------\n");

    switch(glError)
    {
        case GL_STACK_OVERFLOW:
        case GL_STACK_UNDERFLOW:
        {
            GLint iMatMode;
            GLint iMoViMatInfo[2];
            GLint iProjMatInfo[2];
            GLint iTexMatInfo [2];

            glGetIntegerv(GL_MATRIX_MODE,               &iMatMode);

            glGetIntegerv(GL_MODELVIEW_STACK_DEPTH,     &(iMoViMatInfo[0]));
            glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &(iMoViMatInfo[1]));

            glGetIntegerv(GL_PROJECTION_STACK_DEPTH,     &(iProjMatInfo[0]));
            glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &(iProjMatInfo[1]));

            glGetIntegerv(GL_TEXTURE_STACK_DEPTH,        &(iTexMatInfo[0]));
            glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH,    &(iTexMatInfo[1]));

            fprintf(stderr, "    MatrixMode 0x%04x\n", iMatMode);

            fprintf(stderr, "    ModelViewStack %d %d\n", 
                    iMoViMatInfo[0],
                    iMoViMatInfo[1]);

            fprintf(stderr, "    ProjectionStack %d %d\n", 
                    iProjMatInfo[0],
                    iProjMatInfo[1]);
        }
    };
}

SimpleCSMPlugin::SimpleCSMPlugin(void)
{
}


SimpleCSMPlugin::~SimpleCSMPlugin(void)
{
}

void SimpleCSMPlugin::run(int argc, char **argv)
{
#ifdef WIN32
    OSG::preloadSharedObject("OSGImageFileIO");
#endif

    OSG::ChangeList::setReadWriteDefault(true);

    OSG::osgInit(argc,argv);

    OSG::GLErrorCallback = dumpGLError;

    // Assume dir is given
    if(argc == 2) 
    {
//        fprintf(stderr, "start from dir\n");

        std::string szParamFilename = argv[1];
        
        if(szParamFilename[szParamFilename.length() - 1] == '/')
        {
            szParamFilename += "params.csm";
        }
        else
        {
            szParamFilename += "/params.csm";
        }

        fprintf(stderr, "Trying to start from : %s\n", szParamFilename.c_str());

        OSG::ComplexSceneManager::startFrom(szParamFilename);
    }
    else
    {
        OSG::OSGSceneFileType::the().readContainer(
            "Source/Contrib/ComplexSceneManager/data/system-native.osg");
        
        fprintf(stderr, "Got %p\n", OSG::ComplexSceneManager::the());
        
        const char *argvTmp[] = 
        {
            "testCSM",
            "Source/Contrib/ComplexSceneManager/data/system-native.osg",
            "--data",
            "TestData/tie.wrl",
            "--global",
            "Source/Contrib/ComplexSceneManager/data/simple_mouse.osg"
        };
    
        int argcTmp = 6;
        
        OSG::ComplexSceneManager::the()->init(argcTmp, 
                                              const_cast<char **>(argvTmp));
        
        OSG::ComplexSceneManager::the()->run();
    }
}

OSG_END_NAMESPACE

extern "C"
{
  OSG_DLL_EXPORT
  OSG::SimpleCSMPluginInterface *createInterface(void)
  {
      return new OSG::SimpleCSMPlugin();
  }
}
