
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

    UInt32 uiIndent = 0;
    
    while(returnValue == true)
    {
        returnValue = oRHeader.read(is);

        if(returnValue == true)
        {
            if(oRHeader.sOpCode == OFPushLevelOC)
            {
                uiIndent += 2;
                
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
                uiIndent -= 2;
                
                _sRecords.pop();
            }
            else if(oRHeader.sOpCode == OFContinuationOC)
            {
                if(pCurr != NULL)
                {
                    pCurr->readContinue(is, *this, oRHeader.sLength - 4);
                }
                else
                {
                    FWARNING(("OFDatabase::read: Found ContinuationRecord, "
                              "without preceding record.\n"))
                }
            }
            else
            {
                pCurr = OFRecordFactory::the()->createRecord(oRHeader);

                indentLog(uiIndent, PLOG);
                PLOG << "OFDatabase::read: Record ["
                     << pCurr->getOpCode() << " - "
                     << pCurr->findDesc(pCurr->getOpCode()) 
                     << "]" << std::endl;
                
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
        FWARNING(("OFDatabase::read: Record stack inconsistent.\n"));
    }

//    fprintf(stderr, "finished OpenFlight %d\n", returnValue);

    return true;
}

NodeTransitPtr OFDatabase::convert(void)
{
    NodeTransitPtr returnValue(NULL);

    if(_pHeader == NULL)
        return returnValue;

   _pHeader->dump(0);

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

const OFMaterialPaletteRecord *OFDatabase::getMatRecord(UInt32 uiIdx)
{
    if(_pHeader == NULL)
        return NULL;
    
    return _pHeader->getMatRecord(uiIdx);
}


OSG_END_NAMESPACE
