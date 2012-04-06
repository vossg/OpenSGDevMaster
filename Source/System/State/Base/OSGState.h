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


#ifndef _OSGSTATE_H_
#define _OSGSTATE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStateBase.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

class StateOverride;
class DrawEnv;

/*! \brief Wrapper for a complete State. See \ref State for a description.
    \ingroup GrpSystemStateBase
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_SYSTEM_DLLMAPPING State : public StateBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 InvalidKey     = 0x000003FF;

    static const UInt32 SkipRebuild    = 0x80000000;

    static const UInt32 Key1Mask       = 0x000003FF;
    static const UInt32 Key2Mask       = 0x000FFC00;
    static const UInt32 Key3Mask       = 0x3FF00000;

    static const UInt32 DefaultKeyMask = 0x80000000;
    static const UInt32 FullStateMask  = 0x40000000;

#ifdef OSG_NEW_SHADER
    static const UInt32 SkipNumChunks  = 2;
    static const UInt32 UpdateChunk    = 2;
    static const UInt32 FullStateIndex = 2;
#else
    static const UInt32 SkipNumChunks  = 0;
    static const UInt32 UpdateChunk    = 0;
    static const UInt32 FullStateIndex = 0;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL State Management                        */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL State Management                        */
    /*! \{                                                                 */

    void activate  (DrawEnv *pEnv) const;

    void changeFrom(DrawEnv *pEnv, 
                    State   *pOld) const;

    void deactivate(DrawEnv *pEnv) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Enums                                     */
    /*! \{                                                                 */

    enum 
    { 
        AutoSlot        = -1, 
        AutoSlotReplace = -2 
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    StateChunk *getChunk     (UInt32      chunkId                ) const;

    bool        chunkPresent (UInt32      chunkId                ) const;
    bool        chunkPresent (StateChunk *chunk                  ) const;
   
    bool        addChunk     (StateChunk *chunk, 
                              Int32       index = AutoSlotReplace);

    bool        subChunk     (StateChunk *chunk                  );

    bool        subChunk     (UInt32      classid, 
                              Int32       index                  );

    void        clearChunks  (void                               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Properties                                */
    /*! \{                                                                 */

    bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      StateSorting Interface (for Material/Sorter only)       */
    /*! \{                                                                 */

    void   setDefaultSortKey(UInt32 uiSortKey);
    UInt32 getSortKey       (UInt32 uiKeyGen  = SkipRebuild);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  (State * state);

    virtual bool   operator <  (const State &other) const;

    virtual bool   operator == (const State &other) const;
    virtual bool   operator != (const State &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt32 _uiDefaultSortKey;
    UInt32 _uiSortKey;
    UInt32 _uiKeyGen;

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreateAspect(const State *createAspect,
                        const State *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    State(void);
    State(const State &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~State(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    void rebuildSortKey(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    const MFUnrecStateChunkPtr *getMFChunks(void) const;

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef StateBase Inherited;

    friend class FieldContainer;
    friend class StateBase;
    friend class DrawEnv;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const State &source);
};

typedef State *StateP;

#define OSG_SKIP_IT(ITERATOR, STEPS)                        \
    (ITERATOR) += (STEPS)

OSG_END_NAMESPACE

#include "OSGStateBase.inl"
#include "OSGState.inl"

#endif /* _OSGSTATE_H_ */
