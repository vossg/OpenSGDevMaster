
#include <OSGSceneFileHandler.h>
#include <OSGFieldContainerFactory.h>


int main (int argc, char **argv)
{
    OSG::osgInit(argc,argv);

    OSG::NodeRecPtr              file;
    std::vector<OSG::NodeRecPtr> vFile;

#ifdef OSG_MT_FIELDCONTAINERPTR
    OSG::UInt32 iPre = 
        OSG::FieldContainerFactory::the()->getNumContainers();
    
    fprintf(stderr, "FCs pre : %d\n", iPre);
#endif

    if(argc > 1)
    {
        for(OSG::UInt32 i = 0; i < 2; ++i)
        {
            file = OSG::SceneFileHandler::the()->read(argv[1], NULL);
            
            vFile.push_back(file);
            OSG::commitChanges();
            file = NULL;
        }

#if 0
        OSG::UInt32 iPostLoad = 
            OSG::FieldContainerFactory::the()->getContainerStore().size();

        for(OSG::UInt32 i = iPre; i < iPostLoad; ++i)
        {
            fprintf(stderr, "[%d] : ", i);
            
            if(OSG::FieldContainerFactory::the()->getContainerStore()[i] != 
               OSGNULL)
            {
                fprintf(stderr, "%s\n", 
                        OSG::FieldContainerFactory::the()->
                        getContainerStore()[i]->getType().getCName());
            }
            else
            {
                fprintf(stderr, "NULL\n");
            }
        }
#endif
        
        OSG::commitChanges();

        for(OSG::UInt32 i = 0; i < vFile.size(); ++i)
        {
            vFile[i] = NULL;
        }
    }

#ifdef OSG_MT_FIELDCONTAINERPTR
    OSG::UInt32 iPost = 
        OSG::FieldContainerFactory::the()->getNumContainers();

    fprintf(stderr, "FCs post : %d\n", iPost);
    
    for(OSG::UInt32 i = iPre; i < iPost; ++i)
    {
        fprintf(stderr, "[%d] : ", i);

        if(OSG::FieldContainerFactory::the()->getContainer(i) != OSGNULL)
        {
            fprintf(stderr, "%s\n", 
                    OSG::FieldContainerFactory::the()->
                    getContainer(i)->getType().getCName());
        }
        else
        {
            fprintf(stderr, "NULL\n");
        }
    }
#endif

    OSG::osgExit();
}
