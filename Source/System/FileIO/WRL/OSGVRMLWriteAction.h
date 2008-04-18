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

#ifndef _OSGVRMLWRITEACTION_H_
#define _OSGVRMLWRITEACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>
#include <map>

#include "OSGFileIODef.h"
#include "OSGBaseTypes.h"
#include "OSGAction.h"
#include "OSGGeometry.h"
#include "OSGGroup.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Node;
class Action;
class Material;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief DrawAction class
 */

class OSG_FILEIO_DLLMAPPING VRMLWriteAction : public Action
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum TraversalMode
    {
        OSGCollectFC = 0x0001,
        OSGWrite     = 0x0002
    };

    enum WriterOption
    {
        OSGNoOptions        = 0x0000,
        OSGNoIndent         = 0x0001,
        OSGNoNormals        = 0x0002,
        OSGPixelTextures    = 0x0004
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VRMLWriteAction"; };

    // create a new DrawAction by cloning the prototype
    static VRMLWriteAction * create( void );
    
    // prototype access
    // after setting the prototype all new DrawActions are clones of it
    static void             setPrototype(VRMLWriteAction * proto);
    static VRMLWriteAction *getPrototype(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLWriteAction(void); 

    /*------------------------- your_category -------------------------------*/
    
    // default registration. static, so it can be called during static init
    
    static void registerEnterDefault(   const FieldContainerType &type, 
                                        const Functor            &func);
    
    static void registerLeaveDefault(   const FieldContainerType &type, 
                                        const Functor            &func);

    
    // rendering state handling
    
    MaterialPtr    getMaterial(void) const;
    void           setMaterial(MaterialPtr material);

    FILE          *getFilePtr(void) const;
    TraversalMode  getMode   (void) const;

    /*------------------------- your_operators ------------------------------*/

    bool open (const Char8 *szFilename);
    void close(void);

    /*------------------------- assignment ----------------------------------*/

    void   addOptions(UInt32 uiOptions);
    void   subOptions(UInt32 uiOptions);

    UInt32 getOptions(void            );

    virtual Action::ResultE write(NodePtr node);

    /*------------------------- comparison ----------------------------------*/

    bool operator < (const VRMLWriteAction &other) const;
    
    bool operator == (const VRMLWriteAction &other) const;
    bool operator != (const VRMLWriteAction &other) const;

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // access default functors

    virtual std::vector<Functor> *getDefaultEnterFunctors( void );
    virtual std::vector<Functor> *getDefaultLeaveFunctors( void );

    virtual Action::ResultE apply(std::vector<NodePtr>::iterator begin, 
                                  std::vector<NodePtr>::iterator end);

    virtual Action::ResultE apply(NodePtr node);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Action Inherited;

    struct ActionInitializer
    {
        ActionInitializer(void);
        ~ActionInitializer(void);
    };

    struct FCInfo
    {
      private:

        Int32  _iTimesUsed;
        bool   _bOwnName;
        Char8 *_szName;
        bool   _bWritten;

      public:

        FCInfo(void);
        FCInfo(const FCInfo &source);
        ~FCInfo(void);

        Char8 mapChar    (      Char8 c);
        void  convertName(      Char8 *&szName);

        void setName    (const Char8  *szName);
        void buildName  (const Char8  *szTypename,
                             UInt32  uiContainerId);
        void incUse     (void);
        
              UInt32  getUse (void) const;
        const Char8  *getName(void) const;

        bool  getWritten(void) const;
        void  setWritten (void);

        // returnvalue required by MS
        Int32 clear    (void);
    };

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend struct ActionInitializer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    // the prototype which is copied to create new actions
    static VRMLWriteAction * _prototype;

    // default functors for instantiation
    static std::vector<Functor> *_defaultEnterFunctors;
    static std::vector<Functor> *_defaultLeaveFunctors;
    
    static ActionInitializer _actionInitializer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------


    static Action::ResultE writeGroupEnter(const NodeCorePtr pGroup,
                                           Action *pAction);
    static Action::ResultE writeGroupLeave(const NodeCorePtr pGroup,
                                           Action *pAction);

    static Action::ResultE writeMatGroupEnter(const NodeCorePtr pGroup,
                                              Action *pAction);
    static Action::ResultE writeMatGroupLeave(const NodeCorePtr pGroup,
                                              Action *pAction);

    static Action::ResultE writeComponentTransformEnter(const NodeCorePtr pGroup,
                                                        Action *pAction);
    static Action::ResultE writeComponentTransformLeave(const NodeCorePtr pGroup,
                                                        Action *pAction);

    static Action::ResultE writeTransformEnter(const NodeCorePtr pGroup,
                                               Action *pAction);
    static Action::ResultE writeTransformLeave(const NodeCorePtr pGroup,
                                               Action *pAction);

    static void writePoints   (      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);
    static void writeNormals  (      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);
    static void writeColors   (      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);
    static void writeTexCoords(      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);

    static void writeIndex    (      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);

    static void writeLineIndex(      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);

    static void writeMaterial (      GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);

    static bool writeGeoCommon(      NodePtr          pNode,
                                     GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter,
                               const Char8           *setTypename);

    static void writePointSet (      NodePtr          pNode,
                                     GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter);

    static void writeLineSet  (      NodePtr          pNode,
                                     GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter,
                                     bool             bSinglePrimitiveGeo);

    static void writeFaceSet  (      NodePtr          pNode,
                                     GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter,
                                     bool             bSinglePrimitiveGeo);

    static Action::ResultE writeGeoEnter(const NodeCorePtr pGroup, Action *pAction);
    static Action::ResultE writeGeoLeave(const NodeCorePtr pGroup, Action *pAction);

    static bool initializeAction(void);
    static bool terminateAction (void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    MaterialPtr          _material;

    UInt32               _uiIndent;
    FILE                *_pFile;

    TraversalMode        _eTraversalMode;
    bool                 _currentUse;
    UInt32               _uiOptions;

    //std::vector<FCInfo>  _vFCInfos;
    typedef std::map<UInt32, FCInfo *> FCInfosMap;
    FCInfosMap _vFCInfos;

    // this is a quick hack to get material sharing to work. 
    // I don't understand the reasoning and design of the FCInfo stuff and 
    // don't have time to do it right. :( DR 040106
    std::vector<FieldContainerPtr>        _writtenFCs;

    UInt32 _nodeCount;
    UInt32 _currentNodeCount;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    VRMLWriteAction(void);
    VRMLWriteAction(const VRMLWriteAction &source);
    VRMLWriteAction& operator =(const VRMLWriteAction &source);

    void incIndent  (UInt32 uiDelta);
    void decIndent  (UInt32 uiDelta);
    void printIndent(void);

    void    setCurrentUse  (bool bVal                    );
    bool    isCurrentUse   (void                         );

    void    addNodeUse     (NodePtr           &pNode     );
    void    addContainerUse(FieldContainerPtr  pContainer);

    void    clearInfos     (void);
    FCInfo *getInfo        (FieldContainerPtr pContainer);

    void    updateProgress (void                         );

    inline bool        isWritten (FieldContainerPtr fc);
    inline UInt32      getIndex  (FieldContainerPtr fc);
    inline UInt32      setWritten(FieldContainerPtr fc);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef VRMLWriteAction *VRMLWriteActionP;

OSG_END_NAMESPACE

#include "OSGVRMLWriteAction.inl"

#endif /* _OSGVRMLWRITEACTION_H_ */
