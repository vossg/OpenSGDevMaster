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

#include "OSGTransformationInterfaceSensor.h"
#include "OSGTransformationDeviceInterface.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTransformationInterfaceSensorBase.cpp file.
// To modify it, please change the .fcd file
// (OSGTransformationInterfaceSensor.fcd) and 
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TransformationInterfaceSensor::initMethod(InitPhase ePhase)
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

TransformationInterfaceSensor::TransformationInterfaceSensor(void) :
     Inherited(    ),
    _pTrDevice(NULL)
{
}

TransformationInterfaceSensor::TransformationInterfaceSensor(
    const TransformationInterfaceSensor &source) :

     Inherited(source),
    _pTrDevice(NULL  )
{
}

TransformationInterfaceSensor::~TransformationInterfaceSensor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TransformationInterfaceSensor::changed(ConstFieldMaskArg whichField, 
                                            UInt32            origin,
                                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TransformationInterfaceSensor::dump(      UInt32    ,
                                         const BitVector ) const
{
    SLOG << "Dump TransformationInterfaceSensor NI" << std::endl;
}

Quaternion quatFromEul(Real32 rX, Real32 rY, Real32 rZ)
{
    Quaternion returnValue;

    Real32 cx;
    Real32 cy;
    Real32 cz;
    Real32 sx;
    Real32 sy;
    Real32 sz;
    Real32 sc;
    Real32 cs;
    Real32 cc;
    Real32 ss;

    rX /= 2.0;  
    rY /= 2.0;
    rZ /= 2.0;

    cx = osgCos(rX);  
    sx = osgSin(rX);

    cy = osgCos(rY);  
    sy = osgSin(rY);
    
    cz = osgCos(rZ);  
    sz = osgSin(rZ);

    sc = sx * cy;  
    ss = sx * sy;
    cs = cx * sy;  
    cc = cx * cy;

    returnValue.setValueAsQuat(sc * cz - cs * sz,
                               cs * cz + sc * sz,
                               cc * sz - ss * cz,
                               cc * cz + ss * sz);

    return returnValue;
}

void TransformationInterfaceSensor::frame(Time tTime, UInt32 uiFrame)
{
    if(_pTrDevice == NULL)
        return;

    Matrix mMat = _sfTransformation.getValue();

    _pTrDevice->lock();

    if(_pTrDevice->hasNewData() == true)
    {
        Real32 rScale = _sfTranslationScale.getValue();

        editSField(TransformationFieldMask);
        editSField(TranslationFieldMask   );
        editSField(RotationFieldMask      );
            
        _sfTranslation.getValue().setValues(
            _pTrDevice->getTranslate()[0] * rScale,
            _pTrDevice->getTranslate()[1] * rScale,
            _pTrDevice->getTranslate()[2] * rScale);
            
        rScale = _sfRotationScale.getValue() * Pi * 2.0f;

        _sfRotation.getValue().setValue(
            quatFromEul(_pTrDevice->getRotate()[0] * rScale,
                        _pTrDevice->getRotate()[1] * rScale,
                        _pTrDevice->getRotate()[2] * rScale));
            

        _sfRotation.getValue().getValue(_sfTransformation.getValue());
            
        _pTrDevice->clearNewData();
            
        _sfTransformation.getValue()[3][0] = _sfTranslation.getValue()[0];
        _sfTransformation.getValue()[3][1] = _sfTranslation.getValue()[1];
        _sfTransformation.getValue()[3][2] = _sfTranslation.getValue()[2];
            
        _sfTransformation.getValue().multLeft(mMat);

    }

    _pTrDevice->unlock();
}

bool TransformationInterfaceSensor::init(void)
{
    bool returnValue = Inherited::init();

    if(returnValue == true)
    {
        _pTrDevice = 
            dynamic_cast<TransformationDeviceInterface *>(_pDevice.get());

        if(_pTrDevice == NULL)
        {
            returnValue = false;
            
            FWARNING(("device is not a transformation device\n"));
        }
    }

    return returnValue;
}

void TransformationInterfaceSensor::shutdown(void)
{
    Inherited::shutdown();

    _pTrDevice = NULL;
}

OSG_END_NAMESPACE
