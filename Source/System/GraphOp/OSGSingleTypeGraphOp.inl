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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SingleTypeGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

template < class Type > inline
SingleTypeGraphOp<Type>::SingleTypeGraphOp(const char* name): GraphOp(name)
{
}

template < class Type > inline
SingleTypeGraphOp<Type>::~SingleTypeGraphOp(void)
{
}

template < class Type > inline
Action::ResultE SingleTypeGraphOp<Type>::traverseEnter(Node *node)
{
    if(node->getCore()->getType().isDerivedFrom(Type::getClassType()))
        travNodeEnter(node);
    return Action::Continue;
}

template < class Type > inline
Action::ResultE SingleTypeGraphOp<Type>::traverseLeave(
    Node *node, 
    Action::ResultE)
{
    if(node->getCore()->getType().isDerivedFrom(Type::getClassType()))
        travNodeLeave(node);
    return Action::Continue;
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*------------------------------------------------------------------------*/

OSG_END_NAMESPACE
