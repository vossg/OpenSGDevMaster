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

#ifndef _OSGPROGRAMCHUNK_H_
#define _OSGPROGRAMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <istream>

#include "OSGProgramChunkBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

class Window;

/*! \brief Abstract State chunk to wrap programmable functions. See \ref 
           PageSystemProgramChunk for a description.
    \ingroup GrpStateARBProgramObj
    \ingroup GrpLibOSGState
    \includebasedoc
 */

class OSG_STATE_DLLMAPPING ProgramChunk : public ProgramChunkBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ProgramChunkBase                          Inherited;

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
    /*---------------------------------------------------------------------*/
    /*! \name                 ProgamChunk Commands                         */
    /*! \{                                                                 */

          bool   read         (const char        *file  );
          bool   read         (std::istream      &stream);
    
          bool   addParameter (const char        *name, 
                                     Int16        index );                   
          bool   addParameter (const char        *name, 
                                     Int16        index, 
                               const Vec4f       &value );
    
    const Vec4f  getParameter (      Int16        index );
    const Vec4f  getParameter (const char        *name  );
    const Vec4f  getParameter (const std::string &name  );

          bool   setParameter (      Int16        index, 
                               const Vec4f       &value );
          bool   setParameter (const char        *name,  
                               const Vec4f       &value );
          bool   setParameter (const std::string &name, 
                               const Vec4f       &value );
    
          Int16  findParameter(const char        *name  );
          Int16  findParameter(const std::string &name  );
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    State Commands                            */
    /*! \{                                                                 */

    virtual void activate     (DrawEnv    *action, 
                               UInt32      index = 0);

    virtual void changeFrom   (DrawEnv    *pEnv, 
                               StateChunk *old,
                               UInt32      index = 0);

    virtual void deactivate   (DrawEnv    *pEnv, 
                               UInt32      index = 0);

    virtual bool isTransparent(void                     ) const;

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

    // Variables should all be in ProgramChunkBase.

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const ProgramChunk *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ProgramChunk(void);
    ProgramChunk(const ProgramChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProgramChunk(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Program-Specific Methods                         */
    /*! \{                                                                 */

    virtual       UInt32  getExtension (void) const; 
    virtual       GLenum  getTarget    (void) const; 
    virtual const char   *getTargetName(void) const; 

                  void    printCompileError(Window  *win, 
                                            UInt32  id);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

           void handleGL       (DrawEnv                 *pEnv, 
                                UInt32                   id, 
                                Window::GLObjectStatusE  mode, 
                                GLenum                   Target, 
                                UInt32                   extension);
    static void handleDestroyGL(DrawEnv                 *pEnv, 
                                UInt32                   id, 
                                Window::GLObjectStatusE  mode, 
                                GLenum                   Target, 
                                UInt32                   extension);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ProgramChunkBase;

    static StateChunkClass _class;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _funcGenPrograms;
    static UInt32 _funcProgramString;
    static UInt32 _funcBindProgram;
    static UInt32 _funcDeletePrograms;
    static UInt32 _funcProgramLocalParameter4fv;
    static UInt32 _funcGetProgramiv;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ProgramChunk &source);
};

typedef ProgramChunk *ProgramChunkP;

OSG_END_NAMESPACE

#include "OSGProgramChunkBase.inl"
#include "OSGProgramChunk.inl"

#endif /* _OSGPROGRAMCHUNK_H_ */
