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

#include "OSGMTouchData.h"
#include "OSGMTouchDataFields.h"
#include "OSGFieldContainer.h"

#include "OSGSField.ins"

OSG_BEGIN_NAMESPACE

MTouchData::MTouchBlob::MTouchBlob(UInt32 uiEvent,
                                   Int32  iCursorId,
                                   Real32 rX,
                                   Real32 rY,
                                   UInt32 uiCoordSys) :

    _uiEvent   (uiEvent    ),

    _iCursorId (iCursorId  ),
    _vPosition (rX, rY, 0.f),
   
    _uiCoordSys(uiCoordSys )
{
}

//MTouchData::MTouchBlob::~MTouchBlob(void)
//{
//}

bool MTouchData::MTouchBlob::operator ==(const MTouchBlob &rhs) const
{
    return (_uiEvent == rhs._uiEvent && _iCursorId == rhs._iCursorId);
}

bool MTouchData::MTouchBlob::operator !=(const MTouchBlob &rhs) const
{
    return !(*this == rhs);
}

bool MTouchData::MTouchBlob::operator < (const MTouchBlob &rhs) const
{
    return ((_iCursorId <  rhs._iCursorId) ||
            (_iCursorId == rhs._iCursorId && _uiEvent < rhs._uiEvent));
}



MTouchData::MTouchData(void) :
    _vBlobs      (     ),
    _vActiveBlobs(     ),
    _pWindow     (NULL ),
    _pCSMWindow  (NULL )
{
}


MTouchData::MTouchData(const MTouchData &source) :
    _vBlobs      (source._vBlobs      ),
    _vActiveBlobs(source._vActiveBlobs),
    _pWindow     (NULL                ),
    _pCSMWindow  (NULL                )
{
}

MTouchData::~MTouchData(void)
{
}

/*------------------------------ access -----------------------------------*/

void MTouchData::operator = (const MTouchData &rhs)
{
    _vBlobs = rhs._vBlobs;

    _pWindow = rhs._pWindow;
    _pCSMWindow = rhs._pCSMWindow;
}

bool MTouchData::operator ==(const MTouchData &rhs) const
{
    //return (_vBlobs == rhs._vBlobs    &&
    //        _pWindow   == rhs._pWindow  );
    //        _pCSMWindow   == rhs._pCSMWindow  );

    return (_vBlobs == rhs._vBlobs  );
}

void MTouchData::addCursor(UInt32 uiId, 
                           Real32 rX, 
                           Real32 rY,
                           UInt32 uiCoordSys)
{
    MTouchBlob tmpBlob(MTouchData::AddCursor, uiId, rX, rY, uiCoordSys);

    MTouchBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
                                              _vBlobs.end  (),
                                               tmpBlob       );
    if(tbIt == _vBlobs.end())
    {
        _vBlobs.push_back(tmpBlob);
    }
    else if(tmpBlob != *tbIt)
    {
        _vBlobs.insert(tbIt, tmpBlob);
    }
    else
    {
        fprintf(stderr, "addC: blob %d mode %d already present\n",
                uiId,
                MTouchData::AddCursor);
    }
}

void MTouchData::updateCursor(UInt32 uiId, 
                              Real32 rX, 
                              Real32 rY,
                              UInt32 uiCoordSys)
{
    ActiveBlobsStoreIt aIt = std::lower_bound(_vActiveBlobs.begin(),
                                              _vActiveBlobs.end  (),
                                               uiId);

    UInt32 uiEvent = MTouchData::UpdateCursor;

    if(aIt == _vActiveBlobs.end())
    {
        uiEvent = MTouchData::AddCursor;

        _vActiveBlobs.push_back(uiId);
    }
    else
    {
        if(uiId != *aIt)
        {
            uiEvent = MTouchData::AddCursor;
            
            _vActiveBlobs.insert(aIt, uiId);
        }
    }

    MTouchBlob tmpBlob(uiEvent, uiId, rX, rY, uiCoordSys);

//    fprintf(stderr, "update coursor %d / %f %f\n",
//            uiId, rX, rY);

    MTouchBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
                                              _vBlobs.end  (),
                                               tmpBlob       );

    if(tbIt == _vBlobs.end())
    {
        _vBlobs.push_back(tmpBlob);
    }
    else if(tmpBlob != *tbIt)
    {
        _vBlobs.insert(tbIt, tmpBlob);
    }
    else
    {
        *tbIt = tmpBlob;
    }
}

void MTouchData::removeCursor(UInt32 uiId)
{
    MTouchBlob tmpBlob(MTouchData::RemoveCursor, uiId, 0.f, 0.f);

    MTouchBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
                                              _vBlobs.end  (),
                                               tmpBlob       );

    if(tbIt == _vBlobs.end())
    {
        _vBlobs.push_back(tmpBlob);
    }
    else if(tmpBlob != *tbIt)
    {
        _vBlobs.insert(tbIt, tmpBlob);
    }
    else
    {
        fprintf(stderr, "remC: blob %d mode %d already present\n",
                uiId,
                MTouchData::RemoveCursor);
    }

    ActiveBlobsStoreIt aIt = std::lower_bound(_vActiveBlobs.begin(),
                                              _vActiveBlobs.end  (),
                                               uiId);
    
    if(aIt != _vActiveBlobs.end())
    {
        if((*aIt) == uiId)
        {
            _vActiveBlobs.erase(aIt);
        }
    }
    
}


void MTouchData::prepSubmission(void)
{
}

void MTouchData::clear(void)
{
//    fprintf(stderr, "clear\n");
//    this->dump();
    _vBlobs.clear();
}

void MTouchData::dump(void) const
{
    fprintf(stderr, "Blobs (%"PRISize") :\n", _vBlobs.size());
    for(UInt32 i = 0; i < _vBlobs.size(); ++i)
    {
        fprintf(stderr, "  [%d] : %d %d %d | %f %f\n",
                i,
                _vBlobs[i]._uiEvent,
                _vBlobs[i]._iCursorId,
                _vBlobs[i]._uiCoordSys,
                _vBlobs[i]._vPosition[0],
                _vBlobs[i]._vPosition[1]);
    }

    fprintf(stderr, "Active Blobs (%"PRISize") :\n", _vActiveBlobs.size());
    for(UInt32 i = 0; i < _vActiveBlobs.size(); ++i)
    {
        fprintf(stderr, "[%d] : %d\n",
                i,
                _vActiveBlobs[i]);
    }
}

DataType FieldTraits<MTouchData>::_type("MTouchData",        "BaseType"    );

OSG_FIELDTRAITS_GETTYPE (        MTouchData    )
OSG_FIELD_DLLEXPORT_DEF1(SField, MTouchData    )

OSG_END_NAMESPACE
