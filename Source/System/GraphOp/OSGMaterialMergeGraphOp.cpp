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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <sstream>

#include "OSGMaterialMergeGraphOp.h"
#include "OSGGraphOpFactory.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MaterialMergeGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
Merges equivalent materials in a scene.
*/

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpFactory::the()->registerOp(new MaterialMergeGraphOp);
    return true;
}
static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);


MaterialMergeGraphOp::MaterialMergeGraphOp(const char* name)
    : GraphOp(name)
{
}

MaterialMergeGraphOp::~MaterialMergeGraphOp(void)
{
}

GraphOp* MaterialMergeGraphOp::create()
{
    return new MaterialMergeGraphOp();
}


// Similar to boost's next iterator function.  (I think it's from
// boost, at least.)
template<typename T>
T next(T t) { // Iterator passed by value.
    ++t;
    return t;
}


bool isEqual(const FieldContainerPtr a, const FieldContainerPtr b)
{
    // Compare the pointers.
    if(a == b)
        return true;

    if(a == NullFC || b == NullFC)
        return false;

    if(a->getType() != b->getType())
        return false;
    
    //printf("comparing: %s\n", a->getType().getName().str());

    const FieldContainerType &type = a->getType();
    UInt32 fcount = type.getNumFieldDescs();
    
    for(UInt32 i=1;i <= fcount;++i)
    {
        GetFieldHandlePtr fhandlea = a->getField(i);
        GetFieldHandlePtr fhandleb = b->getField(i);
        
        if(fhandlea == NULL || fhandleb == NULL || (fhandlea != NULL &&
                                                    fhandlea->isInternal()))
        {
            continue;
        }

        const FieldType &a_ftype = fhandlea->getType();
        const FieldType &b_ftype = fhandleb->getType();

        if(a_ftype != b_ftype)
            return false;


        // ignore attachments
        if(strcmp(fhandlea->getName().c_str(), "attachments") == 0)
            continue;
        

        FieldContainerPtrSFieldBase::GetHandlePtr sfPtrHandleA =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(fhandlea);

        FieldContainerPtrMFieldBase::GetHandlePtr mfPtrHandleA =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(fhandlea);

        if(sfPtrHandleA == NULL || mfPtrHandleA == NULL)
        {
            if(fhandlea->equal(fhandleb) == false)
                return false;

#if 0
            // This is very slow with multi fields!!!!
            std::ostringstream as;
            OutStream outAS(as);
            fhandlea.pushValueToStream(outAS);

            std::ostringstream bs;
            OutStream outBS(bs);
            fhandleb.pushValueToStream(outBS);
            if(as != bs)
                return false;
#endif
        }
        else
        {
            if(sfPtrHandleA != NULL && sfPtrHandleA->isValid() == true)
            {
                FieldContainerPtrSFieldBase::GetHandlePtr sfPtrHandleB =
                    boost::dynamic_pointer_cast<
                        FieldContainerPtrSFieldBase::GetHandle>(fhandleb);

                if(isEqual((*sfPtrHandleA)->getValue(),
                           (*sfPtrHandleB)->getValue()) == false)
                {
                    return false;
                }
            }
            else if(mfPtrHandleA != NULL && mfPtrHandleA->isValid() == true)
            {
                FieldContainerPtrMFieldBase::GetHandlePtr mfPtrHandleB =
                    boost::dynamic_pointer_cast<
                        FieldContainerPtrMFieldBase::GetHandle>(fhandleb);

                if((*mfPtrHandleA)->size() !=
                   (*mfPtrHandleB)->size())
                {
                    return false;
                }

                for(UInt32 j = 0; j < (*mfPtrHandleA)->size(); ++j)
                {
                    if(isEqual((*(*mfPtrHandleA))[j],
                               (*(*mfPtrHandleB))[j]) == false)
                    {
                        return false;
                    }
                }

           }
#if 0
            if(fhandlea.getCardinality() == FieldType::SINGLE_FIELD)
            {
                if(!isEqual(((SFFieldContainerPtr *) fhandlea.getField())->getValue(),
                            ((SFFieldContainerPtr *) fhandleb.getField())->getValue()))
                    return false;
            }
            else if(fhandlea.getCardinality() == FieldType::MULTI_FIELD)
            {
                if(((MFFieldContainerPtr*)fhandlea.getField())->size() !=
                   ((MFFieldContainerPtr*)fhandleb.getField())->size())
                    return false;
    
                for(UInt32 j=0;j < ((MFFieldContainerPtr*)fhandlea.getField())->size();++j)
                {
                    if(!isEqual((*(((MFFieldContainerPtr *)fhandlea.getField())))[j],
                                (*(((MFFieldContainerPtr *)fhandleb.getField())))[j]))
                        return false;
                }
            }
#endif
        }
    }

    return true;
}


bool equal(MaterialPtr a, MaterialPtr b) {
    // It's too bad Material::operator== doesn't work.
    //return *a == *b;
    return isEqual(a, b);
}


bool MaterialMergeGraphOp::traverse(NodePtr node)
{
    // Find the materials.
    if (!GraphOp::traverse(node)) {
        return false;
    }

    SINFO << "Number of materials before merge: " 
          << _materialObjects.size() << std::endl;

    // Now do the merge.
    MaterialObjectMap::iterator itr = _materialObjects.begin();
    for (; itr != _materialObjects.end(); ++itr)
    {
        MaterialPtr current = itr->first;
        MaterialObjectList& currentList = itr->second;

        MaterialObjectMap::iterator walker = next(itr);
        while (walker != _materialObjects.end()) {
            // Store the next iterator in case we have to delete
            // 'walker' from the map.
            MaterialObjectMap::iterator nextStep = next(walker);

            if (equal(current, walker->first)) {
                // Set the new objects to have the current material,
                // and move the objects to the current list.
                MaterialObjectList::iterator i = walker->second.begin();
                for (; i != walker->second.end(); ++i) {
                    i->setMaterial(current);
                    currentList.push_back(*i);
                }
                _materialObjects.erase(walker);
            }

            walker = nextStep;
        }
    }

    SINFO << "Number of materials after merge: " << _materialObjects.size() << std::endl;
    return true;
}


void MaterialMergeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("MaterialMergeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string MaterialMergeGraphOp::usage(void)
{
    return 
    "MaterialMerge: merge Materials in given subtree\n"
    "  Tries to find and merge equiavlent Materials to reduce the number\n"
    "  of Materials used.\n"
    ;
}

Action::ResultE MaterialMergeGraphOp::traverseEnter(NodePtrConstArg node)
{
    GeometryPtr geo = dynamic_cast<GeometryPtr>(node->getCore());
    if (geo != NullFC)
    {
        addObject(MaterialObject(geo));
        return Action::Continue;
    }
    
    MaterialGroupPtr mg = dynamic_cast<MaterialGroupPtr>(node->getCore());
    if (mg != NullFC)
    {
        addObject(MaterialObject(mg));
        return Action::Continue;
    }

    // Otherwise, keep looking.
    return Action::Continue;
}

Action::ResultE MaterialMergeGraphOp::traverseLeave(NodePtrConstArg node, Action::ResultE res)
{
    return res;
}

void MaterialMergeGraphOp::addObject(MaterialObject m)
{
    MaterialPtr mat = m.getMaterial();
    if (mat == NullFC)
        return;

    _materialObjects[mat].push_back(m);
}

OSG_END_NAMESPACE
