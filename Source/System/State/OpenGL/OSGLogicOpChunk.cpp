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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGLogicOpChunk.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLogicOpChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGLogicOpChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

#ifndef OSG_OGL_ES2
StateChunkClass LogicOpChunk::_class("LogicOp", 1, 50);
#else
StateChunkClass LogicOpChunk::_class("LogicOp", 1, 110);
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LogicOpChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *LogicOpChunk::getClass(void) const
{
    return &_class;
}

/*--------------------------------- Sync ---------------------------------*/

void LogicOpChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------- Output --------------------------------*/

void LogicOpChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LogicOpChunk NI" << std::endl;
}

/*----------------------------- State Commands ---------------------------*/

void LogicOpChunk::activate(DrawEnv *pEnv, UInt32 index)
{
#ifndef OSG_OGL_ES2
    pEnv->incNumChunkChanges();

    if(_sfLogicOp.getValue() != GL_COPY)
    {
        glLogicOp(_sfLogicOp.getValue());
        glEnable (GL_COLOR_LOGIC_OP    );
    }
#endif
}

void LogicOpChunk::changeFrom(DrawEnv    *pEnv,
                              StateChunk *old,
                              UInt32      index  )
{
    old ->deactivate(pEnv, index);
    this->activate  (pEnv, index);
}

void LogicOpChunk::deactivate(DrawEnv *pEnv, UInt32 index)
{
#ifndef OSG_OGL_ES2
    if(_sfLogicOp.getValue() != GL_COPY)
    {
        glDisable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_COPY          );
    }
#endif
}

/*------------------------------- Comparison -----------------------------*/

Real32 LogicOpChunk::switchCost(StateChunk *chunk)
{
    return 0.f;
}

bool LogicOpChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool LogicOpChunk::operator == (const StateChunk &other) const
{
    LogicOpChunk const *tOther = dynamic_cast<LogicOpChunk const *>(&other);

    if(tOther == NULL)
        return false;

    if(tOther == this)
        return true;

    if(getLogicOp() != tOther->getLogicOp())
        return false;

    return true;
}

bool LogicOpChunk::operator != (const StateChunk &other) const
{
    return !(*this == other);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LogicOpChunk::LogicOpChunk(void) :
    Inherited()
{
}

LogicOpChunk::LogicOpChunk(const LogicOpChunk &source) :
    Inherited(source)
{
}

LogicOpChunk::~LogicOpChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE
