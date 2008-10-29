
#include "OSGBaseInitFunctions.h"
#include "OSGSceneFileHandler.h"
#include "OSGIOStream.h"
#include "OSGOSGWriter.h"

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::NodeUnrecPtr pNode = NULL;

    if(argc > 1)
    {
        pNode = OSG::SceneFileHandler::the()->read(argv[1], NULL);
    }

    if(pNode != NULL)
    {
        const char *outFileName = "/tmp/of.osg";

        OSG::IndentFileOutStream outFileStream(outFileName);

        if(!outFileStream )
        {
            std::cerr << "Can not open output stream to file: "
                      << outFileName << std::endl;
            return -1;
        }

        std::cerr << "STARTING PRINTOUT:" << std::endl;

        OSG::OSGWriter writer(outFileStream, 4);
        
        writer.write(pNode);
    }    
    
    pNode = NULL;

    OSG::osgExit();
}
