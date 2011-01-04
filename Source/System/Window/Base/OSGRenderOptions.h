/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
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

#ifndef _OSGRENDEROPTIONS_H_
#define _OSGRENDEROPTIONS_H_

#include "OSGRenderOptionsBase.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;

/*! \brief RenderOptions class. See \ref PageSystemWindowRenderOptions
    for a description. 

  \ingroup GrpSystemWindowBase
  \ingroup GrpLibOSGSystem
  \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING RenderOptions : public RenderOptionsBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef RenderOptionsBase                          Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    void      setWireframe   (bool value          );

    bool      getWireframe   (void                );
    BitVector getChanged     (void                );
    BitVector getLastChanged (void                );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    void activate  (RenderActionBase *pAction);
    void deactivate(RenderActionBase *pAction);

#ifdef OSG_OLD_RENDER_ACTION
    void      activateOptions(RenderAction *action);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    RenderOptions(void);
    RenderOptions(const RenderOptions &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RenderOptions(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL setup handling                             */
    /*! \{                                                                 */

    BitVector   _changed;
    BitVector   _last_changed;
    Real32      _gl_version;
    GLenum      _polygon_mode;
    bool        _backface_culling;
    bool        _two_sided_lighting;
    bool        _spec_tex_lighting;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RenderOptionsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RenderOptions &source);
};

typedef RenderOptions *RenderOptionsP;

OSG_END_NAMESPACE

#include "OSGRenderOptionsBase.inl"

#endif /* _OSGRENDEROPTIONS_H_ */

