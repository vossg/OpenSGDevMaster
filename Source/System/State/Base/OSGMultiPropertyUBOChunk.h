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

#ifndef _OSGMULTIPROPERTYUBOCHUNK_H_
#define _OSGMULTIPROPERTYUBOCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiPropertyUBOChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiPropertyUBOChunk class. See \ref
           PageSystemMultiPropertyUBOChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING MultiPropertyUBOChunk : public MultiPropertyUBOChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiPropertyUBOChunkBase Inherited;
    typedef MultiPropertyUBOChunk     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Interface                               */
    /*! \{                                                                 */

    enum Types   {
        FLOAT_T = 0, 
        DOUBLE_T, 
        INT_T, 
        UINT_T, 
        BOOL_T, 
        VEC3_T, 
        VEC4_T, 
        MAT4_T
    };

          void                 clearMembers     ();
          UInt32               addMember        (Types type, UInt32 cardinality = 1);

          UInt32               getNumProperties () const;
          UInt32               addProperty      ();
          void                 removeProperty   (const UInt32 idx);
          void                 clearProperties  ();

          Real32               getFloatProperty (UInt32 idx, UInt32 num) const;
          Real64               getDoubleProperty(UInt32 idx, UInt32 num) const;
          Int32                getIntProperty   (UInt32 idx, UInt32 num) const;
          UInt32               getUIntProperty  (UInt32 idx, UInt32 num) const;
          bool                 getBoolProperty  (UInt32 idx, UInt32 num) const;
    const Vec3f               &getVec3Property  (UInt32 idx, UInt32 num) const;
    const Vec4f               &getVec4Property  (UInt32 idx, UInt32 num) const;
    const Matrix              &getMat4Property  (UInt32 idx, UInt32 num) const;

          void                 setFloatProperty (UInt32 idx, UInt32 num, Real32 value);
          void                 setDoubleProperty(UInt32 idx, UInt32 num, Real64 value);
          void                 setIntProperty   (UInt32 idx, UInt32 num, Int32  value);
          void                 setUIntProperty  (UInt32 idx, UInt32 num, UInt32 value);
          void                 setBoolProperty  (UInt32 idx, UInt32 num, bool   value);
          void                 setVec3Property  (UInt32 idx, UInt32 num, const Vec3f&  value);
          void                 setVec4Property  (UInt32 idx, UInt32 num, const Vec4f&  value);
          void                 setMat4Property  (UInt32 idx, UInt32 num, const Matrix& value);
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
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   (DrawEnv    *pEnv,
                             UInt32      index = 0);

    virtual void changeFrom (DrawEnv    *pEnv,
                             StateChunk *pOld,
                             UInt32      index = 0);

    virtual void deactivate (DrawEnv    *pEnv,
                             UInt32      index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             OpenGL handling                                  */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static const UInt8 _numTypes;
    bool               _bUpdateBuffer;

    // Variables should all be in MultiPropertyUBOChunkBase.

    void onCreate      (const MultiPropertyUBOChunk *source      = NULL);
    void onCreateAspect(const MultiPropertyUBOChunk *createAspect,
                        const MultiPropertyUBOChunk *source      = NULL);
    void onDestroy     (      UInt32                 uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiPropertyUBOChunk(void);
    MultiPropertyUBOChunk(const MultiPropertyUBOChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiPropertyUBOChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiPropertyUBOChunkBase;

    /*---------------------------------------------------------------------*/
    /*! \name                         buffer                               */
    /*! \{                                                                 */
    std::size_t         calc_property_buffer_size  () const;
    std::vector<UInt8>  create_property_buffer     (DrawEnv* pEnv) const;
    void                create_property_state      (DrawEnv* pEnv);
    void                update_property_state      (DrawEnv* pEnv);

    /*! \}                                                                 */

    bool        check_invariant() const;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiPropertyUBOChunk &source);
};

typedef MultiPropertyUBOChunk *MultiPropertyUBOChunkP;

OSG_END_NAMESPACE

#include "OSGMultiPropertyUBOChunkBase.inl"
#include "OSGMultiPropertyUBOChunk.inl"

#endif /* _OSGMULTIPROPERTYUBOCHUNK_H_ */
