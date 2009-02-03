/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
UInt32 MultiCore::getNCores(void) const
{
    return _mfCores.size();
}

inline
Int32 MultiCore::findCore(NodeCore * const pCore) const
{
    return _mfCores.findIndex(pCore);
}

inline
void MultiCore::insertCore(UInt32           coreIdx, 
                           NodeCore * const coreP  )
{
    MultiCore *pMCore = dynamic_cast<MultiCore *>(coreP);

    if(pMCore != NULL)
    {
        FWARNING(("Can not insert multi-core into multi-core, ignored\n"));
        return;
    }

    editMField(CoresFieldMask, _mfCores);

    MFCoresType::iterator cIt = _mfCores.begin_nc();

    cIt += coreIdx;

    _mfCores.insert(cIt, coreP);
}

inline
const MFUnrecChildNodeCorePtr *MultiCore::getMFCores(void) const
{
    return Inherited::getMFCores();
}

inline
NodeCore *MultiCore::getCores(const UInt32 index) const
{
    return Inherited::getCores(index);
}

inline
void MultiCore::addCore(NodeCore * const value)
{
    MultiCore *pMCore = dynamic_cast<MultiCore *>(value);

    if(pMCore != NULL)
    {
        FWARNING(("Can not insert multi-core into multi-core, ignored\n"));
        return;
    }

    Inherited::addCore(value);
}

inline
void MultiCore::assignCoresFrom(const MFUnrecChildNodeCorePtr &value)
{
    MFUnrecChildNodeCorePtr::const_iterator vIt  = value.begin();
    MFUnrecChildNodeCorePtr::const_iterator vEnd = value.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        MultiCore *pMCore = dynamic_cast<MultiCore *>(*vIt);

        if(pMCore != NULL)
        {
            FWARNING(("Can not insert multi-core into multi-core, ignored\n"));
            return;
        }
    }
    
    Inherited::assignCoresFrom(value);
}

inline
void MultiCore::subCore(UInt32 uiIndex)
{
    Inherited::subCore(uiIndex);
}

inline
void MultiCore::subCoreByObj(NodeCore * const value)
{
    Inherited::subCoreByObj(value);
}

inline
void MultiCore::clearCores(void)
{
    Inherited::clearCores();
}


OSG_END_NAMESPACE
