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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderTreeNodePool.h"
#include "OSGScalarSortTreeBuilder.h"
#include "OSGBaseFunctions.h"
#include "OSGRenderPartition.h"

//#define OSG_DUMP_SORTING

OSG_USING_NAMESPACE

/*! \class OSG::ScalarSortTreeBuilder
    \ingroup 
 */

ScalarSortTreeBuilder ScalarSortTreeBuilder::Proto;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


ScalarSortTreeBuilder::ScalarSortTreeBuilder(void)
{
}

ScalarSortTreeBuilder::~ScalarSortTreeBuilder(void)
{
}


void ScalarSortTreeBuilder::reset(void)
{
    TreeBuilderBase::reset();
}


void ScalarSortTreeBuilder::add(DrawEnv &denv, 
                                RenderPartition *part,
                                RenderTreeNode *pNode,
                                State          *pState,
                                StateOverride  *pStateOverride,
                                UInt32          uiKeyGen      )
{
    if(_pRoot == NULL)
    {
        _pRoot = _pNodePool->create();
    }

    if(_pRoot->getFirstChild() == NULL)
    {
        _pRoot->addChild(pNode);
    }
    else
    {
        RenderTreeNode *pCurrent = _pRoot->getFirstChild();

        RenderTreeNode *pLast    = NULL;
        bool            bFound   = false;

        do
        {
            if(pNode->getScalar() > pCurrent->getScalar())
            {
                pLast    = pCurrent;
                pCurrent = pCurrent->getBrother();
            }
            else
            {
                bFound = true;
            }

        } while(bFound   == false && 
                pCurrent != NULL    );

        if(bFound == true)
        {
            if(pLast == NULL)
            {
                _pRoot->insertFirstChild(pNode);
            }
            else
            {
                _pRoot->insertChildAfter(pLast, pNode);
            }
        }
        else
        {
            _pRoot->addChild(pNode);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGScalarSortTreeBuilder.cpp 142 2006-09-18 08:49:39Z vossg $";
    static Char8 cvsid_hpp[] = OSGSCALARSORTTREEBUILDER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSCALARSORTTREEBUILDER_INLINE_CVSID;
}

#endif
