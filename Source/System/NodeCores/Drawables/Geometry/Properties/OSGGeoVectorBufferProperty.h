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

#ifndef _OSGGEOVECTORBUFFERPROPERTY_H_
#define _OSGGEOVECTORBUFFERPROPERTY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoVectorBufferPropertyBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoVectorBufferProperty class. See \ref
           PageDrawableGeoVectorBufferProperty for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoVectorBufferProperty : 
    public GeoVectorBufferPropertyBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoVectorBufferPropertyBase Inherited;
    typedef GeoVectorBufferProperty     Self;

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

    virtual UInt32 size(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoVectorBufferPropertyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoVectorBufferProperty(void);
    GeoVectorBufferProperty(const GeoVectorBufferProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoVectorBufferProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    virtual bool                  getNormalize   (      void          ) const;
    virtual void                  clear          (      void          );
    virtual void                  resize         (      size_t        );
    virtual void                  getGenericValue(      MaxTypeT&,
                                                  const UInt32        ) const;
    virtual void                  setGenericValue(const MaxTypeT&,
                                                  const UInt32        );
    virtual GeoPropertyTransitPtr clone          (      void          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void onCreate (const GeoVectorBufferProperty *p             = NULL);
    void onDestroy(      UInt32                   uiContainerId       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoVectorBufferPropertyBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoVectorBufferProperty &source);
};

typedef GeoVectorBufferProperty *GeoVectorBufferPropertyP;

OSG_END_NAMESPACE

#include "OSGGeoVectorBufferPropertyBase.inl"
#include "OSGGeoVectorBufferProperty.inl"

#endif /* _OSGGEOVECTORBUFFERPROPERTY_H_ */
