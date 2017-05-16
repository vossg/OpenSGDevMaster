/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#ifndef _OSGUNIFORMBUFFEROBJBASECHUNK_H_
#define _OSGUNIFORMBUFFEROBJBASECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUniformBufferObjBaseChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UniformBufferObjBaseChunk class. See \ref
           PageSystemUniformBufferObjBaseChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING UniformBufferObjBaseChunk : public UniformBufferObjBaseChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UniformBufferObjBaseChunkBase Inherited;
    typedef UniformBufferObjBaseChunk     Self;

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
    /*! \name                    Chunk Id                                  */
    /*! \{                                                                 */

    virtual UInt16 getChunkId(void);

    /*! \}                                                                 */

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

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       query                                  */
    /*! \{                                                                 */

    virtual void   validate               (DrawEnv *pEnv) = 0;
    virtual Int32  getOpenGLId            (DrawEnv *pEnv) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    UInt16 _uiChunkId;

    // Variables should all be in UniformBufferObjBaseChunkBase.
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate      (const UniformBufferObjBaseChunk *source      = NULL);
    void onCreateAspect(const UniformBufferObjBaseChunk *createAspect,
                        const UniformBufferObjBaseChunk *source      = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UniformBufferObjBaseChunk(void);
    UniformBufferObjBaseChunk(const UniformBufferObjBaseChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UniformBufferObjBaseChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    static StateChunkClass _class;
    static volatile UInt16 _uiChunkCounter;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UniformBufferObjBaseChunkBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UniformBufferObjBaseChunk &source);
};

typedef UniformBufferObjBaseChunk *UniformBufferObjBaseChunkP;

OSG_END_NAMESPACE

#include "OSGUniformBufferObjBaseChunkBase.inl"
#include "OSGUniformBufferObjBaseChunk.inl"

#endif /* _OSGUNIFORMBUFFEROBJBASECHUNK_H_ */
