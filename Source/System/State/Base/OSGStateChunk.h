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


#ifndef _OSGSTATECHUNK_H_
#define _OSGSTATECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStateChunkBase.h"

#include <string>

OSG_BEGIN_NAMESPACE

class  DrawEnv;
struct StateChunkClassInit;

/*! \brief The classification class for StateChunks, see \ref StateChunkClass
    for a description. 
*/

class OSG_SYSTEM_DLLMAPPING StateChunkClass
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    StateChunkClass(Char8  *name, 
                    UInt32  numslots  = 1,
                    UInt32  priortity = 50);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Instance Access                              */
    /*! \{                                                                 */

           UInt32   getId       (void     ) const;
           UInt32   getPriority (void     ) const;
    const  Char8   *getName     (void     ) const;
           Int32    getNumSlots (void     ) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Class Access                                */
    /*! \{                                                                 */

           static const Char8 * getName     (UInt32 index);
           static       Int32   getNumSlots (UInt32 index);
    inline static       UInt32  getUsedSlots(void) ;

    typedef std::vector<StateChunkClass *>::const_iterator iterator;

    static iterator begin(void);
    static iterator end  (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    struct StateChunkClassInit;

    friend struct StateChunkClassInit;

    struct StateChunkClassInit
    {
        StateChunkClassInit(void) 
        { 
            addPreFactoryInitFunction(&StateChunkClass::initialize); 
        }
    };

    static StateChunkClassInit InitHelper;


           UInt32                          _classId;
           UInt32                          _numSlots;
           UInt32                          _priority;
           std::string                     _className;

    static std::vector<StateChunkClass *> *_classes;
    static std::vector<StateChunkClass *> *_initClasses;

    static std::vector<     UInt32      > *_numslots;

    static bool terminate (void);
    static bool initialize(void);
};

/*! \brief The abstract base class for StateChunks, see \ref StateChunk
    for a description. 
 */

class OSG_SYSTEM_DLLMAPPING StateChunk : public StateChunkBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

                         UInt32           getClassId      (void) const;
           virtual const StateChunkClass *getClass        (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    static        UInt32           getStaticClassId(void);
    static  const StateChunkClass *getStaticClass  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    virtual UInt16 getChunkId(void);

    /*! \}                                                                 */
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
    /*! \name                      State                                   */
    /*! \{                                                                 */

#ifndef OSG_DISABLE_DEPRECATED
    virtual void update       (DrawEnv   *pEnv      );
#endif

    virtual void activate     (DrawEnv    *pEnv, 
                               UInt32      index = 0) = 0;

    virtual void changeFrom   (DrawEnv    *pEnv, 
                               StateChunk *pOld,
                               UInt32      index = 0) = 0;

    virtual void deactivate   (DrawEnv    *pEnv, 
                               UInt32      index = 0) = 0;

    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StateChunk(void);
    StateChunk(const StateChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StateChunk(void);

    /*! \}                                                                 */

    static void initMethod(InitPhase ePhase);

    /*==========================  PRIVATE  ================================*/
  private:

    typedef StateChunkBase Inherited;

    friend class StateChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StateChunk &source);
};

typedef StateChunk *StateChunkP;

OSG_END_NAMESPACE

#include "OSGStateChunk.inl"
#include "OSGStateChunkBase.inl"

#endif /* _OSGSTATECHUNK_H_ */
