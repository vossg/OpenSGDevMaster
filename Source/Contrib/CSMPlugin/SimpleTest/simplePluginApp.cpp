
#ifdef WIN32
#else
#include <dlfcn.h>
#endif

#include <stdio.h>

#include "OSGSimpleCSMPluginInterface.h"

#ifdef WIN32
void doit(int argc, char **argv)
{
    HMODULE pHandle = 
        LoadLibrary("bin/ReleaseNoOpt/OSGContribCSMSimplePluginRN.dll");

    if(pHandle != NULL)
    {
        OSG::CreateInterfaceF pInitF = 
            reinterpret_cast<OSG::CreateInterfaceF>(
                GetProcAddress(pHandle, "createInterface"));

        if(pInitF != NULL)
        {
            OSG::SimpleCSMPluginInterface *pIf = (pInitF)();

            if(pIf != NULL)
            {
                pIf->run(argc, argv);

                delete pIf;

                FreeLibrary(pHandle);
            }
            else
            {
                fprintf(stderr, "could not get interface\n");
            }
        }
        else
        {
            fprintf(stderr, "could not get init func\n");
        }
    }
    else
    {
        fprintf(stderr, "Could not open plugin so\n");
    }
}
#else
void doit(int argc, char **argv)
{
    void *pHandle = dlopen("bin/libOSGContribCSMSimplePlugin.so", 
                           (RTLD_LAZY | RTLD_GLOBAL));

    if(pHandle != NULL)
    {
        OSG::CreateInterfaceF pInitF = 
            reinterpret_cast<OSG::CreateInterfaceF>(
                dlsym(pHandle, "createInterface"));

        if(pInitF != NULL)
        {
            OSG::SimpleCSMPluginInterface *pIf = (pInitF)();

            if(pIf != NULL)
            {
                pIf->run(argc, argv);

                delete pIf;

                dlclose(pHandle);
            }
            else
            {
                fprintf(stderr, "could not get interface\n");
            }
        }
        else
        {
            fprintf(stderr, "could not get init func\n");
        }
    }
    else
    {
        fprintf(stderr, "Could not open plugin so\n");
    }
}
#endif

int main(int argc, char **argv)
{
    for(int i = 0; i < 5; ++i)
        doit(argc, argv);

    return 0;
}
