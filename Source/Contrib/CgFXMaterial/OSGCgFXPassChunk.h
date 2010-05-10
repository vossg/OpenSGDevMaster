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

#ifndef _OSGCGFXPASSCHUNK_H_
#define _OSGCGFXPASSCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <string>
#include <vector>
#include <map>

#include "OSGCG.h"

#include "OSGCgFXPassChunkBase.h"

OSG_BEGIN_NAMESPACE

class CgFXTechnique;

/*! \brief CgFXPassChunk class. See \ref
           PageKernelCgFXPassChunk for a description.
*/

class OSG_CONTRIBCGFX_DLLMAPPING CgFXPassChunk : public CgFXPassChunkBase
{
  private:

    typedef CgFXPassChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameter Callbacks                       */
    /*! \{                                                                 */

    virtual void activate  (DrawEnv       *pEnv, 
                            State         *pState,
                            StateOverride *pOverride   );

    virtual void deactivate(DrawEnv       *pEnv, 
                            State         *pState,
                            StateOverride *pOverride   );

    virtual void changeFrom(DrawEnv       *, 
                            State         *pNewState,
                            StateOverride *pNewOverride,
                            State         *pOldState,
                            StateOverride *pOldOverride);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Parameters                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual bool isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  (      StateChunk *chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CGFXPassChunkBase.

    CGpass   _pCGPass;
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CgFXPassChunk(void);
    CgFXPassChunk(const CgFXPassChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CgFXPassChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void setPass            (CGpass    pPass  );
  
    void updateStateUniforms(DrawEnv  *pEnv   );
  
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CgFXPassChunkBase;
    friend class CgFXTechnique;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CgFXPassChunk &source);
};

typedef CgFXPassChunk *CgFXPassChunkP;

OSG_END_NAMESPACE

#include "OSGCgFXPassChunkBase.inl"
#include "OSGCgFXPassChunk.inl"

#endif /* _OSGCGFXPASSCHUNK_H_ */
