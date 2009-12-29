
#include "OSGColladaFileType.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaGlobal.h"
#include "OSGColladaOptions.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8           *ColladaFileType::_suffixA[] = { "dae" };

      ColladaFileType  ColladaFileType::_the(_suffixA,
                                              sizeof(_suffixA),
                                             false,
                                             10,
                                             OSG_READ_SUPPORTED);


const Char8 *
ColladaFileType::getName(void) const
{
    return "Collada SCENE";
}

NodeTransitPtr
ColladaFileType::read(
    std::istream &is, const Char8 *fileNameOrExtension, Resolver resolver) const
{
    NodeTransitPtr       rootN;

    ColladaGlobalRefPtr  colGlobal = ColladaGlobal ::create();
    ColladaOptionsRefPtr colOpts   = ColladaOptions::create();

    colOpts->parseOptions(this->getOptions());

    colGlobal->setOptions(colOpts);

    rootN = colGlobal->read(is, fileNameOrExtension);

    return rootN;
}
                      

ColladaFileType::ColladaFileType(
    const Char8  *suffixArray[], UInt16 suffixByteCount,
    bool          override,      UInt32 overridePriority,
    UInt32        flags                                  )

    : Inherited(suffixArray, suffixByteCount,
                override, overridePriority, flags)
{
}

ColladaFileType::~ColladaFileType(void)
{
}
                                 

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
