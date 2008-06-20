/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#include <OSGCSMVRMLNodeHelper.h>
#include <OSGTimeSensor.h>
#include <OSGOrientationInterpolator.h>
#include <OSGGroup.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLTimeSensorHelper
    \ingroup GrpSystemFileIOVRML
    VRML Group description
*/

VRMLNodeHelper *VRMLTimeSensorHelper::create(void)
{
    return new VRMLTimeSensorHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLTimeSensorHelper::VRMLTimeSensorHelper(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLTimeSensorHelper::~VRMLTimeSensorHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLTimeSensorHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "TimeSensorHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node      ::create();
    _pNodeCoreProto = TimeSensor::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);

//    addRefX(_pNodeProto    );
//    addRefX(_pNodeCoreProto);
//    addRefX(_pGenAttProto  );
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLTimeSensorHelper::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    return Inherited::prototypeAddField(szFieldType,
                                        uiFieldTypeId,
                                        szFieldname);
}

void VRMLTimeSensorHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

#ifdef OSG_DEBUG_VRML
    incIndent();
#endif

    Inherited::getFieldAndDesc(pFC,
                               szFieldname,
                               pFieldFC,
                               pField,
                               pDesc);
#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

void VRMLTimeSensorHelper::endNode(FieldContainer *pFC)
{
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLTimeSensorHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper VRMLTimeSensorHelper::_regHelper(
    &VRMLTimeSensorHelper::create,
    "TimeSensor");




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLTimeSensorHelper
    \ingroup GrpSystemFileIOVRML
    VRML Group description
*/

VRMLNodeHelper *VRMLInterpolatorHelper::create(void)
{
    return new VRMLInterpolatorHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLInterpolatorHelper::VRMLInterpolatorHelper(void) :
     Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLInterpolatorHelper::~VRMLInterpolatorHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLInterpolatorHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "InterpolatorHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node      ::create();

    if(osgStringCaseCmp("OrientationInterpolator", szName) == 0)
    {
        _pNodeCoreProto = OrientationInterpolator::create();
    }
    else
    {
        fprintf(stderr, "Unknown Interpolator\n");
        _pNodeCoreProto = Group::create();
    }

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);

//    addRefX(_pNodeProto    );
//    addRefX(_pNodeCoreProto);
//    addRefX(_pGenAttProto  );
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLInterpolatorHelper::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname)
{
    return Inherited::prototypeAddField(szFieldType,
                                        uiFieldTypeId,
                                        szFieldname);
}

void VRMLInterpolatorHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

#ifdef OSG_DEBUG_VRML
    incIndent();
#endif

    Inherited::getFieldAndDesc(pFC,
                               szFieldname,
                               pFieldFC,
                               pField,
                               pDesc);
#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

void VRMLInterpolatorHelper::endNode(FieldContainer *pFC)
{
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLInterpolatorHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLInterpolatorHelper::_regHelperOrientation(
        &VRMLInterpolatorHelper::create,
        "OrientationInterpolator");

OSG_END_NAMESPACE
