/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGTILECAMERADECORATOR_H_
#define _OSGTILECAMERADECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTileCameraDecoratorBase.h"

OSG_BEGIN_NAMESPACE


/*! \brief Camera Decorator class to select a part of the image, see \ref
           PageSystemWindowCameraDecoratorsTile for a description.
    \ingroup GrpWindowCameraObj
    \ingroup GrpLibOSGWindow
    \includebasedoc
 */

class OSG_WINDOW_DLLMAPPING TileCameraDecorator : 
    public TileCameraDecoratorBase
{
    /*==========================  PRIVATE  ================================*/ 

 private:

    /*==========================  PUPLIC   ================================*/

  public:

    typedef TileCameraDecoratorBase                          Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     transformation                           */
    /*! \{                                                                 */
    
    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    access                                    */
    /*! \{                                                                 */

            void setSize      (Real32  left,  
                               Real32  bottom, 
                               Real32  right, 
                               Real32  top   );
    
            void setFullSize  (UInt32  width, 
                               UInt32  height);
 
    virtual void getProjection(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);
 
	virtual void getDecoration(Matrix &result, 
                               UInt32  width, 
                               UInt32  height);
 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual Vec2u tileGetFullSize(void) const;
    virtual Vec4f tileGetRegion  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   dump                                       */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

 protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TileCameraDecorator(void);
    TileCameraDecorator(const TileCameraDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TileCameraDecorator(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/

 private:

    friend class FieldContainer;
    friend class TileCameraDecoratorBase;

    void operator =(const TileCameraDecorator &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef TileCameraDecorator *TileCameraDecoratorP;

OSG_END_NAMESPACE

#include "OSGTileCameraDecoratorBase.inl"
#include "OSGTileCameraDecorator.inl"

#endif /* _OSGTILECAMERADECORATOR_H_ */
