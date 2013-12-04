/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGGEOINSTANCER_H_
#define _OSGGEOINSTANCER_H_

#include "OSGGeoInstancerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoInstancer class. See \ref
           PageSystemGeoInstancer for a description.
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */

class OSG_DRAWABLE_DLLMAPPING GeoInstancer : public GeoInstancerBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoInstancerBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                 Property Interface                           */
    /*! \{                                                                 */

   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    virtual const SFUnrecMaterialPtr *getSFMaterial (void) const;
    virtual       SFUnrecMaterialPtr *editSFMaterial(void);

    virtual       Material           *getMaterial   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    virtual void setMaterial(Material * const value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void            drawPrimitives      (DrawEnv *pEnv  );
            Action::ResultE intersectEnter      (Action  *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Limited Access                             */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume & volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual void fill(DrawableStatsAttachment *pStat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Helper                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoInstancerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoInstancer(void);
    GeoInstancer(const GeoInstancer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoInstancer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extensions Used                         */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    virtual GetFieldHandlePtr  getHandleMaterial        (void) const;
    virtual EditFieldHandlePtr editHandleMaterial       (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoInstancerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoInstancer &source);
};

typedef GeoInstancer *GeoInstancerP;

OSG_END_NAMESPACE

#include "OSGGeoInstancerBase.inl"
#include "OSGGeoInstancer.inl"

#endif /* _OSGGEOINSTANCER_H_ */
