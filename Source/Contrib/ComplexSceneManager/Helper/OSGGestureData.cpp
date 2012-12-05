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

#include "OSGGestureData.h"
#include "OSGGestureDataFields.h"
#include "OSGFieldContainer.h"

#include "OSGSField.ins"

OSG_BEGIN_NAMESPACE

GestureData::GestureBlob::GestureBlob(      UInt32       uiEvent,
                                            Int32        iGestureId,
                                      const std::string &szGesture, 
                                            Real32       rX,
                                            Real32       rY,
                                            UInt32       uiCoordSys) :

    _uiEvent   (uiEvent    ),
    _iGestureId(iGestureId ),
    _vPosition (rX, rY, 0.f),
   
    _uiCoordSys(uiCoordSys ),

    _szGesture (szGesture  )
{
}

//GestureData::GestureBlob::~GestureBlob(void)
//{
//}

bool GestureData::GestureBlob::operator ==(const GestureBlob &rhs) const
{
    // gesture id and uievent uniquely identifies the gesture
    return (_uiEvent == rhs._uiEvent && _iGestureId == rhs._iGestureId );
}

bool GestureData::GestureBlob::operator !=(const GestureBlob &rhs) const
{
    return !(*this == rhs);
}

bool GestureData::GestureBlob::operator < (const GestureBlob &rhs) const
{
    return ((_iGestureId <  rhs._iGestureId) ||
            (_iGestureId == rhs._iGestureId && _uiEvent < rhs._uiEvent));
}



GestureData::GestureData(void) :
    _vBlobs      (     ),
    _vActiveBlobs(     ),
    _pWindow     (NULL ),
    _pCSMWindow  (NULL )
{
}


GestureData::GestureData(const GestureData &source) :
    _vBlobs      (source._vBlobs      ),
    _vActiveBlobs(source._vActiveBlobs),
    _pWindow     (NULL                ),
    _pCSMWindow  (NULL                )
{
}

GestureData::~GestureData(void)
{
}

/*------------------------------ access -----------------------------------*/

void GestureData::operator = (const GestureData &rhs)
{
    _vBlobs     = rhs._vBlobs;

    _pWindow    = rhs._pWindow;
    _pCSMWindow = rhs._pCSMWindow;
}

bool GestureData::operator ==(const GestureData &rhs) const
{
    //return (_vBlobs == rhs._vBlobs    &&
    //        _pWindow   == rhs._pWindow  );
    //        _pCSMWindow   == rhs._pCSMWindow  );

    return (_vBlobs == rhs._vBlobs);
}

void GestureData::addGesture(      UInt32       uiId,
                             const std::string &szGesture,
                                   Real32       rX, 
                                   Real32       rY,
                                   UInt32       uiCoordSys)
{
    GestureBlob tmpBlob(GestureData::AddGesture, 
                        uiId, 
                        szGesture, 
                        rX, 
                        rY, 
                        uiCoordSys             );

    GestureBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
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
                GestureData::AddGesture);
    }
}

void GestureData::updateGesture(      UInt32       uiId,
                                const std::string &szGesture, 
                                      Real32       rX, 
                                      Real32       rY,
                                      UInt32       uiCoordSys)
{
    ActiveBlobsStoreIt aIt = std::lower_bound(_vActiveBlobs.begin(),
                                              _vActiveBlobs.end  (),
                                               uiId);

    UInt32 uiEvent = GestureData::UpdateGesture;

    if(aIt == _vActiveBlobs.end())
    {
        uiEvent = GestureData::AddGesture;

        _vActiveBlobs.push_back(uiId);
    }
    else
    {
        if(uiId != *aIt)
        {
            uiEvent = GestureData::AddGesture;
            
            _vActiveBlobs.insert(aIt, uiId);
        }
    }

    GestureBlob tmpBlob(uiEvent, uiId, szGesture, rX, rY, uiCoordSys);

//    fprintf(stderr, "update coursor %d / %f %f\n",
//            uiId, rX, rY);

    GestureBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
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

void GestureData::removeGesture(UInt32 uiId)
{
    GestureBlob tmpBlob(GestureData::RemoveGesture, uiId, "", 0.f, 0.f);

    GestureBlobStoreIt tbIt = std::lower_bound(_vBlobs.begin(),
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
                GestureData::RemoveGesture);
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


void GestureData::prepSubmission(void)
{
}

void GestureData::clear(void)
{
//    fprintf(stderr, "clear\n");
//    this->dump();
    _vBlobs.clear();
}

void GestureData::dump(void) const
{
    fprintf(stderr, "Blobs (%" PRISize ") :\n", _vBlobs.size());
    for(UInt32 i = 0; i < _vBlobs.size(); ++i)
    {
        fprintf(stderr, "  [%d] : %d %d %d | %f %f\n",
                i,
                _vBlobs[i]._uiEvent,
                _vBlobs[i]._iGestureId,
                _vBlobs[i]._uiCoordSys,
                _vBlobs[i]._vPosition[0],
                _vBlobs[i]._vPosition[1]);
    }

    fprintf(stderr, "Active Blobs (%" PRISize ") :\n", _vActiveBlobs.size());

    for(UInt32 i = 0; i < _vActiveBlobs.size(); ++i)
    {
        fprintf(stderr, "[%d] : %d\n",
                i,
                _vActiveBlobs[i]);
    }
}

DataType FieldTraits<GestureData>::_type("GestureData",        "BaseType"    );

OSG_FIELDTRAITS_GETTYPE (        GestureData    )
OSG_FIELD_DLLEXPORT_DEF1(SField, GestureData    )

OSG_END_NAMESPACE
