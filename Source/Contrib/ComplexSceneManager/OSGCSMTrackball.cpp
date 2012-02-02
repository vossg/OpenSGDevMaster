/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGCSMTrackball.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMTrackballBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMTrackball.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMTrackball::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMTrackball::CSMTrackball(void) :
     Inherited    (  ),
    _oTrackball   (  ),
    _iLastX       (-1),
    _iLastY       (-1),
    _iMouseButtons( 0)

{
    _oTrackball.setStartPosition(0, 0, 10, true);
    _oTrackball.setTranslationScale(1.f);

    _oTrackball.setMode            (Trackball::OSGObject);
    _oTrackball.setSum             (true                );
    _oTrackball.setTranslationMode (Trackball::OSGFree  );
}

CSMTrackball::CSMTrackball(const CSMTrackball &source) :
     Inherited    (source),
    _oTrackball   (      ),
    _iLastX       (-1    ),
    _iLastY       (-1    ),
    _iMouseButtons( 0    )

{
    _oTrackball.setStartPosition(0, 0, 10, true);
    _oTrackball.setTranslationScale(1.f);

    _oTrackball.setMode            (Trackball::OSGObject);
    _oTrackball.setSum             (true                );
    _oTrackball.setTranslationMode (Trackball::OSGFree  );
}

CSMTrackball::~CSMTrackball(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMTrackball::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    if(0x0000 != (whichField & MouseDataFieldMask))
    {
        const MouseData &mData = _sfMouseData.getValue();

        if((0x0000 != (mData.getModifier() & _sfModifierMask.getValue())) ||
           (_sfProcessing.getValue() == 0x01))
        {
            if(mData.getButton() != -1)
            {
                if(mData.getState() == Int32(MouseData::ButtonDown))
                {
                    switch(mData.getButton())
                    {
                        case MouseData::LeftButton :  
                            break;
                            
                        case MouseData::MiddleButton :
                            _oTrackball.setAutoPosition(true);
                            break;
                            
                        case MouseData::RightButton :     
                            _oTrackball.setAutoPositionNeg(true);
                            break;

                        case MouseData::WheelDownButton:
                        {
                            _oTrackball.setAutoPositionNeg(true);

                            Real32 a,b,c,d;

                            a = 0.f;
                            b = 0.f;
                            
                            c = 0.f;
                            d = 0.1f;

                            _oTrackball.updatePositionNeg(a, b, c, d);

                            editSFMatrixResult()->setValue(
                                _oTrackball.getFullTrackballMatrix());
                    
                            editSFRotationMatrixResult()->setValue(
                                _oTrackball.getRotationMatrix());
                        }
                        break;

                        case MouseData::WheelUpButton:
                        {
                            _oTrackball.setAutoPositionNeg(true);

                            Real32 a,b,c,d;

                            a = 0.f;
                            b = 0.f;
                            
                            c = 0.f;
                            d = -0.1f;

                            _oTrackball.updatePositionNeg(a, b, c, d);

                            editSFMatrixResult()->setValue(
                                _oTrackball.getFullTrackballMatrix());

                            editSFRotationMatrixResult()->setValue(
                                _oTrackball.getRotationMatrix());
                        }
                        break;
                    }

                    _iMouseButtons |= 1 << mData.getButton();

                    editSFProcessing()->setValue(true);
                }
                else
                {
                    switch(mData.getButton())
                    {
                        case MouseData::LeftButton :  
                            break;
                            
                        case MouseData::MiddleButton :
                            _oTrackball.setAutoPosition(false);
                            break;
                            
                        case MouseData::RightButton :     
                        case MouseData::WheelDownButton:
                        case MouseData::WheelUpButton:
                            _oTrackball.setAutoPositionNeg(false);
                            break;
                    }       
                    
                    _iMouseButtons &= ~(1 << mData.getButton());

                    editSFProcessing()->setValue(false);
                }
            }
            else
            {
                if(_sfProcessing.getValue() == 0x01)
                {
                    Real32 a,b,c,d;

                    if(mData.getMode() == MouseData::RelValues)
                    {
                        a = 0.f;
                        b = 0.f;

                        c = mData.getX();
                        d = mData.getY();
                    }
                    else
                    {
                        Real32 w = mData.getWindow()->getWidth ();
                        Real32 h = mData.getWindow()->getHeight();

                        Real32 x = mData.getX();
                        Real32 y = mData.getY();
                    
                        a = -2.0 * (_iLastX / w - 0.5);
                        b = -2.0 * (0.5 - _iLastY / h);
                        c = -2.0 * (  x / w - 0.5   );
                        d = -2.0 * (0.5 - y / h     );
                    }

                    if(_iMouseButtons & (1 << MouseData::LeftButton))
                    {
                        _oTrackball.updateRotation(a, b, c, d);     
                    }
                    else if(_iMouseButtons & (1 << MouseData::MiddleButton))
                    {
                        _oTrackball.updatePosition(a, b, c, d);     
                    }
                    else if(_iMouseButtons & (1 << MouseData::RightButton))
                    {
                        _oTrackball.updatePositionNeg(a, b, c, d);  
                    }

                    editSFMatrixResult()->setValue(
                        _oTrackball.getFullTrackballMatrix());

                    editSFRotationMatrixResult()->setValue(
                        _oTrackball.getRotationMatrix());
                }
            }

            _iLastX = mData.getX();
            _iLastY = mData.getY();
        }
    }

    if(0x0000 != (whichField & ReferencePositionFieldMask))
    {
        _oTrackball.setStartPosition(_sfReferencePosition.getValue()[0],
                                     _sfReferencePosition.getValue()[1],
                                     _sfReferencePosition.getValue()[2], 
                                      true                             );

        editSFMatrixResult()->setValue(_oTrackball.getFullTrackballMatrix());

        editSFRotationMatrixResult()->setValue(_oTrackball.getRotationMatrix());
    }

    if(0x0000 != (whichField & ReferenceMatrixFieldMask))
    {
        Matrix m;
            
        m.setValue(&(_sfReferenceMatrix.getValue()[0][0]));
        
        Quaternion so;
        Vec3f      s;
        Vec3f      trans;
        Quaternion ro;
        Vec3f      cnt;
        
        cnt[0] = _sfTransformCenter.getValue()[0];
        cnt[1] = _sfTransformCenter.getValue()[1];
        cnt[2] = _sfTransformCenter.getValue()[2];
        
        m.getTransform(trans, ro, s, so, cnt);
        
        _oTrackball.setStartRotation(ro, true);
            
        ro.invert();
        ro.multVec(trans, trans);
        
        _oTrackball.setStartPosition(trans[0],
                                     trans[1],
                                     trans[2], 
                                     true);

        editSFMatrixResult()->setValue(_oTrackball.getFullTrackballMatrix());
        editSFRotationMatrixResult()->setValue(_oTrackball.getRotationMatrix());
    }

    if(0x0000 != (whichField & TransformCenterFieldMask))
    {
        _oTrackball.setRotationCenter(_sfTransformCenter.getValue());
    }

    if(0x0000 != (whichField & WorldDiagFieldMask))
    {
        _oTrackball.setTranslationScale(((_sfWorldDiag.getValue()[0] +
                                          _sfWorldDiag.getValue()[1] +
                                          _sfWorldDiag.getValue()[2]) / 5.f) *
                                        _sfTranslationScaleFactor.getValue());
    }

#if 0
    if(0x0000 != (whichField & ResetFieldMask))
    {
        _oTrackball.reset();

        VSC::beginEdit(this, MatrixResultFieldMask);
        {
            _sfMatrixResult.setValue(_oTrackball.getFullTrackballMatrix());
        }
        VSC::endEdit  (this, MatrixResultFieldMask);
    }
#endif

    Inherited::changed(whichField, origin, details);
}

void CSMTrackball::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMTrackball NI" << std::endl;
}

OSG_END_NAMESPACE
