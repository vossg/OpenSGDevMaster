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

#ifndef _OSGTEXGENCHUNK_H_
#define _OSGTEXGENCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTexGenChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief State chunk for texture coordinate generation. See \ref 
           PageSystemTexGenChunk for a description.
    \ingroup GrpStateOpenGLObj
    \ingroup GrpLibOSGState
    \includebasedoc
 */

class OSG_STATE_DLLMAPPING TexGenChunk : public TexGenChunkBase
{
    /*==========================  PUBLIC  =================================*/

  public:
    
    static const UInt32 EyeModelViewNone     = 0x0000;
    static const UInt32 EyeModelViewIdentity = 0x0001;
    static const UInt32 EyeModelViewStored   = 0x0002;
    static const UInt32 EyeModelViewCamera   = 0x0003;

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static       UInt32           getStaticClassId(void);
    static const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            from,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate  (DrawEnv    *pEnv, 
                            UInt32      index = 0);

    virtual void changeFrom(DrawEnv    *pEnv, 
                            StateChunk *pOld,
                            UInt32      index = 0);

    virtual void deactivate(DrawEnv    *action, 
                             UInt32     index = 0);

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

    // Variables should all be in TexGenChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TexGenChunk(void);
    TexGenChunk(const TexGenChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TexGenChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef TexGenChunkBase Inherited;

    friend class FieldContainer;
    friend class TexGenChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TexGenChunk &source);
};

typedef TexGenChunk              *TexGenChunkP;

OSG_END_NAMESPACE

#include "OSGTexGenChunkBase.inl"
#include "OSGTexGenChunk.inl"

#endif /* _OSGTEXGENCHUNK_H_ */
