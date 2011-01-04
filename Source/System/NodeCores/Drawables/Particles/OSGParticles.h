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

#ifndef _OSGPARTICLES_H_
#define _OSGPARTICLES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGAction.h"

#include "OSGParticlesBase.h"

OSG_BEGIN_NAMESPACE

class  DrawEnv;
struct ParticlesDrawer;

/*! \ingroup GrpDrawablesParticlesObj
    \ingroup GrpLibOSGDrawables
    \includebasedoc
 */
class OSG_DRAWABLE_DLLMAPPING Particles : public ParticlesBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticlesBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                     Modes                                    */
    /*! \{                                                                 */
    
    enum ModeE
    {
        Points      = 0, 
        Lines, 
        ViewDirQuads, 
        ViewerQuads, 
        Arrows, 
        ViewerArrows, 
        Rectangles, 
        ShaderQuads, 
        ShaderStrips,
        LastMode 
    };
    
    enum DrawOrderE
    {
        Any         = 0,
        BackToFront, 
        FrontToBack 
    };
       
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
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    virtual void drawPrimitives(DrawEnv *pEnv);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    virtual void fill(DrawableStatsAttachment *pStat);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticlesBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Particles(void);
    Particles(const Particles &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Particles(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                NodeCore Specific                             */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume & volume);

    /*! \}                                                                 */
     /*---------------------------------------------------------------------*/
    /*! \name                Particles Specific                            */
    /*! \{                                                                 */

    Int32 *calcIndex(DrawEnv *pEnv, 
                     UInt32  &len, 
                     Int32   *index = NULL);

    ParticlesDrawer *findDrawer(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticlesBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Particles &source);
};

typedef Particles *ParticlesP;

OSG_END_NAMESPACE

#include "OSGParticlesBase.inl"
#include "OSGParticles.inl"

#endif /* _OSGPARTICLES_H_ */
