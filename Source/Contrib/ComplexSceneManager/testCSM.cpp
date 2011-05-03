
#include "OSGComplexSceneManager.h"
#include "OSGOSGSceneFileType.h"
#include "OSGBaseInitFunctions.h"
#include "OSGGLU.h"

void dumpGLError(GLenum glError, const GLubyte *glErrorString)
{
    fprintf(stderr, "Custom error dump\n");
    fprintf(stderr, "-----------------\n");

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
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
#endif
}

int init(int argc, char **argv)
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
    
//    OSG::osgExit();

    return 0;
}

int main (int argc, char **argv)
{
    init(argc, argv);

    return 0;
}
