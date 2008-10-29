#ifndef _OSGOFDATABASE_H_
#define _OSGOFDATABASE_H_

#include <istream>

#include "OSGFileIODef.h"
#include "OSGContainerForwards.h"

#include "OSGOFRecords.h"

#include "stack"

OSG_BEGIN_NAMESPACE

class OFVertexPaletteRecord;
class OFTexturePaletteRecord;

class OSG_FILEIO_DLLMAPPING OFDatabase
{
  protected:

    OFHeaderRecordRCPtr  _pHeader;
    OFRecord            *_pCurrRec;
    
    std::stack<OFRecord *> _sRecords;

  public:

    OFDatabase(void);
    ~OFDatabase(void);

    bool read(std::istream &is);

    NodeTransitPtr convert(void);

    const OFVertexPaletteRecord  *getVertexPalette(void        );
    const OFTexturePaletteRecord *getTexRecord    (UInt32 uiIdx);
};

OSG_END_NAMESPACE

#endif // _OSGOFDATABASE_H
