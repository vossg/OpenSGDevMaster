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

#ifndef _OSGPOINTCHUNK_H_
#define _OSGPOINTCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPointChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PointChunk class. See \ref PageSystemPointChunk for a description.
    \ingroup GrpStateOpenGLObj
    \ingroup GrpLibOSGState
    \includebasedoc
 */

class OSG_STATE_DLLMAPPING PointChunk : public PointChunkBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PointChunkBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32           getStaticClassId(void);
    inline static  const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate     (DrawEnv    *pEnv, 
                               UInt32      index = 0);

    virtual void changeFrom   (DrawEnv    *pEnv, 
                               StateChunk *old,
                               UInt32      index = 0);

    virtual void deactivate   (DrawEnv    *action, 
                               UInt32      index = 0);

    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost(StateChunk *chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PointChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PointChunk(void);
    PointChunk(const PointChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PointChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PointChunkBase;

    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _extPointParameters;
    static UInt32 _extPointSpriteARB;
    static UInt32 _extPointSpriteNV;
    static UInt32 _funcIdPointParameterf;
    static UInt32 _funcIdPointParameterfv;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PointChunk &source);
};

typedef PointChunk *PointChunkP;

OSG_END_NAMESPACE

#include "OSGPointChunkBase.inl"
#include "OSGPointChunk.inl"

#endif /* _OSGPOINTCHUNK_H_ */
