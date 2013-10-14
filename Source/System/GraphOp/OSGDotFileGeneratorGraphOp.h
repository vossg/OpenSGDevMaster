/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#ifndef _OSGDOTFILEGENERATORGRAPHOP_H_
#define _OSGDOTFILEGENERATORGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include <boost/scoped_ptr.hpp>
#include <set>

#include "OSGConfig.h"
#include "OSGUtilDef.h"
#include "OSGGraphOp.h"
#include "OSGMaterial.h"
#include "OSGImage.h"
#include "OSGStateChunk.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpContribDataSolidGraphOp
    \ingroup GrpLibOSGContribDataSolid
 */

class OSG_UTIL_DLLMAPPING DotFileGeneratorGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */
    
    typedef GraphOp           Inherited;
    typedef DotFileGeneratorGraphOp Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(DotFileGeneratorGraphOp);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Classname                                                    */
    /*! \{                                                                 */
    
    static const char *getClassname(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(void);

    virtual GraphOpTransitPtr clone (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    void        setParams(const std::string  params              );

    std::string usage    (      void                             );
    
    void        insert   (const TypeBase    *t, 
                                bool         derived_from = false);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructors                                     */
    /*! \{                                                                 */

             DotFileGeneratorGraphOp(const char *name = "DotFileGenerator");
    virtual ~DotFileGeneratorGraphOp(      void                           );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    Action::ResultE  traverseEnter(Node            * const node);
    Action::ResultE  traverseLeave(Node            * const node, 
                                   Action::ResultE         res );
  
    std::ofstream   &initialize   (void                        );
    void             deinitialize (void                        );
  
    std::string      space        (void                        );
  
    struct Info
    {
        Info(void);
        ~Info(void);

        int         cnt;
        std::string label;
        std::string name;
        std::string id;
        std::string fontcolor;
        void*       obj_id;
        bool        finished;
    };
    
    struct BrewerColor 
    {
        BrewerColor(const std::string &scheme, const std::string &number);
        ~BrewerColor(void);

        std::string scheme;
        std::string number;
    };
    
    class Colors
    {
      public:

        const BrewerColor &color(      void               ) const;
        
              void         add  (const std::string &scheme, 
                                       UInt32       start, 
                                       UInt32       end   );
    
        Colors(void);
        ~Colors(void);

    private:

        typedef std::vector<BrewerColor> VecColorsT;
    
                VecColorsT  _colors;
        mutable std::size_t _current;
    };
    
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructors                                     */
    /*! \{                                                                 */

    const BrewerColor &getColor(const std::string& domain, 
                                const std::string& name);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    Info &NodeInfo        (      Node                * const node          );
    Info &CoreInfo        (      NodeCore            * const core          );
    Info &AttachmentInfo  (      Attachment          * const node          );
    Info &MaterialInfo    (      Material            * const material      );
    Info &ImageInfo       (      Image               * const image         );
    Info &StateChunkInfo  (      StateChunk          * const chunk         );
    Info &IntegralPropInfo(      GeoIntegralProperty * const property, 
                           const char                *       context = NULL);
    Info &VectorPropInfo  (      GeoVectorProperty   * const property, 
                           const char                *       context = NULL);
    Info  MatrixInfo      (const Matrix              &       matrix, 
                                 void                *       handler       );
    Info  EtceteraInfo    (      UInt32                      number        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    bool hasInfo   (void *handler) const;
    bool hasEdge   (const Info& src, const Info& dst) const;
    bool makeEdge  (const Info& src, const Info& dst);
    
    void OpenGroup (bool  rank   );
    void CloseGroup(void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    void DefineNode          (const Info        &info             );
    void DefineCore          (const Info        &info             );
    void DefineAttachment    (const Info        &info             );
    void DefineMaterial      (const Info        &info             );
    void DefineMatrix        (const Info        &info             );
    void DefineImage         (const Info        &info             );
    void DefineStateChunk    (const Info        &info             );
    void DefineProperty      (const Info        &info             );
    void DefineEtceteraNode  (const Info        &info             );
    
    void DefineHoldingEdge   (const Info        &src_info,
                              const Info        &dst_info         );
    void DefineNodeEdge      (const Info        &parent_info, 
                              const Info        &node_info        );
    void DefineCoreEdge      (const Info        &node_info,   
                              const Info        &core_info        );
    void DefineAttachmentEdge(const Info        &node_info,   
                              const Info        &att_info         );
    void DefineSimpleEdge    (const Info        &src_info,    
                              const Info        &dst_info, 
                                    bool         constraint = true, 
                                    std::string  attribute  = ""  );
    void DefineDottedEdge    (const Info        &src_info,    
                              const Info        &dst_info, 
                                    bool         constraint = true, 
                                    std::string  attribute  = ""  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    void HandleAttachment    (      AttachmentContainer * const fc, 
                              const Info                &       info    );
    void HandleMaterial      (      NodeCore            * const core, 
                              const Info                &       info    );
    void HandleTransform     (      NodeCore            * const core, 
                              const Info                &       info    );
    void HandleGeometry      (      NodeCore            * const core, 
                              const Info                &       info    );
    void HandleLight         (      NodeCore            * const core, 
                              const Info                &       info    );
    void HandleVisitSubTree  (      NodeCore            * const core,
                              const Info                &       info    );
    void HandleChunkMaterial (      Material            * const material, 
                              const Info                &       info    );
    void HandleSwitchMaterial(      Material            * const material, 
                              const Info                &       info    );
    void HandleMultiPassMaterial(   Material            * const material, 
                              const Info                &       info    );
    void HandleTextureChunk  (      StateChunk          * const chunk, 
                              const Info                &       info    );
    void HandleBeaconedChunk (      StateChunk          * const chunk, 
                              const Info                &       info    );
    
    bool isSuppressed        (const TypeBase            &t              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    typedef std::map   <const void        *, Info       > MapInfoT;
    typedef std::map   <      std::string,   Colors     > MapColorsT;
    typedef std::map   <      std::string,   BrewerColor> MapUsedColorsT;
    typedef std::vector<const TypeBase    *             > VecTypesT;
    typedef std::pair  <      Info,          Info       > PairInfoT;
    typedef std::vector<      PairInfoT                 > VecEdgesT;
    typedef std::pair  <      const void*,   const void*> PairObjIdsT;

    struct lessPairObjIdsT : public std::binary_function<const PairObjIdsT,
                                                         const PairObjIdsT,
                                                         bool              >
    {
        bool operator()(const PairObjIdsT& lhs, const PairObjIdsT& rhs) const
        {
            return (lhs.first <  rhs.first) ||
                   (lhs.first == rhs.first && lhs.second < rhs.second);
        }
    };

    typedef std::set<PairObjIdsT, lessPairObjIdsT>        SetObjIdsT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
    
    // The output dot file name
    std::string                         _filename;           

    // Include attechments in the graph separately           
    bool                                _include_attachment; 

    // Do not include name attachments
    bool                                _no_name_attachments;           

    // Do not use rank statement
    bool                                _no_ranks;

    // Maximal number of children of a node included in the graph
    Int32                               _max_node_children; 

    // size attribute of graph
    std::string                         _size;                   

    // ranksep attribute of graph
    std::string                         _ranksep; 

    // nodesep attribute of graph
    std::string                         _nodesep;           

    // arbitrary graph attribute entry            
    std::string                         _graph_attributes; 

    boost::scoped_ptr<std::ofstream>    _spStream;       
    MapInfoT                            _mapInfo;
    UInt32                              _node_cnt;
    UInt32                              _core_cnt;
    UInt32                              _attachment_cnt;
    UInt32                              _material_cnt;
    UInt32                              _matrix_cnt;
    UInt32                              _image_cnt;
    UInt32                              _chunk_cnt;
    UInt32                              _integral_prop_cnt;
    UInt32                              _vector_prop_cnt;
    UInt32                              _space;
    MapColorsT                          _colors;
    MapUsedColorsT                      _usedColors;
    VecTypesT                           _suppressed;
    VecTypesT                           _suppressed_derived;
    VecEdgesT                           _dotted_edges;
    SetObjIdsT                          _edges;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_GEN_MEMOBJPTR(DotFileGeneratorGraphOp);

OSG_END_NAMESPACE

#endif // _OSGDOTFILEGENERATORGRAPHOP_H_



