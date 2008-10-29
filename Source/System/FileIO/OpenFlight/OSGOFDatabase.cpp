
#include "OSGOFDatabase.h"

#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

OFDatabase::OFDatabase(void) :
    _pHeader (NULL),
    _pCurrRec(NULL),
    _sRecords(    )
{
}

OFDatabase::~OFDatabase(void)
{
    _pHeader = NULL;
}

bool OFDatabase::read(std::istream &is)
{
    bool returnValue = true;

//    fprintf(stderr, "Start to read openflight\n");

    OFRecordHeader  oRHeader;

    returnValue = oRHeader.read(is);

    if(returnValue == false)
    {
        return returnValue;
    }    

    _pHeader = new OFHeaderRecord(oRHeader);
    
    returnValue = _pHeader->read(is, *this);

    if(returnValue == false)
    {
        return returnValue;
    }    

    OFRecordRCPtr pCurr = NULL;

    while(returnValue == true)
    {
        returnValue = oRHeader.read(is);

        if(returnValue == true)
        {
            if(oRHeader.sOpCode == OFPushLevelOC)
            {
                if(_sRecords.empty() == true)
                {
                    _sRecords.push(_pHeader);
                }
                else
                {
                    _sRecords.push(_pCurrRec);
                }
            }
            else if(oRHeader.sOpCode == OFPopLevelOC)
            {
                _sRecords.pop();
            }
            else
            {
                pCurr = OFRecordFactory::the()->createRecord(oRHeader);

                if(pCurr != NULL)
                {
                    returnValue = pCurr->read(is, *this);
                 
                    switch(pCurr->getOpCode())
                    {
                        case 31:
                        case 33:
                        case 132:
                            break;

                        default:
                        {
                            if(_sRecords.empty() == false)
                            {
                                _sRecords.top()->addChild(pCurr);
                            }
                            else
                            {
                                _pHeader->addChild(pCurr);
                            }
                            
                            _pCurrRec = pCurr;
                            break;
                        }
                    }
                }
                else
                {
                    returnValue = false;
                }
            }
        }
    }

    pCurr = NULL;

    if(_sRecords.empty() != true)
    {
        fprintf(stderr, "Stack finally screwed\n");
    }

//    fprintf(stderr, "finished OpenFlight %d\n", returnValue);

    return true;
}

NodeTransitPtr OFDatabase::convert(void)
{
    NodeTransitPtr returnValue(NULL);

    if(_pHeader == NULL)
        return returnValue;

//    _pHeader->dump(0);

    returnValue = _pHeader->convertToNode(*this);

    return returnValue;
}

const OFVertexPaletteRecord *OFDatabase::getVertexPalette(void)
{
    if(_pHeader == NULL)
        return NULL;
   
    return _pHeader->getVertexPalette();
}

const OFTexturePaletteRecord *OFDatabase::getTexRecord(UInt32 uiIdx)
{
    if(_pHeader == NULL)
        return NULL;
   
    return _pHeader->getTexRecord(uiIdx);
}

OSG_END_NAMESPACE
