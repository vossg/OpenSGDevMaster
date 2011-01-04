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

#ifndef _OSGPARTICLEBSP_H_
#define _OSGPARTICLEBSP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGParticlesFields.h"

#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE
 
class ParticleBSPTree;

/*! \brief Particle BSP Tree Node
    \ingroup GrpDrawablesParticlesHelpers
    \nohierarchy
 */

class OSG_DRAWABLE_DLLMAPPING ParticleBSPNode
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Axis
    { 
        X = 0, 
        Y, 
        Z, 
        Leaf 
    };
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleBSPNode(void);
    ParticleBSPNode(const ParticleBSPNode &source);

    ParticleBSPNode(UInt32 value);
    ParticleBSPNode(UInt8  axis, 
                    Real32 splitvalue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~ParticleBSPNode(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access                                   */
    /*! \{                                                                 */

    bool   isLeaf       (void             ) const;
    Int32  getValue     (void             ) const;
    Real32 getSplitValue(void             ) const;
    UInt8  getAxis      (void             ) const;

    void   setValue     (Int32  value     );
    void   setSplit     (UInt8  axis, 
                         Real32 splitvalue);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void dump(      UInt32     uiIndent = 0, 
              const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    /*==========================  PRIVATE  ================================*/

  private:

    UInt8 _axis;

    union
    {
        Int32   _value;   
        Real32  _splitvalue;
    };
};

/*! \brief Particle BSP Tree 
    \ingroup GrpDrawablesParticlesHelpers
    \nohierarchy
 */

class OSG_DRAWABLE_DLLMAPPING ParticleBSPTree
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleBSPTree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleBSPTree(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Creation / Deletion                            */
    /*! \{                                                                 */

    bool created(void) const;
    
    void build  (Particles *core);
    
    void destroy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Traversal                                 */
    /*! \{                                                                 */

    Int32 *traverse(const Pnt3f  &refPoint, 
                          UInt32 &length, 
                          Int32  *order = NULL) const; 

    Int32 *traverse(const Vec3f  &refVec, 
                          UInt32 &length, 
                          Int32  *order = NULL) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Input / Output                               */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
    
    void putToString(std::string &outVal) const;
     
    bool getFromString(const Char8 *&inVal);
   
   /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Input / Output                               */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;

    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Input / Output                               */
    /*! \{                                                                 */

    bool operator ==(const ParticleBSPTree &source) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                 Node Traversal                               */
    /*! \{                                                                 */

    UInt32 doTraverse(const Pnt3f  &refPoint, 
                            UInt32  index, 
                            UInt32  length, 
                            Int32  *order  ) const; 

    UInt32 doTraverse(const Vec3f  &refVec, 
                            UInt32  index, 
                            UInt32  length, 
                            Int32  *order  ) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Creation Tools                               */
    /*! \{                                                                 */

    UInt32 doBuild(std::vector<Int32>::iterator  begin, 
                   std::vector<Int32>::iterator  end,
                        UInt32                   nodeindex,
                        GeoVectorProperty       *pos      ); 

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    
    std::vector<ParticleBSPNode> _tree;
};


/*! \ingroup GrpDrawablesParticlesFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<ParticleBSPTree> : 
    public FieldTraitsTemplateBase<ParticleBSPTree>
{
  private:

    static DataType       _type;

  public:

    typedef FieldTraits<ParticleBSPTree>  Self;

    enum                  { Convertible = 0x00    };

    static OSG_DRAWABLE_DLLMAPPING 
           DataType       &getType      (void);

    static const Char8    *getSName     (void) { return "SFParticleBSPTree"; }
    static const Char8    *getMName     (void) { return "MFParticleBSPTree"; }

    static ParticleBSPTree getDefault   (void) { return ParticleBSPTree();   }

/*
    static bool            getFromString(      ParticleBSPTree  &outVal,
                                         const Char8           *&inVal)
    {
        return outVal.getFromString(inVal);
    }

    static void           putToString   (const      ParticleBSPTree &inVal,
                                               std::string          &outVal)
    {
        inVal.putToString(outVal);
    }
 */ 
   
    static UInt32 getBinSize(const ParticleBSPTree &oObject)
    {
        return oObject.getBinSize();
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const ParticleBSPTree     &oObject)
    {
       oObject.copyToBin(pMem);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ParticleBSPTree     &oObject)
    {
        oObject.copyFromBin(pMem);
    }
};


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpDrawablesParticlesFieldSFields */
typedef SField<ParticleBSPTree> SFParticleBSPTree;
#else
/*! \ingroup GrpDrawablesParticlesFieldSFields \ingroup GrpLibOSGDrawables */
struct SFParticleBSPTree : public SField<ParticleBSPTree> {};
#endif


OSG_END_NAMESPACE

#include "OSGParticleBSP.inl"

#endif /* _OSGPARTICLES_H_ */
