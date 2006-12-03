/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGStateChunk.h"
#include "OSGLog.h"


OSG_BEGIN_NAMESPACE

struct StateChunkClassCompare
{
    bool operator()(const StateChunkClass *lhs, 
                    const StateChunkClass *rhs)
    {
        return lhs->getPriority() < rhs->getPriority();
    }
};

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGStateChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGStateChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/*! \class OSG::StateChunkClass
    \ingroup GrpSystemState

See \ref StateChunkClass for the
conceptual background.

*/

/*! \var OSG::StateChunkClass::_classId
    The numerical ID associated with each StateChunkClass. It is used to
    uniquely identify and quickly compare the class.
    
    \dev The classId is consecutive in the number of slots allocated to the
    chunk class, i.e. if a class has id 4 and 4 chunks, the next registered
    class will get id 8. The classId is used as an index into the OSG::State's
    chunk vector, which necessitates this behaviour. \enddev
*/   

std::vector<StateChunkClass *> *StateChunkClass::_classes     = NULL;
std::vector<StateChunkClass *> *StateChunkClass::_initClasses = NULL;

/*! The global vector of known StateChunkClasses' number of concurrently
    active slots. Use StateChunkClass::getNumSlots with the Class's ID to access
    it.
    
    \dev See the OSG::StateChunkClass::_classId for details. \enddev
*/   

std::vector<UInt32                     > *StateChunkClass::_numslots   = NULL;


bool StateChunkClass::terminate(void)
{
    delete _classes;
    delete _initClasses;
    delete _numslots;

    return true;
}

bool StateChunkClass::initialize(void)
{
    std::stable_sort(_initClasses->begin    (),
                     _initClasses->end      (),
                      StateChunkClassCompare());

    _classes  = new std::vector<StateChunkClass *>;
    _numslots = new std::vector<     UInt32      >;

    for(UInt32 i = 0; i < _initClasses->size(); ++i)
    {
        (*_initClasses)[i]->_classId = _classes->size();

        for(UInt32 j = 0; j < (*_initClasses)[i]->_numSlots; ++j)
        {
            _classes ->push_back((*_initClasses)[i]);
            _numslots->push_back((*_initClasses)[i]->_numSlots);
        }
    }

    for(UInt32 i = 0; i < _classes->size(); ++i)
    {
        FDEBUG_GV(("[%d][%d] %s %d %d\n",
                   i,
                   (*_classes)[i]->_classId,
                   (*_classes)[i]->_className.c_str(),
                   (*_classes)[i]->_priority,
                   (*_classes)[i]->_numSlots));
    }

    return true;
}

OSG_BEGIN_NAMESPACE

StateChunkClass::StateChunkClassInit StateChunkClass::InitHelper;

OSG_END_NAMESPACE

/*! Constructor. The name is mandatory, the number of concurrently active slots
    is optional, default is 1. 
*/

StateChunkClass::StateChunkClass(Char8  *name, 
                                 UInt32  numslots,
                                 UInt32  priority) : 
    _classId  (       0),
    _numSlots (numslots),
    _priority (priority),
    _className(    name)
{
    if(!_initClasses)
    {
        _initClasses = new std::vector<StateChunkClass *>;

        addPostFactoryExitFunction(&StateChunkClass::terminate); 
    }

    _initClasses->push_back(this);
}

const Char8 *StateChunkClass::getName(void) const
{
    return _className.c_str();
}

Int32 StateChunkClass::getNumSlots(void) const
{
    return(*_numslots)[_classId];
}

/*! Access the name for the class whose id is index. 
*/

const Char8 *StateChunkClass::getName(UInt32 index)
{
    if(index >=(*_classes).size())
            return "<Unknown StatChunkClass!>";

    return(*_classes)[index]->_className.c_str();
}


/*! \var OSG::StateChunkClass::iterator

    Iterator type to access the chunk class list.
*/

/*! Iterator to allow access to all known StateChunkClasses. 
*/

StateChunkClass::iterator StateChunkClass::begin(void)
{
    return _classes->begin();
}

/*! Iterator to allow access to all known StateChunkClasses. 
*/

StateChunkClass::iterator StateChunkClass::end(void)
{
    return _classes->end();
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StateChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

StateChunk::StateChunk(void) :
    Inherited()
{
}

StateChunk::StateChunk(const StateChunk &source) :
    Inherited(source)
{
}

StateChunk::~StateChunk(void)
{
}

UInt16 StateChunk::getChunkId(void)
{
    return 0;
}

/*------------------------------- Sync -----------------------------------*/

void StateChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void StateChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump StateChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

#ifdef OSG_OLD_RENDER_ACTION_ACTIVATE

/*! Activate the chunk, i.e. set the OpenGl state covered by the chunk which is
    different from the default state to the given state.
 */

void StateChunk::activate(DrawActionBase *OSG_CHECK_ARG(action), 
                          UInt32          OSG_CHECK_ARG(index ))
{
    FWARNING(("StateChunk::activate called!\n"));
}

/*! Change from an old chunk of the same type to this chunk. Note that in
    general no type checking is done, make sure to use this on a legal 
    combination of chunks!
 */

void StateChunk::changeFrom(DrawActionBase *action, 
                            StateChunk     *old, 
                            UInt32          index)
{
    old->deactivate(action, index);
    activate(action, index);
}

/*! Deactivate the chunk, i.e. set the OpenGl state covered by the chunk
    which is
    different from the default state to the default state.
 */

void StateChunk::deactivate(DrawActionBase *OSG_CHECK_ARG(action), 
                            UInt32          OSG_CHECK_ARG(index))
{
    FWARNING(("StateChunk::deactivate called!\n"));
}

#endif


#if 0
/*! Activate the chunk, i.e. set the OpenGl state covered by the chunk which is
    different from the default state to the given state.
 */

void StateChunk::activate(DrawEnv *, 
                          UInt32   )
{
    FWARNING(("StateChunk::activate called!\n"));
}

/*! Change from an old chunk of the same type to this chunk. Note that in
    general no type checking is done, make sure to use this on a legal 
    combination of chunks!
 */

void StateChunk::changeFrom(DrawEnv    *pEnv, 
                            StateChunk *pOld, 
                            UInt32      index)
{
    pOld->deactivate(pEnv, index);

    activate(pEnv, index);
}

/*! Deactivate the chunk, i.e. set the OpenGl state covered by the chunk
    which is
    different from the default state to the default state.
 */

void StateChunk::deactivate(DrawEnv *, 
                            UInt32   index)
{
    FWARNING(("StateChunk::deactivate called!\n"));
}
#endif

/*! Check if the chunk is transparent, i.e. needs to be rendered after the
    opaque objects.
 */

bool StateChunk::isTransparent(void) const
{
    return false;
}

/*---------------------- Chunk Class Access -------------------------------*/

const StateChunkClass *StateChunk::getClass(void) const
{
    return NULL;
}

/*-------------------------- Comparison -----------------------------------*/

/*! Calculate how expensive it is to switch from one instance of the chunk
    class to another. In most cases not implemented yet, will return 0.
 */

Real32 StateChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool StateChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

/*! Compare two chunks. In most cases not implemented yet, will return false.
 */

bool StateChunk::operator ==(const StateChunk &OSG_CHECK_ARG(other)) const
{
    return false;
}

bool StateChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}
