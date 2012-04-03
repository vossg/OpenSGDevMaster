/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGSIMPLESHLCHUNKFILE_H_
#define _OSGSIMPLESHLCHUNKFILE_H_

#include "OSGSimpleSHLChunkFileBase.h"
#include "OSGFileContextHandlerMixin.h"

OSG_BEGIN_NAMESPACE


/*! \brief SimpleSHLChunkFile class. See \ref
           PageContribCSMSimpleSHLChunkFile for a description.
*/

class OSG_CONTRIBCSM_DLLMAPPING SimpleSHLChunkFile : 
    public FileContextHandlerMixin<SimpleSHLChunkFileBase, SimpleSHLChunkFile>
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FileContextHandlerMixin<SimpleSHLChunkFileBase, 
                                    SimpleSHLChunkFile    > Inherited;
    typedef SimpleSHLChunkFile                              Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SimpleSHLChunkFileBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleSHLChunkFile(void);
    SimpleSHLChunkFile(const SimpleSHLChunkFile &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleSHLChunkFile(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void postOSGLoading(FileContextAttachment * const pContext);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SimpleSHLChunkFileBase;
    friend class FileContextHandlerMixin<SimpleSHLChunkFileBase, 
                                         SimpleSHLChunkFile    >;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleSHLChunkFile &source);
};

typedef SimpleSHLChunkFile *SimpleSHLChunkFileP;

OSG_END_NAMESPACE

#include "OSGSimpleSHLChunkFileBase.inl"
#include "OSGSimpleSHLChunkFile.inl"

#endif /* _OSGSIMPLESHLCHUNKFILE_H_ */
