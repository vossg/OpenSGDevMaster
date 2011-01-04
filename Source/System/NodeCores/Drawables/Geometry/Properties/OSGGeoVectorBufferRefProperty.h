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

#ifndef _OSGGEOVECTORBUFFERREFPROPERTY_H_
#define _OSGGEOVECTORBUFFERREFPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoVectorBufferRefPropertyBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoVectorBufferRefProperty class. See \ref
           PageDrawableGeoVectorBufferRefProperty for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoVectorBufferRefProperty : 
    public GeoVectorBufferRefPropertyBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoVectorBufferRefPropertyBase Inherited;
    typedef GeoVectorBufferRefProperty     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    void setGLId(UInt32 uiGLId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate(DrawEnv *pEnv,
                          UInt32   index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void *mapBuffer  (GLenum eAccess, DrawEnv *pEnv);
    virtual bool  unmapBuffer(                DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoVectorBufferRefPropertyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoVectorBufferRefProperty(void);
    GeoVectorBufferRefProperty(const GeoVectorBufferRefProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoVectorBufferRefProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate (const GeoVectorBufferRefProperty *p             = NULL);
    void onDestroy(      UInt32                      uiContainerId       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoVectorBufferRefPropertyBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoVectorBufferRefProperty &source);
};

typedef GeoVectorBufferRefProperty *GeoVectorBufferRefPropertyP;

OSG_END_NAMESPACE

#include "OSGGeoVectorBufferRefPropertyBase.inl"
#include "OSGGeoVectorBufferRefProperty.inl"

#endif /* _OSGGEOVECTORBUFFERREFPROPERTY_H_ */
