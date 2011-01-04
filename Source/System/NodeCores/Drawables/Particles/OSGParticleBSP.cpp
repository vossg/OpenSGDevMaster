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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGBaseFunctions.h"

#include "OSGNode.h"
#include "OSGParticleBSP.h"

#include "OSGParticles.h"

OSG_USING_NAMESPACE

/*! \class OSG::ParticleBSPTree

A very simple BSP tree, optimized for particle sorting.
*/

/*! \class OSG::ParticleBSPNode

A node of the ParticleBSPTree.
*/

/*----------------------- constructors & destructors ----------------------*/

ParticleBSPNode::ParticleBSPNode(void) :
    _axis()
{
}
    
ParticleBSPNode::ParticleBSPNode(const ParticleBSPNode &source) :
    _axis(source._axis)
{
    if(isLeaf())
    {
        _value = source._value;
    }
    else
    {
        _splitvalue = source._splitvalue;        
    }
}

ParticleBSPNode::ParticleBSPNode(UInt32 value) :
    _axis(Leaf),
    _value(value)
{
}

ParticleBSPNode::ParticleBSPNode(UInt8 axis, Real32 splitvalue) :
    _axis(axis),
    _splitvalue(splitvalue)
{
}

ParticleBSPNode::~ParticleBSPNode(void)
{
}

/*---------------------------------- output -------------------------------*/

void ParticleBSPNode::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    static const char *axisname = "XYZL";
    
    Real32 v = isLeaf()?_value:_splitvalue;
    
    PLOG << "(" << axisname[_axis] << " " << v << ")";
}


/*-------------------------------------------------------------------------*/
/*---------------------------- BSP Tree -----------------------------------*/
/*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleBSPTree::ParticleBSPTree(void)
{
}

ParticleBSPTree::~ParticleBSPTree(void)
{
} 

/*---------------------------------- output -------------------------------*/

void ParticleBSPTree::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    PLOG << "ParticleBSPTree(";

    if(!_tree.empty())
    {
        for(std::vector<ParticleBSPNode>::const_iterator i = _tree.begin() + 1;
            i != _tree.end(); ++i )
        {
            i->dump();
        }
    }   
    
    PLOG << ")" << std::endl;
}
    
#if 0
void ParticleBSPTree::putToString(std::string &outVal) const
{
    outVal.assign(TypeTraits<UInt32>::putToString(_tree.size()));
    outVal.append(";");
    
    if(! _tree.empty())
    {
        for(std::vector<ParticleBSPNode>::const_iterator i = _tree.begin() + 1;
            i != _tree.end(); ++i )
        {
            outVal.append(TypeTraits<UInt8>::putToString(i->getAxis()));
            outVal.append(":");
            if(i->isLeaf())
            {
                outVal.append(TypeTraits<Int32>::putToString(i->getValue()));
            }
            else
            {
                outVal.append(TypeTraits<Real32>::putToString(
                    i->getSplitValue()));
            }
            outVal.append(";");
        }   
    }
}
    
bool ParticleBSPTree::getFromString(const Char8 *&inVal)
{
    UInt32 size = TypeTraits<UInt32>::getFromString(inVal);
 
    const Char8 *c = strchr(inVal, ';');
    
    if(!c)
        return false;
    c++;
    
    _tree.resize(size);
    
    for(UInt32 i = 1; i < size; ++i)
    {
        UInt8 axis = TypeTraits<UInt8>::getFromString(c);
        c = strchr(c, ':');
        if(!c)
            return false;
        c++;
        
        if(axis == ParticleBSPNode::Leaf)
        {
            Int32 value = TypeTraits<Int32>::getFromString(c);
            _tree[i].setValue(value);
        }
        else
        {
            Real32 value = TypeTraits<Real32>::getFromString(c);
            _tree[i].setSplit(axis, value);           
        }
        c = strchr(c, ';');
        if(!c)
            return false;
        c++;
    }
    
    return true;
}
#endif

UInt32 ParticleBSPTree::getBinSize(void) const
{
    return sizeof(UInt32) // num elements
        + (sizeof(UInt8)+sizeof(UInt32)) * _tree.size();
}
    
void ParticleBSPTree::copyToBin(BinaryDataHandler &pMem) const
{
    UInt8  axis;
    Int32  value;
    Real32 splitvalue;
    UInt32 i;
    UInt32 size = _tree.size();
    pMem.putValue(size);

    for(i=0;i<size;++i)
    {
        axis=_tree[i].getAxis();
        pMem.putValue(axis);
        if(axis==ParticleBSPNode::Leaf)
        {
            value=_tree[i].getValue();
            pMem.putValue(value);
        }
        else
        {
            splitvalue=_tree[i].getSplitValue();
            pMem.putValue(splitvalue);
        }
    }
}
    
void ParticleBSPTree::copyFromBin(BinaryDataHandler &pMem)
{
    UInt8  axis;
    Int32  value;
    Real32 splitvalue;
    UInt32 i;
    UInt32 size;
    pMem.getValue(size);
    _tree.resize(size);

    for(i=0;i<size;++i)
    {
        pMem.getValue(axis);
        if(axis==ParticleBSPNode::Leaf)
        {
            pMem.getValue(value);
            _tree[i].setValue(value);
        }
        else
        {
            pMem.getValue(splitvalue);
            _tree[i].setSplit(axis, Real32(value));
        }
    }
}

bool ParticleBSPTree::operator ==(const ParticleBSPTree &source) const
{
    return false;
}

/*-------------------------------- traversal ------------------------------*/

Int32 *ParticleBSPTree::traverse(const Pnt3f &refPoint, UInt32 &length, 
                                 Int32 *order) const
{
    if(_tree.empty())
        return NULL;
        
    if(order == NULL)
    {
        order = new Int32 [length];
    }
    
    length = doTraverse(refPoint,1,0,order);
    
    return order;
}

UInt32 ParticleBSPTree::doTraverse(const Pnt3f &refPoint, UInt32 index, 
                                   UInt32 length, Int32 *order) const
{
    const ParticleBSPNode *n = &_tree[index];
    
    if(n->isLeaf())
    {
        order[length] = n->getValue();
        return ++length;
    }
    else
    {
        if(refPoint[n->getAxis()] > n->getSplitValue())
        {
            length = doTraverse(refPoint, index * 2    , length, order);
            length = doTraverse(refPoint, index * 2 + 1, length, order);
        }
        else
        {
            length = doTraverse(refPoint, index * 2 + 1, length, order);
            length = doTraverse(refPoint, index * 2    , length, order);
        }
    }
    return length;
}

Int32 *ParticleBSPTree::traverse(const Vec3f &refVec, UInt32 &length, 
                                 Int32 *order) const
{
    if(order == NULL)
    {
        order = new Int32 [length];
    }
    
    length = doTraverse(refVec,1,0,order);
    
    return order;
}

UInt32 ParticleBSPTree::doTraverse(const Vec3f &refVec, UInt32 index, 
                                   UInt32 length, Int32 *order) const
{
    const ParticleBSPNode *n = &_tree[index];
    
    if(n->isLeaf())
    {
        order[length] = n->getValue();
        return ++length;
    }
    else
    {
        if(refVec[n->getAxis()] > 0.f)
        {
            length = doTraverse(refVec, index * 2    , length, order);
            length = doTraverse(refVec, index * 2 + 1, length, order);
        }
        else
        {
            length = doTraverse(refVec, index * 2 + 1, length, order);
            length = doTraverse(refVec, index * 2    , length, order);
        }
    }
    return length;
}

/*--------------------------------- creation ------------------------------*/

void ParticleBSPTree::build(Particles *core)
{
    _tree.clear();
    
    if(core == NULL)
    {
        FWARNING(("ParticleBSP::build: no core!!\n"));
        return;
    }
    
    GeoVectorProperty * const pos = core->getPositions();
    
    if(pos == NULL)
        return;

    const MFInt32 *indices = core->getMFIndices();
        
    // 1. create list for particles
 
    std::vector<Int32> order;
    order.reserve(pos->getSize());
    
    for(UInt32 i = 0; i < pos->getSize(); ++i )
    {     
        if(indices->size() == pos->getSize())
        {        
            order.push_back((*indices)[i]);
        }
        else
        {
            order.push_back(i);            
        }
    }
    
    // reserve mem for tree
    
    _tree.resize(osgNextPower2(order.size()) * 2);
    
    // 2. recursively build the tree
    
    UInt32 nnodes = doBuild(order.begin(), order.end(), 1, pos);
    
    // 3. remove the unneeded elements from the end
    
    if(nnodes < _tree.size())
        _tree.erase( _tree.begin() + nnodes, _tree.end());

    // done
}

/*! \ingroup GrpDrawablesParticlesHelpers
    \nohierarchy
 */

struct ParticleCompare : public std::binary_function<Int32, Int32, bool> 
{
    ParticleCompare(GeoVectorProperty *pos, UInt8 axis) : 
        _pos(pos), 
        _axis(axis)
    {}
    
    bool operator()(Int32 x, Int32 y) 
    { 
        Pnt3f px,py;
        _pos->getValue(px, x);
        _pos->getValue(py, y);
        
        return px[_axis] < py[_axis]; 
    }
    
    GeoVectorProperty *_pos;
    UInt8              _axis;
};
    
UInt32 ParticleBSPTree::doBuild(std::vector<Int32>::iterator  begin, 
                                std::vector<Int32>::iterator  end,
                                     UInt32                   nodeindex,
                                     GeoVectorProperty       *pos)
{
    // reached a leaf?
    
    if(begin + 1 == end)
    {
        _tree[nodeindex].setValue(*begin);
        return nodeindex + 1;
    }
    
    // find the bounding volume of the group
    
    BoxVolume b;
    Pnt3f p;
    
    b.setEmpty();
    
    for(std::vector<Int32>::iterator i = begin; i != end; ++i)
    {
        pos->getValue(p,*i);     
        b.extendBy(p);
    }
    
    // find the axis with the longest extension
    
    Vec3f d = b.getMax() - b.getMin();
    
    UInt8 axis = ParticleBSPNode::X;
    Real32 maxval = d[0];
    
    if(d[1] > maxval)
    {
        axis = ParticleBSPNode::Y;
        maxval = d[1];
    }
    if(d[2] > maxval)
    {
        axis = ParticleBSPNode::Z;
        maxval = d[2];
    }

    // sort in that axis
    ParticleCompare comp(pos, axis);
    
    std::sort(begin,end,comp);
    
    // find median value
    std::vector<Int32>::iterator mid = begin + (end - begin) / 2;
    
    Pnt3f p2;
    pos->getValue(p ,*mid);
    pos->getValue(p2,(*mid)-1);
    _tree[nodeindex].setSplit(axis, (p[axis] + p2[axis]) / 2.f);
    
    return osgMax( doBuild(begin, mid, nodeindex * 2    , pos),
                   doBuild(  mid, end, nodeindex * 2 + 1, pos) );   
}   


void ParticleBSPTree::destroy()
{
    _tree.clear();
}


#include "OSGSField.ins"
#include "OSGMField.ins"

OSG_BEGIN_NAMESPACE

/*-------------------------- field instantiations -------------------------*/

DataType FieldTraits<ParticleBSPTree>::_type("ParticleBSPTree", 
                                             "TypeRoot");

OSG_FIELDTRAITS_GETTYPE(ParticleBSPTree)

OSG_FIELD_DLLEXPORT_DEF1(SField, ParticleBSPTree);

OSG_END_NAMESPACE

