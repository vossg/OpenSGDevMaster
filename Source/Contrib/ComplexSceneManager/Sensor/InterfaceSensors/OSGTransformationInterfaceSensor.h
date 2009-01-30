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

#ifndef _OSGTRANSFORMATIONINTERFACESENSOR_H_
#define _OSGTRANSFORMATIONINTERFACESENSOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTransformationInterfaceSensorBase.h"

OSG_BEGIN_NAMESPACE

class TransformationDeviceInterface;

/*! \brief TransformationInterfaceSensor class. See \ref
           PageContribCSMTransformationInterfaceSensor for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING TransformationInterfaceSensor : 
    public TransformationInterfaceSensorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TransformationInterfaceSensorBase Inherited;
    typedef TransformationInterfaceSensor     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual bool init    (void                      );
    virtual void frame   (Time oTime, UInt32 uiFrame);
    virtual void shutdown(void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TimeSensorBase.

    TransformationDeviceInterface *_pTrDevice;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TransformationInterfaceSensor(void);
    TransformationInterfaceSensor(const TransformationInterfaceSensor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TransformationInterfaceSensor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TransformationInterfaceSensorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TransformationInterfaceSensor &source);
};

typedef TransformationInterfaceSensor *TransformationInterfaceSensorP;

OSG_END_NAMESPACE

#include "OSGTransformationInterfaceSensorBase.inl"
#include "OSGTransformationInterfaceSensor.inl"

#endif /* _OSGTRANSFORMATIONINTERFACESENSOR_H_ */
