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

#ifndef _OSGVERTEXPROGRAMCHUNK_H_
#define _OSGVERTEXPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVertexProgramChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

/*! \brief VertexProgramChunk class. See \ref 
           PageSystemVertexProgramChunk for a description.
    \ingroup GrpStateARBProgramObj
    \ingroup GrpLibOSGState
    \includebasedoc
 */

class OSG_STATE_DLLMAPPING VertexProgramChunk : public VertexProgramChunkBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VertexProgramChunkBase                          Inherited;

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
                         UInt32            origin,
                         BitVector         details);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VertexProgramChunkBase.

     /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate (const VertexProgramChunk *source        = NULL);
    void onDestroy(      UInt32              uiContainerId       );

    /*! \}                                                                 */
   /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VertexProgramChunk(void);
    VertexProgramChunk(const VertexProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VertexProgramChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Program-Specific Methods                         */
    /*! \{                                                                 */

    virtual       UInt32  getExtension(void)  const; 
    virtual       GLenum  getTarget(void)     const; 
    virtual const char   *getTargetName(void) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VertexProgramChunkBase;


    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _arbVertexProgram;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

           UInt32 handleGL       (DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode,
                                  UInt32                   uiOptions);
    static void   handleDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode     );
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VertexProgramChunk &source);
};

typedef VertexProgramChunk *VertexProgramChunkP;

OSG_END_NAMESPACE

#include "OSGVertexProgramChunkBase.inl"
#include "OSGVertexProgramChunk.inl"

#endif /* _OSGVERTEXPROGRAMCHUNK_H_ */
